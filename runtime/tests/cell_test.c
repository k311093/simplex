#include <unity.h>
#include <stdlib.h>
#include <simplex/cell.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_cell_int8(void)
{
    cell_t *c = c_int8(-10);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_int8(c));
    TEST_ASSERT_EQUAL(-10, v_int8(c));

    cell_destroy(c);
}

void test_cell_uint8(void)
{
    cell_t *c = c_uint8(10);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_uint8(c));
    TEST_ASSERT_EQUAL(10, v_uint8(c));

    cell_destroy(c);
}

void test_cell_int16(void)
{
    cell_t *c = c_int16(-30000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_int16(c));
    TEST_ASSERT_EQUAL(-30000, v_int16(c));

    cell_destroy(c);
}

void test_cell_uint16(void)
{
    cell_t *c = c_uint16(60000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_uint16(c));
    TEST_ASSERT_EQUAL(60000, v_uint16(c));

    cell_destroy(c);
}

void test_cell_int32(void)
{
    cell_t *c = c_int32(-2100000000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_int32(c));
    TEST_ASSERT_EQUAL(-2100000000, v_int32(c));

    cell_destroy(c);
}

void test_cell_uint32(void)
{
    cell_t *c = c_uint32(4200000000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_uint32(c));
    TEST_ASSERT_EQUAL(4200000000, v_uint32(c));

    cell_destroy(c);
}

void test_cell_int64(void)
{
    cell_t *c = c_int64(-10);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_int64(c));
    TEST_ASSERT_EQUAL(-10, v_int64(c));

    cell_destroy(c);
}

void test_cell_uint64(void)
{
    cell_t *c = c_uint64(10);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_uint64(c));
    TEST_ASSERT_EQUAL(10, v_uint64(c));

    cell_destroy(c);
}

void test_cell_float32(void)
{
    cell_t *c = c_float32(3.14f);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_float32(c));
    TEST_ASSERT_EQUAL(3.14f, v_float32(c));

    cell_destroy(c);
}

void test_cell_float64(void)
{
    cell_t *c = c_float64(3.14);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_float64(c));
    TEST_ASSERT_EQUAL(3.14, v_float64(c));

    cell_destroy(c);
}

void test_cell_pointer(void)
{
    cell_t *c = nil;
    void *data = (void *)malloc(sizeof(int));

    c = c_pointer(data);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_pointer(c));
    TEST_ASSERT_EQUAL(data, v_pointer(c));

    cell_destroy(c);
    free(data);
}

void test_cell_pair(void)
{
    cell_t *c = nil;
    void *data = (void *)malloc(sizeof(int));

    c = c_cons(c_int8(10), nil);
    c = c_cons(c_uint8(20), c);
    c = c_cons(c_int16(30), c);
    c = c_cons(c_uint16(40), c);
    c = c_cons(c_int32(50), c);
    c = c_cons(c_uint32(60), c);
    c = c_cons(c_int64(70), c);
    c = c_cons(c_uint64(80), c);
    c = c_cons(c_float32(90.0f), c);
    c = c_cons(c_float64(100.0), c);
    c = c_cons(c_pointer(data), c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_pointer(v_car(c)));
    TEST_ASSERT_EQUAL(v_pointer(v_car(c)), data);
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_float64(v_car(c)));
    TEST_ASSERT_EQUAL(100.0, v_float64(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_float32(v_car(c)));
    TEST_ASSERT_EQUAL(90.0f, v_float32(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_uint64(v_car(c)));
    TEST_ASSERT_EQUAL(80, v_uint64(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_int64(v_car(c)));
    TEST_ASSERT_EQUAL(70, v_int64(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_uint32(v_car(c)));
    TEST_ASSERT_EQUAL(60, v_uint32(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_int32(v_car(c)));
    TEST_ASSERT_EQUAL(50, v_int32(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_uint16(v_car(c)));
    TEST_ASSERT_EQUAL(40, v_uint16(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_int16(v_car(c)));
    TEST_ASSERT_EQUAL(30, v_int16(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_TRUE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_uint8(v_car(c)));
    TEST_ASSERT_EQUAL(20, v_uint8(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_TRUE(is_pair(c));
    TEST_ASSERT_FALSE(is_pair(v_cdr(c)));
    TEST_ASSERT_TRUE(is_int8(v_car(c)));
    TEST_ASSERT_EQUAL(10, v_int8(v_car(c)));
    cell_destroy(v_car(c));
    c = v_cdr(c);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_TRUE(is_nil(c));

    free(data);
}

void test_cell_array_int8(void)
{
    int i;
    cell_t *c = c_aint8(100);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_EQUAL(100, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_aint8(c)[i] = (int8_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((int8_t)i, v_aint8(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_uint8(void)
{
    int i;
    cell_t *c = c_auint8(200);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(200, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_auint8(c)[i] = (uint8_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((uint8_t)i, v_auint8(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_int16(void)
{
    int i;
    cell_t *c = c_aint16(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_aint16(c)[i] = (int16_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((int16_t)i, v_aint16(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_uint16(void)
{
    int i;
    cell_t *c = c_auint16(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_auint16(c)[i] = (uint16_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((uint16_t)i, v_auint16(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_int32(void)
{
    int i;
    cell_t *c = c_aint32(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_aint32(c)[i] = (int32_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((int32_t)i, v_aint32(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_uint32(void)
{
    int i;
    cell_t *c = c_auint32(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_auint32(c)[i] = (uint32_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((uint32_t)i, v_auint32(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_int64(void)
{
    int i;
    cell_t *c = c_aint64(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_aint64(c)[i] = (int64_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((int64_t)i, v_aint64(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_uint64(void)
{
    int i;
    cell_t *c = c_auint64(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_auint64(c)[i] = (uint64_t)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((uint64_t)i, v_auint64(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_float32(void)
{
    int i;
    cell_t *c = c_afloat32(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_afloat32(c)[i] = (float)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((float)i, v_afloat32(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_float64(void)
{
    int i;
    cell_t *c = c_afloat64(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_afloat64(c)[i] = (double)i;
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL((double)i, v_afloat64(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_array_pointer(void)
{
    int i;
    cell_t *c = c_apointer(10000);
    void *pointers[10000];

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        pointers[i] = malloc(sizeof(int));
        v_apointer(c)[i] = pointers[i];
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_EQUAL(pointers[i], v_apointer(c)[i]);
        free(pointers[i]);
    }

    cell_destroy(c);
}

void test_cell_array_cell(void)
{
    int i;
    cell_t *c = c_acell(10000);

    TEST_ASSERT_TRUE(is_array(c));
    TEST_ASSERT_FALSE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_asize(c));

    for (i = 0; i < v_asize(c); ++i) {
        v_acell(c)[i] = c_int64(i);
    }

    for (i = 0; i < v_asize(c); ++i) {
        TEST_ASSERT_TRUE(is_int64(v_acell(c)[i]));
        TEST_ASSERT_EQUAL(i, v_int64(v_acell(c)[i]));

        cell_destroy(v_acell(c)[i]);
    }

    cell_destroy(c);
}

void test_cell_iarray_int8(void)
{
    int i;
    int8_t *d = (int8_t *)malloc(sizeof(*d) * 100);
    cell_t *c = c_iaint8(d, 100);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(100, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iaint8(c)[i] = (int8_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((int8_t)i, v_iaint8(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_uint8(void)
{
    int i;
    uint8_t *d = (uint8_t *)malloc(sizeof(*d) * 200);
    cell_t *c  = c_iauint8(d, 200);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(200, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iauint8(c)[i] = (uint8_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((uint8_t)i, v_iauint8(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_int16(void)
{
    int i;
    int16_t *d = (int16_t *)malloc(sizeof(*d) * 10000);
    cell_t *c  = c_iaint16(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iaint16(c)[i] = (int16_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((int16_t)i, v_iaint16(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_uint16(void)
{
    int i;
    uint16_t *d = (uint16_t *)malloc(sizeof(*d) * 10000);
    cell_t *c   = c_iauint16(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iauint16(c)[i] = (uint16_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((uint16_t)i, v_iauint16(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_int32(void)
{
    int i;
    int32_t *d = (int32_t *)malloc(sizeof(*d) * 10000);
    cell_t *c  = c_iaint32(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iaint32(c)[i] = (int32_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((int32_t)i, v_iaint32(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_uint32(void)
{
    int i;
    uint32_t *d = (uint32_t *)malloc(sizeof(*d) * 10000);
    cell_t *c   = c_iauint32(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iauint32(c)[i] = (uint32_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((uint32_t)i, v_iauint32(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_int64(void)
{
    int i;
    int64_t *d = (int64_t *)malloc(sizeof(*d) * 10000);
    cell_t *c  = c_iaint64(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iaint64(c)[i] = (int64_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((int64_t)i, v_iaint64(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_uint64(void)
{
    int i;
    uint64_t *d = (uint64_t *)malloc(sizeof(*d) * 10000);
    cell_t *c   = c_iauint64(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iauint64(c)[i] = (uint64_t)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((uint64_t)i, v_iauint64(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_float32(void)
{
    int i;
    float *d  = (float *)malloc(sizeof(*d) * 10000);
    cell_t *c = c_iafloat32(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iafloat32(c)[i] = (float)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((float)i, v_iafloat32(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_float64(void)
{
    int i;
    double *d = (double *)malloc(sizeof(*d) * 10000);
    cell_t *c = c_iafloat64(d, 10000);

    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iafloat64(c)[i] = (double)i;
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL((double)i, v_iafloat64(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_pointer(void)
{
    int i;
    void **d  = (void **)malloc(sizeof(*d) * 10000);
    cell_t *c = c_iapointer(d, 10000);
    void *pointers[10000];

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        pointers[i] = malloc(sizeof(int));
        v_iapointer(c)[i] = pointers[i];
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_EQUAL(pointers[i], v_iapointer(c)[i]);
        free(pointers[i]);
    }

    cell_destroy(c);
    free(d);
}

void test_cell_iarray_cell(void)
{
    int i;
    cell_t *d = (cell_t *)malloc(sizeof(*d) * 10000);
    cell_t *c = c_iacell(d, 10000);

    TEST_ASSERT_FALSE(is_array(c));
    TEST_ASSERT_TRUE(is_iarray(c));
    TEST_ASSERT_FALSE(is_pair(c));
    TEST_ASSERT_EQUAL(10000, v_iasize(c));

    for (i = 0; i < v_iasize(c); ++i) {
        v_iacell(c)[i] = c_int64(i);
    }

    for (i = 0; i < v_iasize(c); ++i) {
        TEST_ASSERT_TRUE(is_int64(v_iacell(c)[i]));
        TEST_ASSERT_EQUAL(i, v_int64(v_iacell(c)[i]));

        cell_destroy(v_iacell(c)[i]);
    }

    cell_destroy(c);
    free(d);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_cell_int8);
    RUN_TEST(test_cell_uint8);
    RUN_TEST(test_cell_int16);
    RUN_TEST(test_cell_uint16);
    RUN_TEST(test_cell_int32);
    RUN_TEST(test_cell_uint32);
    RUN_TEST(test_cell_int64);
    RUN_TEST(test_cell_uint64);
    RUN_TEST(test_cell_float32);
    RUN_TEST(test_cell_float64);
    RUN_TEST(test_cell_pointer);
    RUN_TEST(test_cell_pair);
    RUN_TEST(test_cell_array_int8);
    RUN_TEST(test_cell_array_uint8);
    RUN_TEST(test_cell_array_int16);
    RUN_TEST(test_cell_array_uint16);
    RUN_TEST(test_cell_array_int32);
    RUN_TEST(test_cell_array_uint32);
    RUN_TEST(test_cell_array_int64);
    RUN_TEST(test_cell_array_uint64);
    RUN_TEST(test_cell_array_float32);
    RUN_TEST(test_cell_array_float64);
    RUN_TEST(test_cell_array_pointer);
    RUN_TEST(test_cell_array_cell);
    RUN_TEST(test_cell_iarray_int8);
    RUN_TEST(test_cell_iarray_uint8);
    RUN_TEST(test_cell_iarray_int16);
    RUN_TEST(test_cell_iarray_uint16);
    RUN_TEST(test_cell_iarray_int32);
    RUN_TEST(test_cell_iarray_uint32);
    RUN_TEST(test_cell_iarray_int64);
    RUN_TEST(test_cell_iarray_uint64);
    RUN_TEST(test_cell_iarray_float32);
    RUN_TEST(test_cell_iarray_float64);
    RUN_TEST(test_cell_iarray_pointer);
    RUN_TEST(test_cell_iarray_cell);

    return UNITY_END();
}
