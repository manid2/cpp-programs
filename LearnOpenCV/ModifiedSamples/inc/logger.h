/****************************************************************************\
 * Copyright (c) 2018 Mani Kumar <maniyoung.d2@gmail.com>
 * ---------------------------------------------------------------------------
 * Project     :  FacialFeaturesRecognizer
 * Author      :  Mani Kumar
 * License     :  GNU GPL v3
 * Origin date :  08-Aug-2018
 *
 * Filename    :  logger.h
 * Description :  Header only logger utility for the project.
 \***************************************************************************/

#ifndef FFR_INC_LOGGER_H_
#define FFR_INC_LOGGER_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <string>

namespace FFR {

// define default log prefixes
#ifndef WITH_TIME_STAMP
#  define WITH_TIME_STAMP
#endif

#ifndef WITH_FILE_NAME
#  define WITH_FILE_NAME
#endif

#ifndef WITH_CLASS_NAME
#  define WITH_CLASS_NAME
#endif

#ifndef WITH_FUNC_NAME
#  define WITH_FUNC_NAME
#endif

typedef std::string String;
static String getLogDateTime(void) {
  struct timeval tv;
  gettimeofday(&tv, 0);

  struct tm ltm;
  localtime_r(&tv.tv_sec, &ltm);

  char timeBuf[80];
  size_t len = strftime(timeBuf, sizeof timeBuf, "%m/%d %H:%M:%S", &ltm);
  sprintf(timeBuf + len, "%06ld", tv.tv_usec);

  return String(timeBuf);
}

#ifdef WITH_TIME_STAMP
// gets the current time stamp in micro seconds.
#define TIME_STAMP getLogDateTime().c_str()
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

// disable verbose debug info - begin
#define DISABLE_DEBUG_INF
#define DISABLE_DEBUG_FUNC
// disable verbose debug info - end

// TODO: add pid and tid
#define DEBUGLE(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() ERR: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__)

#define DEBUGLW(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() WRN: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__)

#ifdef DISABLE_DEBUG_FUNC
# define DEBUGLF(FORMAT, ...)
#else
# define DEBUGLF(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() FUNC: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__)
#endif // DISABLE_DEBUG_FUNC

#ifdef DISABLE_DEBUG_INF
# define DEBUGLD(FORMAT, ...)
#else
# define DEBUGLD(FORMAT, ...) \
        fprintf(stdout, \
                "%s, %s:%5d: %s::%s() INF: " FORMAT ,\
                TIME_STAMP, __FILENAME__, __LINE__, CLASS_NAME, FUNC_NAME, ##__VA_ARGS__)
#endif // DISABLE_DEBUG_INF

}

#endif // FFR_UTIL_LOGGER_H_
