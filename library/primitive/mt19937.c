#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <simplex/macros.h>
#include "mt19937.h"
#include "device_rand.h"

static void mt_twist(mt_ctx_t *mt)
{
    const uint32_t upperMask = 0x80000000, lowerMask = 0x7FFFFFFF;
    const uint32_t A = 0x9908B0DF, M = 397;
    uint32_t i, y, *mtState;

    mtState = mt->mtState;

    for (i = 0; i < MT_STATE_SIZE; ++i) {
        y = (mtState[i] & upperMask) +
            (mtState[(i + 1) % MT_STATE_SIZE] & lowerMask);

        mtState[i] = mtState[(i + M) % MT_STATE_SIZE] ^ (y >> 1);

        if (y % 2) {
            mtState[i] ^= A;
        }

    }

    mt->mtIndex = 0;
}

int mt_ctx_init(mt_ctx_t *mt)
{
    memset(mt->mtState, 0, sizeof(uint32_t) * MT_STATE_SIZE);
    mt->mtIndex = MT_STATE_SIZE + 1;

    return 0;
}

int mt_ctx_uninit(mt_ctx_t *mt)
{
    UNUSED(mt);

    return 0;
}

void mt_seed(mt_ctx_t *mt, uint32_t seed)
{
    const uint32_t F = 0x6C078965, W = 32;
    uint32_t i, *mtState;

    mtState = mt->mtState;

    mt->mtIndex = MT_STATE_SIZE;
    mtState[0] = seed;

    for (i = 1; i < MT_STATE_SIZE; ++i) {
        mtState[i] = F * (mtState[i - 1] ^ (mtState[i - 1] >> (W - 2))) + i;
    }
}

uint32_t mt_rand(mt_ctx_t *mt)
{
    const uint32_t U = 11, S = 7,  B = 0x9D2C5680;
    const uint32_t T = 15, L = 18, C = 0xEFC60000;
    uint32_t result, seed;

    if (mt->mtIndex == MT_STATE_SIZE + 1) {
        device_rand(&seed, sizeof(uint32_t));
        mt_seed(mt, seed);
    }

    if (mt->mtIndex == MT_STATE_SIZE) {
        mt_twist(mt);
    }

    result = mt->mtState[(mt->mtIndex)++];

    result ^= (result >> U);
    result ^= ((result << S) & B);
    result ^= ((result << T) & C);
    result ^= (result >> L);

    return result;
}

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4146)
#endif /* _MSC_VER */

uint32_t mt_uniform(mt_ctx_t *mt, uint32_t upper_bound)
{
    uint32_t r, min;

    if (upper_bound < 2) {
        return 0;
    }

    min = -upper_bound % upper_bound;

    for (;;) {
        r = mt_rand(mt);

        if (r >= min) {
            break;
        }
    }

    return r % upper_bound;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif /* _MSC_VER */

float mt_float(mt_ctx_t *mt)
{
    const uint32_t floatMaxInt = 0x00FFFFFF;

    return ((float)mt_uniform(mt, floatMaxInt)) / ((float)floatMaxInt);
}

float mt_gaussian(mt_ctx_t *mt)
{
    const float S = 0.449871f, T  = 0.386595f, A  = 0.196000f;
    const float B = 0.254720f, R1 = 0.275970f, R2 = 0.278460f;
    float u, v, x, y, q;

    do {
        u = 1.0f - mt_float(mt);
        v = 1.7156f * (mt_float(mt) - 0.5f);
        x = u - S;
        y = fabsf(v) + T;
        q = (x * x) + y * (A * y - B * x);
    } while (q > R1
             && ((q > R2) || ((v * v) > -4.0f * logf(u) * (u * u))));

    return (v / u);
}
