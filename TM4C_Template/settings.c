/*
 * settings.c
 *
 *  Created on: Apr 4, 2019
 *      Author: altra
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "settings.h"

struct ethernet_settings_t ethernet_settings;

void ethernet_info_setup(void) {
    ethernet_settings.local_ip_addr = 0xc0a80f19; // 192.168.15.25
    ethernet_settings.local_gateway = 0xc0a80f01; // 192.168.15.1

    // ethernet_settings.local_ip_addr = 0x0a01064e; // 10.1.6.78
    // ethernet_settings.local_gateway = 0x0a010601; // 10.1.6.1

    ethernet_settings.local_netmask = 0xffffff00; // 255.255.255.0

    // ethernet_settings.dest_ip_addr = 0xc0a80f03;    // 192.168.15.3
    ethernet_settings.dest_ip_addr = 0x0a5bb86f;    // 10.91.184.111
    
    ethernet_settings.dest_udp_port = 2283;
    ethernet_settings.dest_tcp_port = 1824;
}

