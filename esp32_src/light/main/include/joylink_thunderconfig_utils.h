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

#ifndef _JOYLINK_THUNDERCONFIG_UTILS_H_
#define _JOYLINK_THUNDERCONFIG_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif
	
#if defined(__OV_788__) || defined(__MTK_7687__)
#include <stdint.h>
#elif defined(__ESP32__)
#include <stdint.h>

#else
#include <stdio.h>
#include <string.h>
#endif

//JYLK
#define JL_THUNDERCFG_HEAD 					0x4A594C4B
#define JL_THUNDERCFG_HEAD_LEN 				4

#define JL_THUNDERCFG_BRAND_ASSI_LEN		4
#define JL_THUNDERCFG_CID_ASSI_LEN			4

//#define JL_THUNDERCFG_CID_LEN 				8
#define JL_THUNDERCFG_PUID_LEN 				6
#define JL_THUNDERCFG_MAC_LEN 				12
#define JL_THUNDERCFG_ZIGBEE_ID_LEN			26
#define JL_THUNDERCFG_IDENTITY_LEN			32
#define JL_THUNDERCFG_IDENTITY_ASSILEN		26
#define	JL_THUNDERCFG_SSID_LEN				32
#define JL_THUNDERCFG_PWD_LEN 				32
//#define JL_THUNDERCFG_DATA_LEN				128
#define JL_THUNDERCFG_DATA_LEN				250

#define JL_THUNDERCFG_PRIVATE_KEY_LEN 		32
#define JL_THUNDERCFG_PUB_KEY_LEN 	    	64
#define JL_THUNDERCFG_COMPRESSED_KEY_LEN 	33

#define JL_THUNDERCFG_RESET_NORMAL			3
#define JL_THUNDERCFG_RESET_DELAY			30
#define JL_THUNDERCFG_PENDSIGNAL_COUNT		50

typedef enum {
	JL_FRAME_SUBTYPE_UNKNOWN	= -1,
	JL_FRAME_SUBTYPE_DATA 		= 0,
	JL_FRAME_SUBTYPE_BEACON 	= 8,
	JL_FRAME_SUBTYPE_ZIGBEE 	= 98,
	JL_FRAME_SUBTYPE_BLUETOOTH  = 99
} JL_FRAME_SUBTYPE;

typedef enum {
	JL_THUNDERCFG_STATE_TX_AP 		 = 0,	
	JL_THUNDERCFG_STATE_TX_FINISH 	 = 1,
	JL_THUNDERCFG_STATE_TX_NOTHING   = 2,
	JL_THUNDERCFG_STATE_TX_BROADCAST = 3
} JL_THUNDERCFG_STATE_TX;

typedef enum {
	JL_THUNDERCFG_STATE_RX_REQUEST  = 0,
	JL_THUNDERCFG_STATE_RX_REPLY    = 1,
	JL_THUNDERCFG_STATE_RX_FINISH   = 2,
	JL_THUNDERCFG_STATE_RX_NOTHING  = 3
} JL_THUNDERCFG_STATE_RX;

typedef struct _jl_frame_beacon {
	uint8_t ssid[JL_THUNDERCFG_SSID_LEN];
	uint8_t ssid_len;
	uint8_t vendor_specific[JL_THUNDERCFG_DATA_LEN];
	uint8_t vendor_specific_len;
} jl_frame_beacon_t;

typedef struct _jl_frame_data {
	uint8_t raw_data[JL_THUNDERCFG_DATA_LEN];
	uint8_t raw_data_len;
} jl_frame_data_t;

typedef struct _jl_frame_zigbee {
	uint8_t id[JL_THUNDERCFG_SSID_LEN];
	uint8_t id_len;
	JL_THUNDERCFG_STATE_RX rx_state;
} jl_frame_zigbee_t;

typedef struct _jl_device_info {
	uint8_t brand[JL_THUNDERCFG_BRAND_ASSI_LEN];
	uint8_t cid[JL_THUNDERCFG_CID_ASSI_LEN];
//	uint8_t cid[JL_THUNDERCFG_CID_LEN];   //ASCII LEN
	uint8_t puid[JL_THUNDERCFG_PUID_LEN];
	uint8_t mac[JL_THUNDERCFG_MAC_LEN];   //ASCII LEN
} jl_device_info_t;

typedef struct _jl_ap_info {
	uint8_t ssid[JL_THUNDERCFG_SSID_LEN];
	uint8_t ssid_len;
	uint8_t pwd[JL_THUNDERCFG_PWD_LEN];
	uint8_t pwd_len;
} jl_ap_info_t;

typedef struct _jl_key_pair{	
	uint8_t pub_key[JL_THUNDERCFG_PUB_KEY_LEN];	
	uint8_t private_key[JL_THUNDERCFG_PRIVATE_KEY_LEN];
} jl_key_pair_t;

typedef struct _jl_crypt_info {
	jl_key_pair_t local_key_pair;
	uint8_t remote_shared_key[JL_THUNDERCFG_PRIVATE_KEY_LEN];	
} jl_crypt_info_t;

typedef struct _jl_init_param {
jl_ap_info_t ap_info;
void *frame_tx_cb;
void *get_blacklist_cb;
void *put_blacklist_cb;
void *wifi_switch_cb;
void *zigbee_switch_cb;
void *bluetooth_switch_cb;
} jl_init_param_t;
typedef enum
{
	switch_off = 0,
	switch_on
}thunderconfig_switch_status;

typedef struct _jl_thunderconfig {
//	uint8_t identity[JL_THUNDERCFG_IDENTITY_LEN];	
	uint8_t apinfosend_lastid[JL_THUNDERCFG_IDENTITY_ASSILEN+1];	
	thunderconfig_switch_status switch_state;
	jl_crypt_info_t crypt_info;	
	jl_ap_info_t	ap_info;	
	//JL_THUNDERCFG_STATE_TX tx_state;
	//JL_THUNDERCFG_STATE_RX rx_state;
	//JL_THUNDERCFG_STATE_RX last_rx_state;
	//uint8_t rx_counter;
	void *get_blacklist_cb;
	void *put_blacklist_cb;
	void *wifi_switch_cb;
	void *zigbee_switch_cb;
	void *bluetooth_switch_cb;
	void *id_list;
} jl_thunderconfig_t;

/**
 * Callback function prototype for frame transmitting.
 *
 * @param frame_type The type of frame of 802.11 used.
 * @param data The data to be transmited.
 *
 * @return  Returns 0 if succeed; -1 otherwise.
 *
 * @remark 
 *	 The type of data is jl_beacon_rx_t when frame_type
 *   is JL_FRAME_TYPE_BEACON.
 *
 *	 The type of data is jl_data_rx_t when frame_type
 *   is JL_FRAME_TYPE_DATA.
 */
typedef int (*jl_frame_tx_cb_t)(JL_FRAME_SUBTYPE frame_type, void *frmae);

/**
 * Callback function prototype for getting blacklist.
 *
 * @param blacklist A buffer.
 * @param len  The len of blacklist.
 *
 * @return  Return length of blacklist if succeed; -1 otherwise.
 */
typedef int (*jl_get_blacklist_cb_t)(uint8_t *blacklist, uint32_t len);

/**
 * Callback function prototype for putting blacklist.
 *
 * @param blacklist A buffer.
 * @param len  The length of blacklist.
 *
 * @return  Return 0 if succeed; -1 otherwise.
 */
typedef int (*jl_put_blacklist_cb_t)(const uint8_t *blacklist, uint32_t len);

/**
 * Callback function prototype for switch zigbee service.
 *
 * @param on 0:off, 1:on.
 *
 * @return  Return 0 if succeed; -1 otherwise.
 */

typedef int (*jl_wifi_switch_cb_t)(uint8_t on);

typedef int (*jl_zigbee_switch_cb_t)(uint8_t on);

typedef int (*jl_bluetooth_switch_cb_t)(uint8_t on);


extern void joylink_thunderconfig_utils_print(const char *fmt, ...);

extern void joylink_thunderconfig_utils_print_hex(char *tittle, 
										   		  const uint8_t *dest, 
										   		  uint8_t size);

extern int joylink_thunderconfig_utils_make_session_key(const uint8_t *r1, 
														const uint8_t *r2, 
														uint8_t *key);

extern uint16_t joylink_thunderconfig_utils_htons(uint16_t value);

extern uint32_t joylink_thunderconfig_utils_htonl(uint32_t value);

extern uint16_t joylink_thunderconfig_utils_nstoh(uint16_t value);

extern uint32_t joylink_thunderconfig_utils_nltoh(uint32_t value);

extern int joylink_thunderconfig_utils_byte2hex(const uint8_t *pbytes,
												int blen, 
									     		uint8_t *o_phex, 
									     		int hlen);

extern int joylink_thunderconfig_utils_hex2bytes(const uint8_t *phex,
											     int hex_len,
												 uint8_t *o_buf, 
												 int buf_len);
#ifdef  __cplusplus
}
#endif /*!__cplusplus*/
#endif /*!_JOYLINK_THUNDERCONFIG_UTILS_H_*/
