 //===================================================================================================//
/**
 *  WRITER: TechnicaluserX
 *  
 *  DESCRIPTION: Consist of basic mathematical functions. More will be added over time.
 *  
 *  LICENSE: This library is not currently under any license and it is free to modify/distribute. 
 * 
 */
 //===================================================================================================//


#ifndef _TECHLIB_MATH_HPP
#define _TECHLIB_MATH_HPP


#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <unistd.h>
#include <cmath>


namespace techlib{
namespace math{


const long long PRIME_MAX_CHECK = 10000;


int isprime(long long n);

long long random_number_range(long long min, long long max);

long long random_prime_range(long long min, long long max);

// Euclidian Algorithm //
long long gcd(long long a, long long h);

unsigned long long lcm(int count, ...);

// Recursive factorial modulus
long long fast_factorial_modulus(long long fact,long long modulo);

// Iterative factorial modulus
long long fast_factorial_modulus_2(long long fact, long long modulo);

// Recursive exponential modulus
long long fast_exponential_modulus(long long base, long long exp, long long modulo);

// Iterative exponential modulus
long long fast_exponential_modulus_2(long long base, long long exp, long long modulo);

long long fast_multiplication_modulus(long long x, long long y, long long modulo);

};
};
#endif
