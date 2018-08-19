#ifndef _RUNTIME_MUTEX_H_
#define _RUNTIME_MUTEX_H_

#include <simplex/config.h>

#ifdef CONFIG_COMPILER_MSVC

#include <Windows.h>

typedef CRITICAL_SECTION mutex_t;

#define mutex_init   InitializeCriticalSection
#define mutex_uninit DeleteCriticalSection
#define mutex_lock   EnterCriticalSection
#define mutex_unlock LeaveCriticalSection

#else /* CONFIG_COMPILER_MSVC */

#include <pthread.h>

typedef pthread_mutex_t mutex_t;

#define mutex_init(x) pthread_mutex_init(x, NULL)
#define mutex_uninit  pthread_mutex_destroy
#define mutex_lock    pthread_mutex_lock
#define mutex_unlock  pthread_mutex_unlock

#endif /* CONFIG_COMPILER_MSVC */

#endif /* _RUNTIME_MUTEX_H_ */
