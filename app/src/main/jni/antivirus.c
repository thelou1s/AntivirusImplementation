#ifndef ANTIVIRUS_H__
#define ANTIVIRUS_H__

#include <jni.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <sys/types.h>

#include "mavapi_engine.h"
#include "mavapi_updater.h"
#include "jni_utilities.h"
#include "engine_info.h"

#ifdef __cplusplus
extern "C"
{
#endif

	JavaVM* gJVM = NULL;
	jobject gAntivirusObject = NULL;
	jclass gAntivirusClass = NULL;
	jmethodID gJavaScanCallbackMethodId = NULL;

	jclass gScannerCallbackDataClass = NULL;
	jmethodID gScannerCallbackDataAddMalwareInfoMethodId = NULL;
	jmethodID gScannerCallbackDataConstructorId = NULL;
	const char* ENGINE_FOLDER_NAME = "antivirus";

	const char* OLD_PRODUCT_CODE = "203";
	const char* PRODUCT_CODE = "60443";
	const int MAVAPI_VERSION_WITH_NEW_PRODUCT_CODE = 2;

	char* gOpeningArchiveName = "";

	char gTempPath[128] = {0};
	char gEnginePath[128] = {0};
	char gUpdatePath[128] = {0};
	volatile int gIsHalting = 0;

	int gScannerThreadId = 1;
	int gPrefixOption = 3;

	MAVAPI_FUNCS gMavapi;

	const char* getEnginePath()
	{
		return gEnginePath;
	}

	const char* getTempPath()
	{
		return gTempPath;
	}

	const char* getUpdatePath()
	{
		return gUpdatePath;
	}

	int getJniEnvironment(JNIEnv **env)
	{
		int result = (*gJVM)->GetEnv(gJVM, (void **) env, JNI_VERSION_1_6);
		if (result == JNI_EDETACHED)
		{
			LOGE("GetEnv: not attached");
		}
		else if (result == JNI_EVERSION)
		{
			LOGE("GetEnv: version not supported");
		}
		return result;
	}

	int scanCallback(MAVAPI_CALLBACK_DATA * cbData)
	{
		static jstring currentScanFilePath;
		int ret = 0;
		JNIEnv *env;
		int getEnvStat = 0;
		int result = 0;
		int isAttached = 0;

		if (cbData && (int)(cbData->user_data) == gScannerThreadId)
		{
			getEnvStat = getJniEnvironment(&env);
			if (getEnvStat == JNI_EDETACHED)
			{
				if ((result = (*gJVM)->AttachCurrentThread(gJVM, &env, NULL) != 0))
				{
					LOGE("Failed to attach");
				}
				else
				{
					isAttached = 1;
				}
			}
			switch (cbData->type)
			{
				case MAVAPI_CALLBACK_REPORT_FILE_STATUS:

				if (result == 0)
				{
					if (strcmp(cbData->callback_data.file_status_data->file_info.name, gOpeningArchiveName) == 0)
					{
						gOpeningArchiveName = "";
					}

					jstring filename = NULL;
					if (strlen(gOpeningArchiveName) > 0)
					{
						filename = (*env)->NewStringUTF(env, gOpeningArchiveName);
					}
					else
					{
						filename = (*env)->NewStringUTF(env, cbData->callback_data.file_status_data->file_info.name);
					}

                    jobject callbackData = NULL;

					if (cbData->callback_data.file_status_data->scan_answer != 0
							&& cbData->callback_data.file_status_data->scan_answer
							!= 4 && cbData->callback_data.file_status_data->malware_info.name)
					{
                        callbackData = (*env)->NewObject(env, gScannerCallbackDataClass,
                                gScannerCallbackDataConstructorId, filename, currentScanFilePath,
                                cbData->callback_data.pre_scan_data->file_info.level,
                                cbData->callback_data.pre_scan_data->file_info.type);

						if (!callbackData)
						{
							LOGE("Failed to get callbackData");
						}

						jstring malwareName = (*env)->NewStringUTF(env, cbData->callback_data.file_status_data->malware_info.name);
						jstring malwareAppFlags = (*env)->NewStringUTF(env,	cbData->callback_data.file_status_data->malware_info.app_flags);
						jstring malwareMessage = (*env)->NewStringUTF(env, cbData->callback_data.file_status_data->malware_info.message);
						jstring malwareType = (*env)->NewStringUTF(env,	cbData->callback_data.file_status_data->malware_info.type);

						jstring internalFilename = (*env)->NewStringUTF(env, cbData->callback_data.file_status_data->file_info.name);
						(*env)->CallVoidMethod(
						        env,
						        callbackData,
								gScannerCallbackDataAddMalwareInfoMethodId,
								internalFilename,
								currentScanFilePath,
								cbData->callback_data.file_status_data->file_info.level,
								cbData->callback_data.file_status_data->file_info.type,
								malwareName, malwareAppFlags, malwareMessage,
								malwareType);

						(*env)->DeleteLocalRef(env, malwareName);
						(*env)->DeleteLocalRef(env, malwareAppFlags);
						(*env)->DeleteLocalRef(env, malwareMessage);
						(*env)->DeleteLocalRef(env, malwareType);
						(*env)->DeleteLocalRef(env, internalFilename);
					}

					(*env)->CallVoidMethod(env, gAntivirusObject, gJavaScanCallbackMethodId, cbData->type, filename, callbackData);

					(*env)->DeleteLocalRef(env, filename);
					(*env)->DeleteLocalRef(env, callbackData);
				}

				break;
				case MAVAPI_CALLBACK_PRE_SCAN:
				if (result == 0)
				{
					LOGD("Scan callback - Pre-scanning for filename: [--%s - %d - %d --]",
							cbData->callback_data.pre_scan_data->file_info.name,
							cbData->callback_data.pre_scan_data->file_info.level,
							cbData->callback_data.pre_scan_data->file_info.type);
				}
				break;
				case MAVAPI_CALLBACK_REPORT_ERROR:
				if (result == 0)
				{
					LOGD("Scan callback - Scanning error code: [%i]", cbData->callback_data.error_data->code);
				}
				break;
				case MAVAPI_CALLBACK_ARCHIVE_OPEN:
				if (result == 0)
				{
					gOpeningArchiveName =
					cbData->callback_data.archive_open_data->file_info.name;
					LOGD("Scan callback - Open archive: [%s]", cbData->callback_data.archive_open_data->file_info.name);
				}
				break;
				case MAVAPI_CALLBACK_PROGRESS_REPORT:
				if (result == 0)
				{

					LOGD("Scan callback - Scanning progress: [%s]", cbData->callback_data.report_progress_data->message);
				}
				break;
				default:
				break;
			}

			if ((*env)->ExceptionCheck(env))
			{
				(*env)->ExceptionDescribe(env);
			}
			if (isAttached)
			{
				(*gJVM)->DetachCurrentThread(gJVM);
			}
		}
		else
		{
			ret = -1;
		}
		return ret;
	}

	jint JNI_OnLoad(JavaVM* vm, void* reserved)
	{
		gJVM = vm;

		return JNI_VERSION_1_6;
	}

	void Java_com_avira_antivirusimplementation_Antivirus_setEngineResourcePath(JNIEnv* env, jobject this, jstring enginePath, jstring libPath, jstring tempPath, jstring updatePath)
	{
		// Set enginePath
		char* szLibPath = NULL;
		char* szEnginePath = NULL;
		convertToUTF8(env, libPath, &szLibPath);
		convertToUTF8(env, enginePath, &szEnginePath);
		sprintf(gEnginePath, "%s/%s/", szLibPath, szEnginePath);
		free(szLibPath);
		free(szEnginePath);

		// Set tempPath
		char* szTempPath = NULL;
		convertToUTF8(env, tempPath, &szTempPath);
		sprintf(gTempPath, "%s", szTempPath);
		free(szTempPath);

		// Set updatePath
		char* szUpdatePath = NULL;
		convertToUTF8(env, updatePath, &szUpdatePath);
		sprintf(gUpdatePath, "%s", szUpdatePath);
		free(szUpdatePath);
	}

	jint Java_com_avira_antivirusimplementation_Antivirus_initialize(JNIEnv* env, jobject this)
	{
		return initialize_mavapi(&gMavapi);
	}

	void Java_com_avira_antivirusimplementation_Antivirus_setPrefixOption(JNIEnv* env, jobject this, jint prefixOption)
	{
		gPrefixOption = prefixOption;
	}

	void Java_com_avira_antivirusimplementation_Antivirus_loadJavaClassToJNI(JNIEnv* env, jobject this)
	{
		gAntivirusObject = (*env)->NewGlobalRef(env, this);
		// save refs for callback
		gAntivirusClass = (*env)->FindClass(env, "com/avira/antivirusimplementation/Antivirus");
		gAntivirusClass = (*env)->NewGlobalRef(env, gAntivirusClass);
		if (gAntivirusClass == NULL)
		{
			LOGE("Failed to find class - Antivirus");
		}

		gScannerCallbackDataClass = (*env)->FindClass(env, "com/avira/antivirusimplementation/ScannerCallback");
		gScannerCallbackDataClass = (*env)->NewGlobalRef(env, gScannerCallbackDataClass);
		if (gScannerCallbackDataClass == NULL)
		{
			LOGE("Failed to find class - ScannerCallbackData");
		}

		gScannerCallbackDataAddMalwareInfoMethodId = (*env)->GetMethodID(env, gScannerCallbackDataClass, "addMalwareInfo",
		        "(Ljava/lang/String;Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
		if (gScannerCallbackDataAddMalwareInfoMethodId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "addMalwareInfo");
		}

		gScannerCallbackDataConstructorId = (*env)->GetMethodID(env, gScannerCallbackDataClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;II)V");
		if (gScannerCallbackDataConstructorId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "init<>");
		}
	}

	jlong Java_com_avira_antivirusimplementation_Antivirus_registerScanner(JNIEnv* env, jobject this, jint mavapi_version_control)
	{
		LOGD(">>>>>>>>>> JNI Registered DemandScanner >>>>>>>>>>");

		gJavaScanCallbackMethodId = (*env)->GetMethodID(env, gAntivirusClass, "onScanCallback",
		        "(ILjava/lang/String;Lcom/avira/antivirusimplementation/ScannerCallback;)V");
		if (gJavaScanCallbackMethodId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "onScanCallback");
		}

		const char* USE_PRODUCT_CODE = PRODUCT_CODE;
		if (mavapi_version_control < MAVAPI_VERSION_WITH_NEW_PRODUCT_CODE)
		{
			USE_PRODUCT_CODE = OLD_PRODUCT_CODE;
		}

		LOGD(">>>>>>>>>> registerDemandScanner - USE_PRODUCT_CODE [%s]  >>>>>>>>>>", USE_PRODUCT_CODE);

		MAVAPI_FD fd = create_scan_context(&gMavapi, scanCallback,
		     1, // open archives
		     5, // depth level
		     (char *) USE_PRODUCT_CODE, gTempPath, gScannerThreadId, gPrefixOption);
		if (fd != NULL)
		{
			return (jlong) (uintptr_t) fd;
		}
		return 0;
	}

    jint Java_com_avira_antivirusimplementation_Antivirus_terminateScanner(JNIEnv* env, jobject this, jlong threadContextPointer)
    {
        return gMavapi.MAVAPI_release_instance((void*) (uintptr_t)&threadContextPointer);
    }

	jint Java_com_avira_antivirusimplementation_Antivirus_terminate(JNIEnv* env, jobject this, jlong threadContextPointer)
	{
		LOGD(">>>>>>>>>> JNI Terminated >>>>>>>>>>");
		int result;

		if(threadContextPointer != 0)
		{
			result = gMavapi.MAVAPI_release_instance((void*) (uintptr_t)&threadContextPointer);
			LOGD(">>>>>>>>>> releasing demand[%d] >>>>>>>>>>", result);
		}

		result = uninitialize_mavapi(&gMavapi);
		LOGD(">>>>>>>>>> uninit mavapi[%d] >>>>>>>>>>", result);
		return result;
	}

	jint Java_com_avira_antivirusimplementation_Antivirus_scan(JNIEnv* env, jobject this, jstring path, jlong threadContextPointer)
	{
		int isAttached = 0;
		MAVAPI_FD fd = (void*) (uintptr_t) threadContextPointer;
		jmethodID mid;
		int value = 0;
		char *scanPath = NULL;

		convertToUTF8(env, path, &scanPath);

		value = scan_file(&gMavapi, fd, scanPath);
		LOGD(">>>>>>>>>> [%s] >>>>>>>>>> status: [%d]", scanPath, value);
		free(scanPath);
		return value;
	}

	jint Java_com_avira_antivirusimplementation_Antivirus_abortScanning(JNIEnv* env, jobject this, jlong threadContextPointer)
	{
		LOGD(">>>>>>>>>> [%s] >>>>>>>>>>", "abortScanning");
		gIsHalting = 1;
		return scan_abort(&gMavapi, (void*) (uintptr_t) threadContextPointer);
	}

	jstring Java_com_avira_antivirusimplementation_Antivirus_getVDFVersion(JNIEnv* env, jobject this, jlong threadContextPointer)
	{
		MAVAPI_FD fd = (void*) (uintptr_t) threadContextPointer;

		MAVAPI_SIZE_T size = 128;
		MAVAPI_TCHAR *buffer = malloc(size * sizeof(MAVAPI_TCHAR));
		jstring result = NULL;

		int success = gMavapi.MAVAPI_get(&fd, MAVAPI_OPTION_VDF_VERSION, buffer, &size);
		if (success == MAVAPI_S_OK)
		{
			LOGD("!!!!!!!!!!!!!!!!!!!!!!Vdf version: %s", buffer);
			result = (*env)->NewStringUTF(env, buffer);
		}

		free(buffer);
		return result;
	}

	jstring Java_com_avira_antivirusimplementation_Antivirus_getVDFSignatureDate(JNIEnv* env, jobject this, jlong threadContextPointer)
	{
		MAVAPI_FD fd = (void*) (uintptr_t) threadContextPointer;

		MAVAPI_SIZE_T size = 128;
		MAVAPI_TCHAR *buffer = malloc(size * sizeof(MAVAPI_TCHAR));

		gMavapi.MAVAPI_get(&fd, MAVAPI_OPTION_VDF_DATE, buffer, &size);

		LOGD("!!!!!!!!!!!!!!!!!!!!!!Vdf signature date: %s", buffer);
		jstring result = (*env)->NewStringUTF(env, buffer);
		free(buffer);
		return result;
	}

	jstring Java_com_avira_antivirusimplementation_Antivirus_getEngineVersion(JNIEnv* env, jobject this, jlong threadContextPointer)
	{
		MAVAPI_FD fd = (void*) (uintptr_t) threadContextPointer;

		MAVAPI_SIZE_T size = 128;
		MAVAPI_TCHAR *buffer = malloc(size * sizeof(MAVAPI_TCHAR));

		gMavapi.MAVAPI_get(&fd, MAVAPI_OPTION_AVE_VERSION, buffer, &size);

		LOGD("!!!!!!!!!!!!!!!!!!!!!!Engine version: %s", buffer);
		jstring result = (*env)->NewStringUTF(env, buffer);
		free(buffer);
		return result;
	}

#ifdef __cplusplus
}
#endif

#endif
