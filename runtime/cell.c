#include <stdlib.h>
#include <simplex/cell.h>

cell_t cell_nil;

static cell_t *cell_create(void)
{
    cell_t *r = (cell_t *)malloc(sizeof(*r));

    return r;
}

void cell_destroy(cell_t *c)
{
    if (is_array(c)) {
        free(v_adata(c));
    }

    if (!is_nil(c)) {
        free(c);
    }
}

cell_t *cell_int8(int8_t v)
{
    cell_t *c     = cell_create();

    c->type       = CELL_TYPE_INT8;
    c->value.int8 = v;

    return c;
}

cell_t *cell_uint8(uint8_t v)
{
    cell_t *c      = cell_create();

    c->type        = CELL_TYPE_UINT8;
    c->value.uint8 = v;

    return c;
}

cell_t *cell_int16(int16_t v)
{
    cell_t *c      = cell_create();

    c->type        = CELL_TYPE_INT16;
    c->value.int16 = v;

    return c;
}

cell_t *cell_uint16(uint16_t v)
{
    cell_t *c       = cell_create();

    c->type         = CELL_TYPE_UINT16;
    c->value.uint16 = v;

    return c;
}

cell_t *cell_int32(int32_t v)
{
    cell_t *c      = cell_create();

    c->type        = CELL_TYPE_INT32;
    c->value.int32 = v;

    return c;
}

cell_t *cell_uint32(uint32_t v)
{
    cell_t *c       = cell_create();

    c->type         = CELL_TYPE_UINT32;
    c->value.uint32 = v;

    return c;
}

cell_t *cell_int64(int64_t v)
{
    cell_t *c      = cell_create();

    c->type        = CELL_TYPE_INT64;
    c->value.int64 = v;

    return c;
}

cell_t *cell_uint64(uint64_t v)
{
    cell_t *c       = cell_create();

    c->type         = CELL_TYPE_UINT64;
    c->value.uint64 = v;

    return c;
}

cell_t *cell_float32(float v)
{
    cell_t *c        = cell_create();

    c->type          = CELL_TYPE_FLOAT32;
    c->value.float32 = v;

    return c;
}

cell_t *cell_float64(double v)
{
    cell_t *c        = cell_create();

    c->type          = CELL_TYPE_FLOAT64;
    c->value.float64 = v;

    return c;
}

cell_t *cell_pointer(void *v)
{
    cell_t *c        = cell_create();

    c->type          = CELL_TYPE_POINTER;
    c->value.pointer = v;

    return c;
}

cell_t *cell_pair(cell_t *car, cell_t *cdr)
{
    cell_t *c         = cell_create();

    c->type           = CELL_TYPE_PAIR;
    c->value.pair.car = car;
    c->value.pair.cdr = cdr;

    return c;
}

cell_t *cell_array_int8(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(int8_t) * size);

    c->type             = CELL_TYPE_ARRAY_INT8;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_uint8(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(uint8_t) * size);

    c->type             = CELL_TYPE_ARRAY_UINT8;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_int16(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(int16_t) * size);

    c->type             = CELL_TYPE_ARRAY_INT16;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_uint16(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(uint16_t) * size);

    c->type             = CELL_TYPE_ARRAY_UINT16;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_int32(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(int32_t) * size);

    c->type             = CELL_TYPE_ARRAY_INT32;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_uint32(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(uint32_t) * size);

    c->type             = CELL_TYPE_ARRAY_UINT32;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_int64(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(int64_t) * size);

    c->type             = CELL_TYPE_ARRAY_INT64;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_uint64(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(uint64_t) * size);

    c->type             = CELL_TYPE_ARRAY_UINT64;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_float32(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(float) * size);

    c->type             = CELL_TYPE_ARRAY_FLOAT32;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_float64(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(double) * size);

    c->type             = CELL_TYPE_ARRAY_FLOAT64;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_pointer(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(void *) * size);

    c->type             = CELL_TYPE_ARRAY_POINTER;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_array_cell(int size)
{
    cell_t *c           = cell_create();
    void *data          = malloc(sizeof(cell_t *) * size);

    c->type             = CELL_TYPE_ARRAY_CELL;
    c->value.array.size = size;
    c->value.array.data = data;

    return c;
}

cell_t *cell_iarray_int8(int8_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_INT8;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_uint8(uint8_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_UINT8;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_int16(int16_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_INT16;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_uint16(uint16_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_UINT16;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_int32(int32_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_INT32;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_uint32(uint32_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_UINT32;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_int64(int64_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_INT64;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_uint64(uint64_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_UINT64;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_float32(float *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_FLOAT32;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_float64(double *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_FLOAT64;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_pointer(void **data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_POINTER;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}

cell_t *cell_iarray_cell(cell_t *data, int size)
{
    cell_t *c           = cell_create();

    c->type             = CELL_TYPE_IARRAY_CELL;
    c->value.array.size = size;
    c->value.array.data = (void *)data;

    return c;
}
