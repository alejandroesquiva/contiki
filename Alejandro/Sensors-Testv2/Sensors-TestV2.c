#include "contiki.h"
#include "dev/sht11/sht11-sensor.h"
#include "dev/light-sensor.h"
#include "dev/leds.h"
#include <stdio.h>

//Declare the process
PROCESS(send_sensor_info_process, "Print the Sensors Information");

//Make the process start when the module is loaded
AUTOSTART_PROCESSES(&send_sensor_info_process);

/*---------------------------------------------------------------------------*/
static int
get_light(void)
{
  return 10 * light_sensor.value(LIGHT_SENSOR_PHOTOSYNTHETIC) / 7;
}
/*---------------------------------------------------------------------------*/
static int
get_temp(void)
{
  return ((sht11_sensor.value(SHT11_SENSOR_TEMP) / 10) - 396) / 10;
}
/*---------------------------------------------------------------------------*/

//Define the process code
PROCESS_THREAD(send_sensor_info_process, ev, data)
{

	static struct etimer timer;
	static int count = 0;

	PROCESS_BEGIN();

	etimer_set(&timer, CLOCK_CONF_SECOND);
	
	SENSORS_ACTIVATE(light_sensor);
	SENSORS_ACTIVATE(sht11_sensor);
	
	while(1){
	
		PROCESS_WAIT_EVENT();

		if(ev == PROCESS_EVENT_TIMER){
			printf("Hello World!! -> #%i\n",count);
			printf("Light: %d \n", get_light());
			printf("Temperature: %d \n\n", get_temp());
			count++;
			etimer_reset(&timer);
		}
		
	}

	PROCESS_END();	

}
