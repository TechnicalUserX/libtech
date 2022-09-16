#include "../include/log.hpp"


void techlib::log::log(enum techlib::log::style style, const char* display_string, ...){


    struct techlib_log_time_format{
        char day_name[16];
        char month_name[16];
        int day;
        int hour;
        int minute;
        int second;
        int year;
    };

    va_list va;
    va_start(va,display_string);

    time_t t = time(NULL);
    char* time_format= ctime(&t);

    // Initializing and resetting the time format structure
    struct techlib_log_time_format tf;
    memset(tf.day_name,0x0,sizeof(tf.day_name));
    memset(tf.month_name,0x0,sizeof(tf.month_name));
    tf.day = 0;
    tf.hour = 0;
    tf.minute = 0;
    tf.second = 0;
    tf.year = 0;

    sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));


    printf("[");
    bool style_printed = false;

    if(style & TECHLIB_LOG_STYLE_MONTH){
        if(style_printed)
            printf(" ");
        printf("%s",tf.month_name);
        style_printed = true;
    }

    if(style & TECHLIB_LOG_STYLE_DAY){
        if(style_printed)
            printf(" ");
        printf("%d",tf.day);
        style_printed = true;

    }
    if(style & TECHLIB_LOG_STYLE_DAY_NAME){
        if(style_printed)
            printf(" ");
        printf("%s",tf.day_name);
        style_printed = true;

    }
    if(style & TECHLIB_LOG_STYLE_YEAR){
        if(style_printed)
            printf(" ");
        printf("%d",tf.year);
        style_printed = true;
    }
    if(style & TECHLIB_LOG_STYLE_CLOCK){
        if(style_printed)
            printf(" ");
        printf("%02d:%02d:%02d",tf.hour,tf.minute,tf.second);
        style_printed = true;
    }


    printf("] ");
    vprintf(display_string,va);
    printf("\n");
    va_end(va);
    return;
}
