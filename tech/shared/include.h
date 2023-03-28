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
#include <ifaddrs.h>
#include <linux/if.h>
#include <linux/wireless.h>
#include <sys/socket.h>
#include <linux/rtnetlink.h>

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
    #include <cinttypes>
    #include <cstring>
    #include <cstdlib>
    #include <cinttypes>
    #include <cstdbool>
    #include <cwchar>
    #include <ctime>
    #include <cerrno>
    #include <thread>
    #include <cassert>
    #include <clocale>
    #include <cctype>
    #include <cmath>
#else
    #include <stdatomic.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <inttypes.h>
    #include <stdlib.h>
    #include <inttypes.h>
    #include <string.h>
    #include <wchar.h>
    #include <time.h>
    #include <errno.h>
    #include <assert.h>
    #include <locale.h>
    #include <ctype.h>
    #include <math.h>
#endif

#endif