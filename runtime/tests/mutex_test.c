#include <unity.h>
#include <simplex/macros.h>
#include <simplex/thread.h>
#include <simplex/mutex.h>

void setUp(void)
{
}

void tearDown(void)
{
}

static mutex_t lock;
static volatile int val = 0;

thread_func thread(void *arg)
{
    UNUSED(arg);

    int i = 0;

    for (i = 0; i < 100000; ++i) {
        mutex_lock(&lock);
        ++val;
        mutex_unlock(&lock);
    }

    thread_end;
}

void test_mutex(void)
{
    thread_t tid1, tid2, tid3;

    mutex_init(&lock);

    tid1 = thread_create(thread, NULL);
    tid2 = thread_create(thread, NULL);
    tid3 = thread_create(thread, NULL);

    thread_wait(tid1);
    thread_wait(tid2);
    thread_wait(tid3);

    mutex_uninit(&lock);

    TEST_ASSERT_EQUAL(300000, val);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_mutex);

    return UNITY_END();
}
