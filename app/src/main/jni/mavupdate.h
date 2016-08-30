/* 2013 Copyright Avira Operations GmbH & Co.KG */

#ifndef INCLUDE_MAVUPDATE_H_
#define INCLUDE_MAVUPDATE_H_

#include "./mavupdate_defines.h"

/**
 * @mainpage MAVUpdate Library
 *
 * The main goal of MAVUpdate Library is to provide you with the update technology used by
 * the Avira Updater.
 *
 * For more information please consult the documentation.
 *
 * 2013 Copyright Avira Operations GmbH & Co.KG
 * Kaplaneiweg 1 D-88069 Tettnang Germany
 *
 */

/**
 * @defgroup data MAVUPDATE data
 */

/**
 * @ingroup data
 * @defgroup version Version
 * @{
 */

/**
 * \brief The structure used to retrieve MAVUPDATE library version - i.e. @ref mavupdate_get_version
 */
typedef struct MAVUPDATE_version {
    /** Major version of the product */
    unsigned int major;
    /** Minor version of the product */
    unsigned int minor;
    /** Major version of the build */
    unsigned int build_major;
    /** Minor version of the build */
    unsigned int build_minor;
} MAVUPDATE_VERSION;
/**
 * @}
 */

/**
 * @ingroup data
 * @defgroup init Initialization
 * @{
 */

/**
 * \brief The structure used at MAVUPDATE library initialization - i.e. @ref mavupdate_initialize
 */
typedef struct MAVUPDATE_init {
    /**
     * \brief The path to the resource file
     */
     // const MAVUPDATE_TCHAR *resource_file;

    /**
     * \brief Reserved for future use
     */
    void *reserved;
} MAVUPDATE_INIT;
/**
 * @}
 */

/**
 * @ingroup data
 * @defgroup options Options
 * @{
 */
/**
 * \brief Defines all supported options to be used to configure (@ref mavupdate_set) and/or
 *        retrieve the configuration (@ref mavupdate_get) of the MAVUPDATE library
 * \note Every option has a short description, the default value ('Default value: value') and
 *       its map to the configuration file ('Configuration file: option name') and the command
 *       line ('Command line: accepted option(s) name(s)).
 * \note The options that has no default will be marked with the "Default value: None" string.
 */
typedef enum MAVUPDATE_option {
    /**
     * \brief Set the path to the folder containing the license file(s)
     * \note Default value: The path specified for @ref MAVUPDATE_OPTION_INSTALL_DIR
     */
    MAVUPDATE_OPTION_LICENSE_DIR,

    /**
     * \brief Specifies if the library should check or not product's license.
     *        This check ensuring that there is a valid license available which will work 
     *        with the files to be downloaded by the update.
     * \note Default value: 1 (enabled)
     */
    MAVUPDATE_OPTION_LICENSE_CHECK,

    /**
     * \brief Set the username used to authenticate to the server
     * \note Default value: None
     */
    MAVUPDATE_OPTION_USERNAME,

    /**
     * \brief Set the password used to authenticate to the server
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PASSWORD,

    /**
     * \brief Use proxy from system
     * \note Default value: 0 (disabled)
     * \note Implementation to be determined
     */
    MAVUPDATE_OPTION_PROXY_SYSTEM,

    /**
     * \brief Set the proxy server hostname or address
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PROXY_HOST,

    /**
     * \brief Set the Proxy port
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PROXY_PORT,

    /**
     * \brief Set the username used to authenticate (if proxy authentication is required) to the proxy server
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PROXY_USERNAME,

    /**
     * \brief Set the password used to authenticate (if proxy authentication is required) to the proxy server
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PROXY_PASSWORD,

    /**
     * \brief Set the server used for Internet update.
     *        As an example: "http://updaterserver.com/directory"
     * \note Default value: None
     * \note Only http is supported at the moment.
     */
    MAVUPDATE_OPTION_SRVS_INTERNET,

    /**
     * \brief If this flag is true then the master file is not downloaded and checked
     * \note Default value: 0 (disabled) - master file is downloaded
     */
    MAVUPDATE_OPTION_MASTER_FILE_SKIP,

    /**
     * \brief Contains a path to the product file relative to Default Server.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_PRODUCT_FILE,

    /**
     * \brief Contains the directory to be used for install new files.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_INSTALL_DIR,

    /**
     * \brief Contains the directory to be used for temporary downloading / storing update files.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_TEMP_DIR,

    /**
     * \brief Path to be used as backup folder
     * \note Default value: None
     * \note Implementation to be determined
     */
    MAVUPDATE_OPTION_BACKUP_DIR,

    /**
     * \brief Set internet protocol: auto, ipv4, ipv6
     * \note Default value: "auto"
     * \note Implementation to be determined
     */
    MAVUPDATE_OPTION_INTERNET_PROTOCOL,

    /**
     * \brief User agent string which will be reported to the http server
     * \note Default value: "[<product-name>; ]AntiVir-UpdateCP/<updater version> (<target>;<product>; AVE <engine version>; VDF <version>; <language>; <operating system>)"
     * \note The product-name will be set only if the product-name file is specified (@ref MAVUPDATE_OPTION_PRODUCT_NAME_FILE) or if the default product-name file is present
     */
    MAVUPDATE_OPTION_USER_AGENT,

    /**
     * \brief Authentication type: basic, digest, ntlm, any
     * \note Default value: "any"
     */
    MAVUPDATE_OPTION_AUTH_TYPE,

    /**
     * \brief Product-name for use in User Agent String
     * \note Its content will be prepended to the user-agent string
     */
    MAVUPDATE_OPTION_UAS_PRODUCT_NAME,

    /**
     * \brief Sets a unique User Id for the User Agent String
     * \note This will be used to generate backend statistics and is a mandatory option for products
     *       connecting to Avira Servers.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_UAS_UNIQUE_ID,

    /**
     * \brief Sets 2 letter country code for use in User Agent String
     * \note Country information if available, Format is OS specific, may use locale info. ("en_US")
     * \note Default value: None
     */
    MAVUPDATE_OPTION_UAS_COUNTRY,

    /**
     * \brief Sets OS Language for use in User Agent String
     * \note OS Language in two-letter alpha country code as per ISO 3166-1-alpha-2 code elements.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_UAS_OS_LANGUAGE,

    /**
     * \brief Sets Product Language for use in User Agent String
     * \note OS Language in two-letter alpha country code as per ISO 3166-1-alpha-2 code elements.
     * \note Default value: None
     */
    MAVUPDATE_OPTION_UAS_PRODUCT_LANGUAGE,

    /**
     * \brief Build number of the product for use in User Agent String
     * \note Format to use when connecting to Avira servers is "BUILD Major.Minor.Revision.Build"
     * \note Default value: None
     */
    MAVUPDATE_OPTION_UAS_BUILD



} MAVUPDATE_OPTION;

/**
 * @}
 */

/**
 * @ingroup data
 * @defgroup callbacks Callbacks
 * @{
 */

/**
 * \brief The possible return codes for a callback
 * \note The ret code of @ref MAVUPDATE_CALLBACK_LOG callback will be ignored
 */
typedef enum MAVUPDATE_callback_ret {
    /**
     * \brief Use this code to continue the execution
     */
    MAVUPDATE_CRET_CONTINUE = 0,

    /**
     * \brief Use this code to abort the execution
     */
    MAVUPDATE_CRET_ABORT,
} MAVUPDATE_CALLBACK_RET;

/**
 * \brief The available callbacks
 */
typedef enum MAVUPDATE_callback {
    /**
     * \brief The callback used for logging
     * \note Its callback-data is a pointer to the @ref MAVUPDATE_CDATA_LOG structure
     * \note This callback can be triggered by any MAVUPDATE function
     */
    MAVUPDATE_CALLBACK_LOG = 0,

    /**
     * \brief Gives info about the total number of files
     * \note Its callback-data is a pointer to the @ref MAVUPDATE_CDATA_DOWNLOAD_ALL_FILES structure
     * \note This callback is triggered twice only by the @ref mavupdate_download_files function: 1-st
     *       time before the download to start and 2-nd right after the download was finished.
     */
    MAVUPDATE_CALLBACK_DOWNLOAD_ALL,

    /**
     * \brief Gives info about each downloaded file
     * \note Its callback-data is a pointer to the @ref MAVUPDATE_CDATA_DOWNLOAD_FILE structure
     * \note This callback is triggered by the @ref mavupdate_check_for_updates and @ref mavupdate_download_files
     *       functions and it's called several times per file
     */
    MAVUPDATE_CALLBACK_DOWNLOAD_FILE,
} MAVUPDATE_CALLBACK;

/**
 * \brief Defines the available log levels
 */
typedef enum MAVUPDATE_log_level {
    /** Low level (debug, trace) messages. */
    MAVUPDATE_LOG_LEVEL_DEBUG = 0,
    /** informative messages */
    MAVUPDATE_LOG_LEVEL_INFO,
    /** warning messages */
    MAVUPDATE_LOG_LEVEL_WARNING,
    /** error messages */
    MAVUPDATE_LOG_LEVEL_ERROR,
} MAVUPDATE_LOG_LEVEL;

/**
 * \brief Struct passed to @ref MAVUPDATE_CDATA_LOG
 */
typedef struct MAVUPDATE_callback_data_log_args {
    /** Log argument 1 */
    const MAVUPDATE_TCHAR *arg1;
    /** Log argument 2 */
    const MAVUPDATE_TCHAR *arg2;
    /** Log argument 3 */
    const MAVUPDATE_TCHAR *arg3;
} MAVUPDATE_LOG_ARGS;

/**
 * \brief Struct passed for @ref MAVUPDATE_CALLBACK_LOG callback
 */
typedef struct MAVUPDATE_callback_data_log {
    /** The log level */
    MAVUPDATE_LOG_LEVEL level;

    /** The message logged */
    const MAVUPDATE_TCHAR *message;

    /** The message id */
    int message_id;

    /* Log message arguments  */
    MAVUPDATE_LOG_ARGS args;
} MAVUPDATE_CDATA_LOG;

/**
 * \brief The structure passed to the @ref MAVUPDATE_CALLBACK_DOWNLOAD_ALL callback
 */
typedef struct MAVUPDATE_cdata_download_all_files {
    /**
     * \brief The name/address of the server used to download the files
     */
    const MAVUPDATE_TCHAR *server;

    /**
     * \brief The number of files to be downloaded
     */
    size_t count;

    /**
     * \brief The total size to be downloaded
     */
    size_t total_size;

    /**
     * \brief Total size downloaded
     * \note This will be filled when the last @ref MAVUPDATE_CALLBACK_DOWNLOAD_ALL
     */
    size_t completed_size;
} MAVUPDATE_CDATA_DOWNLOAD_ALL_FILES;

/**
 * \brief The structure passed to the @ref MAVUPDATE_CALLBACK_DOWNLOAD_FILE callback
 */
typedef struct MAVUPDATE_cdata_download_file {
    /**
     * \brief Info about the path of the file: remote (src)
     */
    const MAVUPDATE_TCHAR *src;

    /**
     * \brief Info about the path of the file: local (dest)
     */
    const MAVUPDATE_TCHAR *dest;

    /**
     * \brief Info about the file size: total size
     */
    size_t total_size;

    /**
     * \brief Info about the file size: completed size
     */
    size_t completed_size;

    /**
     * \brief If set to 1, the file is already in the temporary file and will not be downloaded again
     *        Otherwise, the file is downloaded from the server
     */
    unsigned int resume;
} MAVUPDATE_CDATA_DOWNLOAD_FILE;

/**
 * \brief The callback function of mavupdate library
 * \param[in] callback_id   The id of the callback (log, progress, download file)
 * \param[in] callback_data Pointer to the callback data
 * \param[in] user_data     Pointer to the user defined data
 * \return one valid @ref MAVUPDATE_CALLBACK_RET value
 */
typedef MAVUPDATE_CALLBACK_RET (*MAVUPDATE_CALLBACK_FN)(MAVUPDATE_CALLBACK callback_id, const void *callback_data,
        void *user_data);
/**
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup funcs MAVUPDATE functions
 * @{
 */

/**
 * \brief Retrieves the library version
 * \param[out] version Pointer to the version structure
 * \note This function can be called before or/and after global initialization
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if version is NULL
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_get_version(MAVUPDATE_VERSION *version);

/**
 * \brief Performs global initialization
 * \param[in] init_data Pointer to the structure used to store initialization data
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_UPDATE_ALREADY_INITIALIZED if the function is called two times without
 *         calling @ref mavupdate_uninitialize()
 * \retval MAVUPDATE_E_INVALID_PARAMETER if the init_data is NULL
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_initialize(const MAVUPDATE_INIT *init_data);

/**
 * \brief Performs global uninitialization
 * \note  Uninitializes the MAVUPDATE library, cleaning up all used resources. Once called,
 *        all subsequent MAVUPDATE calls will fail with MAVUPDATE_E_NOT_INITIALIZED error code.
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_NOT_INITIALIZED if the library was not initialized
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_uninitialize();

/**
 * \brief Sets callback's function and user-data used by the MAVUpdate interface
 * \param[in] callback_fn User defined function that will be called as callback by the library
 * \param[in] user_data   User defined data that will be passed to the callback function
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if the @a callback_fn is NULL
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_set_callback(const MAVUPDATE_CALLBACK_FN callback_fn, void *user_data);

/**
 * \brief Sets MAVUPDATE individual settings.
 * \param[in] option ID of the option to be set. The available ID's can be found in the @ref MAVUPDATE_OPTION enum
 * \param[in] value  New value for the option
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if the @a option is not valid or @a value is NULL
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_set(MAVUPDATE_OPTION option, const MAVUPDATE_TCHAR *value);

/**
 * \brief Reads MAVUPDATE settings.
 * \param[in]     option ID of the option to be set. The available ID's can be found in the @ref MAVUPDATE_OPTION enum
 * \param[in,out] value  Value of the option
 * \param[in,out] size   Specifies the size, given in MAVUPDATE_TCHAR characters, of the @a value argument.
 *                       If the buffer is not large enough, upon return it will contain the needed size. If it's
 *                       equal or larger than the needed size, it will remain unchanged.
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if the @a option is not valid or @a size is NULL
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_get(MAVUPDATE_OPTION option, MAVUPDATE_TCHAR *value, size_t *size);

/**
 * \brief Checks if there are any files to be updated
 * \param[out] result 0 - no updates available, 1 - there are updates available
 * \note After checking for updates, the next logical function call will be @ref mavupdate_download_files
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if the @a result is NULL
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_check_for_updates(unsigned int *result);

/**
 * \brief Start downloading files to be updated
 * \note The @ref mavupdate_check_for_updates function must be called prior to calling this function
 * \note After this call, the next logical function will be @ref mavupdate_install_files
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_download_files();

/**
 * \brief Start installing downloaded files
 * \note The @ref mavupdate_download_files function must be called prior to calling this function
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval other library error codes
 */
MAVUPDATE_RET MAVUPDATE_EXP mavupdate_install_files();

/**
 * \brief Helper function to retrieve a message from the message resources
 * \param[out] msg_out      The retrieved message. Its pointer (i.e. @a *msg_out) must be NULL.
 * \param[in]  msg_id       The message ID to extract from the resource file
 * \param[in]  params_array NULL terminated list of arguments needed to compose the message
 * \note The retrieved @a msg_out must be deallocated by using the @ref mavupdate_free_tchar function.
 * \note The pointer of the @a msg_out (i.e. @a *msg_out) must be NULL, otherwise the function call could trigger memory leaks.
 *
 * \retval MAVUPDATE_S_OK for success
 * \retval MAVUPDATE_E_INVALID_PARAMETER if msg_out is NULL or *msg_out is not NULL
 *
 * Example of usage:
 * @code
 *      MAVUPDATE_TCHAR* tchar_ptr = NULL;
 *      MAVUPDATE_TCHAR *argv[] = {_T("dummy"), NULL};
 *      MAVUPDATE_RET rc = mavupdate_get_message(&tchar_ptr, MAVUPDATE_MSG_ID_PARSER_PROCESS_CMD_LINE_1_E, argv);
 *      ...
 *      mavupdate_free_tchar(&tchar_ptr);
 * @endcode
 */
//MAVUPDATE_RET MAVUPDATE_EXP mavupdate_get_message(MAVUPDATE_TCHAR **msg_out, unsigned int msg_id,
//        const MAVUPDATE_TCHAR **params_array);

/**
 * \brief Helper function that frees an MAVUPDATE_TCHAR buffer allocated in the MAVUPDATE library through the function @ref mavupdate_get_message
 * \param[in,out] buffer Address to the buffer that need to be cleared from memory
 * \note Must be used only in conjunction with @ref mavupdate_get_message, otherwise the behavior is undefined
 * \note This function can be called before or/and after global initialization
 *
 * \retval Nothing
 */
//void MAVUPDATE_EXP mavupdate_free_tchar(MAVUPDATE_TCHAR **buffer);
/** @} */

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_MAVUPDATE_H_

