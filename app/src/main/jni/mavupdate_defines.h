#ifndef INCLUDE_MAVUPDATE_DEFINES_H_
#define INCLUDE_MAVUPDATE_DEFINES_H_

#include <stddef.h>
/**
 *
 * 2012 Copyright Avira Operations GmbH & Co.KG
 * Kaplaneiweg 1 D-88069 Tettnang Germany
 *
 */

#define _UNIX 1
#define _ANSI 1

#if !defined(_WINDOWS) && !defined(_UNIX)
#   error    "Please define a supported platform!"
#endif /* !defined(_WINDOWS) && !defined(_UNIX) */

/**
 * \ingroup data
 * \defgroup types Platform dependent defines
 * @{
 */
#ifdef _WINDOWS
#   ifdef MAKINGDLL_MAVUPDATE
#       define MAVUPDATE_EXP __declspec(dllexport)
#   else /* when using the DLL */
#       define MAVUPDATE_EXP __declspec(dllimport)
#   endif /* MAKINGDLL_MAVUPDATE */
#else /* on UNIX */
#   define MAVUPDATE_EXP
#endif /* _WINDOWS */

#if defined(_WINDOWS)
#   include <tchar.h>
#   define MAVUPDATE_TCHAR TCHAR
#else /* _UNIX */
#   define MAVUPDATE_TCHAR char
#   if !defined(_T)
#       define _T(x) x
#   endif /* _T */
#endif /* _WINDOWS */
/**
 * @}
 */

/**
 * \ingroup data
 * \defgroup codes Return codes
 * @{
 */
/**
 * \brief Update errors returned from update library functions
 */
typedef enum MAVUPDATE_ret {
    /* no error -> everything goes fine */
    MAVUPDATE_S_OK = 0,

    /**
     * \brief One of supplied parameters is invalid
     * \note At least one of the function's parameters is invalid (invalid pointers,
     * empty strings, out of range values, etc.)
     */
    MAVUPDATE_E_INVALID_PARAMETER = 1,

    /**
     * \brief MAVUpdate library already initialized
     * \note This means that @ref mavupdate_initialize was already called
     */
    MAVUPDATE_E_UPDATE_ALREADY_INITIALIZED = 2,

    /**
     * \brief Update library is not initialized
     * \note This means that @ref mavupdate_initialize was not called
     */
    MAVUPDATE_E_NOT_INITIALIZED = 3,

    /**
     * \brief Supplied buffer is too small
     * \note An interface function that requires a buffer size as parameter was called
     * with a value smaller than the needed size
     */
    MAVUPDATE_E_BUFFER_TOO_SMALL = 4,

    /**
     * \brief The required parameter was not set
     * \note This error is returned from @ref mavupdate_get when the requested parameter
     * was not set
     */
    MAVUPDATE_E_PARAMETER_NOT_SET = 5,

    /**
     * \brief Converting failed
     * \note A string could not be converted from one encoding to another or a string
     * could not be converted to a numerical value
     */
    MAVUPDATE_E_CONVERSION_ERROR = 6,

    /**
     * \brief Unknown option ID received
     * \note This error is returned from @ref mavupdate_get and @ref mavupdate_set when the required
     * option ID is not known
     */
    MAVUPDATE_E_OPTION_NOT_SUPPORTED = 7,

    /**
     * \brief Invalid option value received
     * \note This error is returned from @ref mavupdate_set if the given value is not valid
     */
    MAVUPDATE_E_INVALID_VALUE = 8,

    /**
     * \brief Out of memory
     */
    MAVUPDATE_E_NO_MEMORY = 9,

    /**
     * \brief No valid license key found
     */
    MAVUPDATE_E_LICENSE_CHECK = 10,

    /**
     * \brief Invalid value for @ref MAVUPDATE_OPTION_INTERNET_PROTOCOL
     */
    MAVUPDATE_E_INVALID_INTERNET_PROTOCOL_DATA = 13,

    /**
     * \brief Invalid value for @ref MAVUPDATE_OPTION_AUTH_TYPE
     */
    MAVUPDATE_E_INVALID_UPDATE_AUTH_TYPE_DATA = 14,

    /**
     * \brief The update file-tree has not been downloaded or it is corrupted
     * \note If this error occurs, the @ref mavupdate_check_for_updates function should be (re)called
     */
    MAVUPDATE_E_INVALID_UPDATE_TREE = 17,

    /**
     * \brief Update process aborted by user
     */
    MAVUPDATE_E_USER_ABORT = 18,

     /** 
      * \brief Unknown compression algorithm
      * \note This error is returned only if the file extension is not '.gz'
      */
    MAVUPDATE_E_ARCHIVE_MANAGER_UNKNOWN_ALGO = 22,
    
    /* download manager */
    /**
     * \brief Error initializing curl download manager
     */
    MAVUPDATE_E_DOWNLOAD_MANAGER_CURL_INIT = 25,

    /**
     * \brief Error while downloading using curl download manager
     */
    MAVUPDATE_E_DOWNLOAD_MANAGER_CURL_DOWNLOAD = 26,

    /**
     * \brief Error while downloading using file download manager
     */
    MAVUPDATE_E_DOWNLOAD_MANAGER_FILE_DOWNLOAD = 27,

    /**
     * \brief The file is neither info nor idx
     * \note This means that the idx or info file does not have the MD5 present at the end
     */
    MAVUPDATE_E_NEITHER_INFO_NOR_IDX = 34,

    /**
     * \brief File integrity check failed
     * \note This error is returned when the MD5 present at the end of an info or an idx file is different from the
     * calculated file MD5
     */
    MAVUPDATE_E_FILE_INTEGRITY_CHECK_FAILED = 35,

    /**
     * \brief Can not get file
     */
    MAVUPDATE_E_GET_FILE = 36,

    /**
     * \brief The MD5 of the file is different than the one specified in the info file
     */
    MAVUPDATE_E_CHECK_FILE_MD5 = 37,

    /**
     * \brief Error while retrieving the path of the system directory
     */
    MAVUPDATE_E_GET_SYSTEM_DIRECTORY = 38,

    /* MAVUPDATE_E_MARK... */
    /**
     * \brief Error returned when checking if a file is dirty
     */
    MAVUPDATE_E_MARK_CHECK_DIRTY = 39,

    /**
     * \brief Error while marking modules
     */
    MAVUPDATE_E_MARK_MODULE = 40,

    /**
     * \brief Error while marking file
     */
    MAVUPDATE_E_MARK_FILE = 41,

    /**
     * \brief Error while marking dirty files
     */
    MAVUPDATE_E_MARK_DIRTY_FILES = 42,

    /* MAVUPDATE_E_CHECK */
    /**
     * \brief Error while parsing product file
     */
    MAVUPDATE_E_CHECK_PARSE_PRODUCT_FILE = 44,

    /**
     * \brief Error while parsing an xml file
     * \note This error is returned by xml parser
     */
    MAVUPDATE_E_CHECK_SCEW_PARSER_LOAD_XML_FILE = 45,

    /**
     * \brief Error while replacing includes
     */
    MAVUPDATE_E_CHECK_REPLACE_INCLUDES = 46,

    /**
     * \brief Error while searching includes
     */
    MAVUPDATE_E_CHECK_SEARCH_INCLUDE = 47,

    /**
     * \brief Path to the installation directory was not set
     */
    MAVUPDATE_E_CHECK_INSTALL_DIR_DATA = 53,

    /**
     * \brief Path to the product file was not set
     */
    MAVUPDATE_E_CHECK_PRODUCT_FILE_DATA = 54,

    /**
     * \brief No download servers provided
     */
    MAVUPDATE_E_CHECK_DOWNLOAD_SRVS_DATA = 55,

    /**
     * \brief Cannot install info file
     */
    MAVUPDATE_E_CHECK_INSTALL_INFO_FILE = 56,

    /* MAVUPDATE_E_COMPUTE_... */
    /**
     * \brief Error while computing total size
     */
    MAVUPDATE_E_COMPUTE_TOTAL_SIZE = 57,

    /**
     * \brief Error while computing module total size
     */
    MAVUPDATE_E_COMPUTE_MODULE_TOTAL_SIZE = 58,

    /**
     * \brief Error while computing file total size
     */
    MAVUPDATE_E_COMPUTE_FILE_TOTAL_SIZE = 59,

    /* MAVUPDATE_E_DLD_... */
    /**
     * \brief Error while downloading module
     */
    MAVUPDATE_E_DLD_MODULE = 60,

    /**
     * \brief Error while downloading file
     */
    MAVUPDATE_E_DLD_FILE = 61,

    /**
     * \brief The file is not signed by avira
     */
    MAVUPDATE_E_DLD_CHECK_FILE_SIGNATURE = 67,

    /**
     * \brief Error while rollbacking module
     */
    MAVUPDATE_E_ROLLBACK_MODULE = 68,

    /**
     * \brief Error while copying file
     */
    MAVUPDATE_E_PROCESS_COPY_FILE = 69,

    /**
     * \brief Error while processing file
     */
    MAVUPDATE_E_PROCESS_FILE = 70,

    /**
     * \brief Error while processing module
     */
    MAVUPDATE_E_PROCESS_MODULE = 73,

    /**
     * \brief Error while performing update
     */
    MAVUPDATE_E_PERFORM_UPDATE = 74,

    /**
     * \brief Error while updating product
     */
    MAVUPDATE_E_UPDATE_PRODUCT = 76,

    /**
     * \brief Error while installing idx files
     */
    MAVUPDATE_E_INSTALL_IDX_FILES = 77,

    /**
     * \brief Error while marking dirty depend modules
     */
    MAVUPDATE_E_MARK_DIRTY_DEPEND_MODULES = 78,

    /**
     * \brief A rollback was performed because an error occurred while updating
     */
    MAVUPDATE_E_ROLLBACK_PERFORMED = 79,

    /**
     * \brief Error deleting directory
     */
    MAVUPDATE_E_REMOVE_DIR = 80,

    /**
     * \brief MAVUpdate internal error
     * \note An unexpected internal event prevented the normal execution of the library
     * (incorrect pointers, incorrect return values, etc.). Normally this error should
     * never occur
     */
    MAVUPDATE_E_INTERNAL = 82,

    /**
     * \brief An unexpected internal error code received
     * \note This usually indicates an implementation bug
     */
    MAVUPDATE_E_UNKNOWN = 83,

    /**
     * \brief File could not be opened
     * \note For example, the product-name-file does not exist
     */
    MAVUPDATE_E_FILE_OPEN = 84,

    /**
     * \brief File could not be read
     * \note For example, the product-name file does not have read permissions
     */
    MAVUPDATE_E_FILE_READ = 85,

    /**
     * \brief Wrong file contents detected
     * \note For example the product-name file contains non-printable characters
     */
    MAVUPDATE_E_FILE_WRONG_CONTENT = 86,
} MAVUPDATE_RET;
/**
 * @}
 */

#endif  // INCLUDE_MAVUPDATE_DEFINES_H_
