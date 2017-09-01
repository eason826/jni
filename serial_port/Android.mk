LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := SerialPort
LOCAL_CERTIFICATE := platform

LOCAL_JNI_SHARED_LIBRARIES :=libserial_port
LOCAL_REQUIRED_MODULES := libserial_port 
include $(BUILD_PACKAGE)   

######Build Serial Port JNI shared library#############
include $(CLEAR_VARS)

LOCAL_SRC_FILES := jni/SerialPort.c

LOCAL_C_INCLUDES +=$(JNI_H_INCLUDE)

LOCAL_LDLIBS    := -llog

LOCAL_MODULE    := libserial_port
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
