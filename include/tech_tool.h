#ifndef TECH_TOOL_H
#define TECH_TOOL_H

#include "../config/tech_features.h"
#include "../shared/tech_include.h"
#include "../shared/tech_types.h"

#ifdef __cplusplus
    extern "C" {
#endif



#ifdef __cplusplus
    #define TECH_TOOL_CHECK_TYPE(var,type) (typeid(var)==typeid(type))
#else
    #define TECH_TOOL_CHECK_TYPE(var,type) (__builtin_types_compatible_p(__typeof(var),type))
#endif

#define TECH_TOOL_STRINGIZE(x) #x



#ifdef __cplusplus
    }
#endif

#endif