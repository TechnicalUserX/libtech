#ifndef TECH_TYPES_H
#define TECH_TYPES_H

#ifndef TECH_FEATURES_H
#error "Include tech_features.h before including this header file"
#endif

#ifndef TECH_INCLUDE_H
#error "Include tech_include.h before including this header file"
#endif

#define TECH_RETURN_SUCCESS 0
#define TECH_RETURN_FAILURE 1

#include "tech_include.h"

typedef unsigned char tech_byte_t;

typedef char tech_char_t;

typedef int8_t tech_return_t;

typedef uint64_t tech_size_t;

#ifdef __cplusplus
#define tech_thread_local_t thread_local
typedef std::atomic_bool atomic_bool;
typedef std::atomic_int atomic_int;
#else
#define tech_thread_local_t _Thread_local
#endif

#endif