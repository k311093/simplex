#include <unity.h>
#include <simplex/thread.h>

void setUp(void)
{
}

void tearDown(void)
{
}

thread_func thread1(void *arg)
{
    int i = 0;

    for (i = 0; i < 10; ++i) {
        *((int *)arg) += i;
    }

    thread_end;
}

thread_func thread2(void *arg)
{
    int i = 0;

    for (i = 0; i < 10; ++i) {
        *((int *)arg) += i;
    }

    thread_end;
}

void test_thread_basic(void)
{
    int sum[2] = {0,};
    thread_t tid1, tid2;

    tid1 = thread_create(thread1, &sum[0]);
    tid2 = thread_create(thread2, &sum[1]);

    thread_wait(tid1);
    thread_wait(tid2);

    TEST_ASSERT_EQUAL_INT(45, sum[0]);
    TEST_ASSERT_EQUAL_INT(45, sum[1]);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_thread_basic);

    return UNITY_END();
}
