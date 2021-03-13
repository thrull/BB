/*
 * pwr_mng.c
 *
 *  Created on: Oct 13, 2020
 *      Author: John
 */
#include <drivers/power/opt3004.h>
#include "pwr_mng.h"

#include "max17260.h"
#include "bq25895.h"

power_mng_t pwr;

void pwr_init()
{
    bq25895_init();
	max17260_init();
	opt3004_init();

    pwr_step();
}

void pwr_step()
{
	if (HAL_GPIO_ReadPin(USB_VBUS) == HIGH)
	{
	    if (pwr.data_port == PWR_DATA_NONE)
	    {
	        pwr.data_port = PWR_DATA_CHARGE;

	        //power up the negotiator
	        GpioWrite(BQ_OTG, HIGH);
	        HAL_Delay(40);
	        GpioWrite(BQ_OTG, LOW);
	    }
	}
	else
	{
		pwr.data_port = PWR_DATA_NONE;
	}

	bq25895_step();
	max17260_step();
	opt3004_step();


//	DBG("PWR Current: %u", pwr.bat_current);
//	DBG("PWR charge: %u", pwr.bat_charge);
//	DBG("PWR Time to Full: %u", pwr.bat_time_to_full);
//	DBG("Batt Cap: %u", pwr.bat_cap);
}
