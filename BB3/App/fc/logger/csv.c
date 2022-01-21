//#define DEBUG_LEVEL	DEBUG_DBG
#include "csv.h"

#include "fc/fc.h"
#include "etc/epoch.h"
#include "etc/timezone.h"
#include "drivers/rev.h"
#include "drivers/rtc.h"

static osTimerId csv_timer;

#define CSV_PERIOD	240

FIL csv_log_file;
static bool csv_started = false;

void csv_write_line(char * line)
{
	uint8_t l = strlen(line);
	UINT wl;

	DBG("CSV:%s", line);

	ASSERT(f_write(&csv_log_file, line, l, &wl) == FR_OK);
	ASSERT(wl == l);
	ASSERT(f_sync(&csv_log_file) == FR_OK);
}

void csv_write_data()
{
	char line[100];

	uint32_t timestamp = (fc.gnss.fix == 0) ? fc_get_utc_time() : fc.gnss.utc_time;

	//timestamp,latitude,longtitude,ground_speed,heading,gnss_alt,baro_alt,vario,accel
	snprintf(line, sizeof(line), "%lu,%li,%li,%0.1f,%0.0f,%d,%d,%0.0f,%0.3f\r\n",
			timestamp,
			fc.gnss.latitude,
			fc.gnss.longtitude,
			fc.gnss.ground_speed,
			fc.gnss.heading,
			(fc.gnss.fix == 3 ? (int16_t) fc.gnss.altitude_above_ellipsiod : 0),
			(fc.fused.status == fc_dev_ready ? (int16_t) fc_press_to_alt(fc.fused.pressure, 101325) : 0),
			(fc.fused.status == fc_dev_ready ? fc.fused.vario * 100 : 0),
			(fc.imu.status == fc_dev_ready ? fc.imu.acc_total : 0)
			);
	csv_write_line(line);
}

void csv_start_write()
{
	char line[83];

	//create file
	char path[PATH_LEN];

	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t day;
	uint8_t wday;
	uint8_t month;
	uint16_t year;
	uint64_t utc_time = fc_get_utc_time();
	DBG("utc_time %lu", utc_time);
	datetime_from_epoch(utc_time, &sec, &min, &hour, &day, &wday, &month, &year);

	snprintf(path, sizeof(path), "%s/%02u.%04u", PATH_LOGS_DIR, month, year);
	f_mkdir(path);
	snprintf(path, sizeof(path), "%s/%02u.%04u/%02u.%02u.%04u %02u.%02u.csv", PATH_LOGS_DIR, month, year, day, month, year, hour, min);
	uint8_t res = f_open(&csv_log_file, path, FA_WRITE | FA_CREATE_ALWAYS);

	DBG("CSV OPEN %s, res = %u", path, res);
	ASSERT(res == FR_OK);
	if (res != FR_OK)
		return;

	sprintf(line, "timestamp,latitude,longtitude,ground_speed,heading,gnss_alt,baro_alt,vario,accel\r\n");
	csv_write_line(line);
}


void csv_tick_cb(void * arg)
{
	if (csv_started)
	{
		csv_write_data();
	}
	else {
		if (rtc_is_valid())
		{
			csv_start_write();
			fc.logger.csv = fc_logger_record;
			csv_started = true;
		}
	}
}

void csv_start()
{
	DBG("CSV timer start");
    osTimerStart(csv_timer, CSV_PERIOD);
    fc.logger.csv = fc_logger_wait;
}

void csv_init()
{
	csv_started = false;
	csv_timer = osTimerNew(csv_tick_cb, osTimerPeriodic, NULL, NULL);

	fc.logger.csv = fc_logger_off;
}

void csv_stop()
{
	osTimerStop(csv_timer);

	if (csv_started)
	{
		f_close(&csv_log_file);
		csv_started = false;
	}
	fc.logger.csv = fc_logger_off;
}
