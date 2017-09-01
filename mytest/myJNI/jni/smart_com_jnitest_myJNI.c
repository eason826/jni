#include "smart_com_jnitest_myJNI.h"
#include "mytest.h"

JNIEXPORT jint JNICALL Java_smart_com_jnitest_myJNI_Add
  (JNIEnv *env, jobject obj, jint x, jint y)
  {
     return myadd(x,y);
  }
