#include <stddef.h>
#include <stdint.h>
#include <simplex/murmur3.h>

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
#endif /* __GNUC__ */

uint32_t murmur3_hash(const void *key, size_t len, uint32_t seed)
{
    const uint32_t c1 = 0xcc9e2d51, c2 = 0x1b873593;
    const uint32_t c3 = 0xe6546b64, c4 = 0x85ebca6b;
    const uint32_t c5 = 0xc2b2ae35;
    const uint8_t *data = (const uint8_t *)key;
    size_t rem = len;
    uint32_t h1 = seed, k1;

    while (rem >= 4) {
        k1 = data[0]
             | (data[1] << 8)
             | (data[2] << 16)
             | (data[3] << 24);

        k1 *= c1;
        k1  = (k1 << 15) | (k1 >> 17);
        k1 *= c2;

        h1 ^= k1;
        h1  = (h1 << 13) | (h1 >> 19);
        h1  = h1 + (h1 << 2) + c3;

        rem  -= 4;
        data += 4;
    }

    k1 = 0;

    switch (rem) {
        case 3: k1 ^= data[2] << 16;
        case 2: k1 ^= data[1] << 8;
        case 1: k1 ^= data[0];
                k1 *= c1;
                k1  = (k1 << 15) | (k1 >> 17);
                k1 *= c2;
                h1 ^= k1;
    }

    h1 ^= len;

    h1 ^= h1 >> 16;
    h1 *= c4;
    h1 ^= h1 >> 13;
    h1 *= c5;
    h1 ^= h1 >> 16;

    return h1;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif /* __GNUC__ */
