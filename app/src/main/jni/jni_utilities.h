/*
 * jni_utilities.h
 *
 *  Created on: Feb 13, 2013
 *      Author: cfpoon
 */

#ifndef JNI_UTILITIES_H_
#define JNI_UTILITIES_H_

#include <android/log.h>
#include <jni.h>

#define LOG_TAG "AVIRA_ANTIVIRUS"

#ifdef NDEBUG
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#define LOGF(...)
#else
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__)
#endif


void convertToUTF8(JNIEnv *env, jstring input, char** szResult);
jobject NewInteger(JNIEnv* env, int value);

#endif /* JNI_UTILITIES_H_ */
