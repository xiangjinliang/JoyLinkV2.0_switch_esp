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

#ifndef _JOYLINK_UTILS_H
#define _JOYLINK_UTILS_H

#ifdef __LINUX_UB2__ 
#include <stdint.h>
#endif

#if defined(__MTK_7687__)
#include <stdint.h>
#include "lwip/sockets.h"
#elif defined(__REALTEK_8711__)
#include <stdint.h>
#include "platform_stdlib.h"
#include "lwip/sockets.h"
#elif defined(__MICOKIT_3166__)
#include "sockets.h"
#elif defined(__MW300__)
#include "sockets.h"
#include "lwip/sockets.h"
#include <stdint.h>
#elif defined(__QC_4010__)
#include "stdint.h"
//#include "timetype.h"
#include "basetypes.h"
#include "socket_api.h"
#elif defined(__OV_788__) 
#include <stdint.h>
#include <stddef.h> //for size_t
#include "includes.h" 
#include "libpdk.h"
#elif defined(__ESP32__)
#include <stdint.h>
#include "lwip/sockets.h"
#else
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>
#endif
#include "joylink_ret_code.h"

#if defined(__QC_4010__)
typedef unsigned long long uint64_t;
typedef long long int64_t;
#endif

#define JL_MIN(a , b) 				((a > b) ? b : a)
#define JL_MAX(a , b)				((a > b) ? a : b)

/**
 * [joylink_util_get_data_mem]
 *
 * @returns:
 */
double
joylink_util_get_data_mem();

#define DEBUG_MEM_DETAIL(msg) \
    do{\
        printf("\033[0;31m[FATAL][%s][%s][%d]\n", __FILE__, __FUNCTION__, __LINE__);\
        printf("%s", msg);\
        joylink_util_get_data_mem();\
        printf("\033[0m"); \
    }while(0)

/**
 * [joylink_util_ret_msg_get] 
 *
 * @param: [ret_code]
 *
 * @returns: 
 */
char*
joylink_util_ret_msg_get(int32_t ret_code);

/**
 * [joylink_util_cut_ip_port] 
 *
 * @param: [ipport]
 * @param: [out_ip]
 * @param: [out_port]
 *
 * @returns: 
 */
int 
joylink_util_cut_ip_port(const char *ipport, char *out_ip, int *out_port);

/**
 * [joylink_util_byte2hexstr] 
 *
 * @param: [pBytes]
 * @param: [srcLen]
 * @param: [pDstStr]
 * @param: [dstLen]
 *
 * @returns: 
 */
int 
joylink_util_byte2hexstr(const uint8_t *pBytes, int srcLen, 
        uint8_t *pDstStr, int dstLen);

/**
 * [joylink_util_hexStr2bytes] 
 *
 * @param: [phex]
 * @param: [len]
 * @param: [o_buf]
 * @param: [buf_len]
 *
 * @returns: 
 */
int32_t 
joylink_util_hexStr2bytes(const char *phex, int32_t len, uint8_t *o_buf, int buf_len);

/**
 * [joylink_util_get_ipstr] 
 *
 * @param: [pPeerAddr]
 * @param: [str]
 *
 * @returns: 
 */
int 
joylink_util_get_ipstr(struct sockaddr_in* pPeerAddr, char* str);

/**
 * [joylink_util_timer_reset] 
 *
 * @param: [timestamp]
 */
void 
joylink_util_timer_reset(uint32_t *timestamp);

/**
 * [joylink_util_is_time_out] 
 *
 * @param: [timestamp]
 * @param: [timeout]
 *
 * @returns: 
 */
int 
joylink_util_is_time_out(uint32_t timestamp, uint32_t timeout);

/**
 * [joylink_util_strcat] 
 *
 * @param: [dst]
 * @param: [src]
 *
 * @returns: 
 */
char *
joylink_util_strcat(char *dst, const char *src);

int joylink_util_get_randoms(uint8_t *o_dest, uint8_t size);
/**
 * [joylink_util_make_guid] 
 *
 * 
 * @returns: 
 */
uint16_t 
joylink_util_get_random();

/**
 * [joylink_util_get_str_random]
 * NOTE:must joylink_util_free memory
 * @return [str, if error occurs, return NULL]
 */
char *joylink_util_get_str_random();

/**
 * [joylink_util_make_guid] 
 *
 * @param: [guid_str]
 * @param: [max_len]
 *
 * @returns: 
 */
int 
joylink_util_make_guid(uint8_t *guid_str, uint8_t max_len);

/**
 * [joylink_util_addr_cmp] 
 *
 * @param: [jyl_addr]
 * @param: [std_addr]
 *
 * @returns: 
 */
int 
joylink_util_addr_cmp(void *jyl_addr, void *std_addr);

/**
 * [joylink_util_read_file_by_line_and_trim] 
 *
 * @param: [filename]
 * @param: [out_len]
 *
 * @returns: 
 */
char *
joylink_util_read_file_by_line_and_trim(const char *filename, int *out_len);

char *
joylink_str_trim(const char *str);

E_JL_RETCODE joylink_util_get_host_ip(int fd, char *ipv4);

E_JL_RETCODE joylink_util_get_host_ip_by_create_fd(char *ipv4);

#if defined(__MTK_7687__) || defined(__QC_4010__) || defined(__REALTEK_8711__) || defined(__OV_788__) || defined(__ESP32__)
void joylink_util_set_host_ip(const uint8_t *addr);
char * mtk_strdup(const char *s);
#endif

/**
 * [joylink_util_print_buffer] 
 *
 * @param: [msg]
 * @param: [is_fmt]
 * @param: [num_line]
 * @param: [buff]
 * @param: [len]
 */
void
joylink_util_print_buffer(const char *msg, int is_fmt, 
        int num_line, const char *buff, int len);

char *
joylink_util_str_skip_num(char *str);

uint8_t
joylink_util_get_bit1_count(uint64_t value);

#define JL_UTILS_P_FMT        (1)
#define JL_UTILS_P_NO_FMT     (0)

#define joylink_util_fmt_p(msg, buff, len) joylink_util_print_buffer(msg, JL_UTILS_P_FMT, 16, buff, len) 

/**
 * [joylink_util_make_guid_with_ip] 
 *
 * @param: [o_guid]
 * @param: [ip]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_util_make_guid_with_str(char *o_guid, char *str);

typedef struct jl_map_node {
    unsigned hash;
    void *value;
    struct jl_map_node *next;
} jl_map_node_t;

typedef struct {
    jl_map_node_t **buckets;
    unsigned nbuckets;
    unsigned nnodes;
} jl_map_base_t;

typedef struct {
    unsigned bucketidx;
    jl_map_node_t *node;
} jl_map_iter_t;

#define joylink_map_t(T) struct { jl_map_base_t base; T *ref; T tmp; }

#define joylink_map_init(m) memset(m, 0, sizeof(*(m)))

#define joylink_map_deinit(m) joylink_map_deinit_(&(m)->base)

#define joylink_map_find(m, key) ( (m)->ref = joylink_map_find_(&((m)->base), key) )

#define joylink_map_insert(m, key, value)\
    ( (m)->tmp = (value), \
      joylink_map_insert_(&(m)->base, key, &(m)->tmp, sizeof((m)->tmp)) )

#define joylink_map_remove(m, key) joylink_map_remove_(&(m)->base, key)

#define joylink_map_iter(m) joylink_map_iter_()

#define joylink_map_next(m, iter) joylink_map_next_(&(m)->base, iter)

typedef joylink_map_t(void*)    jl_map_void_t;

typedef joylink_map_t(char*)    jl_map_str_t;

typedef joylink_map_t(int)      jl_map_int_t;

typedef joylink_map_t(char)     jl_map_char_t;

typedef joylink_map_t(float)    jl_map_float_t;

typedef joylink_map_t(double)   jl_map_double_t;

void joylink_map_deinit_(jl_map_base_t *m);

void *joylink_map_find_(jl_map_base_t *m, const char *key);

int joylink_map_insert_(jl_map_base_t *m, const char *key, void *value, int vsize);

void joylink_map_remove_(jl_map_base_t *m, const char *key);

jl_map_iter_t *joylink_map_iter_(void);

const char *joylink_map_next_(jl_map_base_t *m, jl_map_iter_t *iter);
/**
 * [joylink_util_set_net_intf_name] 
 *
 * @param: [eth_name]
 *
 * @returns: 
 */
int32_t
joylink_util_set_net_intf_name(const char *eth_name);

void 
joylink_util_bzero(void *s, size_t n);

void *
joylink_util_malloc(size_t size);

void 
joylink_util_freep(void **p);

void 
joylink_util_free(void *p);

void *
joylink_util_realloc(void *ptr, size_t size);

int 
joylink_util_gettimeofday(struct timeval *tv, void *data);

/**
 * [joylink_util_get_joylink_version]
 * @param  version []
 * @return         []
 */
E_JL_RETCODE 
joylink_util_get_joylink_version(char *version);

/**
 * [joylink_util_get_vermber] 
 *
 * @param: [major]
 * @param: [minor]
 * @param: [tail]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_util_get_vermber(char *major, char *minor, char *tail);

#if defined(__OV_788__) 
extern loop_schedule_data_t *ov_pdata;
void joylink_set_ov_data(void *);
#endif /*ov788*/

unsigned long joylink_util_get_file_size(const char *path); 

/**
 * [joylink_utils_system_is_big_endian]
 * @param
 * @param
 * @return
 */
E_JL_BOOL 
joylink_utils_system_is_big_endian(void);

/**
 * [joylink_utils_sleep]
 * @param  [seconds]
 * sleep serval seconds
 */
void joylink_utils_sleep(int32_t seconds);

#endif /* utils.h */
