#include "esp.h"

#include "drivers/esp/esp.h"
#include "drivers/esp/protocol.h"


void thread_esp_start(void *argument)
{
	INFO("Started");

	esp_init();

	start_thread(thread_esp_spi);

	uint32_t timer = HAL_GetTick();

	while(!system_power_off)
	{
	    esp_step();
	    taskYIELD();

	    if (HAL_GetTick() - timer > 1000)
	    {
//	        esp_send_ping();
//	        timer = HAL_GetTick();
	    }
	}

    INFO("Done");
    osThreadSuspend(thread_esp);
}