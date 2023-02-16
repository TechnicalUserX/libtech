#include "../include/tech_log.h"


void tech_log(FILE* output_file, enum tech_log_style_t style,const char* display_string, ...){

    struct tech_log_time_format_t{
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
    struct tech_log_time_format_t tf;
    memset(tf.day_name,0x0,sizeof(tf.day_name));
    memset(tf.month_name,0x0,sizeof(tf.month_name));
    tf.day = 0;
    tf.hour = 0;
    tf.minute = 0;
    tf.second = 0;
    tf.year = 0;

    sscanf(time_format,"%s %s %d %d:%d:%d %d",tf.day_name, tf.month_name, &(tf.day), &(tf.hour), &(tf.minute), &(tf.second), &(tf.year));



    fprintf(output_file,"[");
    bool style_printed = false;

    if(style & TECH_LOG_STYLE_MONTH){
        fprintf(output_file,"%s",tf.month_name);
        style_printed = true;
    }

    if(style & TECH_LOG_STYLE_DAY){
        if(style_printed)
            fprintf(output_file," ");
        fprintf(output_file,"%d",tf.day);
        style_printed = true;

    }
    if(style & TECH_LOG_STYLE_DAY_NAME){
        if(style_printed)
            fprintf(output_file," ");
        fprintf(output_file,"%s",tf.day_name);
        style_printed = true;

    }
    if(style & TECH_LOG_STYLE_YEAR){
        if(style_printed)
            fprintf(output_file," ");
        fprintf(output_file,"%d",tf.year);
        style_printed = true;
    }
    if(style & TECH_LOG_STYLE_CLOCK){
        if(style_printed)
            fprintf(output_file," ");
        fprintf(output_file,"%02d:%02d:%02d",tf.hour,tf.minute,tf.second);
        style_printed = true;
    }

    if(!style){
        fprintf(output_file,"-"); // [-]
    }

    fprintf(output_file,"] ");
    vfprintf(output_file,display_string,va);
    fprintf(output_file,"\n");
    fflush(output_file);
    va_end(va);
    return;
}

