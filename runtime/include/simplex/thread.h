#ifndef _RUNTIME_THREAD_H_
#define _RUNTIME_THREAD_H_

#include <simplex/config.h>

#ifdef CONFIG_PLATFORM_WINDOWS

#include <process.h>
#include <windows.h>

#define thread_func unsigned __stdcall
#define thread_end return 0
#define thread_t HANDLE
#define thread_wait(id) WaitForSingleObject(id, INFINITE)

thread_t thread_create(unsigned (__stdcall *func)(void *), void *arg);

#else /* CONFIG_PLATFORM_WINDOWS */

#include <pthread.h>

#define thread_func void *
#define thread_end return NULL
#define thread_t pthread_t
#define thread_wait(id) pthread_join(id, NULL)

thread_t thread_create(void *(*func)(void *), void *arg);

#endif /* CONFIG_PLATFORM_WINDOWS */

#endif /* _RUNTIME_THREAD_H_ */
