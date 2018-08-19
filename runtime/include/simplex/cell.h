#ifndef _RUNTIME_CELL_H_
#define _RUNTIME_CELL_H_

#include <stdint.h>

enum CELL_TYPE {
    CELL_TYPE_NIL = 0,
    CELL_TYPE_INT8,
    CELL_TYPE_UINT8,
    CELL_TYPE_INT16,
    CELL_TYPE_UINT16,
    CELL_TYPE_INT32,
    CELL_TYPE_UINT32,
    CELL_TYPE_INT64,
    CELL_TYPE_UINT64,
    CELL_TYPE_FLOAT32,
    CELL_TYPE_FLOAT64,
    CELL_TYPE_POINTER,
    CELL_TYPE_PAIR,
    CELL_TYPE_ARRAY = 10000,
    CELL_TYPE_ARRAY_INT8,
    CELL_TYPE_ARRAY_UINT8,
    CELL_TYPE_ARRAY_INT16,
    CELL_TYPE_ARRAY_UINT16,
    CELL_TYPE_ARRAY_INT32,
    CELL_TYPE_ARRAY_UINT32,
    CELL_TYPE_ARRAY_INT64,
    CELL_TYPE_ARRAY_UINT64,
    CELL_TYPE_ARRAY_FLOAT32,
    CELL_TYPE_ARRAY_FLOAT64,
    CELL_TYPE_ARRAY_POINTER,
    CELL_TYPE_ARRAY_CELL,
    CELL_TYPE_ARRAY_END,
    CELL_TYPE_IARRAY = 20000,
    CELL_TYPE_IARRAY_INT8,
    CELL_TYPE_IARRAY_UINT8,
    CELL_TYPE_IARRAY_INT16,
    CELL_TYPE_IARRAY_UINT16,
    CELL_TYPE_IARRAY_INT32,
    CELL_TYPE_IARRAY_UINT32,
    CELL_TYPE_IARRAY_INT64,
    CELL_TYPE_IARRAY_UINT64,
    CELL_TYPE_IARRAY_FLOAT32,
    CELL_TYPE_IARRAY_FLOAT64,
    CELL_TYPE_IARRAY_POINTER,
    CELL_TYPE_IARRAY_CELL,
    CELL_TYPE_IARRAY_END,

};

typedef struct _pair_t pair_t;
typedef struct _array_t array_t;
typedef union _cell_value_t cell_value_t;
typedef struct _cell_t cell_t;

struct _pair_t {
    cell_t *car;
    cell_t *cdr;
};

struct _array_t {
    int   size;
    void *data;
};

union _cell_value_t {
    int8_t   int8;
    uint8_t  uint8;
    int16_t  int16;
    uint16_t uint16;
    int32_t  int32;
    uint32_t uint32;
    int64_t  int64;
    uint64_t uint64;

    float    float32;
    double   float64;

    void    *pointer;

    pair_t   pair;
    array_t  array;
};

struct _cell_t {
    int type;
    cell_value_t value;
};

void cell_destroy(cell_t *c);

cell_t *cell_int8(int8_t v);
cell_t *cell_uint8(uint8_t v);
cell_t *cell_int16(int16_t v);
cell_t *cell_uint16(uint16_t v);
cell_t *cell_int32(int32_t v);
cell_t *cell_uint32(uint32_t v);
cell_t *cell_int64(int64_t v);
cell_t *cell_uint64(uint64_t v);
cell_t *cell_float32(float v);
cell_t *cell_float64(double v);
cell_t *cell_pointer(void *v);
cell_t *cell_pair(cell_t *car, cell_t *cdr);

cell_t *cell_array_int8(int size);
cell_t *cell_array_uint8(int size);
cell_t *cell_array_int16(int size);
cell_t *cell_array_uint16(int size);
cell_t *cell_array_int32(int size);
cell_t *cell_array_uint32(int size);
cell_t *cell_array_int64(int size);
cell_t *cell_array_uint64(int size);
cell_t *cell_array_float32(int size);
cell_t *cell_array_float64(int size);
cell_t *cell_array_pointer(int size);
cell_t *cell_array_cell(int size);

cell_t *cell_iarray_int8(int8_t *data, int size);
cell_t *cell_iarray_uint8(uint8_t *data, int size);
cell_t *cell_iarray_int16(int16_t *data, int size);
cell_t *cell_iarray_uint16(uint16_t *data, int size);
cell_t *cell_iarray_int32(int32_t *data, int size);
cell_t *cell_iarray_uint32(uint32_t *data, int size);
cell_t *cell_iarray_int64(int64_t *data, int size);
cell_t *cell_iarray_uint64(uint64_t *data, int size);
cell_t *cell_iarray_float32(float *data, int size);
cell_t *cell_iarray_float64(double *data, int size);
cell_t *cell_iarray_pointer(void **data, int size);
cell_t *cell_iarray_cell(cell_t *data, int size);

extern cell_t cell_nil;

#define nil             (&cell_nil)

#define c_int8          cell_int8
#define c_uint8         cell_uint8
#define c_int16         cell_int16
#define c_uint16        cell_uint16
#define c_int32         cell_int32
#define c_uint32        cell_uint32
#define c_int64         cell_int64
#define c_uint64        cell_uint64
#define c_float32       cell_float32
#define c_float64       cell_float64
#define c_pointer       cell_pointer
#define c_cons          cell_pair

#define c_aint8         cell_array_int8
#define c_auint8        cell_array_uint8
#define c_aint16        cell_array_int16
#define c_auint16       cell_array_uint16
#define c_aint32        cell_array_int32
#define c_auint32       cell_array_uint32
#define c_aint64        cell_array_int64
#define c_auint64       cell_array_uint64
#define c_afloat32      cell_array_float32
#define c_afloat64      cell_array_float64
#define c_apointer      cell_array_pointer
#define c_acell         cell_array_cell

#define c_iaint8        cell_iarray_int8
#define c_iauint8       cell_iarray_uint8
#define c_iaint16       cell_iarray_int16
#define c_iauint16      cell_iarray_uint16
#define c_iaint32       cell_iarray_int32
#define c_iauint32      cell_iarray_uint32
#define c_iaint64       cell_iarray_int64
#define c_iauint64      cell_iarray_uint64
#define c_iafloat32     cell_iarray_float32
#define c_iafloat64     cell_iarray_float64
#define c_iapointer     cell_iarray_pointer
#define c_iacell        cell_iarray_cell

#define is_nil(c)       ((c) == nil)
#define is_int8(c)      ((c)->type == CELL_TYPE_INT8)
#define is_uint8(c)     ((c)->type == CELL_TYPE_UINT8)
#define is_int16(c)     ((c)->type == CELL_TYPE_INT16)
#define is_uint16(c)    ((c)->type == CELL_TYPE_UINT16)
#define is_int32(c)     ((c)->type == CELL_TYPE_INT32)
#define is_uint32(c)    ((c)->type == CELL_TYPE_UINT32)
#define is_int64(c)     ((c)->type == CELL_TYPE_INT64)
#define is_uint64(c)    ((c)->type == CELL_TYPE_UINT64)
#define is_float32(c)   ((c)->type == CELL_TYPE_FLOAT32)
#define is_float64(c)   ((c)->type == CELL_TYPE_FLOAT64)
#define is_pointer(c)   ((c)->type == CELL_TYPE_POINTER)
#define is_pair(c)      ((c)->type == CELL_TYPE_PAIR)

#define is_array(c) \
    (((c)->type > CELL_TYPE_ARRAY) && ((c)->type < CELL_TYPE_ARRAY_END))
#define is_aint8(c)     ((c)->type == CELL_TYPE_ARRAY_INT8)
#define is_auint8(c)    ((c)->type == CELL_TYPE_ARRAY_UINT8)
#define is_aint16(c)    ((c)->type == CELL_TYPE_ARRAY_INT16)
#define is_auint16(c)   ((c)->type == CELL_TYPE_ARRAY_UINT16)
#define is_aint32(c)    ((c)->type == CELL_TYPE_ARRAY_INT32)
#define is_auint32(c)   ((c)->type == CELL_TYPE_ARRAY_UINT32)
#define is_aint64(c)    ((c)->type == CELL_TYPE_ARRAY_INT64)
#define is_auint64(c)   ((c)->type == CELL_TYPE_ARRAY_UINT64)
#define is_afloat32(c)  ((c)->type == CELL_TYPE_ARRAY_FLOAT32)
#define is_afloat64(c)  ((c)->type == CELL_TYPE_ARRAY_FLOAT64)
#define is_apointer(c)  ((c)->type == CELL_TYPE_ARRAY_POINTER)
#define is_acell(c)     ((c)->type == CELL_TYPE_ARRAY_CELL)

#define is_iarray(c) \
    (((c)->type > CELL_TYPE_IARRAY) && ((c)->type < CELL_TYPE_IARRAY_END))
#define is_iaint8(c)    ((c)->type == CELL_TYPE_IARRAY_INT8)
#define is_iauint8(c)   ((c)->type == CELL_TYPE_IARRAY_UINT8)
#define is_iaint16(c)   ((c)->type == CELL_TYPE_IARRAY_INT16)
#define is_iauint16(c)  ((c)->type == CELL_TYPE_IARRAY_UINT16)
#define is_iaint32(c)   ((c)->type == CELL_TYPE_IARRAY_INT32)
#define is_iauint32(c)  ((c)->type == CELL_TYPE_IARRAY_UINT32)
#define is_iaint64(c)   ((c)->type == CELL_TYPE_IARRAY_INT64)
#define is_iauint64(c)  ((c)->type == CELL_TYPE_IARRAY_UINT64)
#define is_iafloat32(c) ((c)->type == CELL_TYPE_IARRAY_FLOAT32)
#define is_iafloat64(c) ((c)->type == CELL_TYPE_IARRAY_FLOAT64)
#define is_iapointer(c) ((c)->type == CELL_TYPE_IARRAY_POINTER)
#define is_iacell(c)    ((c)->type == CELL_TYPE_IARRAY_CELL)

#define v_int8(c)       ((c)->value.int8)
#define v_uint8(c)      ((c)->value.uint8)
#define v_int16(c)      ((c)->value.int16)
#define v_uint16(c)     ((c)->value.uint16)
#define v_int32(c)      ((c)->value.int32)
#define v_uint32(c)     ((c)->value.uint32)
#define v_int64(c)      ((c)->value.int64)
#define v_uint64(c)     ((c)->value.uint64)
#define v_float32(c)    ((c)->value.float32)
#define v_float64(c)    ((c)->value.float64)
#define v_pointer(c)    ((c)->value.pointer)
#define v_car(c)        ((c)->value.pair.car)
#define v_cdr(c)        ((c)->value.pair.cdr)

#define v_asize(c)      ((c)->value.array.size)
#define v_adata(c)      ((c)->value.array.data)
#define v_aint8(c)      ((int8_t *)((c)->value.array.data))
#define v_auint8(c)     ((uint8_t *)((c)->value.array.data))
#define v_aint16(c)     ((int16_t *)((c)->value.array.data))
#define v_auint16(c)    ((uint16_t *)((c)->value.array.data))
#define v_aint32(c)     ((int32_t *)((c)->value.array.data))
#define v_auint32(c)    ((uint32_t *)((c)->value.array.data))
#define v_aint64(c)     ((int64_t *)((c)->value.array.data))
#define v_auint64(c)    ((uint64_t *)((c)->value.array.data))
#define v_afloat32(c)   ((float *)((c)->value.array.data))
#define v_afloat64(c)   ((double *)((c)->value.array.data))
#define v_apointer(c)   ((void **)((c)->value.array.data))
#define v_acell(c)      ((cell_t **)((c)->value.array.data))

#define v_iasize        v_asize
#define v_iadata        v_adata
#define v_iaint8        v_aint8
#define v_iauint8       v_auint8
#define v_iaint16       v_aint16
#define v_iauint16      v_auint16
#define v_iaint32       v_aint32
#define v_iauint32      v_auint32
#define v_iaint64       v_aint64
#define v_iauint64      v_auint64
#define v_iafloat32     v_afloat32
#define v_iafloat64     v_afloat64
#define v_iapointer     v_apointer
#define v_iacell        v_acell

#endif /* _RUNTIME_CELL_H_ */
