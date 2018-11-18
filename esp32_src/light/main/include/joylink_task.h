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

#ifndef __JOYLINK_TASK__
#define __JOYLINK_TASK__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */
#include "joylink.h"

typedef enum {
    E_JL_TASK_CATEGORY_NULL     = 0x00,
    E_JL_TASK_CATEGORY_IFTTT    = 0x01,
    E_JL_TASK_CATEGORY_CLOUD_CTRL    = 0x02,
    E_JL_TASK_CATEGORY_SYNC_SSID    = 0x04
} E_JL_TASK_CATEGORY;

typedef struct {
    int32_t index;

    int32_t len;
    void *data;
} jl_task_data_t;

typedef struct{
	char name[256];
    int32_t type;
    int32_t label;

    int32_t ttl;
    int32_t state;
    E_JL_TASK_CATEGORY category;
    void* reserv;
}jl_task_mg_t;

typedef enum {
    E_JL_TASK_TYPE_ALONE = 0x00,
    E_JL_TASK_TYPE_COMPLEX
}E_JL_TASK_TYPE;

typedef void (*F_TASK_CB) (jl_list_head_t *data_lh, jl_task_mg_t *pmg);

typedef E_JL_RETCODE (*F_CHECK_CB) (jl_list_head_t *lh, jl_task_data_t *tdata);

typedef struct{
    F_TASK_CB cb;
    jl_task_mg_t tmg;
    jl_list_head_t list;
}jl_task_t;

E_JL_RETCODE
joylink_task_add(jl_task_mg_t *tmg, 
                jl_task_data_t *tdata, 
                F_TASK_CB task_cb, 
                F_CHECK_CB check_cb);

/**
 * [joylink_task_del_by_name] 
 *
 * @param: [type]
 * @param: [name]
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_task_del_by_name(int32_t type, const char *name);

/**
 * [joylink_task_find_by_type_name] 
 *
 * @param: [type]
 * @param: [name]
 *
 * @returns: 
 */
jl_task_t *
joylink_task_find_by_type_name(int32_t type, const char *name);

/**
 * [joylink_task_ttl_dec_timer] 
 *
 * @param: [data]
 */
void 
joylink_task_ttl_dec_timer(void * data);

/**
 * [joylink_task_clear] 
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_task_clear(void);

/**
 * [joylink_task_proc] 
 *
 * @returns: 
 */
E_JL_RETCODE
joylink_task_proc(void);

/**
 * [joylink_task_list_h]
 *
 * @returns:
 */
jl_list_head_t*
joylink_task_list_h(void);

/**
 * [joylink_task_is_in_limit] 
 *
 * @param: [label]
 * @param: [limit]
 *
 * @returns: 
 */
E_JL_BOOL
joylink_task_is_hit_limit(int32_t label, int32_t limit);
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
