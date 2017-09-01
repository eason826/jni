LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := mytest
LOCAL_SRC_FILES := lib/libmytest.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := smart_com_jnitest_myJNI.c

LOCAL_C_INCLUDES += $(LOCAL_PATH)/include      \
                    $(JNI_H_INCLUDE)

LOCAL_MODULE    := libmyjni
LOCAL_MODULE_TAGS := optional

LOCAL_STATIC_LIBRARIES:=mytest
include $(BUILD_SHARED_LIBRARY)
