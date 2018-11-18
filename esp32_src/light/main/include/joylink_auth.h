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

#ifndef _JOYNLINK_AUTH_H_
#define _JOYNLINK_AUTH_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __LINUX_UB2__
#include <stdint.h>
#include <unistd.h>
#endif

#ifdef __MTK_7687__
#include <stdint.h>
#endif

#ifdef __MW300__
#include <stdint.h>
#endif
#ifdef __MICOKIT_3166__
#include <stdint.h>
#endif

#ifdef __ESP32__
#include <stdint.h>
#endif
#if defined(__QC_4010__) || defined(__QC_4531__) || defined(__REALTEK_8711__)
#include <stdint.h>
#endif

#if defined(__QC_4010__) || defined(__OV_788__)
#else
#include <stdio.h>
#endif
#include "joylink_ret_code.h"

#define JL_AUTH_LEN_KEY                     (32)

#define JL_AUTH_LEN_KEY_PUB                 (64)
#define JL_AUTH_LEN_KEY_PUB_COM             (33)
#define JL_AUTH_LEN_KEY_PRI                 (32)
#define JL_AUTH_LEN_KEY_SHARE               (32)
#define JL_AUTH_LEN_KEY_SESSION             (32)
#define JL_AUTH_LEN_KEY_LOCAL               (32)
#define JL_AUTH_LEN_KEY_GUEST               (32)

typedef enum {
    E_JL_ENCRYPT_TYPE_NULL                  = 0x00,
    E_JL_ENCRYPT_TYPE_AC_KEY                = 0x01,
    E_JL_ENCRYPT_TYPE_SHARED_KEY_256        = 0x02,
    E_JL_ENCRYPT_TYPE_SESSION_KEY           = 0x03,
    E_JL_ENCRYPT_TYPE_SHARED_EKY_160        = 0x04,
    E_JL_ENCRYPT_TYPE_LOCAL_KEY             = 0x05,
    E_JL_ENCRYPT_TYPE_GUEST_KEY             = 0x06
}E_JL_ENCRYPT_TYPE;

/**
 * [joylink_auth_init] 
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_init();

/**
 * [joylink_auth_get_pubkey] 
 *
 * @param: [o_pub_key]
 * @param: [max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_get_pubkey(uint8_t *o_pub_key, int32_t max);

/**
 * [joylink_auth_get_compressed_pubkey] 
 *
 * @param: [o_cpub_key]
 * @param: [max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_get_compressed_pubkey(uint8_t *o_cpub_key, int32_t max);

/**
 * [joylink_auth_get_decompress_pubkey] 
 *
 * @param: [o_cpub_key]
 * @param: [o_pub_key]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_get_decompress_pubkey(const uint8_t *cpub_key, uint8_t *o_pub_key);

/**
 * [joylink_auth_get_prikey] 
 *
 * @param: [o_pri_key]
 * @param: [max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_get_prikey(uint8_t *o_pri_key, int32_t max);

/**
 * [joylink_auth_create_share_key] 
 *
 * @param: [pub_key]
 * @param: [len]
 * @param: [o_share_key]
 * @param: [sk_max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_create_share_key(const uint8_t *pub_key, 
                              int32_t len, 
                              uint8_t *o_share_key, 
                              int32_t sk_max);

/**
 * [joylink_auth_create_share_key_by_cpub] 
 *
 * @param: [cpub_key] compressd pubkey
 * @param: [len]
 * @param: [o_share_key]
 * @param: [sk_max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_create_share_key_by_cpub(const uint8_t *cpub_key, 
                                      int32_t len, 
                                      uint8_t *o_share_key, 
                                      int32_t sk_max);
/**
 * [joylink_auth_create_local_key] 
 *
 * @param: [ac_key]
 * @param: [len]
 * @param: [guid]
 * @param: [o_local_key]
 * @param: [lk_max]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_auth_create_local_key(const uint8_t *ac_key, 
                              int32_t len, 
                              const char* guid, 
                              uint8_t *o_local_key, 
                              int32_t lk_max);

/**
 * [joylink_auth_create_gst_key]
 *
 * @param: [ac_key]
 * @param: [len]
 * @param: [guid]
 * @param: [o_local_key]
 * @param: [lk_max]
 *
 * @returns:
 */
E_JL_RETCODE
joylink_auth_create_gst_key(const uint8_t *ac_key,
                            int32_t len,
                            const char* guid,
                            uint8_t *o_local_key,
                            int32_t lk_max);


/**
 * [joylink_auth_create_session_key]
 * @param  s_random_str
 * @param  c_random_str
 * @param  guid
 * @param  o_session_key
 * @return
 */
E_JL_RETCODE 
joylink_auth_create_session_key(char *s_random_str,
                                char *c_random_str,
                                char *guid,
                                char *o_session_key);
/**
 * [joylink_auth_aes_encrypt] 
 *
 * @param: [key]
 * @param: [key_len]
 * @param: [iv]
 * @param: [org_data]
 * @param: [od_len]
 * @param: [o_encrypted_data]
 * @param: [max]
 *
 * @returns: encrypted data len.
 */
int32_t
joylink_auth_aes_encrypt(const uint8_t *key, 
                         int key_len, 
                         const uint8_t *iv, 
                         const uint8_t *org_data, 
                         int32_t od_len, 
                         uint8_t *o_encrypted_data, 
                         int32_t max);

/**
 * [joylink_auth_aes_decrypt] 
 *
 * @param: [key]
 * @param: [key_len]
 * @param: [iv]
 * @param: [encrypted_data]
 * @param: [ed_len]
 * @param: [o_decrpted_data]
 * @param: [max]
 *
 * @returns:decrpted_data len 
 */
int32_t 
joylink_auth_aes_decrypt(const uint8_t *key, 
                         int key_len, 
                         const uint8_t *iv, 
                         const uint8_t *encrypted_data, 
                         int ed_len, 
                         uint8_t *o_decrpted_data, 
                         int max);

#ifdef  __cplusplus
}
#endif /*!__cplusplus*/
#endif /*!_JOYNLINK_AUTH_H_*/
