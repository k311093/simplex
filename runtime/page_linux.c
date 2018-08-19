#include <stdio.h>
#include <sys/mman.h>
#include <simplex/sysinfo.h>
#include <simplex/page.h>

static int page_alloc_size_ = 0;

int page_alloc_size(void)
{
    if (page_alloc_size_ == 0) {
        page_alloc_size_ = sysinfo_alloc_unit();
    }

    return page_alloc_size_;
}

void *page_alloc(void)
{
    void *result, *map_result;

    map_result = mmap(0, page_alloc_size(),
        PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (map_result == MAP_FAILED) {
        result = NULL;
    }
    else {
        result = map_result;
    }

    return result;
}

int page_free(void *pages)
{
    return (munmap(pages, page_alloc_size()) == 0);
}
