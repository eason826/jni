LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := mytest.c

LOCAL_MODULE    := mytest
LOCAL_MODULE_TAGS := optional

include $(BUILD_STATIC_LIBRARY)
