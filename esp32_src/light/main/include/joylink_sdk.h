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

#ifndef _JOYLINK_SDK_H_
#define _JOYLINK_SDK_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "joylink.h"
#include "joylink_rpc.h"
#include "joylink_app_cb.h"
#include "joylink_utils.h"
#ifdef __IOS__
#include "joylink_cloud_connect.h"
#endif

typedef struct {
    char *service_name;
    char *guid;
    int8_t status;
} jl_sv_stat_t;

/**
 * [joylink_main_init] 
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_main_init(void);

/**
 * [joylink_main_finit] 
 */
void
joylink_main_finit(void);

/**
 * [joylink_cloud_finit]
 */
void
joylink_cloud_finit(void);

/**
 * [joylink_main_loop] 
 */

void 
joylink_main_loop(void);

/**
 * [joylink_discover_service]
 * @param  sv_name [service name]
 * @param  ttl
 * @param  type    [E_JL_CB_DATA_TYPE_STRUCT/E_JL_CB_DATA_TYPE_JSON]
 * @param  dest    [E_JL_SRC_TYPE_LAN/E_JL_SRC_TYPE_CLOUD/E_JL_SRC_TYPE_ALL]
 * @param  sd_cb   [sd function cb]
 * @return         [E_ERROR/E_OK]
 */
E_JL_RETCODE
joylink_discover_service(char *sv_name, int32_t ttl, 
                         E_JL_CB_DATA_TYPE type,
                         E_JL_SRC_TYPE dest,
                         F_SERVICE_SD_CB sd_cb);

/**
 * [joylink_proxy_service_create_by_sd_js]
 * @param  sv_js     [json str of service info]
 * @param  sd_rsp_js [json str]
 * @return           [session_id, if error occurs, return E_ERROR]
 */
int32_t 
joylink_proxy_service_create_by_sd_js(const char *sv_js, const char *sd_rsp_js);

/**
 * [joylink_app_register_signal_handler_cb]
 * @param  session_id
 * @param  guid
 * @param  sv_name    [service name]
 * @param  sg_name    [signal name]
 * @param  type       [E_JL_CB_DATA_TYPE_STRUCT/E_JL_CB_DATA_TYPE_JSON]
 * @param  execute
 * @return            [E_ERROR_PARAM_INVAID/E_ERROR/E_OK]
 */
E_JL_RETCODE
joylink_app_register_signal_handler_cb(int32_t session_id,
									   const char *guid,
									   const char *sv_name,
									   const char *sg_name,
									   E_JL_CB_DATA_TYPE type,
									   F_SIGNAL_CB callback);

/**
 * brief: [joylink_app_unregister_signal_handler_cb] 
 *
 * @param: [session_id]
 * @param: [guid]
 * @param: [sv_name]
 * @param: [sg_name]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_app_unregister_signal_handler_cb(
        int32_t session_id,
        const char *guid,
        const char *sv_name,
        const char *sg_name,
        F_SIGNAL_CB callback
        );

/**
 * [joylink_service_call_by_json]
 * NOTE:must joylink_util_free memory
 * @param  json_ctrl [must be json object]
 * @return           [json]
 */
char *
joylink_service_call_by_json(char *json_ctrl);

/**
 * [joylink_proxy_service_create_by_sd] 
 *
 * @param: [sv_js]
 * @param: [sv_name]
 * @param: [sopt]
 * @param: [GUID]
 * @param: [producer_ip]
 *
 * @returns: 
 */
int32_t
joylink_proxy_service_create_by_sd(const char *sv_js, 
            const char *sv_name, jl_session_option_t *sopt, 
            const char *GUID, const char *producer_ip);
/**
 * [joylink_dev_st_change] 
 *
 * @param: [guid]
 * @param: [st]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_dev_st_change(char *guid, E_JL_DEV_ST st);

/**
 * [joylink_session_detect]
 *
 * @param: [session_id]
 * @param: [guid]
 *
 * @returns:
 */
E_JL_RETCODE
joylink_session_detect(int32_t session_id, char *guid);

/**
 * [joylink_session_leave_req] 
 *
 * @param: [session_id]
 * @param: [guid]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_session_leave_req(const int32_t session_id, 
        const char *guid);

/**
 * [joylink_ota_update_server_proxy_create]
 * @return [E_ERROR_PARAM_INVAID/E_ERROR/E_OK]
 */
/*E_JL_RETCODE
joylink_ota_update_server_proxy_create();*/

/**
 * [joylink_ota_update_client_proxy_create]
 * @return [E_ERROR/E_OK]
 */
/*E_JL_RETCODE
joylink_ota_update_client_proxy_create();*/

/**
 * [joylink_print_ver] 
 */
void
joylink_print_ver(void);

/**
 * brief: joylink_cb_local_channel_register 
 *
 * @param: cb
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_local_channel_register(F_GET_UNIQUE_PATH_CB cb);

/**
 * [joylink_cb_ui_register] 
 *
 * @param: [is_guest]
 * @param: [get_guest_key]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_cb_ui_register(void *is_guest, void *get_guest_key);

/**
 * [joylink_session_proxy_node_del] 
 *
 * @param: [session_id]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_session_proxy_node_del(int32_t session_id);

/**
 * [joylink_cloud_gateway_stat_report]
 *
 * @param: [sv_stats]
 * @param: [num]
 *
 * @return:
 */
E_JL_RETCODE
joylink_cloud_gateway_stat_report(jl_sv_stat_t *sv_stats[], uint8_t num);

/**
 * brief: 
 *
 * @Param: data
 * @Param: o_size
 * @Param: o_len
 * @Param: o_infos
 *
 * @Returns: 
 */
E_JL_RETCODE
joylink_parse_as_data(char *data, int32_t *o_size, int32_t *o_len, char ***o_infos);

/**
 * brief: 
 *
 * @Param: guid_of_snap
 * @Param: sv_name
 * @Param: properties
 *
 * @Returns: 
 */
E_JL_RETCODE
joylink_cloud_gateway_report_snapshot(char *guid_of_snap, char *sv_name, char *properties);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
