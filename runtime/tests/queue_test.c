#include <unity.h>
#include <stdlib.h>
#include <stdint.h>
#include <simplex/atomic.h>
#include <simplex/thread.h>
#include <simplex/queue.h>

#define PUSH_ZIE  100000
#define CHECK_VAL 1234567

struct user_data {
    int value;
};

long total_push;
long total_pop;

long producers;

queue_t queue;

void setUp(void)
{
    total_push = 0;
    total_pop = 0;

    queue_init(&queue);
}

void tearDown(void)
{
    queue_uninit(&queue);
}

thread_func producer(void *arg)
{
    queue_t *q = (queue_t *)arg;
    struct user_data *data;
    int i;

    for (i = 0; i < PUSH_ZIE; ++i) {
        data = (struct user_data *)malloc(sizeof(*data));

        data->value = CHECK_VAL;

        queue_push(q, data);

        atomic_add(&total_push, 1);
    }

    atomic_sub(&producers, 1);

    thread_end;
}

thread_func consumer(void *arg)
{
    queue_t *q = (queue_t *)arg;
    struct user_data *data;

    while (queue_size(q) != 0 || producers != 0) {
        data = queue_pop(q);

        if (data == NULL) {
            continue;
        }

        TEST_ASSERT_EQUAL(CHECK_VAL, data->value);

        free(data);

        atomic_add(&total_pop, 1);
    }

    thread_end;
}

void run_test(int pn, int cn)
{
    thread_t *p, *c;
    int i;

    p = malloc(sizeof(thread_t) * pn);
    c = malloc(sizeof(thread_t) * cn);

    producers = pn;

    for (i = 0; i < pn; ++i) {
        p[i] = thread_create(producer, &queue);
    }

    for (i = 0; i < cn; ++i) {
        c[i] = thread_create(consumer, &queue);
    }

    for (i = 0; i < pn; ++i) {
        thread_wait(p[i]);
    }

    for (i = 0; i < cn; ++i) {
        thread_wait(c[i]);
    }

    free(p);
    free(c);

    TEST_ASSERT_EQUAL(total_push, total_pop);
}

void test_queue_spsc(void)
{
    run_test(1, 1);
}

void test_queue_spmc(void)
{
    run_test(1, 10);
}

void test_queue_mpsc(void)
{
    run_test(10, 1);
}

void test_queue_mpmc(void)
{
    run_test(10, 10);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_queue_spsc);
    RUN_TEST(test_queue_spmc);
    RUN_TEST(test_queue_mpsc);
    RUN_TEST(test_queue_mpmc);

    return UNITY_END();
}
