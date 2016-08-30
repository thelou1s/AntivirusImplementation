/*
 * mavapi_engine.h
 *
 *  Created on: Feb 18, 2013
 *      Author: cfpoon
 */

#ifndef MAVAPI_ENGINE_H_
#define MAVAPI_ENGINE_H_

#include "mavapi.h"

typedef struct mavapi_funcs {
	int (*MAVAPI_EXP MAVAPI_set_log_callback)(MAVAPI_LOG_CALLBACK log_fct,
			MAVAPI_LOG_LEVEL min_level, void *user_data);
	int (*MAVAPI_EXP MAVAPI_initialize)(MAVAPI_GLOBAL_INIT *MAVAPI_init);
	int (*MAVAPI_EXP MAVAPI_uninitialize)();
	int (*MAVAPI_EXP MAVAPI_get_version)(MAVAPI_VERSION *version);
	int (*MAVAPI_EXP MAVAPI_create_instance)(MAVAPI_INSTANCE_INIT *init,
			MAVAPI_FD *MAVAPI_fd);
	int (*MAVAPI_EXP MAVAPI_release_instance)(MAVAPI_FD *MAVAPI_fd);
	int (*MAVAPI_EXP MAVAPI_set_user_data)(MAVAPI_FD *MAVAPI_fd,
			void *user_data);
	int (*MAVAPI_EXP MAVAPI_register_callback)(MAVAPI_FD *MAVAPI_fd,
			unsigned int callback_id, MAVAPI_CALLBACK callback);
	int (*MAVAPI_EXP MAVAPI_unregister_callback)(MAVAPI_FD *MAVAPI_fd,
			unsigned int callback_id, MAVAPI_CALLBACK callback);
	int (*MAVAPI_EXP MAVAPI_scan)(MAVAPI_FD *MAVAPI_fd,
			const MAVAPI_TCHAR *file_name);
	int (*MAVAPI_EXP MAVAPI_set)(MAVAPI_FD *MAVAPI_fd, unsigned int option_id,
			MAVAPI_TCHAR *buffer);
	int (*MAVAPI_EXP MAVAPI_get)(MAVAPI_FD *MAVAPI_fd, unsigned int option_id,
			MAVAPI_TCHAR *buffer, MAVAPI_SIZE_T *buffer_size);
	int (*MAVAPI_EXP MAVAPI_get_dynamic_detect)(MAVAPI_TCHAR *type, int *id);
	int (*MAVAPI_EXP MAVAPI_send_signal)(MAVAPI_FD *MAVAPI_fd,
			unsigned int signal_id, MAVAPI_SIGNAL_DATA* data);
	int (*MAVAPI_EXP MAVAPI_set_fops)(MAVAPI_FD *MAVAPI_fd, void *fops_pointer,
			void *fops_context);
	// void MAVAPI_EXP MAVAPI_free(void **ptr);
	int (*MAVAPI_EXP MAVAPI_reload_engine_ex)(
			const MAVAPI_GLOBAL_INIT *global_init);
} MAVAPI_FUNCS, *PMAVAPI_FUNCS;

int initialize_mavapi(PMAVAPI_FUNCS mavapi);
int uninitialize_mavapi(PMAVAPI_FUNCS mavapi);
MAVAPI_FD create_scan_context(PMAVAPI_FUNCS mavapi, MAVAPI_CALLBACK callback,
		int scanArchive, int scanDepth, char* productId, char* tempPath,
		int threadId, int prefixOption);
int scan_file(PMAVAPI_FUNCS mavapi, MAVAPI_FD scanContext, char *filePath);
int scan_abort(PMAVAPI_FUNCS mavapi, MAVAPI_FD scanContext);

#endif /* MAVAPI_ENGINE_H_ */
