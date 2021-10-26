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


#ifndef _TECHLIB_MATH_HPP
#define _TECHLIB_MATH_HPP

#define TECHLIB_WINDLL_API __declspec(dllexport)


#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <unistd.h>
#include <cmath>


namespace techlib{
namespace math{


const long long PRIME_MAX_CHECK = 10000;


TECHLIB_WINDLL_API int isprime(long long n);

TECHLIB_WINDLL_API long long random_number_range(long long min, long long max);

TECHLIB_WINDLL_API long long random_prime_range(long long min, long long max);

// Euclidian Algorithm //
TECHLIB_WINDLL_API long long gcd(long long a, long long h);

TECHLIB_WINDLL_API unsigned long long lcm(int count, ...);

// Recursive factorial modulus
TECHLIB_WINDLL_API long long fast_factorial_modulus(long long fact,long long modulo);

// Iterative factorial modulus
TECHLIB_WINDLL_API long long fast_factorial_modulus_2(long long fact, long long modulo);

// Recursive exponential modulus
TECHLIB_WINDLL_API long long fast_exponential_modulus(long long base, long long exp, long long modulo);

// Iterative exponential modulus
TECHLIB_WINDLL_API long long fast_exponential_modulus_2(long long base, long long exp, long long modulo);

TECHLIB_WINDLL_API long long fast_multiplication_modulus(long long x, long long y, long long modulo);

};
};
#endif