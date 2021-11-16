//
// Created by malanore on 11/13/21.
//

#pragma once

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif

#ifdef _MSC_VER
#define API_EXPORT __declspec(dllexport)
#define API_C_EXPORT EXTERN_C __declspec(dllexport)
#else
#define API_EXPORT
#define API_C_EXPORT EXTERN_C
#endif

#define ARG_IN
#define ARG_OUT

#ifdef __cplusplus
#include <cstdint>
#include <cstdio>
#include <cstring>
#else
#include <stdin.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#endif

#if !defined(__cplusplus) && (!defined(__STDC__) || (__STDC_VERSION__ < 199901L))
/*! \brief Inline specifier no-op in C using standards before C99. */
#define INLINE_FUNCTION
#else
/*! \brief Inline specifier */
#define INLINE_FUNCTION inline
#endif

#if !defined(__cplusplus) && (!defined(__STDC__) || (__STDC_VERSION__ < 201112L))
/*! \brief Thread local specifier no-op in C using standards before C11. */
#define THREAD_LOCAL
#elif !defined(__cplusplus)
/*! \brief Thread local specifier. */
#define THREAD_LOCAL _Thread_local
#elif defined(_MSC_VER)
/*! \brief Thread local specifier. */
#define THREAD_LOCAL __declspec(thread)
#else
/*! \brief Thread local specifier */
#define THREAD_LOCAL thread_local
#endif

// -----------------------------------------------------
// --------------------- API Begin ---------------------


// ---------------------- API End ----------------------
// -----------------------------------------------------

/*!
 * \brief Handle of error message.
 * \return Error message
 */
static char* LastErrorMsg() {
  static THREAD_LOCAL char err_msg[512] = "Everything is fine";
  return err_msg;
}

INLINE_FUNCTION void SetLastError(const char* msg) {
  const int err_buf_len = 512;
  snprintf(LastErrorMsg(), err_buf_len, "%s", msg);
}
