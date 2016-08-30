/* Copyright 2012 Avira GmbH */

#ifndef INCLUDE_MTCHAR_H_
#define INCLUDE_MTCHAR_H_
/**
 * \file stchar.h
 * \brief Conversion between MAVAPI_TCHAR and char//TCHAR
 *
 * UNICODE (WIN) MAVAPI_TCHAR = wchar_t(UCS2) |  char(UTF-8)
 * UNICODE (UNIX) MAVAPI_TCHAR = wchar_t(UCS2) | char(locale)
 * ANSI (WIN + UNIX) MAVAPI_TCHAR = char(locale)  | char(locale)
 *
 * \note Currently only _UNIX and _ANSI are supported.
 */

#ifdef __cplusplus
extern "C" {
#endif

#define _UNIX 1
#define _ANSI 1

/* Checks for the platform defines: _WINDOWS or _UNIX */
#if !defined(_WINDOWS) && !defined(_UNIX)
#   error    "Please define a supported platform!"
#endif /* !defined(_WINDOWS) && !defined(_UNIX) */

/* Checks for the build encoding defines: _UNICODE or _ANSI */
#if !defined(_UNICODE) && !defined(_ANSI)
#   error    "Please define a supported encoding!"
#endif /* !defined(_UNICODE) && !defined(_ANSI) */

#ifdef _WINDOWS
#   error    "Please define a supported platform!"
//#   ifdef MAKINGDLL_MAVAPI
//#       define MAVAPI_EXP __declspec(dllexport)
//#   else /* when using the DLL */
//#       define MAVAPI_EXP __declspec(dllimport)
//#   endif /* MAKINGDLL_MAVAPI */
#else /* on UNIX */
#   define MAVAPI_EXP
#endif /* _WINDOWS */

#if defined(_WINDOWS)
#   error    "Please define a supported platform!"
//#   include <tchar.h>
//#   define MAVAPI_TCHAR TCHAR
//#   define MAVAPI_SIZE_T size_t
#else /* _UNIX */
#   if defined(_UNICODE) /* UNIX, UNICODE */
#   error    "Please define a supported encoding!"
//#       include <wchar.h>
//#       define MAVAPI_TCHAR wchar_t
//#       define MAVAPI_SIZE_T size_t
#   else /* UNIX, ANSI */
#       define MAVAPI_TCHAR char
#       define MAVAPI_SIZE_T unsigned int
#       define _T(x) x
#   endif /* defined(_UNICODE) */
#endif /* _WINDOWS */

#ifdef __cplusplus
}
#endif

#endif  // INCLUDE_MTCHAR_H_
