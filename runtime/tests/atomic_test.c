#include <unity.h>
#include <stdint.h>
#include <simplex/atomic.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_atomic_add(void)
{
    long a = 10, b;

    b = atomic_add(&a, 10);

    TEST_ASSERT_EQUAL_INT(20, a);
    TEST_ASSERT_EQUAL_INT(20, b);
}

void test_atomic_add64(void)
{
    int64_t a = 10, b;

    b = atomic_add64(&a, 10);

    TEST_ASSERT_EQUAL(20, a);
    TEST_ASSERT_EQUAL(20, b);
}

void test_atomic_sub(void)
{
    long a = 10, b;

    b = atomic_sub(&a, 5);

    TEST_ASSERT_EQUAL_INT(5, a);
    TEST_ASSERT_EQUAL_INT(5, b);
}

void test_atomic_sub64(void)
{
    int64_t a = 10, b;

    b = atomic_sub64(&a, 5);

    TEST_ASSERT_EQUAL(5, a);
    TEST_ASSERT_EQUAL(5, b);
}

void test_atomic_or(void)
{
    long a = 10, b;

    b = atomic_or(&a, 3);

    TEST_ASSERT_EQUAL_INT(11, a);
    TEST_ASSERT_EQUAL_INT(11, b);
}

void test_atomic_mbarrier(void)
{
    atomic_mbarrier();
}

void test_atomic_cas_long(void)
{
    long target, old, new;
    int result;

    target = 10;
    old = 10;
    new = 20;

    result = atomic_cas_long(&target, old, new);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(20, target);

    target = 10;
    old = 20;
    new = 20;

    result = atomic_cas_long(&target, old, new);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(10, target);
}

void test_atomic_cas_ptr(void)
{
    void *target, *old, *new;
    int result;

    target = (void *)10;
    old = (void *)10;
    new = (void *)20;

    result = atomic_cas_ptr(&target, old, new);

    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL((void *)20, target);

    target = (void *)10;
    old = (void *)20;
    new = (void *)20;

    result = atomic_cas_ptr(&target, old, new);

    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL((void *)10, target);
}

void test_atomic_revision_cas_ptr(void)
{
    int result;
    long r = 0, l = 0;
    void *target, *old, *new;

    target = (void *)10;
    old = (void *)10;
    new = (void *)20;

    result = atomic_revision_cas_ptr(&l, &r, 0, &target, old, new);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(1, r);
    TEST_ASSERT_EQUAL((void *)20, target);

    target = (void *)10;
    old = (void *)10;
    new = (void *)20;

    result = atomic_revision_cas_ptr(&l, &r, 0, &target, old, new);
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(1, r);
    TEST_ASSERT_EQUAL((void *)10, target);

    target = (void *)10;
    old = (void *)10;
    new = (void *)20;

    result = atomic_revision_cas_ptr(&l, &r, 1, &target, old, new);
    TEST_ASSERT_TRUE(result);
    TEST_ASSERT_EQUAL(2, r);
    TEST_ASSERT_EQUAL((void *)20, target);

    target = (void *)10;
    old = (void *)20;
    new = (void *)20;

    result = atomic_revision_cas_ptr(&l, &r, 2, &target, old, new);
    TEST_ASSERT_FALSE(result);
    TEST_ASSERT_EQUAL(2, r);
    TEST_ASSERT_EQUAL((void *)10, target);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_atomic_add);
    RUN_TEST(test_atomic_add64);
    RUN_TEST(test_atomic_sub);
    RUN_TEST(test_atomic_sub64);
    RUN_TEST(test_atomic_or);
    RUN_TEST(test_atomic_mbarrier);
    RUN_TEST(test_atomic_cas_long);
    RUN_TEST(test_atomic_cas_ptr);
    RUN_TEST(test_atomic_revision_cas_ptr);

    return UNITY_END();
}
