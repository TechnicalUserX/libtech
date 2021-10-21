
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
    #if defined(TECHLIB_LOG_CHARSET_UTF)
        
        #ifndef TECHLIB_LOG_DISABLE_ERRORS

            #define PANIC(str)              { fwprintf(stderr, L"PANIC: %s\n",str);}
            #define PANIC_EXIT(str,code)    { fwprintf(stderr, L"PANIC: %s\n",str);         fwprintf(stderr, L"%s\n",strerror(errno)); exit(code);}
            #define PANIC_RETURN(str,code)  { fwprintf(stderr, L"PANIC_RETURN: %s\n",str);  fwprintf(stderr, L"%s\n",strerror(errno)); return(code);}
            #ifdef __cplusplus
                #define PANIC_THROW(str,code)   { fwprintf(stderr, L"PANIC_THROW: %s\n",str);   fwprintf(stderr, L"Error code from throw: %d\n",code); throw(code);}
            #endif
        #else

            #define PANIC(str)              {}
            #define PANIC_EXIT(str,code)    { exit(code); }
            #define PANIC_RETURN(str,code)  { return(code); }
            #ifdef __cplusplus
                #define PANIC_THROW(num)        { throw(code); }
            #endif
        #endif


    #else

        #ifndef TECHLIB_LOG_DISABLE_ERRORS

            #define PANIC(str)              { fprintf(stderr, "PANIC: %s\n",str);}
            #define PANIC_EXIT(str,code)    { fprintf(stderr, "PANIC_EXIT: %s\n",str);      fprintf(stderr, "%s\n",strerror(errno)); exit(code); }
            #define PANIC_RETURN(str,code)  { fprintf(stderr, "PANIC_RETURN: %s\n",str);  fprintf(stderr, "%s\n",strerror(errno)); return(code); }
            #ifdef __cplusplus
                #define PANIC_THROW(str,code)   { fprintf(stderr, "PANIC_THROW: %s\n",str);     fprintf(stderr, "Error code from throw: %d\n",code); throw(code); }
            #endif
        #else

            #define PANIC(str)              {}
            #define PANIC_EXIT(str,code)    { exit(code); }
            #define PANIC_RETURN(str,code)  { return(code); }
            #ifdef __cplusplus
                #define PANIC_THROW(code)       { throw(code); }
            #endif
            

        #endif



    #endif





    // TIME FORMAT FOR ctime() //
    struct techlib_log_time_format{
        char day_name[4];
        char month_name[4];
        int day;
        int hour;
        int minute;
        int second;
        int year;
    };






    // LOGGING //
#if defined(TECHLIB_LOG_CHARSET_UTF)
    void LOG(const wchar_t* display_string, ...)
#else
    void LOG(const char* display_string, ...)
#endif
{
        va_list va;
        va_start(va,display_string);
        time_t t = time(NULL);
        char time_format[30];
        strcpy(time_format,ctime(&t));
        //printf("%s\n",time_format);
        struct techlib_log_time_format tf;
        sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));
    
    #if defined(TECHLIB_LOG_CHARSET_UTF)
        wprintf(L"[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
        vwprintf(display_string,va);
        wprintf(L'\n');
    #else
        printf("[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
        vprintf(display_string,va);
        printf("\n");
    #endif

    va_end(va);
}









#endif