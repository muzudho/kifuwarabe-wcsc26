#pragma once
#include "../n080_100_sysWorld/n080_070_bmi2.hpp"
#include <random>				// std::mt19937_64
#include <condition_variable>	// std::mutex, std::condition_variable


//────────────────────────────────────────────────────────────────────────────────
// SSE4, SSE2
//────────────────────────────────────────────────────────────────────────────────


#if defined (HAVE_SSE4)
    #include <smmintrin.h>
#elif defined (HAVE_SSE2)
    #include <emmintrin.h>
#endif
