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

#ifndef __JOYLINK_LIST_H_
#define __JOYLINK_LIST_H_

#if defined(__QC_4010__) || defined(__OV_788__)
#else
#include <stdio.h>
#endif

#if defined(__OV_788__)
#else
#include <stdlib.h>
#include <string.h>
#endif

#if defined(__QC_4010__) || defined(__MTK_7687__) || defined(__MW300__) || defined(__MICOKIT_3166__) || defined(__REALTEK_8711__) || defined(__OV_788__) || defined(__ESP32__)
#include <stdint.h>
#endif
#include "joylink_list_basic.h"
#include "joylink_ret_code.h"

typedef enum {
    E_LIST_BOOL_FALSE = 0,
    E_LIST_BOOL_TRUE = 1
}E_LIST_BOOL;

#define mem_get(type, n) joylink_util_malloc(sizeof(type) * n)
/**
 *FIXME zhongxuan
 */
//#define mem_get(type, n) calloc(sizeof(type),n)
#define mem_put(ptr)  \
    do{               \
        joylink_util_free(ptr);    \
        (ptr) = NULL; \
    }while(0)

typedef enum __list_ret{
    E_LIST_RET_OK = 0,
    E_LIST_ERROR = -1,
    E_LIST_ERROR_PARAM_INVAILD = -2
}E_LIST_RET;

typedef struct _id_node	
{
	jl_list_head_t	list;
	int32_t	id;
    int32_t len;
    void *data;
}jl_id_node_t;

typedef E_JL_BOOL (*F_DATA_CHECK_CB) (void *node_data, void *user_data);

typedef void *(*F_DATA_PROC_CB) (void *node_data, void *user_data);
//===========================

/**
 * [joylink_list_idnode_is_exist] 
 *
 * @param: [id]
 * @param: [lhead]
 *
 * @returns: 
 */
E_LIST_BOOL joylink_list_idnode_is_exist(int32_t id, jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_add] 
 * NOTE: [1 joylink_util_malloc the node]
 *       [2 joylink_util_malloc the data]
 * @param: [data]
 * @param: [data_len]
 * @param: [lhead]
 *
 * @returns: 
 */
int32_t 
joylink_list_idnode_add(void *data, int32_t data_len, jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_del] 
 * NOTE: [1 joylink_util_free node->data] 
 *       [2 joylink_util_free node]
 * @param: [id]
 * @param: [lhead]
 *
 * @returns: 
 */
E_LIST_RET 
joylink_list_idnode_del(int32_t id, jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_del_by_node] 
 * NOTE: [1 del node from list]
 *       [2 joylink_util_free node->data]
 *       [3 joylink_util_free node]
 * @param: [node]
 *
 * @returns: 
 */
E_LIST_RET
joylink_list_idnode_del_by_node(jl_id_node_t *node);

/**
 * [joylink_list_idnode_clr_by_node]
 * NOTE: [1 clr node from list]
 *       [2 joylink_util_free node]
 * @param: [node]
 *
 * @returns:
 */
E_LIST_RET
joylink_list_idnode_clr_by_node(jl_id_node_t *node);

/**
 * [joylink_list_ids_get] 
 *
 * @param: [size]
 * @param: [pids]
 * @param: [lhead]
 *
 * @returns: 
 */
int32_t 
joylink_list_ids_get(int32_t size, int32_t *pids, jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_get_by_id] 
 *
 * @param: [id]
 * @param: [lhead]
 *
 * @returns: 
 */
jl_id_node_t * 
joylink_list_idnode_get_by_id(int32_t id, jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_clear] 
 *
 * @param: [lhead]
 *
 * @returns: 
 */
int32_t 
joylink_list_idnode_clear(jl_list_head_t *lhead);

/**
 * [joylink_list_idnode_debugp] 
 *
 * @param: [lhead]
 */
void 
joylink_list_idnode_debugp(jl_list_head_t *lhead);

/**
 * [joylink_list_front] 
 *
 * @param: [lhead]
 *
 * @returns: 
 */
jl_id_node_t * 
joylink_list_front(jl_list_head_t *lhead);

/**
 * [joylink_list_pop_front] 
 *
 * @param: [lhead]
 *
 * @returns: 
 */
jl_id_node_t * 
joylink_list_pop_front(jl_list_head_t *lhead);

/**
 * [joylink_list_back] 
 *
 * @param: [lhead]
 *
 * @returns: 
 */
jl_id_node_t * 
joylink_list_back(jl_list_head_t *lhead);

/**
 * [joylink_list_pop_back] 
 *
 * @param: [lhead]
 *
 * @returns: 
 */
jl_id_node_t * 
joylink_list_pop_back(jl_list_head_t *lhead);

/**
 * [joylink_list_data_get_by_cb] 
 *
 * @param: [lhead]
 * @param: [check_cb]
 * @param: [user_data]
 *
 * @returns: 
 */

void *
joylink_list_data_get_by_cb(jl_list_head_t *lhead, 
        F_DATA_CHECK_CB check_cb, void* user_data);

/**
 * [joylink_list_node_del_by_cb] 
 *
 * @param: [lhead]
 * @param: [check_cb]
 * @param: [user_data]
 *
 * @returns: 
 */

E_LIST_RET
joylink_list_node_del_by_cb(jl_list_head_t *lhead, 
        F_DATA_CHECK_CB check_cb, void* user_data);

/**
 * [joylink_list_every_node_proc_by_cb] 
 *
 * @param: [lhead]
 * @param: [cb_proc]
 * @param: [user_data]
 *
 * @returns: 
 */
E_LIST_RET
joylink_list_every_node_proc_by_cb(jl_list_head_t *lhead, 
        F_DATA_PROC_CB cb_proc, void* user_data);
#endif
