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

#ifndef _JOYLINK_THUNDERCONFIG_PUB_H_
#define _JOYLINK_THUNDERCONFIG_PUB_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#include "joylink_thunderconfig_utils.h"

extern int joylink_thunderconfig_init(jl_init_param_t init_param);

extern int joylink_thunderconfig_destroy();

extern void joylink_thunderconfig_control(uint8_t on);

extern int joylink_thunderconfig_50ms_timer();

extern int joylink_thunderconfig_rx(JL_FRAME_SUBTYPE frame_type, void *frame);

extern int joylink_thunderconfig_set_ap(jl_ap_info_t ap_info);

#ifdef  __cplusplus
}
#endif /*!__cplusplus*/
#endif /*!_JOYLINK_THUNDERCONFIG_PUB_H_*/
