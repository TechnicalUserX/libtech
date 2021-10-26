#include "../include/math.hpp"


TECHLIB_WINDLL_API int techlib::math::isprime(long long n){

    if(n < 2)
        return 0;

    if(n % 2 == 0 && n > 2)
        return 0;

    if(n != 3 && n % 3 == 0)
        return 0;
    

    for(long long i = 1; (6*i+1 <= sqrtl(n) || 6*i-1 <= sqrtl(n))  ; i++)
        if( (n % (6*i+1) == 0 || n % (6*i-1) == 0) && (6*i+1 !=n && 6*i-1 !=n) )
            return 0;
    
    return 1;
}

TECHLIB_WINDLL_API long long techlib::math::random_number_range(long long min, long long max){
    long long dif = max-min;
    return (rand() % (dif+1)) + min;
}

TECHLIB_WINDLL_API long long techlib::math::random_prime_range(long long min, long long max){
    long long dif = max-min;
    long long num = (rand() % (dif+1)) + min; 



    if( techlib::math::isprime(num))
        return num;
    else{

        num = (num % 2 == 0) ? num -1 : num;

        do{
            num += 2;
        }while(!techlib::math::isprime(num));
        return num;
    }

}



// Euclidian Algorithm //
TECHLIB_WINDLL_API long long techlib::math::gcd(long long a, long long h)
{
    while(1)
    {
        long long temp = a % h;
        if( temp == 0 )
            return h;
        a = h;
        h = temp;
    }
}


TECHLIB_WINDLL_API unsigned long long techlib::math::lcm(int count, ...)
{
    int n = count;

    va_list list;
    va_start(list,count);
    int check_unique_prime_numbers[techlib::math::PRIME_MAX_CHECK] = {0};

    unsigned long long A[n];

    for (int i = 0;i<n;i++){

            A[i] = va_arg(list,unsigned long long);

    }

    for (int x = 0;x<n-1;x++){
        int total_divisibility_amount = 0;
        for (int s = 2; s<A[x];s++){


            char divisible = 1;
            int temp_value = A[x];
            int divide_count=0;

            while (divisible){

                char s_is_prime=1;
                for (int y = 2; y<s;y++){
                    if (s % y == 0){
                        s_is_prime = 0;
                    }

                }

                if (temp_value % s == 0 && s_is_prime ==1){
                        total_divisibility_amount++;
                        divide_count++;
                        temp_value/=s;

                }else{
                    if (divide_count){
                        if (divide_count>check_unique_prime_numbers[s]){
                            check_unique_prime_numbers[s] = divide_count;
                        }
                        divide_count=0;
                        divisible=0;
                    }else {
                        divisible=0;
                        divide_count=0;
                    }


                }


            }

        }
        if (total_divisibility_amount == 0 && A[x] != 1){
            if (check_unique_prime_numbers[A[x]] < 1)
                check_unique_prime_numbers[A[x]]++;
        }



    }


    unsigned long long lcm = 1;
    for (int i = 2; i<techlib::math::PRIME_MAX_CHECK;i++){

        if (check_unique_prime_numbers[i]){
            int multiply=1;

            for (int j=0;j<check_unique_prime_numbers[i];j++){

                multiply*=i;
            }
            lcm*=multiply;
        }        


    }


    va_end(list);
    return lcm;
}



// Recursive factorial modulus
TECHLIB_WINDLL_API long long techlib::math::fast_factorial_modulus(long long fact,long long modulo){

    long long m = fact % modulo;

    if(fact == 2)
        return m;

    long long next = techlib::math::fast_factorial_modulus(fact-1,modulo);

    return (m*next) % modulo;
}

// Iterative factorial modulus
TECHLIB_WINDLL_API long long techlib::math::fast_factorial_modulus_2(long long fact, long long modulo){

    long long final_number = 1;
    for(long long i = fact; i > 0; i--){
        final_number = (final_number * i) % modulo;
    }
    return final_number;
}



// Recursive exponential modulus
TECHLIB_WINDLL_API long long techlib::math::fast_exponential_modulus(long long base, long long exp, long long modulo){

    int m = base % modulo;

    if(exp == 1)
        return m;

    long long next = techlib::math::fast_exponential_modulus(base,exp-1,modulo);

    return (m * next) % modulo;
}

// Iterative exponential modulus
TECHLIB_WINDLL_API long long techlib::math::fast_exponential_modulus_2(long long base, long long exp, long long modulo){

    long long m = 1;
    for(long long i = 0; i < exp; i++){

        m = ((m % modulo)  * (base % modulo)) % modulo;
    }
    return m;
}


TECHLIB_WINDLL_API long long techlib::math::fast_multiplication_modulus(long long x, long long y, long long modulo){


    return ((x % modulo) * (y % modulo)) % modulo;
}
