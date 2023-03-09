#ifndef TECH_MATH_H
#define TECH_MATH_H

#include <tech/config/features.h>
#include <tech/shared/include.h>
#include <tech/shared/types.h>

#ifdef __cplusplus
    extern "C" {
#endif

uint64_t tech_math_powm_u64(uint64_t base, uint64_t pow, uint64_t modulo);


#ifdef __cplusplus
    }
#endif

#endif