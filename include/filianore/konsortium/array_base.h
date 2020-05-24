#pragma once


#include <stdint.h>
#include <cmath>
#include <assert.h>
#include <immintrin.h>


namespace konsortium
{

#if defined(_MSC_VER)
# define KONSORTIUM_NOINLINE          __declspec(noinline)
# define KONSORTIUM_INLINE            __forceinline
#else
# define KONSORTIUM_NOINLINE          __attribute__((noinline))
# define KONSORTIUM_INLINE            __attribute__((always_inline)) inline
#endif


    class ArrayBase
    {
    public:
        ArrayBase(){ }
    };

}