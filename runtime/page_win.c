#include <Windows.h>
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
    void *result;

    result = VirtualAlloc(NULL, page_alloc_size(),
        MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    return result;
}

int page_free(void *pages)
{
    int result;

    if (VirtualFree(pages, page_alloc_size(), MEM_DECOMMIT)) {
        result = (int)VirtualFree(pages, 0, MEM_RELEASE);
    }
    else {
        result = 0;
    }

    return result;
}
