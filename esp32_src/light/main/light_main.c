/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "debug_def.h"
#include "lwip/sockets.h"
#include "tcpip_adapter.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "wifi_init.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

//jd SDK
#if defined(__OV_788__)
#include <stdint.h>
#else
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#endif

#ifdef __LINUX_UB2__
#include <unistd.h>
#include <pthread.h>

#ifndef __ANDROID__
#include <ifaddrs.h>
#endif

#include <netdb.h>
#endif

#include "joylink.h"
#include "joylink_utils.h"
#include "joylink_sdk.h"
#include "joylink_task.h"

void joylink_auto_test(char *sv_name)
{ 
    sv_name = sv_name;
}

void 
joylink_task_test_cb(jl_list_head_t *lh, jl_task_mg_t *pmg)
{    
#ifdef _GATEWAY_PROC_

#else
    //joylink_test_thread_comm();
    //joylink_ui_test();
#endif

#ifdef GATEWAY_SQLITE
    /*joylink_sql_test();*/
#endif
#ifdef _TEST_LOCK_
    /*joylink_lock_ctrl();*/
#endif
    /*char v1, v2, v3;*/
    /*joylink_util_get_vermber(&v1, &v2, &v3);*/
    /*joylink_log_info("joylink version:%d.%d.%d :hexv:0X%x", v1, v2, v3, ((v1 << 8) | v2) );*/

    // joylink_test_ui_thread_test();
    /*joylink_ifttt_test();*/
    joylink_auto_test("com.joylink.light");
    // joylink_test_create_session_key();
    // joylink_about_test();
    // joylink_test_thunderconfig();

    /*long tv = joylink_app_get_dev_time();*/
    
    /*joylink_app_set_dev_time(tv);*/

    // joylink_test_service_config();
#ifdef _PAIR_ 
/*#ifndef __ANDROID__*/
#ifdef _DEBUG_PROXY_
#endif
#endif

	/*char guid[JL_MAX_LEN_GUID] = {0};*/
	/*if(E_OK != joylink_app_get_self_guid(guid)){*/
		/*joylink_log_error("guid is null");*/
	/*}*/
    /*char *properties = joylink_package_all_pro(); */

    /*joylink_cloud_gateway_report_snapshot(guid, "com.joylink.light", properties);*/
    
    /*if(NULL != properties){*/
        /*joylink_util_free(properties);*/
    /*}*/
}

int joylink_task_test()
{
   jl_task_mg_t tmg;
   jl_task_data_t tdata;

   memset(&tmg, 0, sizeof(jl_task_mg_t));
   memset(&tdata, 0, sizeof(jl_task_data_t));
   tmg.ttl = JL_MAX_TTL;

   joylink_task_add(&tmg, &tdata, joylink_task_test_cb, NULL);
   return E_OK;
}

//调用joylink主线程
extern int  joylink_main_start();
static void runJoylink(void *pvParameters)
{
   
    printf("test light task and wait.\n");
    
    waitWifiConnect();

    vTaskDelay(1000/ portTICK_PERIOD_MS);


    /*
     *Start main loop
     */     
    printf("xiangjl start task begin...");   
    joylink_main_start();

    
    #if 0
    int once = 0;
    while(1){
        
        joylink_main_loop();
        /*
         *Start a test task.
         */
        if(!once){
            once = 1;
            //joylink_task_test();
        }
        vTaskDelay(100);
    };

    joylink_main_finit();
    #endif
}
static void runPrintLocalIP(void *pvParameters)
{
    tcpip_adapter_ip_info_t ip;
    memset(&ip, 0, sizeof(tcpip_adapter_ip_info_t));

    while(1){
        
        vTaskDelay(50000 / portTICK_PERIOD_MS);

        tcpip_adapter_get_ip_info(ESP_IF_WIFI_STA, &ip);
        ESP_LOGI("test", "IP:"IPSTR, IP2STR(&ip.ip));
        //ESP_LOGI("test", "MASK:"IPSTR, IP2STR(&ip.netmask));
        //ESP_LOGI("test", "GW:"IPSTR, IP2STR(&ip.gw));
    }
}


void app_main()
{
#if 0
    printf("Hello world!\n");
    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();
#endif
    printf("main task init...\n");

    initialise_wifi();

    xTaskCreate(&runJoylink, "runJoylink", 10240, NULL, 5, NULL);
    
    xTaskCreate(&runPrintLocalIP, "runPrintLocalIP", 4096, NULL, 5, NULL);


}
