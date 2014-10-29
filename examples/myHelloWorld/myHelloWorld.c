#include "contiki.h"
#include "dev/leds.h"
#include <stdio.h>

/*We declare the two processes*/
PROCESS(hello_world_process, "Hello World Process");
PROCESS(blink_process,"LED BLINK PROCESS");

/*We requiere the processes to be started automatically */

AUTOSTART_PROCESSES(&hello_world_process,&blink_process);

/*FIRST PROCESS*/

PROCESS_THREAD(hello_world_process,ev,data){
	
	static struct etimer timer;
	static int count = 0;

	PROCESS_BEGIN();

	etimer_set(&timer, CLOCK_CONF_SECOND);

	while(1){
	
		PROCESS_WAIT_EVENT();

		if(ev == PROCESS_EVENT_TIMER){
			printf("Hello World!! -> #%i\n",count);
			count++;
			etimer_reset(&timer);
		}
		
	}

	PROCESS_END();	
}

PROCESS_THREAD(blink_process, ev, data){
	static struct etimer timer;
	static uint8_t leds_state = 0;
	PROCESS_BEGIN();

	while(1){
		etimer_set(&timer, CLOCK_CONF_SECOND/4);
		
		PROCESS_WAIT_EVENT_UNTIL(ev == PROCESS_EVENT_TIMER);

		leds_off(0xff);
		leds_on(leds_state);
		leds_state += 1;	
	}
	
	PROCESS_END();
}
