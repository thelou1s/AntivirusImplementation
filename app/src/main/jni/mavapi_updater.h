/*
 * mavapi_updater.h
 *
 *  Created on: Feb 13, 2013
 *      Author: cfpoon
 */

#ifndef MAVAPI_UPDATER_H_
#define MAVAPI_UPDATER_H_

#include "mavupdate.h"
#include "preloader.h"

typedef struct options {
	size_t check_if_upd_avl_flag;
	size_t show_progress_flag;
	MAVUPDATE_TCHAR *log_filename;
} OPTIONS;

typedef struct mavupdate_funcs {
	int isInitialized;
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_get_version)(
			MAVUPDATE_VERSION *version);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_initialize)(
			const MAVUPDATE_INIT *init_data);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_uninitialize)();
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_set_callback)(
			const MAVUPDATE_CALLBACK_FN callback_fn, void *user_data);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_set)(MAVUPDATE_OPTION option,
			const MAVUPDATE_TCHAR *value);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_get)(MAVUPDATE_OPTION option,
			MAVUPDATE_TCHAR *value, size_t *size);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_check_for_updates)(
			unsigned int *result);
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_download_files)();
	MAVUPDATE_RET (*MAVUPDATE_EXP mavupdate_install_files)();
} MAVAPI_UPDATER_FUNCS, *PMAVAPI_UPDATER_FUNCS;

typedef struct preloader_funcs {
	int isInitialized;
	int (*load)(const char *path);
	void (*unload)(void);
} PRELOADER_FUNCS, *PPRELOADER_FUNCS;

int mavapi_updater_update();

#endif /* MAVAPI_UPDATER_H_ */
