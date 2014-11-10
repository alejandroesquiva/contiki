#include "contiki.h"
#include <stdio.h>
#include "contiki-lib.h"
#include "contiki-net.h"
#include "net/ip/uip.h"
#include "net/ipv6/uip-ds6.h"
#include "net/rpl/rpl.h"
#include "net/netstack.h"
#include "dev/slip.h"


#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiki.h"
#include "contiki-net.h"


#include <ctype.h>


static void
print_local_addresses(void)
{
  int i;
  uint8_t state;

  printf("Server IPv6 addresses:\n");
  for(i = 0; i < UIP_DS6_ADDR_NB; i++) {
    state = uip_ds6_if.addr_list[i].state;
    if(uip_ds6_if.addr_list[i].isused &&
       (state == ADDR_TENTATIVE || state == ADDR_PREFERRED)) {
      printf(" ");
      uip_debug_ipaddr_print(&uip_ds6_if.addr_list[i].ipaddr);
      printf("\n");
    }
  }
}

//Declare the process
PROCESS(send_sensor_info_process, "Print the Sensors Information");

//Make the process start when the module is loaded
AUTOSTART_PROCESSES(&send_sensor_info_process);


//Define the process code
PROCESS_THREAD(send_sensor_info_process, ev, data)
{
  PROCESS_BEGIN();
  print_local_addresses();

  PROCESS_END();
}
