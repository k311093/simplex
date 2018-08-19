#ifndef _RUNTIME_SLAB_H_
#define _RUNTIME_SLAB_H_

typedef struct _slab_t slab_t;

void  slab_init(slab_t *slab, int item_size);
void  slab_uninit(slab_t *slab);
void *slab_alloc(slab_t *slab);
void  slab_free(slab_t *slab, void *item);

#endif /* _RUNTIME_SLAB_H_ */
