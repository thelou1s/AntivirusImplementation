/*
 * jni_utilities.c
 *
 *  Created on: Feb 18, 2013
 *      Author: cfpoon
 */

#include <unistd.h>
#include "jni_utilities.h"

#ifdef __cplusplus
extern "C"
{
#endif
void convertToUTF8(JNIEnv *env, jstring input, char** szResult)
{
	jboolean isCopy;
	const char * szConvert = (*env)->GetStringUTFChars(env, input, &isCopy);
	int size = strlen(szConvert);
	*szResult = realloc(NULL, size + 1);
	memset(*szResult, 0, size + 1);
	memcpy(*szResult, szConvert, size + 1);
	(*env)->ReleaseStringUTFChars(env, input, szConvert);
}

jobject NewInteger(JNIEnv* env, int value)
{
	jclass cls = (*env)->FindClass(env, "java/lang/Integer");
	if (!cls)
	{
		LOGE("Cannot find INTEGER class");
	}

	jmethodID methodID = (*env)->GetMethodID(env, cls, "<init>", "(I)V");
	if (!cls)
	{
		LOGE("Cannot find INTEGER constructor");
	}
	return (*env)->NewObject(env, cls, methodID, value);
}

#ifdef __cplusplus
}
#endif
