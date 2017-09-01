LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_PACKAGE_NAME := myJNI
LOCAL_CERTIFICATE := platform

LOCAL_JNI_SHARED_LIBRARIES :=libmyjni
LOCAL_REQUIRED_MODULES := libmyjni

LOCAL_MODULE_PATH := $(TARGET_OUT_DATA_APPS)
include $(BUILD_PACKAGE)

include $(call all-makefiles-under, $(LOCAL_PATH))
