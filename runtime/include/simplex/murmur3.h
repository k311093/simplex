#ifndef _RUNTIME_MURMUR3_H_
#define _RUNTIME_MURMUR3_H_

#include <stddef.h>
#include <stdint.h>

uint32_t murmur3_hash(const void *key, size_t len, uint32_t seed);

#endif /* _RUNTIME_MURMUR3_H_ */
