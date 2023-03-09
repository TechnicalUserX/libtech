#include <tech/math/math.h>


uint64_t tech_math_powm_u64(uint64_t base, uint64_t pow, uint64_t modulo){

    uint64_t m = 1;
    for(uint64_t i = 0; i < pow; i++){

        m = ((m % modulo)  * (base % modulo)) % modulo;
    }
    return m;
}