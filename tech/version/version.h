#ifndef TECH_VERSON_H
#define TECH_VERSION_H

#include <tech/config/features.h>
#include <tech/shared/include.h>


#define TECH_VERSION "0.0.1-beta"
#define TECH_VERSION_MAJOR 0
#define TECH_VERSION_MINOR 0
#define TECH_VERSION_PATCH 1
#define TECH_VERSION_PRE_RELEASE 1 

typedef int32_t tech_version_t;

const char* tech_version_get(void);

tech_version_t tech_version_get_major(void);

tech_version_t tech_version_get_minor(void);

tech_version_t tech_version_get_patch(void);

tech_version_t tech_version_get_pre_release(void);


#endif