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

#ifndef _JOYLINK_RPC_H_
#define _JOYLINK_RPC_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "joylink.h"

#define MAX_LENGTH				(32)

typedef enum {
    E_JL_CB_DATA_TYPE_STRUCT = 0x00,
    E_JL_CB_DATA_TYPE_JSON,
    E_JL_CB_DATA_TYPE_RSV
}E_JL_CB_DATA_TYPE;

typedef enum {
    E_JL_HANDLER_TYPE_FUNC = 0x00,
    E_JL_HANDLER_TYPE_PROPERTY,
    E_JL_HANDLER_TYPE_SIGNAL,
    E_JL_HANDLER_TYPE_NO_SIGNAL,
    E_JL_HANDLER_TYPE_RSV
}E_JL_HANDLER_TYPE;

typedef struct{
	short	count;
	//short   flag;
}jl_basic_data_describe_t;

typedef struct{
    char    type[MAX_LENGTH];
    char    *data;
	union{
		int32_t length;
		jl_basic_data_describe_t desc;
	};
}jl_basic_data_unit_t;

typedef struct{
    char *name;
    char *type;
    uint32_t len;
	char *data;
}jl_arg_t;

typedef struct{
    int num;
    jl_arg_t *args;
}jl_arg_bucket_t;

typedef struct{
    char *sv_name;
	char type;  //sls  session
}jl_signal_t;

typedef int (*rpc_handler_callback)(jl_arg_bucket_t *in, jl_arg_bucket_t *out, void *data);

typedef struct{
    char *name;
	jl_arg_bucket_t in;
	jl_arg_bucket_t out;//func property
	
    jl_signal_t signal;
	rpc_handler_callback cb;
}jl_rpc_handler_t;

typedef struct{
    char f_num;
    jl_rpc_handler_t** funcs;

    char p_num;
    jl_rpc_handler_t** properties;

    char s_num;
    jl_rpc_handler_t** signals;

    char name[JL_MAX_LEN_NAME];
    short port;
}jl_rpc_sv_t;

typedef struct{
	char type[JL_MAX_LEN_NAME]; //type of handler, such as signal property function
	union{
	    char name[JL_MAX_LEN_NAME]; //only for signal
		char access[MAX_LENGTH]; //only for property
	};
}jl_member_t;

typedef struct{
	E_JL_SRC_TYPE src_type;
	int32_t session_id;
	char service[JL_MAX_LEN_NAME];
	char guid[JL_MAX_LEN_GUID];
	char dest_ip[64];
	jl_member_t member;
}jl_rpc_basic_type_t;

typedef E_JL_RETCODE (*F_SIGNAL_CB)(void *value, jl_rpc_basic_type_t* signal_info);
typedef struct{
	E_JL_CB_DATA_TYPE type;
	F_SIGNAL_CB callback;
}jl_signal_entity_t;

typedef struct{
	char guid[JL_MAX_LEN_GUID];
	jl_list_head_t list; //jl_signal_entity_t
}jl_signal_attribute_t;

typedef struct{
	jl_list_head_t   list;  		 //jl_signal_attribute_t
	jl_rpc_handler_t *handler; 		 //jl_signal_handler_t
}jl_signal_object_t;

/*service discover cb*/
typedef E_JL_RETCODE (*F_SERVICE_SD_CB)(E_JL_CB_DATA_TYPE dtype, void *data, int32_t size);

/**
 * brief: [joylink_japp_proxy_call] 
 *
 * @param: [session_id]
 * @param: [func_name]
 * @param: [args]
 * @param: [o_result]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_japp_proxy_call(int32_t session_id, char* func_name,
				jl_arg_bucket_t *args, jl_arg_bucket_t *o_result,
				void *param);

/**
 * [joylink_japp_send_signal] 
 *
 * @param: [session_id]
 * @param: [guid]
 * @param: [sv_name]
 * @param: [signal_name]
 * @param: [in]
 * @param: [ttl]
 * @param: [count]
 * @param: [dest]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_japp_send_signal(int32_t session_id,
				         char *guid, char* sv_name,
                         char* signal_name, jl_arg_bucket_t *in,
                         int32_t ttl, int32_t count,
                         E_JL_SRC_TYPE dest);

/**
 * brief: [joylink_japp_proxy_set_property] 
 *
 * @param: [session_id]
 * @param: [func_name]
 * @param: [args]
 * @param: [o_result]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_japp_proxy_set_property(int32_t session_id, char* func_name, 
				jl_arg_bucket_t *args, jl_arg_bucket_t *o_result, void* param);

/**
 * brief: [joylink_japp_proxy_get_property] 
 *
 * @param: [session_id]
 * @param: [func_name]
 * @param: [args]
 * @param: [o_result]
 *
 * @returns: 
 */

E_JL_RETCODE joylink_japp_proxy_get_property(int32_t session_id, char* func_name,
				jl_arg_bucket_t *args, jl_arg_bucket_t *o_result, void *param);


/**
 * [joylink_rpc_set_basic_arg] 
 *
 * @param: [arg]
 * @param: [name]
 * @param: [type]
 * @param: [data]
 * @param: [data_len]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_rpc_set_basic_arg(jl_arg_t *arg, 
				const char *name, const char *type,
				void *data, uint32_t data_len);

/**
 * [joylink_rpc_get_arg_data] 
 *
 * @param: [bucket]
 * @param: [name]
 * @param: [data]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_rpc_get_arg_data(jl_arg_bucket_t *bucket, 
				const char *name, void *data, int32_t max_len, uint32_t *o_size);

#define joylink_rpc_get_basic_arg(a, b, c, d) joylink_rpc_get_arg_data(a, b, c, d, NULL)

/**
 * [joylink_rpc_get_arg_data_ptr] 
 * NOTE arg data ptr can not be writed
 * @param: [bucket]
 * @param: [name]
 * @param: [max_len]
 *
 * @returns: arg_data_ptr/NULL
 */
char *joylink_rpc_get_arg_data_ptr(jl_arg_bucket_t *bucket, 
				const char *name, uint32_t *o_size);

#define joylink_rpc_get_basic_arg_ptr(a, b) joylink_rpc_get_arg_data_ptr(a, b, NULL)


/**
 * brief: joylink_rpc_malloc_arg_bucket
 *
 * @Param: bucket
 * @Param: args_num
 *
 * @Returns: 
 */
E_JL_RETCODE joylink_rpc_malloc_arg_bucket(jl_arg_bucket_t *bucket,
				const char args_num);

/**
 * brief: 
 *
 * @Param: bucket
 *
 * @Returns: 
 */
E_JL_RETCODE joylink_rpc_free_arg_bucket(jl_arg_bucket_t *bucket);

/**
 * brief: [joylink_rpc_destory_io_arg_bucket] 
 * joylink_util_free in and out arg bucket
 * @param: [in]   [IN] [jl_arg_bucket_t]
 * @param: [out]  [IN] [jl_arg_bucket_t]
 *
 * @returns: [E_OK : successed, E_ERROR : fabsailed]
 */
E_JL_RETCODE joylink_rpc_destory_io_arg_bucket(jl_arg_bucket_t *in, 
            	jl_arg_bucket_t *out);

/**
 * brief: joylink_rpc_set_arg_name_and_type
 *
 * @Param: arg
 * @Param: name
 * @Param: type
 *
 * @Returns: 
 */
E_JL_RETCODE joylink_rpc_set_arg_name_and_type(jl_arg_t *arg, 
				const char *name, const char *type);

jl_basic_data_unit_t* joylink_rpc_creat_arg_data_by_type(jl_arg_t *arg);

/**
 * [joylink_rpc_set_basic_type_unit] 
 *
 * @param: [signature]
 * @param: [unit]
 * @param: [value]
 * @param: [data_len]
 *
 * @returns: 
 */
int32_t joylink_rpc_set_basic_type_unit(const char *signature, 
                    jl_basic_data_unit_t *unit, void *value, uint32_t data_len);

/**
 * [joylink_rpc_calc_unit_count_by_signature] 
 *
 * @param: [signature]
 *
 * @returns: 
 */
int32_t joylink_rpc_calc_unit_count_by_signature(const char* signature);

/**
 * [joylink_rpc_set_arg_data_with_basic_unit] 
 *
 * @param: [arg]
 * @param: [marshal_data]
 *
 * @returns: 
 */
int32_t joylink_rpc_set_arg_data_with_basic_unit(jl_arg_t *arg, 
			const char *marshal_data);

/**
 * [joylink_rpc_get_basic_unit_data] 
 *
 * @param: [unit]
 */
void joylink_rpc_get_basic_unit_data(jl_basic_data_unit_t *unit);

/**
 * [joylink_rpc_update_arg_bucket_arg] 
 *
 * @param: [arg]
 * @param: [name]
 * @param: [type]
 * @param: [data]
 * @param: [data_len]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_rpc_update_arg_bucket_arg(jl_arg_bucket_t *bucket, 
            		const char *arg_name, void *data, uint32_t data_len);

/**
 * [joylink_rpc_printf_arg_data] 
 *
 * @param: [arg]
 *
 * @returns: 
 */
int32_t joylink_rpc_printf_arg_data(jl_arg_t *arg);

/**
 * [joylink_rpc_free_arg_data] 
 *
 * @param: [arg]
 *
 * @returns: 
 */
int32_t joylink_rpc_free_arg_data(jl_arg_t *arg);

/**
 * [joylink_rpc_set_array_type_unit] 
 *
 * @param: [signature]
 * @param: [unit]
 * @param: [value]
 * @param: [count]
 *
 * @returns: 
 */
E_JL_RETCODE joylink_rpc_set_array_type_unit(const char *signature, 
        jl_basic_data_unit_t *unit, void *value, uint32_t count);

/**
 *
 * brief: [joylink_rpc_find_hndl_by_name] 
 * joylink rpc find func handler and property handler by name
 * @param: [hndl_list]   [IN]  [handler list]
 * @param: [name] 		 [IN]  [handler name]
 * @param: 
 * 
 * @returns: 		 [E_OK : hndl , E_ERROR : NULL]
 */
jl_rpc_handler_t* joylink_rpc_find_hndl_by_name(
					const jl_list_head_t* hndl_list, const char* name);
/**
 * brief: [joylink_rpc_func_handler] 
 * NOTE output args o_result must be joylink_util_free memory
 * @param: [hndl]   		 [IN] [rpc handler]
 * @param: [m_param]   		 [IN] [marshal data]
 * @param: [o_result]        [OUT][marshal data]
 *
 * @returns: 		 [E_OK : successed, E_ERROR : failed]
 */
E_JL_RETCODE joylink_rpc_func_handler(jl_rpc_handler_t *hndl,
					jl_marshal_data_t *m_param, jl_marshal_data_t *o_result, void* exdata);

/**
 * [joylink_rpc_cloud_data_proc]
 * @param  msg
 * @return     [E_ERROR/E_OK]
 */
E_JL_RETCODE joylink_rpc_cloud_data_proc(jl_msg_t *msg);

/**
 * brief: [joylink_rpc_find_signal_object] 
 *
 * @param:
 * @param:
 * @param:
 * @param:
 * @param:
 *
 * @returns: 
 */
jl_signal_object_t*
joylink_rpc_find_signal_object(const char* guid,
				const char *sv_name, const char *sg_name);

/**
 * brief: [joylink_rpc_proxy_sls_signal_handler] 
 *
 * @param: [guid]   		 [IN] [guid]
 * @param: [sv_name]   		 [IN] [service name]
 * @param: [sig_name]        [IN] [signal name]
 * @param: [m_buf]   		 [IN] [marshal data buffer]
 * @param: [m_size]          [IN] [marshal data length]
 *
 * @returns: 		 [E_OK : successed, E_ERROR : failed]
 */
E_JL_RETCODE joylink_rpc_proxy_sls_signal_handler(
					jl_signal_object_t *s_obj, jl_rpc_basic_type_t* s_info,
					char *m_buf, unsigned int m_size);

/**
 * brief: [joylink_rpc_destory_sls_obj] 
 * joylink rpc deinit signal object
 * @param:
 * 
 * @returns: 		 [E_OK , E_ERROR]
 */
E_JL_RETCODE joylink_rpc_destory_sls_obj(void);

/**
 * brief: [joylink_get_error_msg] 
 * must call joylink_rpc_destory_io_arg_bucket api to joylink_util_free ptr
 * @param:
 * @param:
 *
 * @returns: 
 */
char*
joylink_get_error_msg(const E_JL_RETCODE ret, jl_arg_bucket_t *out);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
