#ifndef TECH_INCLUDE_H
#define TECH_INCLUDE_H

#ifndef TECH_FEATURES_H
#error "Include tech_features.h before including this header file"
#endif

// Language independent
#include <termios.h>
#include <unistd.h>
#include <langinfo.h>
#include <sys/ioctl.h>

#if defined(_PTHREAD_H) || defined(_SEMAPHORE_H)
    #error "Do not include pthread.h and semaphroe.h before including tech libraries"
#endif

#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

#ifdef __cplusplus
    #include <atomic>
    #include <cstdarg>
    #include <cstdio>
    #include <cstdint>
    #include <cstring>
    #include <cstdlib>
    #include <cstdbool>
    #include <cwchar>
    #include <ctime>
    #include <cerrno>
    #include <thread>
    #include <cassert>
    #include <clocale>
    #include <cctype>
#else
    #include <stdatomic.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include <string.h>
    #include <wchar.h>
    #include <time.h>
    #include <errno.h>
    #include <assert.h>
    #include <locale.h>
    #include <ctype.h>
#endif

#endif