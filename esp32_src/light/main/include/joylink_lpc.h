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
 * @brief:
 *
 * @version: 1.0
 *
 * --------------------------------------------------
 */
#ifndef __JOYLINK_LPC_H__
#define __JOYLINK_LPC_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "joylink_ret_code.h"
#include "joylink_rpc.h"

/**
 * brief: [joylink_lpc_call_function] 
 * NOTE
 * @param: [service_name]   [IN] 
 * @param: [member_name]    [IN] 
 * @param: [signal_name]    [IN]
 * @param: [in]   		    [IN] [jl_arg_bucket_t]
 * @param: [in]   		    [IN] [guid]
 * @param: [out]   	        [IN] [jl_arg_bucket_t]
 *
 *
 * @returns: 		        [E_OK : successed, E_ERROR : failed]
 */
E_JL_RETCODE joylink_lpc_call_function(const char *service_name, 
					const char *member_name,
					jl_arg_bucket_t *in, jl_arg_bucket_t *out, const char *guid);

/**
 * brief: [joylink_lpc_get_property] 
 * NOTE
 * @param: [service_name]   [IN] 
 * @param: [member_name]    [IN] 
 * @param: [signal_name]    [IN]
 * @param: [in]   		    [IN] [jl_arg_bucket_t]
 * @param: [in]   		    [IN] [guid]
 * @param: [out]   	        [IN] [jl_arg_bucket_t]
 *
 *
 * @returns: 		        [E_OK : successed, E_ERROR : failed]
 */
E_JL_RETCODE joylink_lpc_get_property(const char *service_name, 
					const char *member_name,
					jl_arg_bucket_t *in, jl_arg_bucket_t *out, const char *guid);

/**
 * brief: [joylink_lpc_set_property] 
 * NOTE
 * @param: [service_name]   [IN] 
 * @param: [member_name]    [IN] 
 * @param: [signal_name]    [IN]
 * @param: [in]   		    [IN] [jl_arg_bucket_t]
 * @param: [in]   		    [IN] [guid]
 * @param: [out]   	        [IN] [jl_arg_bucket_t]
 *
 *
 * @returns: 		        [E_OK : successed, E_ERROR : failed]
 */
E_JL_RETCODE joylink_lpc_set_property(const char *service_name, 
					const char *member_name,
					jl_arg_bucket_t *in, jl_arg_bucket_t *out, const char *guid);

#ifdef __cplusplus
}
#endif

#endif

