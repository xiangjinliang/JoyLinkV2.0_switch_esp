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

#ifndef _JOYLINK_RET_CODE_H_
#define _JOYLINK_RET_CODE_H_

#if defined(__QC_4010__) || defined(__OV_788__)
#else
#include <stdio.h>
#endif

typedef enum _bool_{
    E_BOOL_FAIL = 0,
    E_BOOL_TRUE = 1
}E_JL_BOOL;

typedef enum _ret_code{
    /*UI INTERFACE*/
    E_ERROR_JSON_ILLEGAL                    = -9001, //json_ctrl is not json
    E_ERROR_SDK_NO_MEMBER                   = -9002, //there is no "member" in json_ctrl
    E_ERROR_SDK_NO_MEMBER_TYPE              = -9003, //there is no "type" in member
    E_ERROR_SDK_NO_IN                       = -9004, //there is no "in" in json_ctrl
    E_ERROR_SDK_NO_SESSION_ID               = -9005, //there is no "in" in json_ctrl
    E_ERROR_SDK_NO_GUID                     = -9006, //there is no "guid" in json_ctrl
    E_ERROR_SDK_NO_DESTIP                   = -9007, //there is no "destIp" in json_ctrl
    E_ERROR_SDK_NO_SERVICE                  = -9008, //there is no "service" in json_ctrl
    E_ERROR_SDK_NO_MEMBER_NAME              = -9009, //there is no "name" in member
    E_ERROR_SDK_NO_MEMBER_ACCESS            = -9010, //there is no "access" in member
    E_ERROR_SDK_NO_IN_NAME                  = -9011, //there is no "name" in in args
    E_ERROR_SDK_NO_IN_TYPE                  = -9012, //there is no "type" in in args
    E_ERROR_SDK_NO_IN_LEN                   = -9013, //there is no "len" in in args
    E_ERROR_SDK_NO_IN_DATA                  = -9014, //there is no "data" in in args
    E_ERROR_SDK_DATA_LEN_NOT_MATCH          = -9015, //data and len not match
    E_ERROR_SDK_AY_DATA_LEN_ERROR           = -9016, //len error when type is "ay"
    E_ERROR_SDK_IN_TYPE_UNSUPPORT           = -9017, //type is not support
    E_ERROR_SDK_PARSE_JSON_CTRL_ERROR       = -9018, //parse json ctrl error
    E_ERROR_SDK_SESSION_ID_ILLEGAL          = -9019, //session id illegal
    E_ERROR_SDK_PACKAGE_OUT_ERROR           = -9019, //package out error

    /*PACKET*/
    E_ERROR_KEY_ERROR                       = -8001, //KEY

    /*SERVICE*/
    E_ERROR_SERVICE_OFFLINE                 = -7003,
    E_ERROR_SERVICE_UNKOWN_MEMBER    		= -7002, 
    E_ERROR_SERVICE_UNKOWN          		= -7001, //SERVICE
    
    /*APP*/
    E_ERROR_APP_LOCKED              		= -6002,
    E_ERROR_APP_BUSY                 		= -6001, //APP

    /*RPC*/
	E_ERROR_PARSE_CLOUD_DATA     			= -5081, //
	E_ERROR_CLOUD_SEND      				= -5080, //

	E_ERROR_DATA_PARSE      				= -5071, //
	E_ERROR_PACKET_REQUEST      			= -5070, //

	E_ERROR_SIGNAL_NO_HANDLER      			= -5065, //
	E_ERROR_SIGNAL_NO_FIND      			= -5064, //
	E_ERROR_SIGNAL_HAS_REGISTERED      		= -5063, //Signal has registered by other japp.
	E_ERROR_UNREGISTER_SIGNAL_NOLIST      	= -5062, //Signal list is NULL when unregister signal , please check out in param(session id) in the joylink_app_unregister_signal_handler_cb api.
	E_ERROR_REGISTER_SIGNAL_NOLIST      	= -5061, //Signal list is NULL when register signal, please check out in param(session id) in the joylink_app_register_signal_handler_cb api.
	E_ERROR_SIGNAL     						= -5060, //

	E_ERROR_UNMARSHAL_RESET_SIG      		= -5051, //In the process of unmarshalling it doesn't reset signature 
    E_ERROR_UNMARSHAL      		     		= -5050, //Joylink RPC unmarshl args  failed

	E_ERROR_MARSHAL_RESET_SIG 		 		= -5042, //In the process of marshalling it doesn't reset signature
    E_ERROR_MARSHAL      		 	 		= -5040, //Joylink RPC marshl args  failed
	
	E_ERROR_RPC_PROXY_OFFLINE		 		= -5022, //Joylink comsumer calls RPC, provider doesn't reply data because of some reasons , leading to recvfrom timeout.
	E_ERROR_RPC_PROXY_CALL			 		= -5021, //Joylink comsumer calls RPC, provider happens some error.Please get error message by calling api interface(joylink_get_error_msg).
	E_ERROR_RPC_PROXY      	         		= -5020, //Joylink comsumer happens some error.

	E_ERROR_RPC_ARGS_NOSIGNATURE    		= -5014, //It doesn't find signature in the handler
	E_ERROR_RPC_ARGS_NODATA      			= -5013, //Args data length is zero.  
    E_ERROR_RPC_ARGS_NOMEM      			= -5012, //RPC getting arg data buffer is too small.  
    E_ERROR_RPC_ARGS_NUM_NOMATCH       		= -5011, //Args num doesn't match the num in the handler.
    E_ERROR_RPC_ARGS      			 		= -5010, //RPC ARG ERROR
   
	E_ERROR_RPC_NO_USER_ERROR_MSG       	= -5002, //There isn't msg arg in the arg bucket.
    E_ERROR_RPC_NO_HANDLER_CALLBACK         = -5001, //There isn't callback entity in the handler.
    E_ERROR_RPC                      		= -5000, //
    
    /*TASK:-1300~-1399*/
    E_ERROR_TASK_NO_EANBLE           		= -1300, //TASK -- SESSION
    
    /*SESSION:-1200~-1299*/
    E_ERROR_SESSION_NO_FIND          		= -1201, //SES -- SESSION
    E_ERROR_SESSION_SERVER_NO_FIND   		= -1200, //SES -- SESSION
    
    /*MDNS:-1100~1199*/
    E_ERROR_MDNS             		        = -1100, //MDNS
    
    /*RUDP:-1000~-1099*/
    E_ERROR_RUDP_TIMEOUT             		= -1001, //RUDP
    E_ERROR_RUDP_PENDING             		= -1000, //RUDP
    
    /*IFTTT:-500~-599*/
    E_ERROR_IFTTT_OVERLOAD                  = -508,
    E_ERROR_IFTTT_NO_MATCH                  = -507,
    E_ERROR_IFTTT_DELETE                    = -506,
    E_ERROR_IFTTT_WRITE                     = -505,
    E_ERROR_IFTTT_READ                      = -504,
    E_ERROR_IFTTT_SETUP                     = -503,
    E_ERROR_IFTTT_CHECK                     = -502,
    E_ERROR_IFTTT_DUP                       = -501,
    E_ERROR_IFTTT_PARSE                     = -500,

    /*net:-200~-299*/
    E_ERROR_TCP_SEND_TO_CLOUD               = -200,

    /*sls:-100~-199*/
    E_ERROR_NO_FIND_SLS_DATA                = -100,

    /*General:-1~-99*/
    E_ERROR_CLOUD_NO_CONNECT                = -10,
    E_ERROR_GUID_UNKNOWN                    = -9, 
    E_ERROR_GUID_NO_FIND                    = -8, //GUID
    E_ERROR_SELECT_FAILED            		= -7,	 
    E_ERROR_RET_CODE                	 	= -6,	
    E_ERROR_EXIST                    		= -5,	  //EXIST	
    E_ERROR_NOEXIST                 		= -4,	  //NOEXIST
    E_ERROR_NOMEM           		 		= -3,	  //it hasn't enough memory in system
    E_ERROR_PARAM_INVAID             		= -2,	  //in or out params are invalid
    E_ERROR                          		= -1,	  //OK
    E_OK                             		= 0,
    E_ERROR_NULL
}E_JL_RETCODE;
#endif
