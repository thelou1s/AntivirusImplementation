/* Copyright:  2013 Copyright (c) Avira Operations GmbH & Co.KG
 * =====================================================================================
 *
 *       Filename:  messages.h
 *
 *    Description:  Default log messages  
 *
 *    This header contains the default messages used in the logging callback.
 *    If you want to use you own messages for example in a translated version,
 *    you can create a custom message-mapping between the numeric IDs specified in
 *    here, and your own version of the message.
 *
 *    Changing anything in this header will not result in different default messages being
 *    sent from the MAVUPDATE, it is merely intended as an official reference for the
 *    currently assigned message IDs.
 *
 *
 *   Organization:  2013 Avira Operations GmbH & Co.KG
 *
 * =====================================================================================
 */
#ifndef INCLUDE_MESSAGES_H_
#define INCLUDE_MESSAGES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "./mavupdate_defines.h"

#define TABLE_END 20000
/**
  \brief This structure is the map between the message id and it's string representation
*/
typedef struct string_map {
    int id;                     //!< Message id
    MAVUPDATE_TCHAR *message;   //!< Message
} MSG_STRING_MAP;


MSG_STRING_MAP mavupdate_error_map[] = {
        {10000    ,  _T("No install dir specified.")},
        {10001    ,  _T("Install directory doesn't exist.")},
        {10002    ,  _T("Temporary directory not specified.")},
        {10003    ,  _T("Temporary directory doesn't exist.")},
        {10004    ,  _T("File md5 check failed.")},
        {10005    ,  _T("File signature check failed.")},
        {10006    ,  _T("File download failed.")},
        {10007    ,  _T("File check failed.")},
        {10008    ,  _T("File integrity check failed.")},
        {10009    ,  _T("File installation failed")},
        {10010    ,  _T("Master file integrity check failed.")},
        {10011    ,  _T("Archive download failed.")},
        {10012    ,  _T("Archive unpacking failed.")},
        {10013    ,  _T("Archive verification failed.")},
        {10014    ,  _T("Product name is unknown.")},
        {10015    ,  _T("Product file integrity check failed.")},
        {10016    ,  _T("Product file download failed.")},
        {10017    ,  _T("Product file archive download failed.")},
        {10018    ,  _T("Download source (hosts) not specified.")},
        {10019    ,  _T("No license(s) given. Check failed.")},
        {10020    ,  _T("Unable to retrieve date info.")},
        {10021    ,  _T("Backup failed.")},
        {10022    ,  _T("Rollback failed.")},
        {TABLE_END                                    ,  _T("UNNOWN ERROR STRING")}
};

MSG_STRING_MAP mavupdate_info_map[] = {
        {11000   ,  _T("Can't mark dirty files. Files list is empty.")},
        {11001   ,  _T("Dirty files marked successfully.")},
        {11002   ,  _T("Signature checked.")},
        {11003   ,  _T("File checked.")},
        {11004   ,  _T("File list created.")},
        {11005   ,  _T("Verifying License Expiry.")},
        {11006   ,  _T("Finished license date verification.")},
        {11007   ,  _T("VDF is newer than maximum license date.")},
        {11008   ,  _T("Installation refused due to license date check.")},
        {11009   ,  _T("Installation refused. Error during backuping install dir.")},
        {11010   ,  _T("Starting install.")},
        {11011   ,  _T("Finished install.")},
        {11012   ,  _T("File possibly downgraded")},
        {11013   ,  _T("File updated.")},
        {11014   ,  _T("File installed.")},
        {11015   ,  _T("File update rejected due to old file version.")},
        {11016   ,  _T("Rolling back.")},
        {11017   ,  _T("Rollback successful.")},
        {TABLE_END                                    ,  _T("UNNOWN ERROR STRING")}
};

MSG_STRING_MAP mavupdate_debug_map[] = {
        {TABLE_END                                    ,  _T("UNNOWN ERROR STRING")}
};

MSG_STRING_MAP mavupdate_warning_map[] = {
        {TABLE_END                                    ,  _T("UNNOWN ERROR STRING")}
};
#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_MESSAGES_H_
