#TOOL_CHAIN_PATH=$(HOME)/esp/xtensa-esp32-elf/bin
TOOL_CHAIN_PATH=/opt/esp32/crossTools/xtensa-esp32-elf/bin
#WORK_SPACE_PATH=~/esp/esp-idf-v2.0-rc1
#WORK_SPACE_PATH=/home/meng/esp/esp-idf-v2.0-rc1
WORK_SPACE_PATH=/home/jdwl/ESP32/IDF/esp-idf

CC=$(TOOL_CHAIN_PATH)/xtensa-esp32-elf-gcc
AR=$(TOOL_CHAIN_PATH)/xtensa-esp32-elf-ar
RANLIB=${TOOL_CHAIN_PATH}/xtensa-esp32-elf-ranlib

#LDFLAGS+=-L$(WORK_SPACE_PATH)/components/lwip/include/lwip
LDFLAGS+=-L$(WORK_SPACE_PATH)/components/esp32

CFLAGS+=-I$(WORK_SPACE_PATH)/components/lwip/include/lwip
CFLAGS+=-I$(WORK_SPACE_PATH)/components/lwip/include/lwip/port
CFLAGS+=-I$(WORK_SPACE_PATH)/components/esp32/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/nvs_flash/test_nvs_host
CFLAGS+=-I$(WORK_SPACE_PATH)/components/freertos/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/tcpip_adapter/include
#add by xjl
CFLAGS+=-I$(WORK_SPACE_PATH)/components/vfs/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/driver/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/soc/esp32/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/heap/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/soc/include
CFLAGS+=-I$(WORK_SPACE_PATH)/components/lwip/include/lwip/posix

CFLAGS+= -D CONFIG_TCP_OVERSIZE_QUARTER_MSS
CFLAGS+= -D__ESP32__
#by xjl
CFLAGS+= -D_POSIX_SOURCE   

CFLAGS+= -DCONFIG_FREERTOS_MAX_TASK_NAME_LEN=16
CFLAGS+=-ffunction-sections -fdata-sections -fstrict-volatile-bitfields -mlongcalls -nostdlib
CFLAGS+=-Wno-old-style-declaration

CFLAGS+=-Os
CFLAGS += -D_SAVE_FILE_

#CFLAGS+= -Wno-address
