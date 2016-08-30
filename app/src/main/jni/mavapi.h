/* Copyright 2012 Avira Operations GmbH & Co KG */

#ifndef INCLUDE_MAVAPI_H_
#define INCLUDE_MAVAPI_H_

#include "./mtchar.h"

#define MAVAPI_MAJOR       1
#define MAVAPI_MINOR       0
#define MAVAPI_BUILD_MAJOR 0
#define MAVAPI_BUILD_MINOR 7

/**
 * \mainpage MAVAPI
 *
 * MAVAPI stands for Mobile AntiVirus Application Programming Interface.
 * Its main purpose is to offer a very simple scanning interface for clients who want
 * to programmatically integrate scanning services into their applications.
 *
 * This document explains how to use the MAVAPI interface shared libraries written and provided 
 * by Avira Operations GmbH & Co. KG.
 * The provided LICENSE file explains the terms and conditions
 * for using the MAVAPI interface shared libraries.
 *
 * By utilizing the implemented MAVAPI interface, it becomes
 * very simple to quickly integrate MAVAPI into your applications.
 *
 * See: \ref defs "MAVAPI options", \ref defs "MAVAPI constants", \ref defs "MAVAPI defines",
 * \ref structs "MAVAPI structures", \ref funcs "MAVAPI functions"
 *
 */

/**
 * \defgroup defs MAVAPI constants
 * @{
 *
 * \defgroup rets MAVAPI return codes
 * @{
 */

/**
 * \brief Operation ended with success
 */
#define MAVAPI_S_OK                                    0
/**
 * \brief One of supplied parameters is invalid
 * \note At least one of the function's parameters is invalid (invalid pointers,
 * empty strings, out of range values, etc.).
 */
#define MAVAPI_E_INVALID_PARAMETER                     1
/**
 * \brief MAVAPI was already initialized
 * \note Trying to initialize an already initialized MAVAPI library (\ref MAVAPI_initialize was
 * already called successfully).
 */
#define MAVAPI_E_ALREADY_INITIALIZED                   2
/**
 * \brief MAVAPI is not initialized
 * \note The used functionality requires the MAVAPI library to be initialized first
 * (a successful call of \ref MAVAPI_initialize is needed before).
 */
#define MAVAPI_E_NOT_INITIALIZED                       3
/**
 * \brief Memory allocation failed
 * \note There is not enough memory available for allocation.
 */
#define MAVAPI_E_NO_MEMORY                             7
/**
 * \brief VDF file(s) not found
 * \note Path to the VDF files is not correct, files are missing, or there are
 * no access rights to open the files.
 */
#define MAVAPI_E_VDF_NOT_FOUND                         8
/**
 * \brief VDF file(s) read failed
 * \note VDF files are damaged or truncated.
 */
#define MAVAPI_E_VDF_READ                              9
/**
 * \brief VDF file(s) crc check failed
 * \note One ore more VDF files failed checksum check because they were damaged,
 * manipulated or truncated.
 */
#define MAVAPI_E_VDF_CRC                               10
/**
 * \brief Inconsistent versions in VDF files set
 * \note There are incompatible VDF files within the VDF set. Not all relevant VDF
 * files were downloaded or the engine is too old for the present VDF set.
 */
#define MAVAPI_E_VDF_VERSION                           11
/**
 * \brief Engine initialization failed
 * \note Engine is too old for this version of MAVAPI. MAVAPI used a wrong character
 * set when initializing the engine.
 */
#define MAVAPI_E_WRONG_ENGINE                          12
/**
 * \brief Engine file(s) not found
 * \note One or more engine files are not present in the engine's directory.
 */
#define MAVAPI_E_ENGINE_NOT_FOUND                      13
/**
 * \brief Invalid MAVAPI binary encountered
 * \details Not used.
 */
#define MAVAPI_E_WRONG_MAVAPI                          14
/**
 * \brief Inconsistent versions in engine files set
 * \note There are incompatible engine files within the engine set which do not match the
 * expected version. The engine file set was not updated or is too old for the present engine set.
 */
#define MAVAPI_E_SELFCHK_PATCHED                       15
/**
 * \brief Engine file(s) read failed
 * \note One or more engine files are damaged or truncated.
 */
#define MAVAPI_E_SELFCHK_FILE_ERR                      16
/**
 * \brief Engine file(s) crc check failed
 * \note One or more engine files failed checksum check because they were manipulated,
 * damaged or truncated.
 */
#define MAVAPI_E_SELFCHK_FILE_CRC                      17
/**
 * \brief MAVAPI internal error
 * \note An unexpected internal event prevented the normal execution of the library
 * (incorrect pointers, incorrect return values, etc.). Normally this error should
 * never occur. If this error occurs there is a major problem which must be fixed.
 */
#define MAVAPI_E_INTERNAL                              19
/**
 * \brief Unsupported feature
 * \note The requested functionality (feature, command, option) may be known but it is
 * not supported by this version of MAVAPI or engine. For instance a called function
 * is not available in the current library or engine.
 */
#define MAVAPI_E_NOT_SUPPORTED                         20
/**
 * \brief An error occurred during a file scan
 * \note Not used.
 */
#define MAVAPI_E_RESULT_ERROR                          21
/**
 * \brief Could not extract file
 * \note A file to extract during an archive scanning could not be found.
 */
#define MAVAPI_E_RESULT_FILE_NOT_FOUND                 22
/**
 * \brief Option is not supported
 * \note Trying to set or retrieve a value for an option with an unknown or
 *  obsolete id.
 */
#define MAVAPI_E_OPTION_NOT_SUPPORTED                  23
/**
 * \brief Archive maximum recursion limit reached
 * \note The limit on the maximum number of archive recursions was exceeded when extracting
 * a file because the file was packed too many times or it contained other deeply nested files.
 * The decompression will be aborted as soon as the limit is exceeded.
 */
#define MAVAPI_E_HIT_MAX_REC                           24
/**
 * \brief Archive maximum extraction size reached
 * \note Size of an uncompressed file has exceeded the maximum extraction size. The decompression
 * will be aborted as soon as the limit is exceeded.
 */
#define MAVAPI_E_HIT_MAX_SIZE                          25
/**
 * \brief Archive maximum extraction ratio reached
 * \note Size of an uncompressed file has exceeded the maximum extraction ratio.
 * The decompression will be aborted as soon as the limit is exceeded.
 */
#define MAVAPI_E_HIT_MAX_RATIO                         26
/**
 * \brief Encrypted contents found
 * \note One or more files inside the archive are encrypted, but there are also
 * files which are not encrypted and can be extracted; or all files inside the
 * archive are encrypted and it's not possible to extract them.
 */
#define MAVAPI_E_ENCRYPTED                             27
/**
 * \brief Unsupported archive type/format
 * \note The archive type is not supported. The version of a known archive type is
 * not supported. The compression method is not supported. The archive format is unknown.
 */
#define MAVAPI_E_UNSUPPORTED                           28
/**
 * \brief Archive generic processing error
 * \note Any other archive scan processing error which is not covered by
 * MAVAPI_E_PROC_<name> error codes.
 */
#define MAVAPI_E_PROC_ERROR                            29
/**
 * \brief File was not completely scanned
 * \note Scanning was aborted by user or as result of a terminal warning or error.
 */
#define MAVAPI_E_INCOMPLETE                            30
/**
 * \brief Cannot extract multi-volume archive
 * \note In case of an archive which is part of a multi-volume archive set, a file
 * could not be fully extracted because is split over several archive parts.
 * Processing the next file may be successful if all information is stored in that part.
 */
#define MAVAPI_E_PARTIAL                               31
/**
 * \brief Maximum number of files in archive reached
 * \note Maximum files count limit was reached while scanning an archive.
 * The scanning will be aborted as soon as the limit is exceeded.
 */
#define MAVAPI_E_HIT_MAX_COUNT                         32
/**
 * \brief Scan was aborted by signal
 * \note A scan in progress was aborted by user with \ref MAVAPI_SIGNAL_SCAN_ABORT signal.
 */
#define MAVAPI_E_ABORTED                               33
/**
 * \brief Scan timed out
 * \note A scan in progress exceeded the maximum user set scan time-out.
 */
#define MAVAPI_E_TIMEOUT                               34
/**
 * \brief Could not open file
 * \note File is missing or there are no access rights to open it.
 */
#define MAVAPI_E_FILE_OPEN                             40
/** File read error */
/**
 * \brief Could not read file
 * \note There are no access rights to read file, or the file has been removed, or
 * data from file end is missing, or file is truncated.
 */
#define MAVAPI_E_FILE_READ                             41
/**
 * \brief Could not write file
 * \note There are no access rights to write file, or the file has been removed.
 * Disk quota exceeded or disk is damaged.
 */
#define MAVAPI_E_FILE_WRITE                            42
/**
 * \brief Invalid value in configuration or command
 * \note Failure in MAVAPI Client Library communication with MAVAPI Service resulting
 * in commands with invalid values which cannot be accepted by Service (for instance
 * SET or GET commands with invalid values). The engine path given to the
 * \ref MAVAPI_reload_engine_ex() function collides with previous engine path.
 */
#define MAVAPI_E_INVALID_VALUE                         65
/**
 * \brief Path is not absolute
 * \note Path to a given or required directory is not absolute (for example the path of
 * the temporary scanning directory is not absolute).
 */
#define MAVAPI_E_NOT_ABSOLUTE_PATH                     67
/**
 * \brief Directory path does not exist
 * \note Path to a given directory does not exist (for example the path of the temporary
 * scanning directory does not exist).
 * \note This error can only be triggered by the MAVAPI Client Library.
 */
#define MAVAPI_E_DIR_NOT_EXISTS                        68
/**
 * \brief File was filtered from scanning
 * \note Currently not used
 */
#define MAVAPI_E_MATCHED                               69
/**
 * \brief Invalid option value
 * \note A configuration command received a value buffer which is not acceptable as
 * a value for the associated option id (for instance it is empty).
 */
#define MAVAPI_E_OPTION_VALUE_INVALID                  76
/**
 * \brief Failed to create file
 * \note Failed to create a temporary file in the temporary scanning directory
 * because there are no access rights, or the file already exists, etc.
 */
#define MAVAPI_E_FILE_CREATE                           78
/**
 * \brief Failed to delete file
 * \note Failed to delete a temporary file in the temporary scanning directory
 * because there are no access rights, file is locked, file does not exist anymore, etc.
 */
#define MAVAPI_E_FILE_DELETE                           79
/**
 * \brief Failed to close file
 * \note Failed to close a temporary file in the temporary scanning directory because
 * there are no access rights, file was accidentally deleted, etc.
 */
#define MAVAPI_E_FILE_CLOSE                            80
/**
 * \brief Unknown engine error
 * \note Engine returns an unknown error code.
 */
#define MAVAPI_E_UNKNOWN                               81
/**
 * \brief Failed to set a detect type option
 * \note MAVAPI failed to set a detect type option (for instance
 * \ref MAVAPI_OPTION_DETECT_APPL, others)
 */
#define MAVAPI_E_PREFIX_SET                            90
/**
 * \brief Failed to retrieve a detect type option
 * \note MAVAPI failed to retrieve a detect type option (for instance
 * \ref MAVAPI_OPTION_DETECT_APPL, others).
 */
#define MAVAPI_E_PREFIX_GET                            91
/**
 * \brief Keyfile has not been found
 * \note No keyfile could be found.
 */
#define MAVAPI_E_KEY_NO_KEYFILE                        101
/**
 * \brief Access to key file has been denied
 * \note Check the access rights for the key file on the local filesystem.
 */
#define MAVAPI_E_KEY_ACCESS_DENIED                     102
/**
 * \brief An invalid header has been found
 * \note The license file is probably corrupted or has been modified.
 */
#define MAVAPI_E_KEY_INVALID_HEADER                    103
/**
 * \brief Invalid keyfile version number
 * \note You seem to be using an outdated license type.
 */
#define MAVAPI_E_KEY_KEYFILE_VERSION                   104
/**
 * \brief No valid license found
 * \note You either have not supplied any license or only licenses
 * which are not valid for your product id.
 */
#define MAVAPI_E_KEY_NO_LICENSE                        105
/**
 * \brief Key file is invalid (invalid CRC)
 * \note The license file is probably corrupted or has been modified.
 */
#define MAVAPI_E_KEY_FILE_INVALID                      106
/**
 * \brief Invalid license record detected
 * \note The license file is probably corrupted.
 */
#define MAVAPI_E_KEY_RECORD_INVALID                    107
/**
 * \brief Application is evaluation version
 * \note Currently not used
 */
#define MAVAPI_E_KEY_EVAL_VERSION                      108
/**
 * \brief Application is demo version
 * \note Currently not used
 */
#define MAVAPI_E_KEY_DEMO_VERSION                      109
/**
 * \brief Illegal (cracked) license in keyfile
 * \note The license you are trying to use has been blacklisted.
 */
#define MAVAPI_E_KEY_ILLEGAL_LICENSE                   110
/**
 * \brief No FUP II/III license found
 * \note Currently not used
 */
#define MAVAPI_E_KEY_NO_FUP_LICENSE                    111
/**
 * \brief No FUP II/III keyfile found
 * \note Currently not used
 */
#define MAVAPI_E_KEY_NO_FUP2_KEYFILE                   112
/**
 * \brief This key has expired
 * \note You are trying to use engine or VDF files which are newer than your license expiration date.
 */
#define MAVAPI_E_KEY_EXPIRED                           113
/**
 * \brief Error reading from key file
 * \note MAVAPI could not properly read the key file.
 */
#define MAVAPI_E_KEY_READ                              114
/**
 * \brief Operation not allowed (license restriction)
 * \note Scan command was issued without setting a valid product id.
 */
#define MAVAPI_E_LICENSE_RESTRICTION                   120
/**
 * \brief Error loading engine modules
 * \note MAVAPI could not load engine modules because they are not available or
 * there are no access rights.
 */
#define MAVAPI_E_LOADING_ENGINE_MODULES                121
/**
 * \brief MAVAPI is busy
 * \note A configuration request was given during scanning a file (for instance
 * SET/GET command or callback register/unregister command).
 * \ref MAVAPI_uninitialize was called without releasing all MAVAPI instances before.
 */
#define MAVAPI_E_BUSY                                  122
/**
 * \brief Internal memory limit reached
 * \note An engine-internal safety limit regarding memory usage of a subroutine
 * has been reached (this can i.e. be caused by excessively large dictionaries in archives).
 */
#define MAVAPI_E_MEMORY_LIMIT                          125
/**
 * \brief Incomplete archive block read
 * \note An archive block is damaged and could not be read.
 */
#define MAVAPI_E_PROC_INCOMPLETE_BLOCK_READ            150
/**
 * \brief Bad archive header
 * \note The archive header is invalid.
 */
#define MAVAPI_E_PROC_BAD_HEADER                       151
/**
 * \brief Bad compressed data
 * \note The compressed data from the archive is invalid. Some files could not be
 * extracted and scanned.
 */
#define MAVAPI_E_PROC_INVALID_COMPRESSED_DATA          152
/**
 * \brief Obsolete archive information
 * \note Archive is packed with a very old or a developer version of a packer
 * application and contains obsolete information and unsupported entries.
 */
#define MAVAPI_E_PROC_OBSOLETE                         153
/**
 * \brief Bad header format
 * \note The archive header has been changed with a newer (unsupported) version of
 * a packer application. The archive header is damaged.
 */
#define MAVAPI_E_PROC_BAD_FORMAT                       154
/**
 * \brief Bad header crc
 * \note An archive header failed checksum check.
 */
#define MAVAPI_E_PROC_HEADER_CRC                       155
/**
 * \brief Bad data crc.
 * \note Checksum of compressed data does not match.
 */
#define MAVAPI_E_PROC_DATA_CRC                         156
/**
 * \brief Bad crc for extracted file
 * \note Checksum of a decompressed file does not match.
 */
#define MAVAPI_E_PROC_FILE_CRC                         157
/**
 * \brief Invalid decompression table
 * \note Archive contains an invalid decompression table.
 */
#define MAVAPI_E_PROC_BAD_TABLE                        158
/**
 * \brief Unexpected end of file
 * \note Decompression aborted because of unexpected end of file in archive.
 */
#define MAVAPI_E_PROC_UNEXPECTED_EOF                   159
/**
 * \brief Archive internal handle error
 * \note An internal handle related to archive processing is invalid or not initialized.
 */
#define MAVAPI_E_PROC_ARCHIVE_HANDLE                   160
/**
 * \brief No files could be extracted
 * \note Archive is invalid, corrupt or damaged.
 */
#define MAVAPI_E_PROC_NO_FILES_TO_EXTRACT              161
/**
 * \brief Archive internal callback error
 * \note Decompression aborted because an internal archive callback is invalid or caused an error.
 */
#define MAVAPI_E_PROC_CALLBACK                         162
/**
 * \brief File extraction failed.
 * \note Not all archive contents could be extracted.
 */
#define MAVAPI_E_PROC_TOTAL_LOSS                       163

/**
 * @}
 * \ingroup defs
 * \defgroup error_cat Error categories
 * \note Used by the error callbacks to categorize the errors they return
 * @{
 */
/** i/o error category */
#define MAVAPI_ECAT_ERROR_IO                           0
/** scan error category */
#define MAVAPI_ECAT_ERROR_SCAN                         1
/** unpack error category */
#define MAVAPI_ECAT_ERROR_UNPACK                       2
/** uncategorised error category */
#define MAVAPI_ECAT_ERROR_GENERIC                      3
/**
 * @}
 * \ingroup defs
 * \defgroup error_level Error levels
 * \note Used by the error callbacks to categorize the returned errors
 * @{
 */
/** error level */
#define MAVAPI_ELEVEL_ERROR                            0
/** warning level */
#define MAVAPI_ELEVEL_WARNING                          1
/** info level */
#define MAVAPI_ELEVEL_INFO                             2

/** @}*/

/**
 * \ingroup defs
 * \defgroup scan_warnings Scan warnings
 * \note Warnings that can be received during the scanning process
 * @{
 */
/** File has potentially been damaged by virus */
#define MAVAPI_W_DAMAGED                       1
/** File is suspicious */
#define MAVAPI_W_SUSPICIOUS                    4
/** An abort was triggered by the progress callback */
#define MAVAPI_W_PROGRESS_ABORT                8
/** A malformed archive header was detected */
#define MAVAPI_W_HEADER_MALFORMED              16
/**
 * This file could be an archive bomb, ratio
 * might be exceeded or something else might
 * have happened to trigger that detection
 */
#define MAVAPI_W_POTENTIAL_ARCH_BOMB           32
/** The ratio set by the application regarding unpacking size in archives has been exceeded */
#define MAVAPI_W_RATIO_EXCEEDED                64
/** Unpacking has reached the maximum limit of extracted data */
#define MAVAPI_W_MAX_EXTRACTED                 128

/** @}*/

/**
 * \ingroup defs
 * \defgroup options MAVAPI options
 *
 * @{
 *
 * \remark
 * Many options used to configure the MAVAPI instance have a default value
 * that is written in its descriptionas a note (i.e. Default value: \<value\>).
 * \remark
 * The options that have no default (i.e. unsupported options, obsolete, ignored) will be marked
 * with the "Default value: None" string.
 * \remark
 * Some options are mandatory to be set before a scan can be started. These are marked as
 * Default value: mandatory
 *
 * \defgroup get_set GET/SET options (read/write)
 * \brief "SET" requests are available to configure MAVAPI. For the following requests,
 * a "GET" counterpart is also available and these are therefore labeled as
 * "read/write". Only the "SET" version is listed here although a "GET" version
 * also exists. The "GET" response will return the same data that is provided
 * with the "SET" request (although the representation of the data may be
 * different. For example, if supported, a "SET" request with "10K" could lead to a "GET"
 * response with "10240".)
 * @{
 */

/**
 * \brief Activates archive detection and scanning.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_ARCHIVE_SCAN                     3
/**
 * \brief Set the maximum allowed size (in bytes) for any file within an archive.
 * \note A value of "0" means the maximum allowed value (INT64_MAX bytes).
 * \note This setting has no meaning if ARCHIVE_SCAN is deactivated.
 * \note Default value: 1073741824 (1GByte)
 */
#define MAVAPI_OPTION_ARCHIVE_MAX_SIZE                 4
/**
 * \brief Set the maximum allowed recursion within an archive.
 * \note A value of "0" means the maximum allowed value (1000 recursion levels).
 * \note This setting has no meaning if ARCHIVE_SCAN is deactivated.
 * \note Default value: 10
 */
#define MAVAPI_OPTION_ARCHIVE_MAX_REC                  5
/**
 * \brief Set the maximum allowed decompressing-ratio within an archive.
 * \note A value of "0" means the maximum allowed value (INT32_MAX).
 * \note This setting has no meaning if ARCHIVE_SCAN is deactivated.
 * \note Default value: 250
 */
#define MAVAPI_OPTION_ARCHIVE_MAX_RATIO                6
/**
 * \brief Set the maximum allowed number of files within an archive.
 * \note A value of "0" means the maximum allowed value (INT64_MAX).
 * \note This setting has no meaning if ARCHIVE_SCAN is deactivated.
 * \note Default value: 0
 */
#define MAVAPI_OPTION_ARCHIVE_MAX_COUNT                7
/**
 * \brief Set the temporary directory used for scanning files.
 * \note Default value: mandatory
 */
#define MAVAPI_OPTION_SCAN_TEMP                        11
/**
 * \brief Set the maximum number of seconds allowed to scan a file before aborting
 * \note Default value: 0 (no timeout)
 */
#define MAVAPI_OPTION_SCAN_TIMEOUT                     12


/**
 * \brief Activate detection for the specified type.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_ADSPY                     21

/**
 * \brief Activate detection for the specified type.
 * Applications flagged by these detections are usually not dangerous,
 * but may be unwanted in some scenarios. These are usually legal applications,
 * as a result this option is deactivated by default.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_DETECT_APPL                      22

/**
 * \brief Activate detection for the specified type.
 * This detection type is for backdoor clients. While not malicious for the user,
 * they may be unwanted because they can be used to remotely control other devices.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_BDC                       23

/**
 * \brief Activate detection for the specified type.
 * This detection type is reserved for applications that will incur potentially hidden
 * costs.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_DIAL                      24

/**
 * \brief Activate detection for the specified type.
 * This detection type is reserved for some games that may be unwanted in corporate
 * environments. As they are not malicious as such, this option is deactivated by default.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_DETECT_GAME                      25

/**
 * \brief Activate detection for the specified type.
 * This detection type is reserved for files which try to hide their file extension by
 * various obfuscation techniques to trick users.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_HIDDENEXT                 26

/**
 * \brief Activate detection for the specified type.
 * This category is reserved for joke programs which are generally harmless but
 * try to play a joke or trick on users.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_DETECT_JOKE                      27

/**
 * \brief Activate detection for the specified type.
 * This category is for files which are obfuscated or packed in an uncommon fashion. These
 * cannot be considered malicious per se, but can be regarded as suspicious.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_DETECT_PCK                       28

/**
 * \brief Activate detection for the specified type.
 * This category is for detecting Phishing, malicious social engineering and related malware.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_PHISH                     29

/**
 * \brief Activate detection for the specified type.
 * Detections in this category may be a security or privacy risk to users.
 * \note Default value: 0 (disabled)
 */
#define MAVAPI_OPTION_DETECT_SPR                       30

/**
 * \brief Activate detection for the specified type.
 * Detections in this category are excessively displaying advertisements.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_ADWARE                    31

/**
 * \brief Activate detection for the specified type.
 * Detections in the category are reserved for possibly fraudulent software.
 * \note Default value: 1 (enabled)
 */
#define MAVAPI_OPTION_DETECT_PFS                       32


/**
 * \brief Activate detection for all types.
 * Enables all optional types which can be via MAVAPI_OPTION_DETECT_*.
 **/
#define MAVAPI_OPTION_DETECT_ALLTYPES                  41

/** @} */
/**
 * \ingroup options
 * \defgroup set SET options (write only)
 * \brief "SET" requests are available to configure MAVAPI. Usually a "SET" request also
 * has a "GET" request counterpart to retrieve current settings. However, the
 * following commands do not have a "GET" counterpart and are therefore labeled
 * as "write only".
 * @{
 */

/**
 * \brief Set the product key-id that is required by the application.
 * \note MAVAPI will check if the key-id is within the license and that it is not
 * expired. If it is available and is valid, the MAVAPI can be initialized and used
 * by the application.If not, most requests will result in an error response.
 */
#define MAVAPI_OPTION_PRODUCT                          40
/** @} */
/**
 * \ingroup options
 * \defgroup get GET options (read only)
 * \brief "GET" requests are available to retrieve current MAVAPI settings.
 * Usually a "GET" request also has a "SET" request counterpart to configure
 * MAVAPI. However, the following commands do not have a "SET" counterpart
 * and are therefore labeled as "read only".
 * @{
 */
/** Retrieve engine version number */
#define MAVAPI_OPTION_AVE_VERSION                      51
/** Retrieve vdf(-set) version number */
#define MAVAPI_OPTION_VDF_VERSION                      52
/** Retrieve the expiration date of the MAVAPI license (YYYYMMDD) */
#define MAVAPI_OPTION_EXPIRE                           54
/** Retrieve the number of signatures in the vdf(-set) */
#define MAVAPI_OPTION_VDFSIGCOUNT                      55
/** Retrieve the license date of the vdf(-set). Date is the form of YYYYMMDD. */
#define MAVAPI_OPTION_VDF_DATE                         67

/** @} */
/** @}*/

/**
 * \ingroup defs
 * \defgroup callbacks_id Callbacks' ids
 * @{
 */

/**
 * \brief Triggered after a file is scanned. The callback data contains the status of the last scanned file.
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
#define MAVAPI_CALLBACK_REPORT_FILE_STATUS             0

/**
 * \brief Triggered to report an error or a warning.
 * \note Can be triggered at any time, multiple times for each scanned file or subfiles.
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
#define MAVAPI_CALLBACK_REPORT_ERROR                   3

/**
 * \brief Triggered before the scanning begins. Can be used to create filters.  For example, if we want to scan only .exe files, we install
 * a PRE_SCAN callback. Before each file is scanned, the PRE_SCAN callback will be called. Inside our implementation of the callback,
 * we implement the filter. If the returned code is success, the file will be scanned, otherwise it will be skipped.
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
#define MAVAPI_CALLBACK_PRE_SCAN                       4

/**
 * \brief Triggered before opening an archive. If the returned code is success, the archive will be opened, otherwise
 * it will be skipped from opening.
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
#define MAVAPI_CALLBACK_ARCHIVE_OPEN                   5

/**
 * \brief Triggered when messages related to scan progress are available.
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
#define MAVAPI_CALLBACK_PROGRESS_REPORT                6

/** @}
 * \ingroup defs
 * \defgroup signal_ids Signal IDs
 * @{
 */
/**
 * \brief Will cause the MAVAPI instance to abort scanning process as soon as possible
 * \note The signal have no associated specific data. When calling \ref MAVAPI_send_signal function, "data"
 *       argument may be NULL.
 * \todo Add new signals as needed.
 */
#define MAVAPI_SIGNAL_SCAN_ABORT                       1

/** @}
 * \ingroup defs
 * \defgroup other_commands_ids MAVAPI commands
 * @{
 */

/**
 * @}
 * \ingroup defs
 * \defgroup scan_statuses MAVAPI scan statuses
 * @{
 */
/** Processed object is clean. */
#define MAVAPI_SCAN_STATUS_CLEAN               0
/** Viral code found during object processing. */
#define MAVAPI_SCAN_STATUS_INFECTED            1
/** Suspicious code found during object processing. */
#define MAVAPI_SCAN_STATUS_SUSPICIOUS          2
/** An error occurred during object processing */
#define MAVAPI_SCAN_STATUS_ERROR               3
/** Object processing finished. */
#define MAVAPI_SCAN_STATUS_FINISHED            4

/** @} */

/**
 * @}
 * \ingroup defs
 * \defgroup file_type File types
 * \note Used by the callbacks to report the type of the scanned file
 * @{
 */
/** Regular file (all files are regular) */
#define MAVAPI_FTYPE_REGULAR                           4
/** Known archive type */
#define MAVAPI_FTYPE_ARCHIVE                           1
/** File is in an archive */
#define MAVAPI_FTYPE_IN_ARCHIVE                        2
/** @} */
/** @} */

/**
 * \defgroup structs MAVAPI structures
 * @{
 */

/**
 * \brief The structure used at MAVAPI initialization
 */
typedef struct MAVAPI_global_init {
    /** The unique program number which identifies the 3rd party application
     * for the license checking function.
     * This has to be requested from Avira.
     */
    unsigned int program_type;

    /** Absolute path to a directory containing engine modules */
    MAVAPI_TCHAR *engine_dirpath;

    /** Absolute path to a directory containing the signature files */
    MAVAPI_TCHAR *vdfs_dirpath;

    /** Absolute path to a license file */
    MAVAPI_TCHAR *key_dir;
} MAVAPI_GLOBAL_INIT;

/**
 * \brief The structure used at MAVAPI instance creation
 */
typedef struct MAVAPI_instance_init {
    /** Initialization flags, right now no flag is defined.
     */
    unsigned int flags;
} MAVAPI_INSTANCE_INIT;

/**
 * \brief Contains data about the scanned file
 */
typedef struct MAVAPI_file_info {
    /** file name */
    MAVAPI_TCHAR *name;
    /** The file type. See \ref file_type.
     * Note: can be one or more types (ex: file is an archive and is found in an archive).
     */
    unsigned int type;
    /** The file recursion level (0 for regular files, +1 for each level in an archive) */
    unsigned int level;
} MAVAPI_FILE_INFO;

/**
 * \brief Contains data about the found malware in an infected/suspicious file
 */
typedef struct MAVAPI_malware_info {
    /** The malware name or null if file is clean */
    MAVAPI_TCHAR *name;
    /** Kind of the found malware */
    MAVAPI_TCHAR *type;
    /** Additional information about found malware (not used)*/
    MAVAPI_TCHAR *message;
    /** malware flags */
    MAVAPI_TCHAR *app_flags;
} MAVAPI_MALWARE_INFO;

/**
 * \brief Contains the data sent to a prescan callback
 */
typedef struct MAVAPI_pre_scan_data {
    /** General purpose flags field. \note Currently defined flags: none. */
    unsigned int flags;
    /** Information (name, type, level) about the scanned file */
    MAVAPI_FILE_INFO file_info;
} MAVAPI_PRESCAN_DATA;

/**
 * \brief Contains the data sent to a archive_open callback
 */
typedef struct MAVAPI_archive_open_data {
    /** General purpose flags field. \note Currently defined flags: none. */
    unsigned int flags;
    /** Information (name, type, level) about the archive to be opened */
    MAVAPI_FILE_INFO file_info;
} MAVAPI_ARCHIVE_OPEN_DATA;

/**
 * \brief Generic container
 *
 * This kind of container is very useful in case of need to store many options. It offers a very elegant
 * encapsulation and a very high flexibility (the user will not know how data will be stored).\n
 * The elements from container are accessed using a key (MAVAPI_key_value#id member). The element is accessed through
 * MAVAPI_key_value#value member and its type through MAVAPI_key_value#type member
 */
typedef struct MAVAPI_key_value {
    /** The element associated id */
    unsigned int id;
    /** The element type */
    unsigned int type;
    /** The element value */
    char *value;
} MAVAPI_KEY_VALUE;

/**
 * \brief Contains the data sent to a report file status callback
 * \note See \ref MAVAPI_CALLBACK_REPORT_FILE_STATUS
 */
typedef struct MAVAPI_file_status_data {
    /** General purpose flags field. \note Currently defined flags: none. */
    unsigned int flags;
    /** File scan answer. See \ref scan_statuses for available values */
    unsigned int scan_answer;
    /** File information (name, type, level). See \ref MAVAPI_file_info for more details */
    MAVAPI_FILE_INFO file_info;
    /**
     * \brief Malware information (name, type, etc).
     * See \ref MAVAPI_malware_info for more details.
     * \note Contains data only if the object processed is not clean.
     */
    MAVAPI_MALWARE_INFO malware_info;
    /** warning value to report
     * See \ref scan_warnings
     */
    unsigned int warning;
    /** additional info to report
     * See \ref scan_info
     */
    unsigned int info;
} MAVAPI_FILE_STATUS_DATA;

/**
 * \brief The structure associated with report error callback
 *
 * The callback is triggered each time an error occurred on scanning process
 * (an I/O error for instance). Also the callback can be called if warnings or infos
 * reports during scanning are activated.
 *
 * \note See \ref MAVAPI_CALLBACK_REPORT_ERROR
 */
typedef struct MAVAPI_error_data {
    /** Information (name, type, level) about the file where the error occured */
    MAVAPI_FILE_INFO file_info;
    /** error category see \ref error_cat */
    unsigned int category;
    /** error level see \ref error_level */
    unsigned int level;
    /** error code. See \ref rets
     * \note If error level is not MAVAPI_ELEVEL_ERROR this field contains flags.
     * See \ref scan_warnings and \ref scan_info
     */
    int code;
    /** The container contain currently only the error code string.
     * \note The \ref code is the id within container (not used)
     */
    MAVAPI_KEY_VALUE *options;
} MAVAPI_ERROR_DATA;

/**
 * \brief The structure associated with report progress callback
 *
 * The current message format looks like: "5 750/1000". This means that 5 seconds have passed
 * since the beginning of the scan of the top level file that you have passed to the engine to scan.
 * This also tells you that the current sub-object of the archive that is currently being processed is
 * _estimated_ to be 1000bytes in size according to information available in the archive, and that 750
 * bytes of this object have so far been extracted.
 * There is no way to get bytes extracted/estimated for the whole archive or the whole scan job.
 * This can only be done per sub-object. The seconds passed however are always for the whole scan job
 * started by calling MAVAPI_scan(). The value for extraction size is an estimate based on header
 * information, while most of the time it is correct, this can be completely incorrect for some archives
 * with incorrect headers information.
 *
 * \note The message might be extended in the future, so be prepared for additional content!
 */
typedef struct MAVAPI_report_progress_data {
    /** Reserved */
    unsigned int flags;
    /** the progress message, currently in the format (%d %lld/%lld)*/
    MAVAPI_TCHAR *message;
} MAVAPI_REPORT_PROGRESS_DATA;

/**
 *      \brief Structure passed by MAVAPI to a user defined callback, containing all the necessary data.
 */
typedef struct MAVAPI_callback_data {
    /** The callback id. See \ref callbacks_id */
    unsigned int type;
    /** The callback version */
    unsigned int version;
    /** Reserved */
    unsigned int flags;
    /**
     * \brief User custom data
     * \note MAVAPI will not make any assumption regarding this field. It will just be passed back to callback
     *       function
     */
    void *user_data;
    /**
     * \brief  Callbacks specific data
     */
    union specific_data {
        /** specific data for pre scan callback \n See \ref MAVAPI_pre_scan_data */
        MAVAPI_PRESCAN_DATA *pre_scan_data;
        /** specific data for archive open callback \n See \ref MAVAPI_archive_open_data */
        MAVAPI_ARCHIVE_OPEN_DATA *archive_open_data;
        /** specific data for file status callback \n See \ref MAVAPI_file_status_data */
        MAVAPI_FILE_STATUS_DATA *file_status_data;
        /** specific data for error report callback \n See \ref MAVAPI_error_data */
        MAVAPI_ERROR_DATA *error_data;
        /** specific data for report progress callback \n See \ref MAVAPI_report_progress_data */
        MAVAPI_REPORT_PROGRESS_DATA *report_progress_data;
        /** private data. Reserved for internal use */
        void *private_data;
    } callback_data;
} MAVAPI_CALLBACK_DATA;

/**
 * \brief  The structure to be passed when sending a signal
 */
typedef struct MAVAPI_signal_data {
    /** signal id. See \ref signal_ids */
    unsigned int signal_id;

    /**
     * \brief Signal specific data
     * \note Currently MAVAPI has defined only \ref MAVAPI_SIGNAL_SCAN_ABORT signal which doesn't require any
     *       data. Thus, "specific_data" field is currently empty.
     * \todo Add specific date as soon as new signals, which require data will be defined.
     */
    void *signal_data;
} MAVAPI_SIGNAL_DATA;

/**
 * \brief  The structure to be passed when sending a command
 */
typedef struct MAVAPI_command_data {
    /** signal id. See \ref signal_ids */
    unsigned int signal_id;

    /**
     * \brief Signal specific data
     * \note Currently MAVAPI has defined only \ref MAVAPI_SIGNAL_SCAN_ABORT signal which doesn't require any
     *       data. Thus, "specific_data" field is currently empty.
     * \todo Add specific date as soon as new signals, which require data will be defined.
     */
    union signal_specific_data {
    } signal_data;
    void *command_data;
} MAVAPI_COMMAND_DATA;

/**
 * \brief The structure used to retrieve MAVAPI version
 */
typedef struct MAVAPI_version {
    /** Major version of the product */
    unsigned int major;
    /** Minor version of the product */
    unsigned int minor;
    /** Major version of the build */
    unsigned int build_major;
    /** Minor version of the build */
    unsigned int build_minor;
} MAVAPI_VERSION;

/**
 * \brief The enumeration used to specify the MAVAPI's logging levels
 */
typedef enum _MAVAPI_log_level {
    /** Low level (debug, trace) messages.
     * This the service MESSAGE level equivalent
     */
    MAVAPI_LOG_DEBUG = 0,
    /** informative messages */
    MAVAPI_LOG_INFO,
    /** warning messages */
    MAVAPI_LOG_WARNING,
    /** alert messages (i.e. malware found or any other alert) */
    MAVAPI_LOG_ALERT,
    /** error messages */
    MAVAPI_LOG_ERROR
} MAVAPI_LOG_LEVEL;

/** @} */
/**
 * \defgroup typedefs MAVAPI typedefs
 * @{
 */

/**
 * \brief MAVAPI instance handle.
 */
typedef void * MAVAPI_FD;

/**
 * \brief MAVAPI callback function pointer definition.
 * \param data [IN]: Pointer to the structure containing the callback data.
 */
typedef int (*MAVAPI_CALLBACK)(MAVAPI_CALLBACK_DATA *data);


/**
* \brief Struct passed for @ref MAVAPI_LOG_CALLBACK callback
*/
typedef struct MAVAPI_callback_data_log {
    /** The log level */
    MAVAPI_LOG_LEVEL level;

    /** The default message logged. */
    const MAVAPI_TCHAR *message;

    /** The message id in case you want to override the default message. See header file mavapi_msg.h */
    int message_id;

    /** Log argument 1, may be NULL */
    const MAVAPI_TCHAR *arg1;

    /** Log argument 2, may be NULL */
    const MAVAPI_TCHAR *arg2;

    /** Log argument 3 may be NULL */
    const MAVAPI_TCHAR *arg3;
} MAVAPI_CALLBACK_DATA_LOG;

/**
 * \brief MAVAPI callback for logging. This is mainly intended for debugging purposes.
 * \param log_level [IN]: The log level for the given message
 * \param message   [IN]: The message to be logged
 * \param user_data [IN]: The user context
 * \return Nothing
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
typedef void (*MAVAPI_LOG_CALLBACK)(MAVAPI_CALLBACK_DATA_LOG * log_data, void *user_data);

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup funcs MAVAPI functions
 * @{
 */
/**
 * \brief Sets the MAVAPI logging function
 * \param log_fct   [IN]: The function used for logging. If given  function is NULL all data set with a previous
 *                        MAVAPI_set_log_callback call will be cleared so logging will not be performed anymore.
 * \param min_level [IN]: Sets the desired minimum log level. This can be used to filter unwanted log-levels, so that if a
 *                        message have a lower level, it will be automatically "thrown" by the MAVAPI
 * \param user_data [IN]: The user context
 * \return Null if success or an error code otherwise
 *
 * \note This function can be called before or/and after global initialization (calling before it's recommended, so that
 *       any error messages in the MAVAPI_initialize() can be logged)
 * \note This can be called several times in the same process, so that MAVAPI's user can change the log-level on-the-fly
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
int MAVAPI_EXP MAVAPI_set_log_callback(MAVAPI_LOG_CALLBACK log_fct,
        MAVAPI_LOG_LEVEL min_level, void *user_data);

/**
 * \brief MAVAPI initialization function
 * Initializes the MAVAPI library, according to the parameters specified in the initialization structure.
 * It should be called once per process.
 * \param MAVAPI_init [IN]: A pointer to the initialization structure, which must be filled with the proper values for initialization
 * \return Null if success or an error code otherwise
 *
 * \note The initialization function must be called a single time per process and before calling any other
 *       MAVAPI function (except the MAVAPI_set_log_callback() function).
 */
int MAVAPI_EXP MAVAPI_initialize(MAVAPI_GLOBAL_INIT *MAVAPI_init);

/**
 * \brief MAVAPI uninitialization function
 * Uninitializes the MAVAPI library, cleaning up all used resources. Once called, all subsequent MAVAPI calls will fail
 * with MAVAPI_E_NOT_INITIALIZED error code.
 * \return Null if everything went OK or an error code otherwise
 *
 * \note The uninitialization function must be called a single time per process and must be last called
 *       MAVAPI function.
 * \note All MAVAPI instances must be released before calling this function, otherwise the \ref MAVAPI_E_BUSY will be returned.
 */
int MAVAPI_EXP MAVAPI_uninitialize();

/**
 * \brief Returns MAVAPI version
 *
 * \param version [OUT]: Pointer to the structure where to store the result
 * \return MAVAPI_S_OK on success and an error otherwise
 *
 * \note If this function is called before \ref MAVAPI_initialize(),
 *       the \ref MAVAPI_E_NOT_INITIALIZED will be returned instead.
 */
int MAVAPI_EXP MAVAPI_get_version(MAVAPI_VERSION *version);

/**
 * \brief MAVAPI factory function
 * The function opens a connection to the MAVAPI daemon for client-mode, or,
 * for library mode, it creates a new MAVAPI instance.
 *
 * \param init       [IN]: Pointer to a structure containing all the initialization data needed to create a
 *                         MAVAPI instance.
 * \param MAVAPI_fd [OUT]: Handle to the MAVAPI instance. To be used in all the subsequent MAVAPI calls
 * \return Null if everything went OK or an error code otherwise
 */
int MAVAPI_EXP MAVAPI_create_instance(MAVAPI_INSTANCE_INIT *init,
        MAVAPI_FD *MAVAPI_fd);

/**
 * \brief Destroys a MAVAPI handler, previously created with \ref MAVAPI_create_instance.
 * The function closes the connection to the MAVAPI daemon for client-mode, or,
 * for library mode, it releases the MAVAPI instance.
 *
 * \param MAVAPI_fd [IN/OUT]: MAVAPI instance to be released. As a precaution, the  pointer will be
 *                            nulled in order to become very clear that pointer will be unusable for now on
 * \return Null if everything went OK or an error code otherwise
 *
 * \note \li For each handler created with \ref MAVAPI_create_instance function, the
 *       correspondent \c \b MAVAPI_release_instance must be called!
 *       \li After calling the function the \c \b MAVAPI_fd pointer will be invalid and must not be used anymore
 */
int MAVAPI_EXP MAVAPI_release_instance(MAVAPI_FD *MAVAPI_fd);

/**
 * \brief Sets user specific data.
 * This functions sets user data that will be returned untouched as <i> user_data </i>
 * member of \ref MAVAPI_CALLBACK_DATA structure.
 *
 * \param MAVAPI_fd [IN/OUT]: Handle to the MAVAPI instance.
 * \param user_data     [IN]: user specific data
 * \return MAVAPI_S_OK in case of success or an error code otherwise
 *
 * \note The user is responsible for the memory management. This function will only set the value given in the
 *       \ref MAVAPI_CALLBACK_DATA structure. It will not reserve or free memory for the data, or manipulate it in any way.
 */
int MAVAPI_EXP MAVAPI_set_user_data(MAVAPI_FD *MAVAPI_fd, void *user_data);

/**
 * \brief Registers a client defined callback.
 * \param MAVAPI_fd   [IN]: Handle to the MAVAPI instance on which the callback will be available.
 * \param callback_id [IN]: The callback type (e.g. MAVAPI_CALLBACK_REPORT_FILE_STATUS, MAVAPI_CALLBACK_ARCHIVE_OPEN etc.)
 * \param callback    [IN]: Pointer to a callback function
 * \return MAVAPI_S_OK if everything went OK or an error code otherwise\n\n
 *
 * \note Callback registering is not allowed during scanning operations, otherwise the \ref MAVAPI_E_BUSY will be returned.
 * \note Only one callback function is allowed to be registered per callback type/id. If for the given type/id
 *       a callback function was already registered then this function will return \ref MAVAPI_E_INVALID_PARAMETER
 *      \sa callbacks_id
 * \note It is the responsibility of the integrator to implement callbacks in a reentrant and thread-safe fashion.
 */
int MAVAPI_EXP MAVAPI_register_callback(MAVAPI_FD *MAVAPI_fd,
        unsigned int callback_id, MAVAPI_CALLBACK callback);

/**
 * \brief Unregisters a previously registered client defined callback
 * \param MAVAPI_fd   [IN]: Handle to the MAVAPI instance.
 * \param callback_id [IN]: The callback type (e.g. MAVAPI_CALLBACK_REPORT_FILE_STATUS, MAVAPI_CALLBACK_ARCHIVE_OPEN etc.)
 * \param callback    [IN]: Pointer to a callback function
 * \return MAVAPI_S_OK in case of success or an error code otherwise
 *
 * \note Callback unregistering is not allowed during scanning operations, otherwise the \ref MAVAPI_E_BUSY will be returned.
 * \note The callback type/id is searched by MAVAPI in its internal callback list and if found then the callback function
 *       will be removed, otherwise this function will return \ref MAVAPI_E_INVALID_PARAMETER
 * \note The MAVAPI_CALLBACK callback parameter is currently being ignored.
 */
int MAVAPI_EXP MAVAPI_unregister_callback(MAVAPI_FD *MAVAPI_fd,
        unsigned int callback_id, MAVAPI_CALLBACK callback);

/**
 * \brief Starts a scanning process. During the scan operation the registered callbacks may be triggered.
 * \param MAVAPI_fd [IN]: The handle of the MAVAPI instance that will do the scanning
 * \param file_name [IN]: The name of the file to be scanned.
 * \return Null in case of success or an error code otherwise
 *
 * \note The execution will not leave \ref MAVAPI_scan function until scan process is finished.
 * \note MAVAPI supports various scan types depending on the file_name format:
 *       - 'path/to/the/file/on/disk' for normal file scanning.
 */
int MAVAPI_EXP MAVAPI_scan(MAVAPI_FD *MAVAPI_fd, const MAVAPI_TCHAR *file_name);

/**
 * \brief Sets MAVAPI individual settings.
 * \param MAVAPI_fd [IN]: Pointer to a MAVAPI instance
 * \param option_id [IN]: The id of the option to be set
 * \param buffer    [IN]: NULL-terminated string containing the value of the option to be set
 *
 * \return MAVAPI_S_OK If everything went ok an error code otherwise.
 * \note Calling this function during a scanning operation performed by this instance will fail.
 */
int MAVAPI_EXP MAVAPI_set(MAVAPI_FD *MAVAPI_fd, unsigned int option_id,
        MAVAPI_TCHAR *buffer);

/**
 * \brief Reads MAVAPI settings.
 * \param MAVAPI_fd       [IN]: Pointer to a MAVAPI instance
 * \param option_id       [IN]: The id of the option to be retrieved
 * \param buffer         [OUT]: Buffer allocated by caller which will store the result of a successful get as a NULL terminated string.
 *                              If the buffer is NULL and the other parameters are valid, the function will set the needed buffer-size and return MAVAPI_S_OK
 * \param buffer_size [IN/OUT]: Specifies the size, given in MAVAPI_TCHAR characters, of the buffer argument.
 *                              If the buffer is not large enough, upon return it will contain the needed size. If it's
 *                              equal or larger than the needed size, it will remain unchanged.
 *
 * \return MAVAPI_S_OK If everything went ok
 *         an error code otherwise.
 */
int MAVAPI_EXP MAVAPI_get(MAVAPI_FD *MAVAPI_fd, unsigned int option_id,
        MAVAPI_TCHAR *buffer, MAVAPI_SIZE_T *buffer_size);

/**
 * \brief Sends a signal to a specific MAVAPI instance
 * The \ref MAVAPI_scan may take a long amount of time to finish scanning its target and in some
 * situations a forced abort would be desirable. In these kind of situations, MAVAPI_send_signal may help
 * by sending signals to a running MAVAPI instance (\ref MAVAPI_SIGNAL_SCAN_ABORT for instance).
 *
 * \param MAVAPI_fd [IN]: MAVAPI instance
 * \param signal_id [IN]: Identifies the signal to be sent. See \ref signal_ids "Signal IDs section"
 * \param data      [IN]: Specific data to be sent when sending the signal. See \ref MAVAPI_SIGNAL_DATA
 * \return MAVAPI_S_OK for success or an error code otherwise.
 *
 * \note The MAVAPI signals were designed to be sent asynchronously, when an event arrives (Ctrl+C was issued
 *       for instance) and if program execution is within \ref MAVAPI_scan. It makes no sense to
 *       send a signal to a MAVAPI instance when we have execution flow control.
 *       \sa Current supported \ref signal_ids
 */
int MAVAPI_EXP MAVAPI_send_signal(MAVAPI_FD *MAVAPI_fd, unsigned int signal_id,
        MAVAPI_SIGNAL_DATA* data);

/**
 * \brief Specify the new fops who will be used by the engine for reading (NOT SUPPORTED YET)
 * \param MAVAPI_fd    [IN]: MAVAPI instance
 * \param fops_pointer [IN]: Pointer to the fops to use in the current MAVAPI session
 * \param fops_context [IN]: This context will be passed back to the application by each call to the fops used
 * \return MAVAPI_S_OK for success or an error code otherwise.
 *
 * \note This function currently has no effect.
 */
int MAVAPI_EXP MAVAPI_set_fops(MAVAPI_FD *MAVAPI_fd, void *fops_pointer,
        void *fops_context);

/** @} */

#ifdef __cplusplus
}

#endif

#endif  // INCLUDE_MAVAPI_H_

