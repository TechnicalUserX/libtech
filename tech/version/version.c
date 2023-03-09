#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>
#include <tech/version/version.h>


const char* tech_version_get(void){

    #ifdef TECH_VERSION
        return TECH_VERSION;
    #else
        return NULL;
    #endif
}


const char* tech_version_get_major(void){

    #ifdef TECH_VERSION_MAJOR
        return TECH_VERSION_MAJOR;
    #else
        return NULL;
    #endif
}


const char* tech_version_get_minor(void){

    #ifdef TECH_VERSION_MINOR
        return TECH_VERSION_MINOR;
    #else
        return NULL;
    #endif
}


const char* tech_version_get_patch(void){

    #ifdef TECH_VERSION_PATCH
        return TECH_VERSION_PATCH;
    #else
        return NULL;
    #endif
}


const char* tech_version_get_pre_release(void){

    #ifdef TECH_VERSION_PRE_RELEASE
        return TECH_VERSION_PRE_RELEASE;
    #else
        return NULL;
    #endif
}