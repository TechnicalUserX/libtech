#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>
#include <tech/version/version.h>


const char* tech_version_get(void){

    return TECH_VERSION;
}


tech_version_t tech_version_get_major(void){

    return TECH_VERSION_MAJOR;

}


tech_version_t tech_version_get_minor(void){

    return TECH_VERSION_MINOR;

}


tech_version_t tech_version_get_patch(void){

    return TECH_VERSION_PATCH;

}


tech_version_t tech_version_get_pre_release(void){

    return TECH_VERSION_PRE_RELEASE;

}