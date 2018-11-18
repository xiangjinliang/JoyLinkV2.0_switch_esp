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

#ifndef __JOYLINK_APP_CB_H__
#define __JOYLINK_APP_CB_H__

#include "joylink.h"
#include "joylink_rpc.h"


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

typedef struct{
    int32_t id;                                 //only for sqlite2
    char guid[JL_MAX_LEN_GUID];
    int32_t cloud_enable;
    char cloud_url[JL_MAX_LEN_URL];
    char name[JL_MAX_LEN_NAME];
    char language[JL_MAX_LEN_LANGUAGE];

    char ac_key[JL_AUTH_LEN_KEY];
    char local_key[JL_AUTH_LEN_KEY_LOCAL];
    char gst_key[JL_AUTH_LEN_KEY_GUEST];

    int32_t bound;

    int32_t b_locked;
    char locker_guid[JL_MAX_LEN_GUID];

    char software_version[JL_MAX_LEN_VERSION];
    char active_url[JL_MAX_LEN_URL];
    int32_t reserve_a;
    int32_t reserve_b;
}jl_config_t;

typedef enum {
    E_JL_CONFIG_OP_GET      = 0x00,
    E_JL_CONFIG_OP_UPD      = 0x01
}E_JL_CONFIG_OP;

typedef struct{
    int32_t id;                                 //only for sqlite2
    int32_t dev_db_id;                          //only for sqlite2
    int32_t uid;                                //only for subdev short id
    jl_config_t config;
    char manufacturer[JL_MAX_LEN_MANUFACTURER];
    char publish_date[JL_MAX_LEN_DATE];
    /**
     *app_id and secret is for SDK active
     */
    char app_id[JL_MAX_LEN_APP_ID];
    char secret[JL_MAX_LEN_SECRET];
    char eth_name[JL_MAX_LEN_ETH];
    char sv_list[JL_MAX_NUM_SERVICE][JL_MAX_LEN_NAME];
    int32_t sv_num;
}jl_japp_info_t;

typedef struct{
    int32_t id;                                 //only for sqlite2
    char guid[JL_MAX_LEN_GUID];
    char sv_name[JL_MAX_LEN_NAME];
    int32_t st;
}jl_dbt_service_t;

typedef struct{
    char protocol[JL_MAX_LEN_PRO];
    int rssi;
}jl_dev_transmission_t;

typedef struct{
    int rom;
    int ram;
    float cpu_freq;
    unsigned short cpu_core_number;
    char cpu_model[JL_MAX_LEN_MODEL];
}jl_dev_hardware_t;

typedef enum {
    E_JL_DEV_TYPE_NORMAL = 0x00,
    E_JL_DEV_TYPE_GW,
    E_JL_DEV_TYPE_SUB_DEV,
    E_JL_DEV_TYPE_RSV
}E_JL_DEV_TYPE;

typedef struct{
    int32_t id;                          //only for sqlite2
    char name[JL_MAX_LEN_NAME];          //nessary or not
    char default_language[JL_MAX_LEN_LANGUAGE];
    char software_version[JL_MAX_LEN_VERSION];
    jl_dev_transmission_t transmission;

    unsigned short CID;
    unsigned short brand;

    char puid[JL_MAX_LEN_PUID];
    char model_code[JL_MAX_LEN_MODE_CODE];
    char platform[JL_MAX_LEN_PLATFORM];
    char manufacturer[JL_MAX_LEN_MANUFACTURER];
    char main_board_model[JL_MAX_LEN_MODEL]; 
    int power_supply_mode;
    char production_date[JL_MAX_LEN_DATE];
    char device_id[JL_MAX_LEN_DEVICE_ID];
    jl_dev_hardware_t hardware;

    E_JL_DEV_TYPE dev_type;
}jl_dev_info_t;

typedef struct{
	jl_japp_info_t app_info;
	jl_dev_info_t  dev_info;
}jl_gateway_dev_info_t, jl_dev_storage_info_t;

/**
 * brief: 
 * NOTE: return char * must joylink_util_malloc
 */
typedef char* (*F_GET_SERVICE_JSON_CB)(const char* sv_name);

typedef E_JL_RETCODE (*F_SERVICE_INIT_CB)(jl_list_head_t *fun_list, const char *name, const char*guid);

typedef E_JL_RETCODE (*F_SIGNAL_INIT_CB)(jl_list_head_t *fun_list, 
        const char *service_name, const char* signal_name, const char*guid);

typedef E_JL_RETCODE (*F_APP_CONFIG_CB)(jl_config_t *conf, const char*guid);

typedef E_JL_RETCODE (*F_APP_GET_CB)(void *data, const char*guid, E_JL_DEV_TYPE dev_type);

typedef E_JL_RETCODE (*F_APP_LKEY_OP_CB)(char*guid, char *l_key, E_JL_LKEY_OP op);

typedef char* (*F_GET_UNIQUE_PATH_CB)(void);

typedef int64_t (*F_GET_DEV_TIME_CB)(void);

typedef E_JL_RETCODE (*F_SET_DEV_TIME_CB)(int64_t tv);

/**
 * brief: 
 * NOTE: If func cb return out_result, 
 *       out_result->msg_body must joylink_util_malloc.
 */
typedef E_JL_RETCODE (*F_FUNC_CB)(jl_arg_bucket_t *in_args, jl_arg_bucket_t *out_result, void *data);

typedef int32_t (*F_GW_GET_GUIDS)(const char *sv_name, int32_t max, char o_guids[64][JL_MAX_LEN_GUID]);

typedef E_JL_BOOL (*F_UI_IS_GUEST)(const char *guid);

typedef E_JL_SERVICE_STATUS (*F_APP_GET_SV_STAT)(char *guid, char *service_name);

typedef char * (*F_UI_GET_GUEST_KEY)(const int mode);

typedef E_JL_RETCODE (*F_RESET_CB)(char *guid, int level);

typedef char * (*F_IFTTT_READ_CB)(int idx);

typedef E_JL_RETCODE (*F_IFTTT_WRITE_CB)(char *id, char *script);

typedef E_JL_RETCODE (*F_IFTTT_DELETE_CB)(char *id);

typedef int (*F_IFTTT_COUNT_CB)();

typedef E_JL_RETCODE (*F_IFTTT_LOAD_CB)();

/**
 * brief: 
 * NOTE: Remmber to joylink_util_free the return char *. 
 */
char *
joylink_cb_get_service_js(const char *name);

E_JL_BOOL
joylink_app_is_guest(const char *guid);

char *
joylink_app_get_guest_key(const int mode);

/**
 * [joylink_cb_service_init] 
 *
 * @param: [fun_list]
 * @param: [name]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_service_init(jl_list_head_t *fun_list, const char *name, const char *guid);

/**
 * [joylink_cb_app_register] 
 *
 * @param: [get_sv_js_cb]
 * @param: [sv_init_cb]
 * @param: [config_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_app_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
        					F_SERVICE_INIT_CB sv_init_cb,
        					F_APP_GET_CB get_app_info_cb,
        					F_APP_GET_CB get_dev_info_cb,
        					F_APP_CONFIG_CB upd_config_cb,
        					F_APP_LKEY_OP_CB lkey_op_cb,
                            F_APP_GET_SV_STAT get_sv_stat,
                            F_RESET_CB reset_cb);
/**
 * [joylink_cb_session_register] 
 *
 * @param: [get_sv_js_cb]
 * @param: [sv_init_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_session_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
                    F_SERVICE_INIT_CB sv_init_cb);

/**
 * [joylink_cb_about_register] 
 *
 * @param: [get_sv_js_cb]
 * @param: [sv_init_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_about_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
                    F_SERVICE_INIT_CB sv_init_cb);

/**
 * [joylink_cb_conf_register] 
 *
 * @param: [get_sv_js_cb]
 * @param: [sv_init_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_conf_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
        					F_SERVICE_INIT_CB sv_init_cb);

/**
 * [joylink_cb_ota_update_client_register]
 * @param  get_sv_js_cb
 * @param  sv_init_cb
 * @return [E_ERROR_PARAM_INVAID/E_OK]
 */
E_JL_RETCODE joylink_cb_ota_update_client_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
                                     F_SERVICE_INIT_CB sv_init_cb);

#if defined(_IFTTT_ENABLED_)
/**
 * [joylink_app_register_property_cb] 
 *
 * @param: [fun_list]
 * @param: [name]
 * @param: [set_cb]
 * @param: [get_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_ifttt_register_int(F_SERVICE_INIT_CB sv_init_cb,
                              F_IFTTT_LOAD_CB sv_load);

E_JL_RETCODE
joylink_cb_ifttt_register_ext(F_IFTTT_READ_CB sv_read,
                              F_IFTTT_WRITE_CB sv_write,
                              F_IFTTT_DELETE_CB sv_delete,
                              F_IFTTT_COUNT_CB sv_count);
#endif
/**
 * brief: joylink_cb_cloud_gateway_register
 *
 * @param: get_sv_js_cb
 * @param: sv_init_cb
 *
 * @returns:
 */
E_JL_RETCODE
joylink_cb_cloud_gateway_register(F_GET_SERVICE_JSON_CB get_sv_js_cb,
                                  F_SERVICE_INIT_CB sv_init_cb);

#if defined(_THUNDERCONFIG_ENABLED_)
/**
 * [joylink_cb_thunderconfig_register] 
 *
 * @param: [get_sv_js_cb]
 * @param: [sv_init_cb]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_thunderconfig_register(F_GET_SERVICE_JSON_CB get_sv_js_cb, 
        					F_SERVICE_INIT_CB sv_init_cb);
#endif


E_JL_RETCODE
joylink_app_register_property_cb(jl_list_head_t *fun_list, 
                        const char* name, 
                        F_FUNC_CB set_cb, 
                        F_FUNC_CB get_cb);

/**
 * [joylink_app_register_func_cb] 
 *
 * @param: [fun_list]
 * @param: [name]
 * @param: [func]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_register_func_cb(jl_list_head_t *fun_list, 
                    const char * name, 
                    F_FUNC_CB func);

/**
 * [joylink_test_rpc_proxy_signal_handler] 
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_test_rpc_proxy_signal_handler(void);


/**
 * [joylink_app_config_upd] 
 *
 * @param: [conf]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_config_upd(jl_config_t *conf, const char*guid);

/**
 * [joylink_app_init_app_dev_info] 
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_init_app_dev_info();

/**
 * [joylink_app_get_app_info] 
 *
 * @returns: 
 */

/**
 * [joylink_app_is_locked] 
 *
 * @returns: 
 */
E_JL_BOOL
joylink_app_is_locked(const char* guid);

/**
 * [joylink_app_guest_mode]
 *
 * @returns:
 */
E_JL_BOOL
joylink_app_guest_mode(const char* guid);

/**
 * [joylink_app_get_app_info] 
 *
 * @param: [app_info]
 * @param: [guid]
 * @param: [type_dev]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_app_info(jl_japp_info_t *app_info, const char *guid, E_JL_DEV_TYPE type_dev);

/**
 * [joylink_app_get_net_eth_name] 
 *
 * @param: [o_eth_name]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_net_eth_name(char *o_eth_name);

/**
 * [joylink_app_get_device_info] 
 *
 * @param: [dev_info]
 * @param: [guid]
 * @param: [type_dev]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_device_info(jl_dev_info_t *dev_info, const char *guid, E_JL_DEV_TYPE type_dev);

/**
 * [joylink_app_get_self_guid] 
 *
 * @param: [o_guid]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_self_guid(char *o_guid);

/**
 * [joylink_app_get_app_id] 
 *
 * @param: [guid]
 * @param: [o_app_id]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_app_get_app_id(const char *guid, char *o_app_id);

/**
 * [joylink_app_get_secret] 
 *
 * @param: [guid]
 * @param: [o_secret]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_app_get_secret(const char *guid, char *o_secret);

/**
 * [joylink_app_get_device_id] 
 *
 * @param: [guid]
 * @param: [o_device_id]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_device_id(const char *guid, char *o_device_id);

/**
 * [joylink_app_get_puid] 
 *
 * @param: [guid]
 * @param: [o_puid]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_puid(const char *guid, char* o_puid);

/**
 * [joylink_app_get_conf] 
 *
 * @param: [guid]
 * @param: [o_conf]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_conf(const char *guid, jl_config_t *o_conf);

/**
 * [joylink_app_get_self_conf] 
 *
 * @param: [conf]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_get_self_conf(jl_config_t *conf);

/**
 * [joylink_cb_gw_register] 
 *
 * @param: [gw_get_guids]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_gw_register(F_GW_GET_GUIDS gw_get_guids);

/**
 * [joylink_app_get_sv_guids] 
 *
 * @param: [sv_name]
 * @param: [max]
 * @param: [o_guids[JL_MAX_NUM_GUID][JL_MAX_LEN_GUID]]
 *
 * @returns: guids num
 */
int32_t
joylink_app_get_sv_guids(const char *sv_name, int32_t max, 
        char o_guids[JL_MAX_NUM_GUID][JL_MAX_LEN_GUID]);

/**
 * brief: joylink_app_get_unique_path 
 * NOTE caller this interface and please free return pointer.
 * @param: 
 *
 * @returns: 
 */
char *
joylink_app_get_unique_path(void);

/**
 * [joylink_app_get_sv_guids] 
 *
 * @param: [sv_name]
 * @param: [max]
 * @param: [o_guids[JL_MAX_NUM_GUID][JL_MAX_LEN_GUID]]
 *
 * @returns: guids num
 */
E_JL_SERVICE_STATUS
joylink_app_get_service_stat(char *guid, char *service_name);

/**
 * [joylink_app_cb_reset] 
 *
 * @param: [guid]
 * @param: [level]
 *
 * @returns: recode 
 */
E_JL_RETCODE
joylink_app_cb_reset(char *guid, int level);

/**
 * [joylink_app_cb_sync_time_register] 
 *
 * @param: [set_time]
 * @param: [get_time]
 *
 * @returns: recode 
 */
E_JL_RETCODE
joylink_app_cb_sync_time_register(F_GET_DEV_TIME_CB get_time, F_SET_DEV_TIME_CB set_time);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __JOYLINK_APP_CB_H__ */
