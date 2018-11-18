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

/*
 * joylink_sql.h
 *
 */
#ifndef JOYLINK_SQL_H_
#define JOYLINK_SQL_H_

#include <string.h>
#include "sqlite3.h"
#include "joylink_app_cb.h"

/**
 * [joylink_sql_init] 
 *
 * @returns: 
 */
int32_t 
joylink_sql_init(const char *sqlite_db);

/**
 * [joylink_sql_exec] 
 *
 * @param: [sql]
 *
 * @returns: 
 */
int32_t
joylink_sql_exec(const char *sql);

/**
 * [joylink_sql_prepare] 
 *
 * @param: [sql]
 * @param: [stmt]
 *
 * @returns: 
 */
int32_t
joylink_sql_prepare(const char *sql, sqlite3_stmt** stmt);

/**
 * [joylink_sql_get_table] 
 *
 * @param: [sql]
 * @param: [resultp]
 * @param: [nrow]
 * @param: [ncolumn]
 *
 * @returns: 
 */
int32_t
joylink_sql_get_table(const char *sql, char *** resultp, int32_t* nrow, int32_t* ncolumn);

/**
 * [joylink_sql_db_tables_init] 
 *
 * @returns: 
 */
int32_t 
joylink_sql_db_tables_init(const char *sqlite_db);

/**
 * [joylink_get_last_insert_rowid] 
 *
 * @returns: 
 */
int32_t
joylink_get_last_insert_rowid();

/**
 * [joylink_sql_dev_info_create] 
 *
 * @returns: 
 */
int32_t
joylink_sql_dev_info_create();

/**
 * [joylink_sql_insert_dev_info] 
 *
 * @param: [dev_info]
 *
 * @returns: 
 */
int32_t
joylink_sql_insert_dev_info(jl_dev_info_t *dev_info);

/**
 * [joylink_sql_dev_info_del_by_id] 
 *
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_dev_info_del_by_id(int32_t id);

/**
 * [joylink_sql_dev_info_del_by_puid_devid] 
 *
 * @param: [puid]
 * @param: [devid]
 *
 * @returns: 
 */
int32_t
joylink_sql_dev_info_del_by_puid_devid(const char *puid, const char *devid);

/**
 * [joylink_sql_dev_info_get_by_puid_devid] 
 *
 * @param: [dev]
 * @param: [puid]
 * @param: [devid]
 *
 * @returns: 
 */
int32_t
joylink_sql_dev_info_get_by_puid_devid(jl_dev_info_t *dev, 
        const char *puid, const char *devid);

/**
 * [joylink_sql_dev_info_get_by_id] 
 *
 * @param: [dev]
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_dev_info_get_by_id(jl_dev_info_t *dev, int32_t id);

/**
 * [joylink_sql_config_create] 
 *
 * @returns: 
 */
int32_t
joylink_sql_config_create();

/**
 * [joylink_sql_insert_config] 
 *
 * @param: [config]
 *
 * @returns: 
 */
int32_t
joylink_sql_insert_config(jl_config_t *config);

/**
 * [joylink_sql_config_del_by_id] 
 *
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_config_del_by_guid(const char *guid);

/**
 * [joylink_sql_config_get_by_guid] 
 *
 * @param: [config]
 * @param: [guid]
 *
 * @returns: 
 */
int32_t
joylink_sql_config_get_by_guid(jl_config_t *config, const char *guid);

/**
 * [joylink_sql_config_update_by_guid] 
 *
 * @param: [guid]
 * @param: [config]
 *
 * @returns: 
 */
int32_t
joylink_sql_config_update_by_guid(const char *guid, jl_config_t *config);

/**
 * [joylink_sql_app_info_create] 
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_create();

/**
 * [joylink_sql_insert_app_info] 
 *
 * @param: [app_info]
 *
 * @returns: 
 */
int32_t
joylink_sql_insert_app_info(const char *guid, jl_japp_info_t *app_info);

/**
 * [joylink_sql_app_info_del_by_id] 
 *
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_del_by_guid(const char *guid);

/**
 * [joylink_sql_app_info_update_by_guid] 
 *
 * @param: [guid]
 * @param: [app_info]
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_update_by_guid(const char *guid, jl_japp_info_t *app_info);

/**
 * [joylink_sql_app_info_update_guid] 
 *
 * @param: [org_guid]
 * @param: [new_guid]
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_update_guid(const char *org_guid, const char *new_guid);

/**
 * [joylink_sql_app_info_get_by_guid] 
 *
 * @param: [app_info]
 * @param: [guid]
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_get_by_guid(jl_japp_info_t *app_info, const char *guid);

/**
 * [joylink_sql_app_info_get_by_uid] 
 *
 * @param: [app_info]
 *
 * @returns: 
 */
int32_t
joylink_sql_app_info_get_by_uid(jl_japp_info_t *app_info, int32_t uid);

/**
 * [joylink_sql_service_st_create] 
 *
 * @returns: 
 */
int32_t
joylink_sql_service_st_create();

/**
 * [joylink_sql_service_st_del_by_id] 
 *
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_service_st_del_by_guid(const char *guid);

/**
 * [joylink_sql_insert_service_st] 
 *
 * @param: [service_st]
 *
 * @returns: 
 */
int32_t
joylink_sql_insert_service_st(char sv_list[JL_MAX_NUM_SERVICE][JL_MAX_LEN_NAME], 
        const char *guid, int32_t num);

/**
 * [joylink_sql_service_st_update_by_guid_sv_name] 
 *
 * @param: [guid]
 * @param: [sv_name]
 * @param: [st]
 *
 * @returns: 
 */
int32_t
joylink_sql_service_st_update_by_guid_sv_name(const char *guid, 
        const char *sv_name, int32_t st);

/**
 * [joylink_sql_service_st_get_by_guid_sname] 
 *
 * @param: [service_st]
 * @param: [guid]
 * @param: [sv_name]
 *
 * @returns: 
 */
int32_t
joylink_sql_service_st_get_by_guid_sname(jl_dbt_service_t *service_st, 
        const char *guid, const char *sv_name);

/**
 * [joylink_sql_service_sts_get_by_guid] 
 *
 * @param: [service_st[JL_MAX_NUM_SERVICE]]
 * @param: [guid]
 *
 * @returns: 
 */
int32_t
joylink_sql_service_sts_get_by_guid(jl_dbt_service_t *service_st, 
        const char *guid);

/**
 * [joylink_sql_insert_lkey] 
 *
 * @param: [keys]
 *
 * @returns: 
 */
int32_t
joylink_sql_insert_lkey(const char *guid, const char *local_key);

/**
 * [joylink_sql_keys_del_by_id] 
 *
 * @param: [id]
 *
 * @returns: 
 */
int32_t
joylink_sql_keys_del_by_guid(const char *guid);

/**
 * [joylink_sql_keys_update_by_guid] 
 *
 * @param: [guid]
 * @param: [keys]
 *
 * @returns: 
 */
int32_t
joylink_sql_keys_update_by_guid(const char *guid, const char *local_key);

/**
 * [joylink_sql_keys_get_by_guid] 
 *
 * @param: [keys]
 * @param: [guid]
 *
 * @returns: 
 */
int32_t
joylink_sql_keys_get_by_guid(const char *guid, char *o_local_key);

/**
 * [joylink_sql_get_guid_by_device_id] 
 *
 * @param: 
 * @param:
 *
 * @returns: 
 */
int32_t
joylink_sql_get_guid_by_device_id(const char *device_id, char *guid);

#endif /* JOYLINK_SQL_H_ */
