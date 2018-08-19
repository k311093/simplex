#ifndef _PRIMITIVE_MT19937_H_
#define _PRIMITIVE_MT19937_H_

#include <stdint.h>

#define MT_STATE_SIZE 624

struct _mt_ctx_t {
    uint32_t mtState[MT_STATE_SIZE];
    int      mtIndex;
};

typedef struct _mt_ctx_t mt_ctx_t;

int      mt_ctx_init(mt_ctx_t *mt);
int      mt_ctx_uninit(mt_ctx_t *mt);

void     mt_seed(mt_ctx_t *mt, uint32_t seed);

uint32_t mt_rand(mt_ctx_t *mt);
uint32_t mt_uniform(mt_ctx_t *mt, uint32_t upper_bound);
float    mt_float(mt_ctx_t *mt);
float    mt_gaussian(mt_ctx_t *mt);

#endif /* _PRIMITIVE_MT19937_H_ */
