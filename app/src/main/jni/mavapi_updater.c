/*
 * mavapi_updater.c
 *
 *  Created on: Feb 13, 2013
 *      Author: cfpoon
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include <stdbool.h>
#include <dlfcn.h>
#include "mavupdate.h"
#include "mavapi_updater.h"
#include "jni_utilities.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define AV_PATH_SEPARATOR_CHAR '/'
#define t_strrchr strrchr

const char* MAVAPI_UPDATER_LIB = "libmavupdate.so";
const char* PRELOADER_LIB = "libmavpreload.so";

//const MAVUPDATE_TCHAR PRODUCT_IDX[] = _T("android_mobile-int.idx"); // For Old VDF file use
const MAVUPDATE_TCHAR PRODUCT_IDX[] = _T("android-xmobile-int.idx"); // For New xVDF file use

char gServerName[128] = {0};
char gProxyName[128] = {0};
char gProxyPort[128] = {0};
char gBackUpPath[128] = {0};

static void * gUpdaterlib = NULL;
static void * gPreloaderlib = NULL;

OPTIONS gOptions = {0, 0, NULL};

MAVAPI_UPDATER_FUNCS gMavapiUpdater;
PRELOADER_FUNCS gPreloader;

int load_mavapi_updater(PMAVAPI_UPDATER_FUNCS mavapiUpdater, char *libPath) {

	if (gUpdaterlib != NULL)
	{
		dlclose(gUpdaterlib);
		gUpdaterlib = NULL;
	}

	gUpdaterlib = dlopen(libPath, RTLD_NOW);
	if (!gUpdaterlib)
	{
		LOGD("TEST_ENGINE: Loading libs1 [%p][%s]", gUpdaterlib, dlerror());
		return EXIT_FAILURE;
	}

	mavapiUpdater->mavupdate_get_version = dlsym(gUpdaterlib, "mavupdate_get_version");
	mavapiUpdater->mavupdate_initialize = dlsym(gUpdaterlib, "mavupdate_initialize");
	mavapiUpdater->mavupdate_uninitialize = dlsym(gUpdaterlib,
			"mavupdate_uninitialize");
	mavapiUpdater->mavupdate_set_callback = dlsym(gUpdaterlib,
			"mavupdate_set_callback");
	mavapiUpdater->mavupdate_set = dlsym(gUpdaterlib, "mavupdate_set");
	mavapiUpdater->mavupdate_get = dlsym(gUpdaterlib, "mavupdate_get");
	mavapiUpdater->mavupdate_check_for_updates = dlsym(gUpdaterlib,
			"mavupdate_check_for_updates");
	mavapiUpdater->mavupdate_download_files = dlsym(gUpdaterlib,
			"mavupdate_download_files");
	mavapiUpdater->mavupdate_install_files = dlsym(gUpdaterlib,
			"mavupdate_install_files");

	mavapiUpdater->isInitialized = 1;
	return EXIT_SUCCESS;
}

int load_preloader(PPRELOADER_FUNCS preloader, char *libPath) {

	if (gPreloaderlib != NULL)
	{
		dlclose(gPreloaderlib);
		gPreloaderlib = NULL;
	}

	gPreloaderlib = dlopen(libPath, RTLD_NOW);

	if (!gPreloaderlib)
	{
		LOGE("TEST_ENGINE: preloading libs1 [%p][%s]", gPreloaderlib, dlerror());
		return EXIT_FAILURE;
	}

	preloader->load = dlsym(gPreloaderlib, "preload");
	preloader->unload = dlsym(gPreloaderlib, "unload");

	if (!preloader->load || !preloader->unload) {
		LOGE(
				"TEST_ENGINE: Failed to obtain function pointer [%p][%s]", gPreloaderlib, dlerror());
		return EXIT_FAILURE;
	}

	preloader->isInitialized = 1;
	return EXIT_SUCCESS;
}

MAVUPDATE_TCHAR *get_filename_from_path(const MAVUPDATE_TCHAR *path) {
	MAVUPDATE_TCHAR* ptr = t_strrchr(path, AV_PATH_SEPARATOR_CHAR);
	if (ptr != NULL)
	ptr++;
	return ptr;
}

void show_progress(const MAVUPDATE_TCHAR *source, const MAVUPDATE_TCHAR *destination,
		size_t completedSize, size_t totalSize) {
	int i = 0;

	if (source != NULL && destination != NULL && totalSize > 0) {
		LOGD(
				"Downloading file: \x1b[32m%s\x1b[0m Completed: [\x1b[33m%3.2f%%\x1b[35m ", get_filename_from_path(source), (double)(completedSize * 100 / totalSize));
		for (i = 0; i < completedSize * 100 / totalSize;) {
			printf("=");
			i += 5;
		}
		for (; i < 100;) {
			printf(" ");
			i += 5;
		}
		if ((completedSize % totalSize) == 0) {
			printf("\x1b[0m]\n");
		} else {
			printf("\x1b[0m]\r");
		}
	}
}

MAVUPDATE_CALLBACK_RET main_callback(MAVUPDATE_CALLBACK callbackId,
		const void *callbackData, void *userData) {
	MAVUPDATE_CDATA_DOWNLOAD_FILE *downloadDataPtr;
	MAVUPDATE_CDATA_LOG *logDataPtr;
	FILE *logFile = NULL;
	OPTIONS *options;
	switch (callbackId) {
		case MAVUPDATE_CALLBACK_DOWNLOAD_FILE:
		downloadDataPtr = (MAVUPDATE_CDATA_DOWNLOAD_FILE *) callbackData;

		if (downloadDataPtr != NULL && userData != NULL) {
			options = (OPTIONS *) userData;
			if (options->show_progress_flag != 0) {
				show_progress(downloadDataPtr->src, downloadDataPtr->dest,
						downloadDataPtr->completed_size,
						downloadDataPtr->total_size);
			}
		}
		break;
		case MAVUPDATE_CALLBACK_LOG:
		logDataPtr = (MAVUPDATE_CDATA_LOG *) callbackData;
		if (logDataPtr != NULL && userData != NULL) {
			options = (OPTIONS *) userData;
			if (options->log_filename == NULL)
			{
				LOGD(logDataPtr->message, logDataPtr->level, stdout);
			}
			else
			{
				logFile = fopen(options->log_filename, "a+");
				if(logFile != NULL)
				{
					LOGD(logDataPtr->message, logDataPtr->level, logFile);
					fclose(logFile);
				}
			}
		}
		default:
		break;
	}
	return 0;
}

void display_result(MAVUPDATE_RET result)
{
	switch (result)
	{
		case MAVUPDATE_E_CHECK_DOWNLOAD_SRVS_DATA:
		LOGD("Empty server string ! \n");
		break;
		case MAVUPDATE_E_DOWNLOAD_MANAGER_CURL_DOWNLOAD:
		LOGD("Unable to download from specified location\n");
		break;
		case MAVUPDATE_E_CHECK_PRODUCT_FILE_DATA:
		LOGD("No product file specified\n");
		break;
		case MAVUPDATE_E_UNKNOWN:
		LOGD("Temporary directory not specified \n");
		break;
		case MAVUPDATE_S_OK:
		LOGD("Success !\n");
		break;
		case MAVUPDATE_E_LICENSE_CHECK:
		LOGD("Licence check error \n");
		break;
		default:
		LOGD("Error code: %d\n", result);
	}
}

int mavapi_updater_update()
{
	MAVUPDATE_RET result = MAVUPDATE_S_OK;
	int RESULT_NO_UPDATES = -1;
	int updateAvailable = 0;

	LOGD("Checking for updates: ");

	result = gMavapiUpdater.mavupdate_check_for_updates(&updateAvailable);

	LOGD("Update-check result [%d]: ", result);
	display_result(result);

	if(result == MAVUPDATE_S_OK)
	{
		if (updateAvailable == 1)
		{
			LOGD("Updates available\n");
			if (result == MAVUPDATE_S_OK && gOptions.check_if_upd_avl_flag == 0)
			{
				LOGD("Downloading: ");
				result = gMavapiUpdater.mavupdate_download_files();
				display_result(result);
			}
		}
		else
		{
			LOGD("No updates available\n");
			result = RESULT_NO_UPDATES;
		}
	}

	return result;
}

jint Java_com_avira_antivirusimplementation_Updater_initialize(JNIEnv* env,
		jobject this)
{
	MAVUPDATE_RET result = 0;
	MAVUPDATE_INIT init;

	LOGD(">>>>>>>>>>>> mavapi_updater_initialize >>>>>>>>>>>>");
	const char *enginePath = (const char *) getEnginePath();

	LOGD(">>>>>>>>>>>> mavapi_updater_initialize - enginePath [%s]>>>>>>>>>>>>", enginePath);

	PPRELOADER_FUNCS preloader = &gPreloader;
	if (preloader->isInitialized != 1)
	{
		int preloaderPathLength = strlen(enginePath) + strlen(PRELOADER_LIB)
		+ 1;
		char *preloaderPath = malloc(preloaderPathLength);
		memset(preloaderPath, 0, preloaderPathLength);
		sprintf(preloaderPath, "%s%s", enginePath, PRELOADER_LIB);

		LOGD(">>>>>>>>>>>> mavapi_updater_initialize - Preloader [%s]>>>>>>>>>>>>", preloaderPath);
		if (load_preloader(preloader, preloaderPath) == EXIT_SUCCESS)
		{
			LOGD(">>>>>>>>>>>> mavapi_updater_initialize - Engine path [%s]>>>>>>>>>>>>", enginePath);
			int preloadResult = preloader->load(enginePath);
			LOGD(">>>>>>>>>>>> mavapi_updater_initialize - Preloader result [%d]>>>>>>>>>>>>", preloadResult);
		}
		free(preloaderPath);
	}

	PMAVAPI_UPDATER_FUNCS mavapi = &gMavapiUpdater;
	if (mavapi->isInitialized != 1)
	{
		int updaterLibPathLength = strlen(enginePath) + strlen(MAVAPI_UPDATER_LIB)
		+ 1;
		char *updaterPath = malloc(updaterLibPathLength);
		memset(updaterPath, 0, updaterLibPathLength);
		sprintf(updaterPath, "%s%s", enginePath, MAVAPI_UPDATER_LIB);

		LOGD(">>>>>>>>>>>> mavapi_updater_initialize - Loading Updater library [%s]>>>>>>>>>>>>", updaterPath);

		load_mavapi_updater(mavapi, updaterPath);
		free(updaterPath);
	}

	memset(&init, 0, sizeof(MAVUPDATE_INIT));
	result |= mavapi->mavupdate_initialize(&init);
	result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_INSTALL_DIR, enginePath);
	result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_LICENSE_DIR, enginePath);
	result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_LICENSE_CHECK, _T("1"));
	result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_TEMP_DIR, (const char *) getUpdatePath());

	if(strlen(gBackUpPath) != 0)
	{
		LOGD(" !!!!!!!!!!!!!!Backup path: %s", gBackUpPath);
		result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_BACKUP_DIR, gBackUpPath);
	}

	if(strlen(gServerName) != 0)
	{
		LOGD(" !!!!!!!!!!!!!!!!!!!!!!!!! %s", gServerName);
		result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_SRVS_INTERNET, gServerName);
		LOGD(" !!!!!!!!!!!!!!!!!!!!!!!!!MAVUPDATE_OPTION_SRVS_INTERNET result: %d", result);
	}
	if(strlen(gProxyName) != 0)
	{
		result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_PROXY_HOST,
				gProxyName);
	}
	if(strlen(gProxyPort) != 0)
	{
		result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_PROXY_PORT, gProxyPort);
	}

	LOGD(">>>>>>>>>>>> mavapi_updater_initialize - Product IDX = %s >>>>>>>>>>>>", PRODUCT_IDX);

	result |= mavapi->mavupdate_set(MAVUPDATE_OPTION_PRODUCT_FILE, PRODUCT_IDX);
	result |= mavapi->mavupdate_set_callback(&main_callback, &gOptions);

	return result;
}

void Java_com_avira_antivirusimplementation_Updater_uninitialize(JNIEnv* env,
		jobject this)
{
	MAVUPDATE_RET result = gMavapiUpdater.mavupdate_uninitialize();

	if (result == MAVUPDATE_S_OK)
	{
		gMavapiUpdater.isInitialized = 0;
	}

	LOGD(">>>>>>>>>>>> mavupdate_uninitialize - result = %d", result);

	gPreloader.unload();
	gPreloader.isInitialized = 0;
}

void Java_com_avira_antivirusimplementation_Updater_setBackUpPath(JNIEnv* env,
		jobject this, jstring backupPath)
{
	if(strlen(gBackUpPath)==0)
	{
		char* szBackUpPath = NULL;
		convertToUTF8(env, backupPath, &szBackUpPath);
		sprintf(gBackUpPath, "%s", szBackUpPath);
		free(szBackUpPath);
	}
}

void Java_com_avira_antivirusimplementation_Updater_setServerSettings(JNIEnv* env,
		jobject this, jobject configs)
{
	static jclass sUpdateServerConfiguration= NULL;
	static jmethodID sGetServerNameMethodId = NULL;
	static jmethodID sGetProxyNameMethodId = NULL;
	static jmethodID sGetProxyPortMethodId = NULL;

	if(sUpdateServerConfiguration == NULL)
	{
		sUpdateServerConfiguration = (*env)->FindClass(env, "com/avira/android/antivirus/UpdateServerConfiguration");
		sUpdateServerConfiguration = (*env)->NewGlobalRef(env, sUpdateServerConfiguration);
		if (sUpdateServerConfiguration == NULL)
		{
			LOGE("Failed to find class - UpdateServerConfiguration");
		}

		sGetServerNameMethodId = (*env)->GetMethodID(env, sUpdateServerConfiguration, "getUpdateServer",
						"()Ljava/lang/String;");
		if (sGetServerNameMethodId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "getServerNameMethodId");
		}

		sGetProxyNameMethodId = (*env)->GetMethodID(env, sUpdateServerConfiguration, "getProxyServer",
						"()Ljava/lang/String;");
		if (sGetProxyNameMethodId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "getProxyNameMethodId");
		}

		sGetProxyPortMethodId = (*env)->GetMethodID(env, sUpdateServerConfiguration, "getProxyPort",
						"()Ljava/lang/String;");
		if (sGetProxyPortMethodId == NULL)
		{
			LOGE("Unable to get method ref: [%s]", "getProxyPortMethodId");
		}
	}

	jstring server = (*env)->CallObjectMethod(env, configs, sGetServerNameMethodId);
	jstring proxy = (*env)->CallObjectMethod(env, configs, sGetProxyNameMethodId);
	jstring proxyPort = (*env)->CallObjectMethod(env, configs, sGetProxyPortMethodId);

	char* szServerName = NULL;
	convertToUTF8(env, server, &szServerName);
	sprintf(gServerName, "%s", szServerName);
	free(szServerName);

	char* szProxyName = NULL;
	convertToUTF8(env, proxy, &szProxyName);
	sprintf(gProxyName, "%s", szProxyName);
	free(szProxyName);

	char* szProxyPort = NULL;
	convertToUTF8(env, proxyPort, &szProxyPort);
	sprintf(gProxyPort, "%s", szProxyPort);
	free(szProxyPort);

	(*env)->DeleteLocalRef(env, server);
	(*env)->DeleteLocalRef(env, proxy);
	(*env)->DeleteLocalRef(env, proxyPort);
}

jint Java_com_avira_antivirusimplementation_Updater_downloadUpdate(JNIEnv* env,
		jobject this)
{
	return mavapi_updater_update();
}

jint Java_com_avira_antivirusimplementation_Updater_installUpdate(JNIEnv* env,
		jobject this)
{
	MAVUPDATE_RET result;
	LOGD("Installing: ");
	result = gMavapiUpdater.mavupdate_install_files();
	display_result(result);

	return result;
}

#ifdef __cplusplus
}
#endif

