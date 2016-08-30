/*
 * mavapi_engine.c
 *
 *  Created on: Feb 18, 2013
 *      Author: cfpoon
 */
#include <dlfcn.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include "mavapi_engine.h"
#include "jni_utilities.h"
#include "engine_info.h"

#define DISABLE_PUA_AND_ADWARE_PREFIX_SCANNING 0
#define PUA_PREFIX_SCANNING 1
#define ADWARE_PREFIX_SCANNING 2
#define PUA_AND_ADWARE_PREFIX_SCANNING 3

#ifdef __cplusplus
extern "C"
{
#endif

const char* MAVAPI_LIB = "libmavapi.so";
static void * gMavapiLib = NULL;

void debug_log_callback(MAVAPI_LOG_LEVEL logLevel, const MAVAPI_TCHAR *message,
		void *user_data) {
	if (!message)
		return;

	LOGD(">>>>>>>>>> debug_log_callback >>>>>>>>>> message - %s", message);

	return;
}

int load_mavapi(PMAVAPI_FUNCS mavapi, char *libPath) {
	//void * lib = NULL;

	if (gMavapiLib != NULL) {
		dlclose(gMavapiLib);
		gMavapiLib = NULL;
	}

	gMavapiLib = dlopen(libPath, RTLD_NOW);
	if (!gMavapiLib) {
		LOGD("TEST_ENGINE: Loading libs1 [%p][%s]", gMavapiLib, dlerror());
		return EXIT_FAILURE;
	}

	mavapi->MAVAPI_set_log_callback = dlsym(gMavapiLib,
			"MAVAPI_set_log_callback");
	if (mavapi->MAVAPI_set_log_callback == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_initialize = dlsym(gMavapiLib, "MAVAPI_initialize");
	if (mavapi->MAVAPI_initialize == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_uninitialize = dlsym(gMavapiLib, "MAVAPI_uninitialize");
	if (mavapi->MAVAPI_uninitialize == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_get_version = dlsym(gMavapiLib, "MAVAPI_get_version");
	if (mavapi->MAVAPI_get_version == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_create_instance = dlsym(gMavapiLib,
			"MAVAPI_create_instance");
	if (mavapi->MAVAPI_create_instance == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_release_instance = dlsym(gMavapiLib,
			"MAVAPI_release_instance");
	if (mavapi->MAVAPI_release_instance == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_set_user_data = dlsym(gMavapiLib, "MAVAPI_set_user_data");
	if (mavapi->MAVAPI_set_user_data == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_register_callback = dlsym(gMavapiLib,
			"MAVAPI_register_callback");
	if (mavapi->MAVAPI_register_callback == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_unregister_callback = dlsym(gMavapiLib,
			"MAVAPI_unregister_callback");
	if (mavapi->MAVAPI_unregister_callback == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_scan = dlsym(gMavapiLib, "MAVAPI_scan");
	if (mavapi->MAVAPI_scan == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_set = dlsym(gMavapiLib, "MAVAPI_set");
	if (mavapi->MAVAPI_set == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_get = dlsym(gMavapiLib, "MAVAPI_get");
	if (mavapi->MAVAPI_get == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_send_signal = dlsym(gMavapiLib, "MAVAPI_send_signal");
	if (mavapi->MAVAPI_send_signal == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	mavapi->MAVAPI_set_fops = dlsym(gMavapiLib, "MAVAPI_set_fops");
	if (mavapi->MAVAPI_set_fops == NULL) {
		LOGD("Fail to load symbol");
		return EXIT_FAILURE;
	}
	// void MAVAPI_EXP MAVAPI_free(void **ptr);
	LOGD("TEST_ENGINE: FUNCS[%p]", mavapi->MAVAPI_create_instance);
	LOGD("TEST_ENGINE: FUNCS[%p]", mavapi->MAVAPI_release_instance);

	return EXIT_SUCCESS;
}

int initialize_mavapi(PMAVAPI_FUNCS mavapi) {
	LOGD(
			">>>>>>>>>>>>>>>>>>>>>>>> [%s] >>>>>>>>>>>>>>>>>>>>>>>>", "initialize_mavapi");

	char* enginePath = (char*) getEnginePath();
	LOGD(
			">>>>>>>>>>>>>>>>>>>>>>>> [%s = %s] >>>>>>>>>>>>>>>>>>>>>>>>", "getEnginePath", enginePath);

	int strLength = strlen(enginePath) + strlen(MAVAPI_LIB) + 1;
	char *mavapiPath = malloc(strLength);
	memset(mavapiPath, 0, strLength);
	sprintf(mavapiPath, "%s/%s", enginePath, MAVAPI_LIB);

	memset(mavapi, 0, sizeof(MAVAPI_FUNCS));
	int loaded_mavapi = load_mavapi(mavapi, mavapiPath);
	LOGD(
			">>>>>>>>>>>>>>>>>>>>>>>> [loaded mavapi : %i] >>>>>>>>>>>>>>>>>>>>>>>>", loaded_mavapi);
	free(mavapiPath);
	LOGD(
			">>>>>>>>>>>>>>>>>>>>>>>> [%s] >>>>>>>>>>>>>>>>>>>>>>>>", "setLogCallBack");
	mavapi->MAVAPI_set_log_callback((MAVAPI_LOG_CALLBACK) &debug_log_callback, MAVAPI_LOG_DEBUG,
			NULL);

	MAVAPI_GLOBAL_INIT globalInit;
	memset(&globalInit, 0, sizeof(MAVAPI_GLOBAL_INIT));

	globalInit.program_type = 0;
	globalInit.engine_dirpath = enginePath;
	globalInit.vdfs_dirpath = enginePath;
	globalInit.key_dir = enginePath;
	LOGD(
			">>>>>>>>>>>>>>>>>>>>>>>> [%s] >>>>>>>>>>>>>>>>>>>>>>>>", "Mavapi_initialize");
	return mavapi->MAVAPI_initialize(&globalInit);
}

int uninitialize_mavapi(PMAVAPI_FUNCS mavapi) {
	return mavapi->MAVAPI_uninitialize();
}

MAVAPI_FD create_scan_context(PMAVAPI_FUNCS mavapi, MAVAPI_CALLBACK callback,
		int scanArchive, int scanDepth, char* productId, char* tempPath,
		int threadId, int prefixOption) {
	MAVAPI_FD fd = NULL;
	MAVAPI_INSTANCE_INIT init;
	init.flags = 0;

	int ret = mavapi->MAVAPI_create_instance(&init, &fd);
	if (fd != NULL && ret == MAVAPI_S_OK) {
		ret = mavapi->MAVAPI_register_callback(&fd,
				MAVAPI_CALLBACK_REPORT_FILE_STATUS, callback);
		ret = mavapi->MAVAPI_register_callback(&fd, MAVAPI_CALLBACK_PRE_SCAN,
				callback);

		ret = mavapi->MAVAPI_register_callback(&fd,
				MAVAPI_CALLBACK_REPORT_ERROR, callback);
		ret = mavapi->MAVAPI_register_callback(&fd,
				MAVAPI_CALLBACK_ARCHIVE_OPEN, callback);

		ret = mavapi->MAVAPI_register_callback(&fd,
				MAVAPI_CALLBACK_PROGRESS_REPORT, callback);

		ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_SCAN_TEMP, tempPath);
		ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_ARCHIVE_SCAN,
				scanArchive ? "1" : "0");
		char scanDepthString[128] = { 0 };
		sprintf(scanDepthString, "%d", scanDepth);
		ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_ARCHIVE_MAX_REC,
				scanDepth >= 0 ? scanDepthString : "0");
		ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_PRODUCT, productId);
		ret = mavapi->MAVAPI_set_user_data(&fd, (void *) threadId);

		switch (prefixOption) {
		case DISABLE_PUA_AND_ADWARE_PREFIX_SCANNING:
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_SPR, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_APPL, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_PFS, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_ADWARE, "0");
			break;

		case PUA_PREFIX_SCANNING:
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_SPR, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_APPL, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_PFS, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_ADWARE, "0");
			break;

		case ADWARE_PREFIX_SCANNING:
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_SPR, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_APPL, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_PFS, "0");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_ADWARE, "1");
			break;

		case PUA_AND_ADWARE_PREFIX_SCANNING:
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_SPR, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_APPL, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_PFS, "1");
			ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_ADWARE, "1");
			break;
		}


		ret = mavapi->MAVAPI_set(&fd, MAVAPI_OPTION_DETECT_ADSPY, "1");

		MAVAPI_SIZE_T size = 128;
		MAVAPI_TCHAR *buffer = malloc(size * sizeof(MAVAPI_TCHAR));
		ret = mavapi->MAVAPI_get(&fd, MAVAPI_OPTION_ARCHIVE_MAX_RATIO, buffer,
				&size);
		LOGD(
				"!!!!!!!!!!!!!!!!!!!!!!MAVAPI_OPTION_ARCHIVE_MAX_RATIO: %s", buffer);
		ret = mavapi->MAVAPI_get(&fd, MAVAPI_OPTION_ARCHIVE_MAX_COUNT, buffer,
				&size);
		LOGD(
				"!!!!!!!!!!!!!!!!!!!!!!MAVAPI_OPTION_ARCHIVE_MAX_COUNT: %s\n!!!!!!!!!!!!!!!!!!!!!! 0 means unlimited.", buffer);
		ret = mavapi->MAVAPI_get(&fd, MAVAPI_OPTION_ARCHIVE_MAX_REC, buffer,
				&size);
		LOGD("!!!!!!!!!!!!!!!!!!!!!!MAVAPI_OPTION_ARCHIVE_MAX_REC: %s", buffer);
		free(buffer);
	}
	return fd;
}

int scan_file(PMAVAPI_FUNCS mavapi, MAVAPI_FD scanContext, char *filePath) {
	return mavapi->MAVAPI_scan(&scanContext, filePath);
}

int scan_abort(PMAVAPI_FUNCS mavapi, MAVAPI_FD scanContext) {
	MAVAPI_SIGNAL_DATA signal_data;
	memset(&signal_data, 0, sizeof(MAVAPI_SIGNAL_DATA));
	signal_data.signal_id = MAVAPI_SIGNAL_SCAN_ABORT;
	signal_data.signal_data = NULL;

	return mavapi->MAVAPI_send_signal(&scanContext, MAVAPI_SIGNAL_SCAN_ABORT,
			&signal_data);
}

#ifdef __cplusplus
}
#endif
