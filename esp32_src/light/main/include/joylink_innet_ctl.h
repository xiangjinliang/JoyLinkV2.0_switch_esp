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

#ifndef _JOYLINK_INNET_CTL_H_
#define _JOYLINK_INNET_CTL_H_
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "thunderconfig_utils.h"

//#include "joylink_smnt.h"
//#include "thunderconfig.h"


#define SIZE_CID 			8
#define SIZE_PUID			6
#define SIZE_MAC			6
#define SIZE_SMNT_KEY		16

#define MODE_THUNDER_USERVERYFY_ALLNO	(0x00)
#define MODE_THUNDER_USERVERYFY_INNET 	(0x01 << 1)
#define MODE_THUNDER_USERVERYFY_BOND	(0x01 << 2)


typedef struct _joylink_innet_init_param 
{
	uint8_t     mode_thunder;
	uint8_t 	puid[SIZE_PUID+1];
	uint8_t 	mac[SIZE_MAC];
	uint8_t 	smnt_key[SIZE_SMNT_KEY+1];
	uint16_t 	cid;
	uint16_t 	brand;
	void 	*switch_channel_cb;
	void 	*config_finish_cb;
	void 	*frame_tx_cb;
	void	*printf_func;
} joylink_innet_param_t;

typedef enum 
{
	FRAME_SUBTYPE_UNKNOWN				= -1,//JL_FRAME_SUBTYPE_UNKNOWN,
	FRAME_SUBTYPE_RAWDATA 				= 0, //JL_FRAME_SUBTYPE_DATA,
	FRAME_SUBTYPE_BEACON 				= 8, //JL_FRAME_SUBTYPE_BEACON,
	FRAME_SUBTYPE_UDP_MULTIANDBROAD		= FRAME_SUBTYPE_BEACON + 1,					//udp multicast and broadcast data,used for SMNT
} joylink_rx_type_t;



// 2-byte Frame control field
typedef struct{
    uint16_t        Ver:2;                // Protocol version
    uint16_t        Type:2;                // MSDU type
    uint16_t        SubType:4;            // MSDU subtype
    uint16_t        ToDs:1;                // To DS indication
    uint16_t        FrDs:1;                // From DS indication
    uint16_t        MoreFrag:1;            // More fragment bit
    uint16_t        Retry:1;            // Retry status bit
    uint16_t        PwrMgmt:1;            // Power management bit
    uint16_t        MoreData:1;            // More data bit
    uint16_t        Wep:1;                // Wep data
    uint16_t        Order:1;            // Strict order expected
} FRAME_CONTROL_HEADER;

typedef struct{
    FRAME_CONTROL_HEADER   FC;
    uint16_t          Duration;
    uint8_t           Addr1[6];
    uint8_t           Addr2[6];
    uint8_t            Addr3[6];
    uint16_t            Frag:4;
    uint16_t            Sequence:12;
    uint8_t            Octet[0];
} *PHEADER_802_11_SMNT;


typedef struct
{
	PHEADER_802_11_SMNT head_802_11;
	int 	length;
}joylink_frame_udp_t;

typedef struct 
{	
	uint8_t ssid[33];
	uint8_t ssid_len;
	uint8_t pwd[33];
	uint8_t pwd_len;
	uint8_t thunder_mode;
	uint32_t thunder_timeout;
} joylink_innet_result_t;

typedef void (*joylink_innet_result_callback_t)(joylink_innet_result_t result_info);
typedef int (*joylink_switch_channel_cb_t)(uint8_t channel);

int joylink_innet_init(joylink_innet_param_t init_para);
int joylink_innet_timingcall(void);
int joylink_innet_rx_handler(joylink_rx_type_t frame_type, void *frame);

int joylink_innet_userconfirm_report(void);


#endif






