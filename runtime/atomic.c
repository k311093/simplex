#include <simplex/atomic.h>

int atomic_revision_cas_ptr(long *l, long *oldr, long r,
                            void **t, void *o, void *n)
{
    while(!atomic_cas_long(l, 0, 1));

    if (*oldr == r && *t == o) {
        atomic_add(oldr, 1);

        *t = n;
        *l = 0;

        return 1;
    }

    *l = 0;

    return 0;
}
