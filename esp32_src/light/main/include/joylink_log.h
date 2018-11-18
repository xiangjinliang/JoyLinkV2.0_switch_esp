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

#ifndef __JOYLINK_LOG_H__
#define __JOYLINK_LOG_H__

#ifdef __LINUX_UB2__
#include <pthread.h>
#include <sys/types.h>
#endif

#if defined(__QC_4010__) || defined(__OV_788__)
#else
#include <stdio.h>
#endif
#if defined(__OV_788__)
#else
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include "joylink_utils.h"
#endif

#ifndef __MTK_7687__
//#include <dirent.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#define JL_LOG_LEVEL_FATAL      (0)
#define JL_LOG_LEVEL_NOTICE     (1)
#define JL_LOG_LEVEL_INFO       (2)
#define JL_LOG_LEVEL_ERROR      (3)
#define JL_LOG_LEVEL_WARN       (4)
#define JL_LOG_LEVEL_DEBUG      (5)

extern E_JL_RETCODE
joylink_net_log_send(char *buff, int32_t size);

extern void
joylink_net_log_buff_clean();

extern char *
joylink_net_log_buff();

#define Black   0;30
#define Red     0;31
#define Green   0;32
#define Brown   0;33
#define Blue    0;34
#define Purple  0;35
#define Cyan    0;36

#define JL_LOG_LEVEL  JL_LOG_LEVEL_DEBUG

//#define JL_LOG_LEVEL  JL_LOG_LEVEL_ERROR

#if defined(__ANDROID__)
#include <android/log.h>
#define TAG_LOG "JOYLINK"

//------------------ android log -----------------
#define joylink_log_debug(format, ...)  do {if (JL_LOG_LEVEL >= JL_LOG_LEVEL_DEBUG) {__android_log_print(ANDROID_LOG_DEBUG, TAG_LOG, "[Debug]: %s, %s, %d\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);}}while(0)
#define joylink_log_warn(format, ...)  do {if (JL_LOG_LEVEL >= JL_LOG_LEVEL_WARN) {__android_log_print(ANDROID_LOG_WARN, TAG_LOG, "[Warn]: %s, %s, %d\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);}}while(0)
#define joylink_log_error(format, ...)  do {if (JL_LOG_LEVEL >= JL_LOG_LEVEL_ERROR)  {__android_log_print(ANDROID_LOG_ERROR, TAG_LOG, "[Error]: %s, %s, %d\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);}}while(0)
#define joylink_log_info(format, ...)  do {if (JL_LOG_LEVEL >= JL_LOG_LEVEL_DEBUG) {__android_log_print(ANDROID_LOG_DEBUG, TAG_LOG, "[Info]: %s, %s, %d\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);}}while(0)


#define joylink_log_fatal(format, ...) do{}while(0)
#define joylink_log_notice(format, ...) do{}while(0)
#define joylink_log_printf(format, ...) do{}while(0)

#elif defined(__LINUX__) || defined(__ESP32__) ||defined(__MTK_7687__) || defined(__IOS__) || defined(__MICOKIT_3166__) || defined(__MW300__) || defined(__QC_4010__) || defined(__QC_4531__) || defined(__REALTEK_8711__) || defined(__OV_788__)

#if defined(__MICOKIT_3166_LIB__) || defined(__MW300__) || defined(__QC_4010__) || defined(__QC_4531__) || defined(__REALTEK_8711__) || defined(__OV_788__) || defined(__MICOKIT_3166__)

//----------------- thin log start ---------------------------
#define joylink_log_fatal(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_FATAL){\
            printf("\033[0;31m[FATAL][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_notice(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_NOTICE){\
            printf("\033[0;36m[NOTICE][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
            char buff[1024 * 5] = {0}; \
            sprintf(buff, "\033[0;36m[NOTICE][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("-------%s\n", buff);\
        }\
    }while(0)

#define joylink_log_info(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_INFO){\
            printf("\033[1;36m[INFO][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_error(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_ERROR){\
            printf("\033[0;31m[ERROR][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_warn(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_WARN){\
            printf("\033[1;33m[WARN][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_debug(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_DEBUG){\
            printf("\033[1;32m[DEBUG][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_printf(format, ...) \
    do{\
        printf(format, ##__VA_ARGS__);\
    }while(0)

//----------------- thin log end ---------------------------
#else 

//----------------- net log start ---------------------------
#define joylink_log_fatal(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_FATAL){\
            printf("\033[0;31m[FATAL][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
        }\
    }while(0)

#define joylink_log_notice(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_NOTICE){\
            printf("\033[0;36m[NOTICE][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
            if(joylink_net_log_buff() != NULL){\
                joylink_net_log_buff_clean();\
                sprintf(joylink_net_log_buff(), "\033[0;36m[NOTICE][%s][%s][%d]\r\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
            }\
        }\
    }while(0)
#define joylink_log_info(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_INFO){\
            printf("\033[1;36m[INFO][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
            if(joylink_net_log_buff() != NULL){\
                joylink_net_log_buff_clean();\
                sprintf(joylink_net_log_buff(), "\033[1;36m[INFO][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
            }\
        }\
    }while(0)
#define joylink_log_error(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_ERROR){\
            printf("\033[0;31m[ERROR][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
            if(joylink_net_log_buff() != NULL){\
                joylink_net_log_buff_clean();\
                sprintf(joylink_net_log_buff(), "\033[0;31m[ERROR][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
            }\
        }\
    }while(0)
#define joylink_log_warn(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_WARN){\
            printf("\033[1;33m[WARN][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
            if(joylink_net_log_buff() != NULL){\
                joylink_net_log_buff_clean();\
                sprintf(joylink_net_log_buff(), "\033[1;33m[WARN][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
            }\
        }\
    }while(0)
#define joylink_log_debug(format, ...) \
    do{\
        if(JL_LOG_LEVEL >= JL_LOG_LEVEL_DEBUG){\
            printf("\033[1;32m[DEBUG][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
            fflush(stdout);\
            printf("\033[0m"); \
            if(joylink_net_log_buff() != NULL){\
                joylink_net_log_buff_clean();\
                sprintf(joylink_net_log_buff(), "\033[1;32m[DEBUG][%s][%s][%d]\n" format "\r\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__);\
                joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
            }\
        }\
    }while(0)
#define joylink_log_printf(format, ...) \
    do{\
        printf(format, ##__VA_ARGS__);\
        fflush(stdout);\
        if(joylink_net_log_buff() != NULL){\
            joylink_net_log_buff_clean();\
            sprintf(joylink_net_log_buff(), format, ##__VA_ARGS__);\
            joylink_net_log_send(joylink_net_log_buff(), strlen(joylink_net_log_buff()) + 1);\
        }\
    }while(0)

#endif
//----------------- net log start ---------------------------

#endif 

#define LOG_ERROR_RET(format, ...) \
    do{\
        joylink_log_error(format, ##__VA_ARGS__);\
        goto RET;\
    }while(0)

#define LOG_ERROR_EXIT(format, ...) \
    do{\
        joylink_log_debug(format, ##__VA_ARGS__);\
    }while(0)

#define LOG_OK_RET(format, ...) \
    do{\
        joylink_log_debug(format, ##__VA_ARGS__);\
        goto RET;\
    }while(0)

#define LOG_WARN_RET(format, ...) \
    do{\
        joylink_log_warn(format, ##__VA_ARGS__);\
        goto RET;\
    }while(0)

#define LOG_PARAM_ERROR_RET()\
    do{\
        joylink_log_error("param error");\
        return E_ERROR_PARAM_INVAID; \
    }while(0)

#define LOG_PARAM_ERROR_NULL()\
    do{\
        joylink_log_error("param error");\
        return NULL; \
    }while(0)
    
#define LOG_ERROR_OCCUR_RET() \
	do{\
		joylink_log_error("An error has occurred, code run at [%d] line in [%s] file", __LINE__, __FILE__);\
		goto RET;\
	}while(0)
	
#define LOG_MAKE_ERRORNO_RET(ret_code) \
	do{\
		ret = ret_code;\
		joylink_log_error("%s", (char *)joylink_util_ret_msg_get(ret_code));\
		goto RET;\
	}while(0)

#ifdef __cplusplus
}
#endif

#endif /* __LOGGING_H__ */
