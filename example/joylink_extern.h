#ifndef _JOYLINK_EXTERN_H_
#define _JOYLINK_EXTERN_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#include "joylink.h"

/*
 * user set
 */
#define JLP_VERSION  1
#define JLP_MAC "27:50:40:30:20:99"
/*
 * Create dev and get the index from developer center
 */
#if 0
#define JLP_DEV_TYPE	E_JLDEV_TYPE_NORMAL
#define JLP_LAN_CTRL	E_LAN_CTRL_ENABLE
#define JLP_CMD_TYPE	E_CMD_TYPE_LUA_SCRIPT

#define JLP_UUID "87B580" 
#define IDT_CLOUD_PUB_KEY "0241A5170B0299294D39B0676D3D85BE732EE3EC664A0DCFA43C871A0D85192371"
#endif

#define JLP_DEV_TYPE	E_JLDEV_TYPE_NORMAL
#define JLP_LAN_CTRL	E_LAN_CTRL_ENABLE
#define JLP_CMD_TYPE	E_CMD_TYPE_LUA_SCRIPT

#define JLP_UUID "D06C8B" 
#define IDT_CLOUD_PUB_KEY "032CB17798F78720FFE154D80FDB77F00654CA761EFBE187FF445EBE916D91A4B7"
//#define JLP_UUID "FDC88B" //test_2
//#define IDT_CLOUD_PUB_KEY "0366A746D4C5CDDD6A8AA58EC51BE5E57A3E91DEB0E062ED4B4903399EBCE3FE14"
//for test2
//#define JLP_UUID "FDC88B" //test_2
//#define IDT_CLOUD_PUB_KEY "0366A746D4C5CDDD6A8AA58EC51BE5E57A3E91DEB0E062ED4B4903399EBCE3FE14"
//#define JLP_UUID "55A484" //test_2
//#define IDT_CLOUD_PUB_KEY "03B637049598B1F7A17E9242C0802862806C601CB613C749501CD778C0C97E152E"

typedef struct __jdV2SetDevCtrl{
	int (*dev_get_net_st)(void);	
	void (*dev_set_connect_st)(int state);
	int (*dev_user_data_get)(void *user_data);	
	int (*dev_user_data_set)(void *user_data);
}JDV2_SET_DEV_CTRL;
void initDevCtrl(JDV2_SET_DEV_CTRL *devCtrl);

#define USER_DATA_POWER   "Power"

typedef struct _user_dev_status_t {
    int Power;
} user_dev_status_t;

#ifdef __cplusplus
}
#endif

#endif

