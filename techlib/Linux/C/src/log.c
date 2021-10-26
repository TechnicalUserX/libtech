#include "../include/log.h"


void techlib_log_ascii(const char* display_string, ...){

    struct techlib_log_time_format{
        char day_name[4];
        char month_name[4];
        int day;
        int hour;
        int minute;
        int second;
        int year;
    };

    va_list va;
    va_start(va,display_string);
    time_t t = time(NULL);
    char time_format[30];
    strcpy(time_format,ctime(&t));
    //printf("%s\n",time_format);
    struct techlib_log_time_format tf;
    sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));


    printf("[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
    vprintf(display_string,va);
    printf("\n");

    va_end(va);
}


void techlib_log_widechar(const wchar_t* display_string, ...){

    struct techlib_log_time_format{
        char day_name[4];
        char month_name[4];
        int day;
        int hour;
        int minute;
        int second;
        int year;
    };

    va_list va;
    va_start(va,display_string);
    time_t t = time(NULL);
    char time_format[30];
    strcpy(time_format,ctime(&t));
    //printf("%s\n",time_format);
    struct techlib_log_time_format tf;
    sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));

    wprintf(L"[%02d:%02d:%02d] ",tf.hour, tf.minute, tf.second);
    vwprintf(display_string,va);
    wprintf(L"\n");


    va_end(va);
}
