/*
 * src_ethernet.h
 *
 *  Created on: Apr 3, 2019
 *      Author: altra
 */

#ifndef SRC_ETHERNET_SRC_ETHERNET_H_
#define SRC_ETHERNET_SRC_ETHERNET_H_

//#include "benetton.h"
#include <stdint.h>
#include <stdbool.h>
#include "httpserver_raw/httpd.h"
#include "src_util/locator.h"
#include "src_util/lwiplib.h"

#define SYSTICK_INT_PRIORITY 0x80
#define ETHERNET_INT_PRIORITY 0xC0

//#define FAULT_SYSTICK 15 // System Tick
#define UDP_PORT 1824

struct udp_pcb *local_udp_client;
// struct pbuf *udp_package_ptr;

void init_ethernet(uint32_t sysClock);
void ethernet_convert_to_octet(uint32_t ui32Addr);
void ethernet_send_udp(struct pbuf *p);
static void ethernet_periodic_status();
static void ethernet_get_ip_addr();
err_t ethernet_init_tcp_server();
static err_t ethernet_tcp_connect_callback(void *arg, struct tcp_pcb *tpcb, err_t err);
static void ethernet_tcp_error_callback(void *arg, err_t err);
static err_t ethernet_tcp_receive_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static err_t ethernet_tcp_send_callback(void *arg, struct tcp_pcb *tpcb, uint16_t len);
#endif /* SRC_ETHERNET_SRC_ETHERNET_H_ */
