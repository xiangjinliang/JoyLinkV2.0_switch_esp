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
 * =============================================================================
 *
 *       Filename:  joylink_sql_service_st.h
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  2016年12月06日 10时57分30秒
 *
 *         Author:  evils (joylink), wanggang7@jd.com
 *   Organization:  GPL
 *
 * ===============================================================================
 */

#ifndef __JOYLINK_SQL_SERVICE_ST_H__
#define __JOYLINK_SQL_SERVICE_ST_H__

#if defined (__cplusplus)
extern "C"{
#endif /*defined (__cplusplus) */

/**
 * [joylink_sql_service_st_guid_update_by_new_guid] 
 *
 * @param: [guid]
 * @param: [sv_name]
 * @param: [st]
 *
 * @returns: 
 */
int32_t
joylink_sql_service_st_guid_update_by_new_guid(const char *org_guid, const char *new_guid);

#if defined (__cplusplus)
}
#endif /*defined (__cplusplus) */
#endif /*__H__ */ 

