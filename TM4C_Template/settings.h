/*
 * settings.h
 *
 *  Created on: Apr 4, 2019
 *      Author: altra
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <stdint.h>
#include <stdbool.h>

struct ethernet_settings_t
{
    uint32_t debug_flags; // DBGF_*
    
    uint32_t local_ip_addr;
    uint32_t local_netmask;
    uint32_t local_gateway;

    uint32_t dest_ip_addr;
    uint32_t dest_udp_port;
    uint32_t dest_tcp_port;
};

extern struct ethernet_settings_t ethernet_settings;

void ethernet_info_setup(void);

#endif /* SETTINGS_H_ */
