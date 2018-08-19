#include <unity.h>
#include <simplex/sysinfo.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_sysinfo_page_size(void)
{
    int page_size = sysinfo_page_size();

    while (page_size > 1) {
        TEST_ASSERT_TRUE(page_size % 2 == 0);
        page_size /= 2;
    }
}

void test_sysinfo_cpu_cores(void)
{
    int cpu_cores = sysinfo_cpu_cores();

    TEST_ASSERT_GREATER_THAN(0, cpu_cores);
}

void test_sysinfo_alloc_unit(void)
{
    int page_size = sysinfo_alloc_unit();

    while (page_size > 1) {
        TEST_ASSERT_TRUE(page_size % 2 == 0);
        page_size /= 2;
    }
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_sysinfo_page_size);
    RUN_TEST(test_sysinfo_cpu_cores);
    RUN_TEST(test_sysinfo_alloc_unit);

    return UNITY_END();
}
