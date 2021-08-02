
#ifndef _TECHLIB_LOG_H
#define _TECHLIB_LOG_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <stdarg.h>

    // ERROR PRINTING //
    #if defined(TECHLIB_CHARSET_ASCII)
        
        #ifndef TECHLIB_SOCKET_DISABLE_ERRORS

            #define PANIC(str,ret) { printf("PANIC: %s\n",str); return ret;}
            #define PANIC_FATAL(str,ret){ printf("PANIC: %s\n",str); printf("%s\n",strerror(errno)); exit(ret);}
            #define PANIC_THROW_ERROR(str,num){printf("PANIC: %s\n",str); printf("Error code from throw: %d\n",num); throw(num);}

        #else
            #define PANIC(str,ret) {return ret;}
            #define PANIC_FATAL(str,ret){ exit(ret);}
            #define PANIC_THROW_ERROR(num){throw(ret)}

        #endif


    #define 


    #elif defined(TECHLIB_CHARSET_UTF)

        #ifndef TECHLIB_SOCKET_DISABLE_ERRORS

            #define PANIC(str,ret) { wprintf(L"PANIC: %s\n",str); return ret;}
            #define PANIC_FATAL(str,ret){ wprintf(L"PANIC: %s\n",str); wprintf(L"%s\n",strerror(errno)); exit(ret);}
            #define PANIC_THROW_ERROR(str,num){wprintf(L"PANIC: %s\n",str); wprintf(L"Error code from throw: %d\n",num); throw(num);}

        #else
            #define PANIC(str,ret) {return ret;}
            #define PANIC_FATAL(str,ret){ exit(ret);}
            #define PANIC_THROW_ERROR(num){throw(ret)}

        #endif





    #endif





    // TIME FORMAT FOR ctime() //
    struct techlib_time_format{
        char day_name[4];
        char month_name[4];
        int day;
        int hour;
        int minute;
        int second;
        int year;
    };






    // LOGGING //
#if defined(TECHLIB_CHARSET_ASCII)
    void LOG(const char* display_string, ...)
#elif defined(TECHLIB_CHARSET_UTF)
    void LOG(const wchar_t* display_string, ...)
#endif
{
        va_list va;
        va_start(va,display_string);
        time_t t = time(NULL);
        char time_format[30];
        strcpy(time_format,ctime(&t));
        //printf("%s\n",time_format);
        struct techlib_time_format tf;
        sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));

    
    #if defined(TECHLIB_CHARSET_ASCII)
        printf("[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
        vprintf(display_string,va);
        printf('\n');
    #elif defined(TECHLIB_CHARSET_UTF)
        wprintf( L"[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
        vwprintf(display_string,va);
        wprintf(L"\n");
    #endif

    va_end(va);
}









#endif