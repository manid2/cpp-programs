/*
 * debug_macros.h
 *
 *  Created on: 08-May-2018
 *      Author: Mani Kumar
 */

#ifndef DEBUG_MACROS_H_
#define DEBUG_MACROS_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <string>

//namespace LilPDF {

#define WITH_FILE_NAME
#define WITH_FUNC_NAME


#ifdef WITH_TIME_STAMP
typedef std::string PDFString;
// gets the current time stamp in micro seconds.
PDFString getLogDateTime(void);
#define TIME_STAMP getLogDateTime.c_str()
#else
#define TIME_STAMP "-"
#endif

#if defined(WITH_FILE_PATH) && !defined(WITH_FILE_NAME)
#define __FILENAME__ __FILE__
#elif defined(WITH_FILE_NAME)
// To get short form of filename
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#else
#define __FILENAME__ "-"
#endif

#if defined(WITH_CLASS_NAME)
#define CLASS_NAME _className.c_str()
#else
#define CLASS_NAME "-"
#endif

#if defined(WITH_FUNC_NAME)
#define FUNC_NAME  __FUNCTION__
#else
#define FUNC_NAME "-"
#endif

// TODO: add pid and tid

#define DEBUG_ERR(FORMAT, ...) \
        fprintf(stderr, \
                "%s, %s:%5d: %s::%s() ERR: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__);

#define DEBUG_WRN(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() WRN: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__);

#define DEBUG_INF(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() INF: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__);

//}  // namespace LPDF

#endif /* DEBUG_MACROS_H_ */
