#include <process.h>
#include <windows.h>
#include <simplex/thread.h>

thread_t thread_create(unsigned (__stdcall *func)(void *), void *arg)
{
    thread_t result = (thread_t)_beginthreadex(NULL, 0, func, arg, 0, NULL);

    return result;
}
