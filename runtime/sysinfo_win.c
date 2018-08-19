#include <Windows.h>
#include <simplex/sysinfo.h>

int sysinfo_page_size(void)
{
    SYSTEM_INFO system_info;

    GetSystemInfo(&system_info);

    return (int)system_info.dwPageSize;
}

int sysinfo_cpu_cores(void)
{
    SYSTEM_INFO system_info;

    GetSystemInfo(&system_info);

    return (int)system_info.dwNumberOfProcessors;
}

int sysinfo_alloc_unit(void)
{
    SYSTEM_INFO system_info;

    GetSystemInfo(&system_info);

    return (int)system_info.dwAllocationGranularity;
}
