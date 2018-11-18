/*Copyright (c) 2015-2050, JD Smart All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License. */

/* --------------------------------------------------
 * @file: joylink_net.h
 *
 * @brief: 
 *
 * @version: 1.0
 *
 * --------------------------------------------------
 */

#ifndef __JOYLINK_NET__
#define __JOYLINK_NET__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#if defined(__QC_4010__) || defined(__OV_788__)
#else
#include <stdio.h>
#endif
#include <stdint.h>

#if defined(__MTK_7687__)
#include <stdint.h>
#include "lwip/sockets.h"
#elif defined(__REALTEK_8711__)
#include <stdint.h>
#include "lwip/sockets.h"
#elif defined(__MICOKIT_3166__)
#include "sockets.h"
#include <errno.h>
#elif defined(__MW300__)
#include <stdint.h>
#include "lwip/sockets.h"
#elif defined(__QC_4010__)
#include "basetypes.h"
#include "socket_api.h"
#elif defined(__ESP32__) 
#include <stdint.h>
#include "lwip/sockets.h"
#elif defined(__OV_788__) 
#include <stddef.h> //for size_t
#include "includes.h" 
#include "libpdk.h"
#else
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#ifndef __ANDROID__
#include <ifaddrs.h>
#endif
#include <netdb.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include "joylink_ret_code.h"

typedef enum {
    E_JL_IP_TYPE_V4 = 0, 
    E_JL_IP_TYPE_V6 = 1 
}E_JL_IP_TYPE;

typedef struct {
    union {
        char v4[16];
        char v6[64];
    };
    E_JL_IP_TYPE type;
    short port;
}jl_ip_info_t;

/**
 * [joylink_net_bind] 
 *
 * @param: [port]
 *
 * @returns: 
 */
int 
joylink_net_bind(short port);

/**
 * [joylink_net_udp_recvfrom] 
 *
 * @param: [fd]
 * @param: [len]
 * @param: [from_addr]
 *
 * @returns: 
 */
char * 
joylink_net_udp_recvfrom(int fd, int *len, struct sockaddr_in *from_addr);

/**
 * [joylink_net_udp_release] 
 */
void 
joylink_net_udp_release();

/**
 * [joylink_net_udp_sendto] 
 *
 * @param: [sock]
 * @param: [buf]
 * @param: [len]
 * @param: [dest]
 * @param: [pReply_data]
 * @param: [pReply_len]
 *
 * @returns: 
 */
int 
joylink_net_udp_sendto(int sock, char *buf, int len,
                        struct sockaddr_in *dest, int select_usecs,
                        char **pReply_data, int *pReply_len);

/**
 * [joylink_net_udp_reply] 
 *
 * @param: [sock]
 * @param: [buf]
 * @param: [len]
 * @param: [dest]
 *
 * @returns: 
 */
int 
joylink_net_udp_reply(int sock, char *buf, int len, struct sockaddr_in *dest);

/**
 * [joylink_net_udp_connect] 
 *
 * @param: [sock]
 * @param: [dest]
 *
 * @returns: 
 */
int 
joylink_net_udp_connect(int sock, struct sockaddr_in *dest);

/**
 * [joylink_net_http_activate] 
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_net_http_activate(const char *app_id,
                          const char *secret,
                          const char *device_id,
                          const char *active_url);

/**
* [joylink_adapter_inet_ntoa] 
*
* @param: [in_a]
*
* @returns: 
*/
char *  
joylink_adapter_inet_ntoa(struct in_addr in_a);

/**
* [joylink_adapter_inet_addr] 
*
* @param: [cp]
*
* @returns: 
*/
unsigned long
joylink_adapter_inet_addr(const char *cp);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
