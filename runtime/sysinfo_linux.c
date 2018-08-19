#include <unistd.h>
#include <simplex/sysinfo.h>

#define ALLOC_MIN_PAGES 16

int sysinfo_page_size(void)
{
    return (int)sysconf(_SC_PAGESIZE);
}

int sysinfo_cpu_cores(void)
{
    return (int)sysconf(_SC_NPROCESSORS_ONLN);
}

int sysinfo_alloc_unit(void)
{
    return sysinfo_page_size() * ALLOC_MIN_PAGES;
}
