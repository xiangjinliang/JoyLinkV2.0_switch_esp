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

#ifndef _JOYLINK_LOCAL_CHANNLE_H_
#define _JOYLINK_LOCAL_CHANNLE_H_

#include "joylink_ret_code.h"
#include "joylink.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * [joylink_local_channel_transfer_data_wait_reply]
 * NOTE joylink_util_free memory point after call api interface 
 * @param
 * @return
 */
char *
joylink_local_channel_transfer_data_wait_reply(const char *buf, 
			const int32_t buf_size, int32_t *o_size);

/**
 * [joylink_local_channel_proc] 
 *
 * @param: [fd]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_local_channel_proc(int32_t fd);

/**
 * [joylink_packet_transfer_buf] 
 *  NOTE joylink_util_free o_buf
 * @param: [head]
 * @param: [mdesc]
 * @param: [msg_body]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_packet_transfer_buf(jl_header_t *head, jl_msg_desc_t *desc, 
        const char *msg_body, char **o_buf, int32_t *o_size);

/**
 * [joylink_packet_transfer_buf] 
 *
 * @param: [head]
 * @param: [mdesc]
 * @param: [msg_body]
 *
 * @returns: 
 */
E_JL_RETCODE 
joylink_parse_transfer_buf(char *t_buf, jl_msg_t *msg);

#ifdef __cplusplus
}
#endif

#endif /* _JOYLINK_LOCAL_CHANNLE_H_ */
