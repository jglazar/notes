/*
    Random number generation
*/

#include <stdio.h>
#include <stdint.h>

// 128-bit state achieves 2^126 period. 
// Passes Big Crush tests
// initial state must be odd
// note: 128-bit types only supported on some compilers, like GCC and Clang 
// could use multiplier 0x0fc94e3bf4e9ab32866458cd56f5e605 instead
static __uint128_t state_128 = 314159;
static const __uint128_t multiplier_128 = 0xda942042e4dd58b5;
static const float FLOAT_CONV_64 = 1.0f / (float)UINT64_MAX;
static const double DOUBLE_CONV_64 = 1.0 / (double)UINT64_MAX;
uint64_t rng_64() { return (state_128 *= multiplier_128) >> 64; }
uint64_t to_range_64(uint64_t rng, uint64_t range) 
{ 
    __uint128_t res = (__uint128_t)rng * (__uint128_t)range; 
    return res >> 64;
}
uint64_t to_range_unbias_64(uint64_t rng, uint64_t range)
{
    uint64_t t = (-range) % range; 
    uint64_t l, x;
    __uint128_t m;
    do
    {
        uint64_t x = rng_64();
        __uint128_t m = (__uint128_t)x * (__uint128_t)range; 
        l = (uint64_t)m;
    } while (l < t); 
    return m >> 64;
}
float to_float_64(uint64_t rng) { return (float)rng * FLOAT_CONV_64; }
float to_double_64(uint64_t rng) { return (double)rng  * DOUBLE_CONV_64; }


// 64-bit state achieves 2^62 period. 
// Beware: 64-bit state should only be used for under a billion samples
// initial state must be odd
// could use multiplier 7664345821815920749 (see more in 3rd ed. and L'Ecuyer)
static uint64_t state_64 = 314159;
static const uint64_t multiplier_64 = 2585821657736338717;
static const float FLOAT_CONV_32 = 1.0f / (float)UINT32_MAX;
static const double DOUBLE_CONV_32 = 1.0 / (double)UINT32_MAX;
uint32_t rng_32() { return (state_64 *= multiplier_64) >> 32; }
uint32_t to_range_32(uint32_t rng, uint32_t range) 
{ 
    uint64_t res = (uint64_t)rng * (uint64_t)range;
    return res >> 32;
}
uint32_t to_range_unbias_32(uint32_t rng, uint32_t range)
{
    uint32_t t = (-range) % range; 
    uint32_t l, x;
    uint64_t m;
    do
    {
        x = rng_32();
        m = (uint64_t)x * (uint64_t)range; 
        l = (uint32_t)m;
    } while (l < t); 
    return m >> 32;
}
float to_float_32(uint32_t rng) { return (float)rng  * FLOAT_CONV_32; }
float to_double_32(uint32_t rng) { return (double)rng  * DOUBLE_CONV_32; }


int main()
{
    int range = 5;

    puts("\ntesting 128-bit state RNG");
    //puts("\nint / float / double");
    for (int i = 0; i < 100; i++) { rng_64(); } // warm up
    for (int i = 0; i < 10; i++)
    {
        uint64_t my_rng_64 = rng_64();
        uint64_t my_ranged_64 = to_range_64(my_rng_64, range);
        float my_float_64 = to_float_64(my_rng_64);
        printf("%d/%f ", (int)my_ranged_64, my_float_64);
        //double my_double_64 = to_double_64(my_rng_64);
        //printf("%d/%f/%f ", (int)my_ranged_64, my_float_64, my_double_64);
    }

    puts("\ntesting 64-bit state RNG");
    //puts("\nint / float / double");
    for (int i = 0; i < 100; i++) { rng_32(); } // warm up
    for (int i = 0; i < 10; i++)
    {
        uint32_t my_rng_32 = rng_32();
        uint32_t my_ranged_32 = to_range_32(my_rng_32, range);
        float my_float_32 = to_float_32(my_rng_32);
        printf("%d/%f ", (int)my_ranged_32, my_float_32);
        //double my_double_32 = to_double_32(my_rng_32);
        //printf("%d/%f/%f ", (int)my_ranged_32, my_float_32, my_double_32);
    }
    return 0;
}
