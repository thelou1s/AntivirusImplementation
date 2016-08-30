/* Copyright 2012 Avira Operations GmbH & Co KG */
/**
 * This header contains the default messages used in the logging callback.
 * If you want to use you own messages for example in a translated version,
 * you can create a custom message-mapping between the numeric IDs specified in
 * here, and your own version of the message.
 *
 * Changing anything in this header will not result in different default messages being
 * sent from the MAVAPI, it is merely intended as an official reference for the currently assigned
 * message IDs.
 */


#ifndef INCLUDE_MAVAPI_MSG_H_
#define INCLUDE_MAVAPI_MSG_H_

#include "./mtchar.h"

/*
 * Marks the end of each string mapping table
 */
#define TABLE_END 0x9999

/**
 * String mapping table structure
 */
typedef struct string_map {
    int id;
    MAVAPI_TCHAR * str;
} MSG_STRING_MAP;

/**
 * These are generic messages issued by the MAVAPI.
 * Range is 0 - 999
 */
MSG_STRING_MAP mavapi_generic_msg_map[] = {
        {0,     _T("Cleaning up temporary file.")},
        {1,     _T("Requesting new temporary file.")},
        {2,     _T("Creating new temporary file.")},
        {3,     _T("Filtered out a detection due to deactivated prefix:")},
        {4,     _T("Found matching pattern or detection:")},
        {5,     _T("Finished scanning an object.")},
        {6,     _T("Object scan status still clean.")},
        {7,     _T("Reporting status for object.")},
        {8,     _T("Archive extraction progress.")},
        {9,     _T("Opening archive for extraction.")},
        {10,    _T("Skipping archive extraction.")},
        {11,    _T("Attempting to extract an object from a container.")},
        {12,    _T("Skipping object extraction from container.")},
        {13,    _T("Attempting to scan an object.")},
        {14,    _T("Skipping scan of an object.")},
        {15,    _T("Current object is an archive.")},
        {16,    _T("Aborting scan completely.")},
        {17,    _T("Aborting scan of current object.")},
        {18,    _T("File validation found damaged file.")},
        {19,    _T("File validation found unsigned file.")},
        {20,    _T("File validation found corrupt file.")},
        {21,    _T("File validation found modified file.")},
        {22,    _T("File validation encountered an error.")},
        {23,    _T("File validation successful.")},
        {24,    _T("File validation found developer signature.")},
        {25,    _T("Failed to load a module.")},
        {26,    _T("Function not present in loaded module.")},
        {27,    _T("Engine directory not set.")},
        {28,    _T("VDF directory not set.")},
        {29,    _T("License key path or directory not set.")},
        {30,    _T("Directory does not exist, is not an absolute path or cannot be accessed.")},
        {31,    _T("Initializing MAVAPI.")},
        {32,    _T("Uninitializing MAVAPI.")},
        {33,    _T("Initializing scanning instance.")},
        {34,    _T("Uninitializing scanning instance.")},
        {35,    _T("Setting user data.")},
        {36,    _T("Registering callback.")},
        {37,    _T("Unregistering callback.")},
        {38,    _T("Instance not initialized.")},
        {39,    _T("Temp folder not set.")},
        {40,    _T("Engine thread not initialized.")},
        {41,    _T("Archive callback not registered.")},
        {42,    _T("Pre-scan callback not registered.")},
        {43,    _T("Error callback not registered.")},
        {44,    _T("Progress callback not registered.")},
        {45,    _T("Status callback not registered.")},
        {46,    _T("No valid product id or license set.")},
        {47,    _T("Starting file scan:")},
        {48,    _T("Setting option to value.")},
        {49,    _T("Getting value of option.")},
        {50,    _T("Sending a signal to the scan.")},
        {51,    _T("Object recursion level:")},
        {TABLE_END, _T("UNKNOWN ERROR STRING")}
};

/**
 * These are messages issued for specific error codes.
 * * Range is 200 - 399
 */
MSG_STRING_MAP mavapi_error_msg_map[] = {
        {1000,   _T("[MAVAPI_S_OK] No error.")},
        {1001,   _T("[MAVAPI_E_INVALID_PARAMETER] Invalid parameter has been passed.")},
        {1002,   _T("[MAVAPI_E_ALREADY_INITIALIZED] MAVAPI is already initialized.")},
        {1003,   _T("[MAVAPI_E_NOT_INITIALIZED] MAVAPI has not been initialized.")},
        {1004,   _T("[MAVAPI_E_NO_MEMORY] Failed to allocate memory.")},
        {1005,   _T("[MAVAPI_E_VDF_NOT_FOUND] Virus database could not be found.")},
        {1006,   _T("[MAVAPI_E_VDF_READ] Virus database could not be read")},
        {1007,   _T("[MAVAPI_E_VDF_CRC] Virus database has been modified or is corrupted.")},
        {1008,   _T("[MAVAPI_E_VDF_VERSION] Virus database has incorrect version.")},
        {1009,   _T("[MAVAPI_E_WRONG_ENGINE] Attempted to load wrong engine.")},
        {1010,   _T("[MAVAPI_E_ENGINE_NOT_FOUND] One or more engine files could not be found.")},
        {1011,   _T("[MAVAPI_E_WRONG_MAVAPI] Wrong version of MAVAPI.")},
        {1012,   _T("[MAVAPI_E_SELFCHK_PATCHED] Engine components have been patched.")},
        {1013,   _T("[MAVAPI_E_SELFCHK_FILE_ERR] Engine self-check could not open or read files.")},
        {1014,   _T("[MAVAPI_E_SELFCHK_FILE_CRC] Engine self-check failed.")},
        {1015,   _T("[MAVAPI_E_INTERNAL] Internal engine error.")},
        {1016,   _T("[MAVAPI_E_NOT_SUPPORTED] The feature you are trying to use it not supported.")},
        {1017,   _T("[MAVAPI_E_RESULT_ERROR] The scan has terminated with an error.")},
        {1018,   _T("[MAVAPI_E_RESULT_FILE_NOT_FOUND] File to scan could not be found.")},
        {1019,   _T("[MAVAPI_E_OPTION_NOT_SUPPORTED] The option you are trying to use it not supported." )},
        {1020,   _T("[MAVAPI_E_HIT_MAX_REC] Archive unpacking has reached the configured recursion limit.")},
        {1021,   _T("[MAVAPI_E_HIT_MAX_SIZE] Archive unpacking has reached the configured size limit.")},
        {1022,   _T("[MAVAPI_E_HIT_MAX_RATIO] Archive unpacking has reached the configured ratio limit.")},
        {1023,   _T("[MAVAPI_E_ENCRYPTED] Archive unpacking has encountered an encrypted file.")},
        {1024,   _T("[MAVAPI_E_UNSUPPORTED] Archive unpacking has encountered an unsupported compression method.")},
        {1025,   _T("[MAVAPI_E_PROC_ERROR] Archive unpacking has encountered a processing error.")},
        {1026,   _T("[MAVAPI_E_INCOMPLETE] The archive was not be scanned completely.")},
        {1027,   _T("[MAVAPI_E_PARTIAL] Cannot extract multi-volume archive.")},
        {1028,   _T("[MAVAPI_E_HIT_MAX_COUNT] Maximum number of files in archive reached.")},
        {1029,   _T("[MAVAPI_E_ABORTED] Scan was aborted by signal.")},
        {1030,   _T("[MAVAPI_E_TIMEOUT] A scan in progress exceeded the configured scan time-out.")},
        {1031,   _T("[MAVAPI_E_FILE_OPEN] File is missing or there are no access rights to open it.")},
        {1032,   _T("[MAVAPI_E_FILE_READ] Error while trying to read a file.")},
        {1033,   _T("[MAVAPI_E_FILE_WRITE] Error while trying to write a file.")},
        {1034,   _T("[MAVAPI_E_INVALID_VALUE] Invalid value in configuration or command")},
        {1035,   _T("[MAVAPI_E_NOT_ABSOLUTE_PATH] Path to a given or required directory is not absolute.")},
        {1036,   _T("[MAVAPI_E_DIR_NOT_EXISTS] Path to a given directory does not exist.")},
        {1037,   _T("[MAVAPI_E_MATCHED] File was filtered from scanning.")},
        {1038,   _T("[MAVAPI_E_OPTION_VALUE_INVALID] Invalid option value.")},
        {1039,   _T("[MAVAPI_E_FILE_CREATE] Failed to create a file.")},
        {1040,   _T("[MAVAPI_E_FILE_DELETE] Failed to delete a file.")},
        {1041,   _T("[MAVAPI_E_FILE_CLOSE] Failed to close a file.")},
        {1042,   _T("[MAVAPI_E_UNKNOWN] Unknown error occurred.")},
        {1043,   _T("[MAVAPI_E_PREFIX_SET] Failed to set a detect type option.")},
        {1044,   _T("[MAVAPI_E_PREFIX_GET] Failed to get a detect type option.")},
        {1045,   _T("[MAVAPI_E_KEY_NO_KEYFILE] License file could not be found or opened.")},
        {1046,   _T("[MAVAPI_E_KEY_ACCESS_DENIED] Access to license file has been denied.")},
        {1047,   _T("[MAVAPI_E_KEY_INVALID_HEADER] License file has an invalid header.")},
        {1048,   _T("[MAVAPI_E_KEY_KEYFILE_VERSION] License file has incorrect version.")},
        {1049,   _T("[MAVAPI_E_KEY_NO_LICENSE] No valid license found.")},
        {1050,   _T("[MAVAPI_E_KEY_FILE_INVALID] Invalid license found.")},
        {1051,   _T("[MAVAPI_E_KEY_RECORD_INVALID] Invalid license record.")},
        {1052,   _T("[MAVAPI_E_KEY_EVAL_VERSION] License is for evaluation only.")},
        {1053,   _T("[MAVAPI_E_KEY_DEMO_VERSION] License is for demo only.")},
        {1054,   _T("[MAVAPI_E_KEY_ILLEGAL_LICENSE] License key is illegal.")},
        {1055,   _T("[MAVAPI_E_KEY_NO_FUP_LICENSE] No FUP II/III license found.")},
        {1056,   _T("[MAVAPI_E_KEY_NO_FUP2_KEYFILE] No FUP II/III keyfile found.")},
        {1057,   _T("[MAVAPI_E_KEY_EXPIRED] License key is expired.")},
        {1058,   _T("[MAVAPI_E_KEY_READ] Could not read license key.")},
        {1059,   _T("[MAVAPI_E_LICENSE_RESTRICTION] Operation not allowed due to license restriction.")},
        {1060,   _T("[MAVAPI_E_LOADING_ENGINE_MODULES] An error occurred while loading engine modules.")},
        {1061,   _T("[MAVAPI_E_BUSY] MAVAPI is busy.")},
        {1062,   _T("[MAVAPI_E_MEMORY_LIMIT] Internal memory limit reached.")},
        {1063,   _T("[MAVAPI_E_PROC_INCOMPLETE_BLOCK_READ] An archive block is damaged and could not be read.")},
        {1064,   _T("[MAVAPI_E_PROC_BAD_HEADER] The archive header is invalid.")},
        {1065,   _T("[MAVAPI_E_PROC_INVALID_COMPRESSED_DATA] The compressed data from the archive is invalid.")},
        {1066,   _T("[MAVAPI_E_PROC_OBSOLETE] Obsolete archive information.")},
        {1067,   _T("[MAVAPI_E_PROC_BAD_FORMAT] Bad header format.")},
        {1068,   _T("[MAVAPI_E_PROC_HEADER_CRC] An archive header failed checksum check.")},
        {1069,   _T("[MAVAPI_E_PROC_DATA_CRC] Checksum of compressed data does not match.")},
        {1070,   _T("[MAVAPI_E_PROC_FILE_CRC] Checksum of a decompressed file does not match.")},
        {1071,   _T("[MAVAPI_E_PROC_BAD_TABLE] Archive contains an invalid decompression table.")},
        {1072,   _T("[MAVAPI_E_PROC_UNEXPECTED_EOF] Decompression aborted because of unexpected end of file in archive.")},
        {1073,   _T("[MAVAPI_E_PROC_ARCHIVE_HANDLE] An internal handle related to archive processing is invalid or not initialized.")},
        {1074,   _T("[MAVAPI_E_PROC_NO_FILES_TO_EXTRACT] No files could be extracted.")},
        {1075,   _T("[MAVAPI_E_PROC_CALLBACK] Archive internal callback error")},
        {1076,   _T("[MAVAPI_E_PROC_TOTAL_LOSS] File extraction failed.")},
        {TABLE_END, _T("UNKNOWN ERROR STRING")}
};

/**
 * These are messages issued for warnings
 * Range is 1200-1299
 */
MSG_STRING_MAP mavapi_warning_msg_map[] = {
        {1200,   _T("[MAVAPI_W_DAMAGED] The scanned object is potentially damaged.")},
        {1201,   _T("[MAVAPI_W_SUSPICIOUS] The scanned object is suspicious.")},
        {1202,   _T("[MAVAPI_W_PROGRESS_ABORT] Archive unpacking was aborted by callback.")},
        {1203,   _T("[MAVAPI_W_HEADER_MALFORMED] An archive with a malformed header was discovered.")},
        {1204,   _T("[MAVAPI_W_POTENTIAL_ARCH_BOMB] The object has features of an archive bomb.")},
        {1205,   _T("[MAVAPI_W_RATIO_EXCEEDED] The configured unpacking ratio was exceeded.")},
        {1206,   _T("[MAVAPI_W_MAX_EXTRACTED] The maximum configured unpacking size was reached.")},
        {TABLE_END, _T("UNKNOWN WARNING STRING")}
};


#endif  // INCLUDE_MAVAPI_MSG_H_

