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

#ifndef _JOYLINK_H_
#define _JOYLINK_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "joylink_auth.h"
#include "joylink_net.h"
#include "joylink_list.h"

#define _VERSION_  "3.0.14"
#define _GIT_HEAD_  ""

//---------------------  SERVICE SERVER PORT ----------------------
/**
 *NOTE:
 *JL_SERVICE_SERVER_PORT Must consistent with port in service json txt
 *like port:30000 with JL_SERVICE_SERVER_PORT:
    {
    "services":[
        {
            "name":"com.joylink.light",
            "port":30000,
            "transType":2,
            "isMultipoint":1,
            "funcs":[
            ],
        }
        ]
    }
 */
//-----------------------------------------------------------------

#define JL_SERVICE_SERVER_PORT                      (30000)
#define JL_BASIC_SERVER_PORT                        (30001)
#define JL_BROADCAST_PORT                           (30002)
#define JL_MDNS_SERVER_PORT                         (30003)
#define JL_PAIR_BROADCAST_PORT                      (30010)
#define JL_NET_LOG_SERVER_PORT                      (30011)

#define JL_CLOUD_GUID               "00000000000000000000000000000000" 

//TCP_SERVER_PORT only for test
#define JL_BASIC_TCP_SERVER_PORT                    JL_BASIC_SERVER_PORT 
#define JL_BASIC_RUDP_SERVER_PORT                   (30004)

#define JL_BASIC_SERVER_TRAN_TYPE   (E_JL_TRANS_TYPE_RUDP)


#define JL_CLOUD_CON_ST_ERROR          (-1)
#define JL_CLOUD_CON_ST_INIT           (0)
#define JL_CLOUD_CON_ST_AUTH           (1)
#define JL_CLOUD_CON_ST_SDK_ACTIVE     (2)
#define JL_CLOUD_CON_ST_WORK           (3)
#define JL_CLOUD_CON_ST_VLD            (4)

#define JL_MAX_LEN_GUID			    (33)
#define JL_MAX_NUM_SERVICE          (10)
#define JL_MAX_NUM_GUID			    (64)
#define JL_MAX_LEN_APP_ID           (33)
#define JL_MAX_LEN_PUID			    (7)
#define JL_MAX_LEN_NAME             (128)
#define JL_MAX_LEN_MODE_CODE        (128)
#define JL_MAX_LEN_URL              (128)
#define JL_MAX_LEN_SIG              (64)
#define JL_MAX_LEN_VERSION          (33)
#define JL_MAX_LEN_LANGUAGE         (33)
#define JL_MAX_LEN_MANUFACTURER     (16)
#define JL_MAX_LEN_PLATFORM         (16)
#define JL_MAX_LEN_MODEL            (16)
#define JL_MAX_LEN_IFTTT_ELEM       (9)
#define JL_MAX_LEN_IFTTT_SCRIPT     (33)

#define JL_MAX_LEN_MSG				(256)
#define JL_MAX_LEN_DEVICE_ID        (32)
#define JL_MAX_LEN_APP_ID           (33)
#define JL_MAX_LEN_SECRET           (33)
#define JL_MAX_LEN_PATH           	(256)
#define JL_MAX_SV_PER_APP           (10)
#define JL_MAX_LEN_DATE             (11)
#define JL_MAX_LEN_ETH              (8)
#define JL_MAX_LEN_PRO              (7)

#if defined (__IOS__) || defined (__ANDROID__)
#define JL_MAX_BUF_SIZE				(10*1024)
#else
#define JL_MAX_BUF_SIZE				(4*1024)
#endif

#define JOYLINK_JAPP_INFO_MAX_LEN       (512)
#define JOYLINK_DEVICE_INFO_MAX_LEN     (512)

#define JL_MAX_TTL                      (0x7FFFFFFF)
#define JL_SV_DEFAULT_TTL               (600)

#define JL_ALL_GUID                 "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"
#define JL_REMOTE_IP                "joylink_remote" 

//------ service info ------
#define JL_ALL_SERVICE                "com.joylink.all"
#define JL_ABOUT_SERVICE              "com.joylink.about"
#define JL_SESSION_SERVICE            "com.joylink.session"
#define JL_CONF_SERVICE               "com.joylink.config"
#define JL_OTA_UPDATE_CLIENT_SERVICE  "com.joylink.update.client"
#define JL_OTA_UPDATE_SERVER_SERVICE  "com.joylink.update.server"
#define JL_IFTTT_SERVICE              "com.joylink.agent.ifttt"
#define JL_CLOUD_GATEWAY_SERVICE      "com.joylink.cloud.gateway"
#define JL_THUNDERCONFIG_SERVICE      "com.joylink.agent.thunderConfig"
#define JL_SV_SEN_MAGNETIC            "com.joylink.sensor.magnetic_switch"
#define JL_SV_BLE_SMARTLOCK 		  "com.joylink.smartlock"

#define DEFAULT_SEVICE_CONF_SESSION_ID               (9)
#define DEFAULT_SEVICE_SESSION_SESSION_ID            (10)
#define DEFAULT_SEVICE_ABOUT_SESSION_ID              (11)
#define DEFAULT_SERVICE_CLOUD_GATEWAY_SESSION_ID     (12)

//------ only for test ------
#define JL_LIGHT_SERVICE                            "com.joylink.light" 
#define JL_IFTTT_SERVER_PORT                        (10000)
#define JL_TEST_SERVER_PORT                         (20000)

#ifdef __ANDROID__
#define JL_UNIX_DOMAIN_PATH							"/mnt/sdcard/.unix.domain"
#else
#define JL_UNIX_DOMAIN_PATH							"/tmp/unix.domain"
#endif

#if defined(__MW300__) || defined(__QC_4010__) || defined(__MICOKIT_3166__) || defined(__REALTEK_8711__)
#define JL_ASSERT(exp) 
#else
#define JL_ASSERT(exp) assert(exp)
#endif

#pragma pack(1)
typedef struct {
    uint32_t    magic;             //0x4A594C4B  JYLK
    uint16_t    version;
    uint32_t    serial;
    char        sender[16];
    char        dest[16];
    uint16_t    desc_len;
    uint16_t    desc_encrypt_type;
    uint16_t    len;
    uint16_t    crc;
}jl_header_t;
#pragma pack()

typedef struct {
    int32_t session_id;
    uint32_t timestamp;
    char type;
    char no_reply;
    char ttl;

    char sender[JL_MAX_LEN_GUID];
    char dest[JL_MAX_LEN_GUID];

    char service[JL_MAX_LEN_NAME];
    char member[JL_MAX_LEN_NAME];

    uint16_t encrypt_type;
    int32_t len;
    char signature[JL_MAX_LEN_SIG];
    //uint16_t    crc;
}jl_msg_desc_t;

typedef struct {
    jl_header_t head;
    jl_msg_desc_t desc;
    char *msg_body;
}jl_msg_t;

typedef struct {
    char signature[64];
    uint32_t len;
    char *msg_body;
}jl_marshal_data_t;

typedef enum {
    E_JL_ADDR_TYPE_NULL        = 0x00,
    E_JL_ADDR_TYPE_STD         = 0x01,
    E_JL_ADDR_TYPE_JYL         = 0x02
} E_JL_ADDR_TYPE;

typedef enum {
    E_JL_TRANS_TYPE_NULL       = 0x00,
    E_JL_TRANS_TYPE_UDP        = 0x01,
    E_JL_TRANS_TYPE_RUDP       = 0x02,
    E_JL_TRANS_TYPE_TCP        = 0x03,
    E_JL_TRANS_TYPE_UDS        = 0x04,             //UNIX Domain Socket
    E_JL_TRANS_TYPE_UART       = 0x05
}E_JL_TRANS_TYPE;

typedef enum {
    E_JL_MSG_TYPE_INVALID      = 0x00,
    E_JL_MSG_TYPE_FUN_CALL     = 0x01,
    E_JL_MSG_TYPE_FUN_RET      = 0x02,
    E_JL_MSG_TYPE_ERROR        = 0x03,
    E_JL_MSG_TYPE_SIGNAL       = 0x04
}E_JL_MSG_TYPE;

typedef enum {
    E_JL_MSG_TRANSFER_TYPE_MULTI      = 0x10,
	E_JL_MSG_TRANSFER_TYPE_SINGLE     = 0x20,
	E_JL_MSG_TRANSFER_TYPE_RSV        = 0x30
}E_JL_MSG_TRANSFER_TYPE;

typedef enum {
	E_JL_ENCTYPE_NOTHING        = 0x00,
	E_JL_ENCTYPE_PSKAES         = 0x01,
	E_JL_ENCTYPE_ECDH           = 0x02,
	E_JL_ENCTYPE_ACCESSKEY_AES  = 0x03,
	E_JL_ENCTYPE_SESSIONKEY_AES = 0x04
}E_JL_ENCTYPE;

typedef enum ss_{
    E_JL_REV_ST_MAGIC           = 0x01,
    E_JL_REV_ST_HEAD            = 0x02,
    E_JL_REV_ST_MSG_DESC        = 0x03,
    E_JL_REV_ST_MSG_BODY        = 0x04,
    E_JL_REV_ST_END             = 0x05,
    E_JL_REV_ST_ERROR           = 0x06
}E_JL_REV_ST;

typedef enum dev_st_{
    E_JL_DEV_ST_CONNECTING      = 0x01,
    E_JL_DEV_ST_WORK            = 0x02,
    E_JL_DEV_ST_TIME_OUT        = 0x03,
    E_JL_DEV_ST_RESET           = 0x04,
    E_JL_DEV_ST_DISCON          = 0x05,
    E_JL_DEV_ST_ERROR           = 0x06,
    E_JL_DEV_ST_LAN_CONNECTING  = 0x07,
    E_JL_DEV_ST_CLOUD_CONNECTING= 0x08,
    E_JL_DEV_ST_INIT            = 0x09
}E_JL_DEV_ST;

typedef enum _src_type{
    E_JL_SRC_TYPE_LAN           = 0x00,
    E_JL_SRC_TYPE_CLOUD         = 0x01,
    E_JL_SRC_TYPE_ALL           = 0x02
}E_JL_SRC_TYPE;

typedef enum status{
    E_JL_SERVICE_STATUS_OFFLINE  = 0x00,
    E_JL_SERVICE_STATUS_ONLINE   = 0x01
}E_JL_SERVICE_STATUS;

typedef struct{
    int32_t is_multipoint;
    char trans_type;
    short port;
    int ttl;
}jl_session_option_t;

typedef struct {
    char name[JL_MAX_LEN_NAME];
    char guid[JL_MAX_LEN_GUID];
    jl_session_option_t opt;
    jl_ip_info_t addr;
    int32_t src_type;
    char version[JL_MAX_LEN_VERSION];
}jl_sd_rsp_t;

typedef struct{
    int32_t fd;
    int32_t trans_type;
    jl_ip_info_t addr;
}jl_trans_info_t;

typedef struct{
    char name[JL_MAX_LEN_NAME]; 		//FIXME zhongxuan may be deleted
	jl_list_head_t	list;			    //jl_rpc_handler_t
}jl_service_t;

typedef struct{
    jl_ip_info_t addr;
    char guid[JL_MAX_LEN_GUID];
}jl_trans_opt_t;

typedef struct{
    char GUID[JL_MAX_LEN_GUID];
    int32_t HB;
    char locker_guid[JL_MAX_LEN_GUID];
    char sharekey[JL_AUTH_LEN_KEY_SHARE];
    char localkey[JL_AUTH_LEN_KEY_LOCAL];
    E_JL_BOOL is_locked;
    jl_trans_info_t trans;
    E_JL_BOOL is_remote;
}jl_app_node_t;

typedef jl_app_node_t jl_consumer_t;
typedef jl_app_node_t jl_producer_t;

typedef enum {
    E_JL_SERVER_LABEL_NULL          	= 0x00,
    E_JL_SERVER_LABEL_BASIC         	= 0x01,
    E_JL_SERVER_LABEL_ADVANCED      	= 0x02,
    E_JL_SERVER_LABEL_EXTERN       	 	= 0x04,
    E_JL_SERVER_LABEL_MDNS         	 	= 0x08,
    E_JL_SERVER_LABEL_LOCAL_CHANNEL		= 0x10,
    E_JL_SERVER_LABEL_BROADCAST     	= 0x20,
    E_JL_SERVER_LABEL_PAIR              = 0x40
}E_JL_SERVER_LABEL;

typedef struct{
    int32_t fd;
    short port;
    char url[64];
    char tran_type; 
    char label;

    jl_msg_t msg;
    struct sockaddr_in from_addr;
    uint32_t addr_len;
    jl_list_head_t session_list;  
}jl_server_t;

typedef struct _key_cache{	
    char guid[JL_MAX_LEN_GUID];
	char share_key[JL_AUTH_LEN_KEY_SHARE];	
	char local_key[JL_AUTH_LEN_KEY_LOCAL];
    E_JL_BOOL is_loaded;
}jl_key_node_t;

typedef enum {
    E_JL_LKEY_OP_ADD = 0x01,
    E_JL_LKEY_OP_DEL = 0x02,
    E_JL_LKEY_OP_UPD = 0x03,
    E_JL_LKEY_OP_GET = 0x04,
    E_JL_LKEY_OP_LOAD = 0x05
}E_JL_LKEY_OP;

/**
 * brief: 
 * 1 one service must belong one server
 * 2 one server can suport multi service
 * 3 one dev have muti service
 * 4 not support multi thread
 * 5 buffer can reuse
 */
typedef struct{
    /*
     *jl_server_t list 
     *manager service for producer
     */
    jl_list_head_t server_list;  

    /*
     *jl_session_t list
     *only manager proxy service with session info. 
     */
    jl_list_head_t proxy_list;

    /*
     * sls send handler list
     * no sission
     */
    jl_list_head_t server_sls_list;

    /*
     * jl_signal_object_t
     * sls cb list
     */
    jl_list_head_t proxy_sls_list;  

    /*
     *mem buffers to reuse
     */
    
    E_JL_BOOL is_sdk_actived; 
    int32_t sdk_level_map;
	
#ifdef __LINUX__
	pthread_mutex_t lock;
    pthread_mutex_t lock_ui;
#endif

#ifdef _MTHREAD_ 
	pthread_mutex_t     sock_lock;
    pthread_rwlock_t    proxy_list_rw_lock;
	pthread_mutex_t     cloud_fd_lock;
    //pthread_rwlock_t  a_rw_lock;
    //pthread_rwlock_t  c_rw_lock;
#endif

}jl_context_t;

extern jl_context_t __g_context;

//------ inline funs ------
static inline jl_context_t *
joylink_get_context(void) 
{ 
    return &__g_context; 
}

static inline jl_list_head_t *
joylink_get_context_server_list(void)
{
    return &__g_context.server_list;
}

static inline jl_list_head_t *
joylink_get_context_proxy_list(void) 
{
    return &__g_context.proxy_list;
}

static inline jl_list_head_t *
joylink_get_context_server_sls_list(void) 
{
    return &__g_context.server_sls_list;
}

static inline jl_list_head_t *
joylink_get_context_proxy_sls_list(void)
{
    return &__g_context.proxy_sls_list;
}

#if defined (_MTHREAD_)

#define joylink_rlock_prox_list() 	pthread_rwlock_rdlock(&__g_context.proxy_list_rw_lock);
#define joylink_wlock_prox_list() 	pthread_rwlock_wrlock(&__g_context.proxy_list_rw_lock);
#define joylink_unlock_prox_list() 	pthread_rwlock_unlock(&__g_context.proxy_list_rw_lock);

#define joylink_wlock_rudp_list() 	pthread_rwlock_wrlock(&rudp_list_rw_lock);
#define joylink_unlock_rudp_list() 	pthread_rwlock_unlock(&rudp_list_rw_lock);

#else
	
#define joylink_rlock_prox_list() 	((void) 0)
#define joylink_wlock_prox_list() 	((void) 0)
#define joylink_wlock_rudp_list()   ((void) 0)
#define joylink_unlock_rudp_list()  ((void) 0)
#define joylink_unlock_prox_list()  ((void) 0)

#endif

//------  inline end  ------

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
