# Automatically generated build file. Do not edit.
COMPONENT_INCLUDES += $(PROJECT_PATH)/main/include
COMPONENT_LDFLAGS += -L$(BUILD_DIR_BASE)/main -lmain $(PROJECT_PATH)/main/lib/libjoylinksdk.a -lnewlib
COMPONENT_LINKER_DEPS += $(PROJECT_PATH)/main/lib/libjoylinksdk.a
COMPONENT_SUBMODULES += 
COMPONENT_LIBRARIES += main
component-main-build: 
