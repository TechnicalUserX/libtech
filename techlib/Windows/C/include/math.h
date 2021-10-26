 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 * 
 *  VERSION: 1.0.0
 *  
 *  DESCRIPTION: Consist of basic mathematical functions. More will be added over time.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_MATH_H
#define _TECHLIB_MATH_H

#define TECHLIB_WINDLL_API __declspec(dllexport)


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <math.h>

#define TECHLIB_MATH_PRIME_MAX_CHECK 10000

TECHLIB_WINDLL_API int techlib_math_isprime(long long n);

TECHLIB_WINDLL_API long long techlib_math_random_number_range(long long min, long long max);

TECHLIB_WINDLL_API long long techlib_math_random_prime_range(long long min, long long max);

// Euclidian Algorithm //
TECHLIB_WINDLL_API long long techlib_math_gcd(long long a, long long h);

TECHLIB_WINDLL_API unsigned long long techlib_math_lcm(int count, ...);

// Recursive factorial modulus
TECHLIB_WINDLL_API long long techlib_math_fast_factorial_modulus(long long fact,long long modulo);

// Iterative factorial modulus
TECHLIB_WINDLL_API long long techlib_math_fast_factorial_modulus_2(long long fact, long long modulo);

// Recursive exponential modulus
TECHLIB_WINDLL_API long long techlib_math_fast_exponential_modulus(long long base, long long exp, long long modulo);

// Iterative exponential modulus
TECHLIB_WINDLL_API long long techlib_math_fast_exponential_modulus_2(long long base, long long exp, long long modulo);

TECHLIB_WINDLL_API long long techlib_math_fast_multiplication_modulus(long long x, long long y, long long modulo);


#endif