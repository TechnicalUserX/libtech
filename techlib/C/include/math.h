#ifndef _TECHLIB_MATH_H
#define _TECHLIB_MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <math.h>

#define TECHLIB_MATH_PRIME_MAX_CHECK 10000

int techlib_math_isprime(long long n);

long long techlib_math_random_number_range(long long min, long long max);

long long techlib_math_random_prime_range(long long min, long long max);

// Euclidian Algorithm //
long long techlib_math_gcd(long long a, long long h);

unsigned long long techlib_math_lcm(int count, ...);

// Recursive factorial modulus
long long techlib_math_fast_factorial_modulus(long long fact,long long modulo);

// Iterative factorial modulus
long long techlib_math_fast_factorial_modulus_2(long long fact, long long modulo);

// Recursive exponential modulus
long long techlib_math_fast_exponential_modulus(long long base, long long exp, long long modulo);

// Iterative exponential modulus
long long techlib_math_fast_exponential_modulus_2(long long base, long long exp, long long modulo);

long long techlib_math_fast_multiplication_modulus(long long x, long long y, long long modulo);


#endif