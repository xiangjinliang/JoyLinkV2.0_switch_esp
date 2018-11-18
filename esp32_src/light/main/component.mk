#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)


#LIBC_PATH += $(COMPONENT_PATH)/lib/libjdmain.a
#LIBC_PATH += $(COMPONENT_PATH)/lib/libexample.a
#LIBC_PATH += $(COMPONENT_PATH)/lib/libjoylinksdk.a
#LIBC_PATH += $(COMPONENT_PATH)/lib/liblight.a
#LIBC_PATH += $(COMPONENT_PATH)/lib/libota.a
LIBC_PATH += $(COMPONENT_PATH)/lib/libjoylinksdk.a

COMPONENT_ADD_LDFLAGS += $(LIBC_PATH) -lnewlib

COMPONENT_ADD_LINKER_DEPS += $(LIBC_PATH) 