CC=gcc
AR=ar
RANLIB=gcc-ranlib

LDFLAGS=-fPIC -shared 
CFLAGS +=-fPIC 
CFLAGS += -D__LINUX_UB2__ 
CFLAGS += -D__LINUX__  
CFLAGS += -g 

#by xjl
#CFLAGS += -D_SAVE_FILE_

LIBS+= -lpthread

#CFLAGS +=-Wextra 
#CFLAGS += -Wall -Werror
CFLAGS +=-Wshadow -Wpointer-arith -Waggregate-return -Winline  -Wunreachable-code -Wcast-align -Wredundant-decls 
