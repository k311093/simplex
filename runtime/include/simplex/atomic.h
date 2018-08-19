#ifndef _RUNTIME_ATOMIC_H_
#define _RUNTIME_ATOMIC_H_

#include <simplex/config.h>

#ifdef CONFIG_COMPILER_MSVC

#include <Windows.h>

#define atomic_add         InterlockedAddNoFence
#define atomic_add64       InterlockedAddNoFence64
#define atomic_sub(x, y)   InterlockedAddNoFence((x), -(y))
#define atomic_sub64(x, y) InterlockedAddNoFence64((x), -(y))
#define atomic_or(x, y)    (InterlockedOrNoFence((x), (y)) | (y))
#define atomic_mbarrier    MemoryBarrier
#define atomic_cas_long(x, y, z) \
    (InterlockedCompareExchangeNoFence((x), (z), (y)) == (y))
#define atomic_cas_ptr(x, y, z) \
    (InterlockedCompareExchangePointerNoFence((x), (z), (y)) == (y))

#else /* CONFIG_COMPILER_MSVC */

#define atomic_add      __sync_add_and_fetch
#define atomic_add64    __sync_add_and_fetch
#define atomic_sub      __sync_sub_and_fetch
#define atomic_sub64    __sync_sub_and_fetch
#define atomic_or       __sync_or_and_fetch
#define atomic_mbarrier __sync_synchronize
#define atomic_cas_long __sync_bool_compare_and_swap
#define atomic_cas_ptr  __sync_bool_compare_and_swap

#endif /* CONFIG_COMPILER_MSVC */

int atomic_revision_cas_ptr(long *l, long *oldr, long r,
                            void **t, void *o, void *n);

#endif /* _RUNTIME_ATOMIC_H_ */
