#include <unity.h>
#include <simplex/page.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_page(void)
{
    char *page = (char *)page_alloc();
    int page_size = page_alloc_size();
    int i;

    TEST_ASSERT_NOT_EQUAL(0, page_size);
    TEST_ASSERT_NOT_NULL(page);

    for (i = 0; i < page_size; ++i) {
        page[i] = 0x20;
    }

    for (i = 0; i < page_size; ++i) {
        TEST_ASSERT_EQUAL(0x20, page[i]);
    }

    TEST_ASSERT_TRUE(page_free(page));
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(test_page);

    return UNITY_END();
}
