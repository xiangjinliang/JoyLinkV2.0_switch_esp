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
#include "esp_spiffs.h"
#include "esp_vfs_fat.h"

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

#if 1
/* 初始化SPI文件系统 */
int initvfs_Spiffs(void)
{
    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };

    printf("begin to mount or format filesystem..\n");

    
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            printf("Failed to mount or format filesystem\n");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            printf("Failed to find SPIFFS partition\n");
        } else {
            printf("Failed to initialize SPIFFS (%s)\n", esp_err_to_name(ret));
        }
        return;
    }
    
    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        printf("Failed to get SPIFFS partition information (%s)\n", esp_err_to_name(ret));
    } else {
        printf("Partition size: total: %d, used: %d\n", total, used);
    }

    printf("end to mount or format filesystem..\n");
    
}
#else


#define MOUNT_PATH "/spiflash"

static void initialize_filesystem()
{
    printf("begin to mount or fatfs filesystem..\n");

    static wl_handle_t wl_handle;
    const esp_vfs_fat_mount_config_t mount_config = {
        .max_files = 4,
        .format_if_mount_failed = true,
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE
    };
    esp_err_t err = esp_vfs_fat_spiflash_mount(MOUNT_PATH, "storage", &mount_config, &wl_handle);
    if (err != ESP_OK) {
        printf("Failed to mount FATFS (%s)\n", esp_err_to_name(err));
        return;
    }
    
    printf("end to mount or fatfs filesystem..\n");
}
#endif

//调用joylink主线程
extern int  joylink_main_start();
static void runJoylink(void *pvParameters)
{
   
    printf("test light task and wait.\n");
    
    waitWifiConnect();

    vTaskDelay(1000/ portTICK_PERIOD_MS);
    //initialize_filesystem();
    initvfs_Spiffs();

    /*
     *Start main loop
     */     
    printf("xiangjl start task begin...");   
    joylink_main_start();

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

    xTaskCreate(&runJoylink, "runJoylink", 20240, NULL, 5, NULL);
    
    xTaskCreate(&runPrintLocalIP, "runPrintLocalIP", 4096, NULL, 5, NULL);


}
