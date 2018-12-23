#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#ifndef __ESP32__
#define __ESP32__
#endif
#include "../../../example/joylink_extern.h"

/**
 * Brief:
 * This test code shows how to configure gpio and how to use gpio interrupt.
 *outpu:继电器[G33 G32 G35 G34]，三色灯[G27 G26 G25]
 *input:按键[G15 G4 G19 G23]
 * Test:
 * Connect GPIO18 with GPIO4
 * Connect GPIO19 with GPIO5
 * Generate pulses on GPIO18/19, that triggers interrupt on GPIO4/5
 *
 */

/* IO define begin */
#define GPIO_MAX_DELAY 0xFFFFFFFF

#define RELAY_OUTPUT1 33
#define RELAY_OUTPUT2 32
#define RELAY_OUTPUT3 30
#define RELAY_OUTPUT4 31
#define KEY_IN1 15
#define KEY_IN2 4
#define KEY_IN3 19
#define KEY_IN4 23
#define LED_OUT1 27
#define LED_OUT2 26
#define LED_OUT3 25

#define GPIO_RELAY_OUTPUT_PIN_SEL ((1ULL<<RELAY_OUTPUT1)|(1ULL<<RELAY_OUTPUT2)|(1ULL<<RELAY_OUTPUT3)|(1ULL<<RELAY_OUTPUT4)|\
							(1ULL<<LED_OUT1)|(1ULL<<LED_OUT2)|(1ULL<<LED_OUT3))
#define GPIO_IN_PIN_SEL ((1ULL << KEY_IN1)|(1ULL << KEY_IN2)|(1ULL << KEY_IN3)|(1ULL << KEY_IN4))
#define ESP_INTR_FLAG_DEFAULT 0

/* IO define end */

static xQueueHandle key_in_evt_queue = NULL;

/* device ctrl begin*/
JDV2_SET_DEV_CTRL devCtrls = {0};

int dev_get_net_st(void)
{
	return 1;
}
void dev_set_connect_st(int state)
{
	if(2 == state)
	{
		gpio_set_level(LED_OUT1, 1);		
		gpio_set_level(LED_OUT2, 0);		
		gpio_set_level(LED_OUT3, 0);
	} else if(1 == state)
	{
		gpio_set_level(LED_OUT1, 0);		
		gpio_set_level(LED_OUT2, 1);		
		gpio_set_level(LED_OUT3, 0);
	}else
	{
		gpio_set_level(LED_OUT1, 0);		
		gpio_set_level(LED_OUT2, 0);		
		gpio_set_level(LED_OUT3, 1);
	}
}
int dev_user_data_get(user_dev_status_t *user_data)
{	
	int val1 = 0;
	val1 = gpio_get_level(RELAY_OUTPUT1);
	if (val1 == 1)
	{
		user_data->Power = 1;
	}
	else
	{
		user_data->Power = 0;
	}
	printf("get pin value(%d) by xjl.\n", val1);
	return 0;
	
}
int dev_user_data_set(user_dev_status_t *user_data)
{
	if (user_data->Power == 1)
	{
		gpio_set_level(RELAY_OUTPUT1, 1);
	}
	else
	{		
		gpio_set_level(RELAY_OUTPUT1, 0);
	}
	
	printf("set pin value(%d),by xjl.\n",user_data->Power);
	return 0;
}

void initdevCtrl(void)
{
	devCtrls.dev_get_net_st     = dev_get_net_st;
	devCtrls.dev_set_connect_st = dev_set_connect_st;
	devCtrls.dev_user_data_get  = dev_user_data_get;
	devCtrls.dev_user_data_set  = dev_user_data_set;
	initDevCtrl(&devCtrls);
	return;
}
/* device ctrl end*/

static void gpio_task_Input(void* arg)
{
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(key_in_evt_queue, &io_num, GPIO_MAX_DELAY)) {
			int val1 = gpio_get_level(io_num);
            printf("GPIO[%d] intr, val: %d\n", io_num, val1);
			switch(io_num)
			{
				case KEY_IN1:				
					if(gpio_get_level(RELAY_OUTPUT1))
						gpio_set_level(RELAY_OUTPUT1, 0);
					else						
						gpio_set_level(RELAY_OUTPUT1, 1);
					break;
				case KEY_IN2:
					if(gpio_get_level(RELAY_OUTPUT2))
						gpio_set_level(RELAY_OUTPUT2, 0);
					else						
						gpio_set_level(RELAY_OUTPUT2, 1);
					break;
				case KEY_IN3:
					if(gpio_get_level(RELAY_OUTPUT3))
						gpio_set_level(RELAY_OUTPUT3, 0);
					else						
						gpio_set_level(RELAY_OUTPUT3, 1);
					break;
				case KEY_IN4:
					if(gpio_get_level(RELAY_OUTPUT4))
						gpio_set_level(RELAY_OUTPUT4, 0);
					else						
						gpio_set_level(RELAY_OUTPUT4, 1);
					break;
				default:
					break;
			}
        }
    }
}

static void IRAM_ATTR key_isr_handler(void* arg)
{
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(key_in_evt_queue, &gpio_num, NULL);
}

void initOutputPin(void)
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = GPIO_RELAY_OUTPUT_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
	printf("init initOutputPin.by xjl.\n");

}

void initInPin(void)
{
    gpio_config_t io_conf;

    //interrupt of rising edge
    io_conf.intr_type = GPIO_PIN_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    io_conf.pin_bit_mask = GPIO_IN_PIN_SEL;
    //set as input mode    
    io_conf.mode = GPIO_MODE_INPUT;	
    io_conf.pull_down_en = 1;
    //enable pull-up mode
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

	//设置中断	
    //install gpio isr service
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(KEY_IN1, key_isr_handler, (void*) KEY_IN1);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(KEY_IN2, key_isr_handler, (void*) KEY_IN2);
    //remove isr handler for gpio number.
    //gpio_isr_handler_remove(GPIO_INPUT_IO_0);
    //hook isr handler for specific gpio pin again
    gpio_isr_handler_add(KEY_IN3, key_isr_handler, (void*) KEY_IN3);
    gpio_isr_handler_add(KEY_IN4, key_isr_handler, (void*) KEY_IN4);
	//change gpio intrrupt type for one pin
    //gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_ANYEDGE);
    
	printf("init initInPin.by xjl\n");

}
void initGpioCtrlDevice(void)
{
	printf("init initGpioCtrlDevice begin. by xjl\n");

	initOutputPin();
	initInPin();
	/* 初始化设备控制，连接至设备库 */
	initdevCtrl();
    //create a queue to handle gpio event from isr
    key_in_evt_queue = xQueueCreate(10, sizeof(uint32_t));
    //start gpio task
    xTaskCreate(gpio_task_Input, "gpio_task_example", 2048, NULL, 10, NULL);
	
	printf("init initGpioCtrlDevice end. by xjl\n");
	/*
    int cnt = 0;
    while(1) {
        printf("cnt: %d\n", cnt++);
        vTaskDelay(1000 / portTICK_RATE_MS);
        gpio_set_level(GPIO_OUTPUT_IO_0, cnt % 2);
        gpio_set_level(GPIO_OUTPUT_IO_1, cnt % 2);
    }
    */
}


