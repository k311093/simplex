#include <pthread.h>
#include <simplex/thread.h>

thread_t thread_create(void *(*func)(void *), void *arg)
{
    thread_t result;

    pthread_create(&result, NULL, func, arg);

    return result;
}
