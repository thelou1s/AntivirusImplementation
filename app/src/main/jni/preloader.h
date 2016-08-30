/* Copyright:  2013 Copyright (c) Avira Operations GmbH & Co.KG
 * =====================================================================================
 *
 *       Filename:  preloader.h
 *
 *    Description:  Functions to preload libraries
 *
 *        Version:  1.0
 *        Created:  02/26/2013 09:45:50 AM
 *
 *   Organization:  2013 Avira Operations GmbH & Co.KG
 *
 * =====================================================================================
 */
#ifndef INCLUDE_PRELOADER_H_
#define INCLUDE_PRELOADER_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MAVPRELOAD_MAJOR       1
#define MAVPRELOAD_MINOR       0
#define MAVPRELOAD_BUILD_MAJOR 0
#define MAVPRELOAD_BUILD_MINOR 0


/**
 * Preloading library function
 * \param path Library path
 * \return Retuns 0 if preload was successful, -1 if path is NULL
 *                -2 if path is too long, and -3 if error occures
 *                during loading of shared object
 */

int preload(char * path);
/**
 * Unloading library and freeing resources
 */

void unload();

#ifdef __cplusplus
}
#endif
#endif  // INCLUDE_PRELOADER_H_
