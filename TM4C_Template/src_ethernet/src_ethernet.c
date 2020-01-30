/*
 * src_ethernet.c
 *
 *  Created on: Apr 3, 2019
 *      Author: altra
 */

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"

#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/emac.h"
#include "driverlib/flash.h"

#include "src_util/uartstdio.h"
#include "src_mk_led/mk_led_control.h"
#include "src_ethernet.h"

#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/opt.h>

#include "settings.h"

extern volatile uint8_t ip_ready;
volatile uint32_t g_ui32IPAddress;
struct ethernet_settings_t ethernet_settings;
static struct tcp_pcb *daq_pcb;

enum echo_states
{
    ES_NONE = 0,
    ES_ACCEPTED,
    ES_RECEIVED,
    ES_CLOSING
};

struct echo_state
{
    u8_t state;
    u8_t retries;
    struct tcp_pcb *pcb;
    /* pbuf (chain) to recycle */
    struct pbuf *p;
};

enum ethernet_connection_state
{
    NONE = 0,
    CONNECTED,
    SENDING,
    RECEIVING,
    ERROR
};

struct eth_state_t
{
    uint8_t state;
    uint8_t entries;
    struct tcp_pcb *pcb;
    struct pbuf *p;
};

void init_ethernet(uint32_t sysClock)
{
    // Reference https://tinyurl.com/y5owhgjx

    uint32_t ui32User0, ui32User1;
    uint8_t mac_address[8];

    UARTprintf("Ethernet Initializing...\n");

    MAP_FlashUserGet(&ui32User0, &ui32User1);
    if ((ui32User0 == 0xffffffff) || (ui32User1 == 0xffffffff))
    {
        UARTprintf("No MAC programmed!\n");
        while (1)
            ;
    }

    mac_address[0] = ((ui32User0 >> 0) & 0xff);
    mac_address[1] = ((ui32User0 >> 8) & 0xff);
    mac_address[2] = ((ui32User0 >> 16) & 0xff);
    mac_address[3] = ((ui32User1 >> 0) & 0xff);
    mac_address[4] = ((ui32User1 >> 8) & 0xff);
    mac_address[5] = ((ui32User1 >> 16) & 0xff);

    UARTprintf("MAC: %X:%X:%X:%X:%X:%X\n", mac_address[0], mac_address[1], mac_address[2], mac_address[3], mac_address[4], mac_address[5]);

    lwIPInit(sysClock,
             mac_address,
             ethernet_settings.local_ip_addr,
             ethernet_settings.local_netmask,
             ethernet_settings.local_gateway,
             IPADDR_USE_DHCP);

    LocatorInit();
    LocatorMACAddrSet(mac_address);
    LocatorAppTitleSet("Wonderful DAQ");

    /* Init TCP Server */
    {
        udp_init();
        local_udp_client = udp_new();

        if (local_udp_client == NULL)
        {
            UARTprintf("UDP Server Open Failed.\n");
        }
        else
        {
            UARTprintf("UDP Server Up.\n");
        }

        if (udp_bind(local_udp_client, IP_ADDR_ANY, UDP_PORT) != ERR_OK)
        {
            UARTprintf("UDP Bind Failed.\n");
        }
    }

    /* Initialize TCP Server */
    ethernet_init_tcp_server();

    // Initialize a sample httpd server.
    httpd_init();

    IntPrioritySet(INT_EMAC0, ETHERNET_INT_PRIORITY);
    IntPrioritySet(FAULT_SYSTICK, SYSTICK_INT_PRIORITY);
}

void ethernet_send_udp(struct pbuf *p)
{
    struct ip_addr ctrl;
    ctrl.addr = htonl(ethernet_settings.dest_ip_addr);

    set_board_led(BOARD_LED_1, LED_ON);

    udp_sendto(local_udp_client, p, &ctrl, ethernet_settings.dest_udp_port);

    set_board_led(BOARD_LED_1, LED_OFF);
}

void lwIPHostTimerHandler(void)
{
    // ethernet_periodic_status();
    ethernet_get_ip_addr();
}

static void ethernet_periodic_status()
{
    const uint32_t interval = 100;
    static uint32_t counter = 0;
    counter++;
    if (counter > interval)
    {
        counter = 0;
        uint32_t ip = lwIPLocalIPAddrGet();

        UARTprintf("IP=%d.%d.%d.%d RX=%d TX=%d DROP=%d\n",
                   (ip >> 0) & 0xff, (ip >> 8) & 0xff, (ip >> 16) & 0xff, (ip >> 24) & 0xff,
                   lwip_stats.link.recv, lwip_stats.link.xmit, lwip_stats.link.drop);
    }
}

static void ethernet_get_ip_addr()
{
    uint32_t new_ip_address;
    new_ip_address = lwIPLocalIPAddrGet();

    if (new_ip_address != g_ui32IPAddress)
    {
        if (new_ip_address == 0xffffffff)
        {
            UARTprintf("Waiting for link.\n");
        }
        else if (new_ip_address == 0)
        {
            UARTprintf("Waiting for IP address.\n");
        }
        else
        {
            UARTprintf("IP Address: ");
            ethernet_convert_to_octet(new_ip_address);
            UARTprintf("\n");
            UARTprintf("Open a browser and enter the IP address.\n");
            ip_ready = 1;
        }

        g_ui32IPAddress = new_ip_address;
    }

    if ((new_ip_address == 0) || (new_ip_address == 0xffffffff))
    {
    }
}

void ethernet_convert_to_octet(uint32_t ui32Addr)
{
    char pcBuf[16];
    sprintf(pcBuf, "%d.%d.%d.%d", ui32Addr & 0xff, (ui32Addr >> 8) & 0xff,
            (ui32Addr >> 16) & 0xff, (ui32Addr >> 24) & 0xff);
    UARTprintf(pcBuf);
}

err_t ethernet_init_tcp_server()
{
    daq_pcb = tcp_new();

    if (daq_pcb != NULL)
    {
        err_t err;

        err = tcp_bind(daq_pcb, IP_ADDR_ANY, ethernet_settings.dest_tcp_port);
        if (err == ERR_OK)
        {
            UARTprintf("TCP Bind Successs\n");
            daq_pcb = tcp_listen(daq_pcb);
            tcp_accept(daq_pcb, ethernet_tcp_connect_callback);
        }
        else
        {
            UARTprintf("TCP Bind Failure %d\n", err);
        }
    }
}

err_t ethernet_tcp_connect_callback(void *arg, struct tcp_pcb *newpcb, err_t err)
{

    err_t ret_err;
    struct echo_state *es;
    LWIP_UNUSED_ARG(arg);

    /* Commonly observed practice to call tcp_setprio() */
    tcp_setprio(newpcb, TCP_PRIO_MIN);

    es = (struct echo_state *)mem_malloc(sizeof(struct echo_state));

    if (es != NULL)
    {
        UARTprintf("Connection Request Accepted\r\n");
        es->state = ES_ACCEPTED;
        es->pcb = newpcb;
        es->retries = 0;
        es->p = NULL;

        /* Pass newly allocated es to our callbacks */
        tcp_arg(newpcb, es);
        tcp_recv(newpcb, ethernet_tcp_receive_callback);
        tcp_err(newpcb, ethernet_tcp_error_callback);
        // tcp_poll(newpcb, ethernet_tcp_poll_callback);
        ret_err = ERR_OK;
    }
    else
    {
        UARTprintf("Connection Request Rejected");
        ret_err = ERR_MEM;
    }

    return ret_err;
}

void ethernet_tcp_error_callback(void *arg, err_t err)
{
    struct eth_state_t *eth_state;

    UARTprintf("Connection Error %d\r\n", err);
    LWIP_UNUSED_ARG(err);

    eth_state = (struct eth_state_t *)arg;
    if (eth_state != NULL)
    {
        mem_free(eth_state);
    }
}

err_t ethernet_tcp_receive_callback(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    UARTprintf("[TCP] YO I got something\r\n");
    struct echo_state *es;
    err_t ret_err;

}

err_t ethernet_tcp_send_callback(void *arg, struct tcp_pcb *tpcb, uint16_t len)
{
}
