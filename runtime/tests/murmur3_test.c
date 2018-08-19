#include <unity.h>
#include <simplex/murmur3.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_murmur3_basic(void)
{
    TEST_ASSERT_EQUAL_UINT32(0x00000000, murmur3_hash("", 0, 0));
    TEST_ASSERT_EQUAL_UINT32(0xbfebd3f1, murmur3_hash("", 0, 14));
    TEST_ASSERT_EQUAL_UINT32(0x3c2569b2, murmur3_hash("a", 1, 0));
    TEST_ASSERT_EQUAL_UINT32(0xb8079b46, murmur3_hash("ab", 2, 1));
    TEST_ASSERT_EQUAL_UINT32(0x96c13c57, murmur3_hash("abc", 3, 2));
    TEST_ASSERT_EQUAL_UINT32(0x1411db9c, murmur3_hash("abcd", 4, 3));
    TEST_ASSERT_EQUAL_UINT32(0x038715b2, murmur3_hash("abcde", 5, 4));
    TEST_ASSERT_EQUAL_UINT32(0x70a43b80, murmur3_hash("abcdef", 6, 5));
    TEST_ASSERT_EQUAL_UINT32(0x71827cc0, murmur3_hash("abcdefg", 7, 6));
    TEST_ASSERT_EQUAL_UINT32(0x274be5a5, murmur3_hash("abcdefgh", 8, 7));
    TEST_ASSERT_EQUAL_UINT32(0xfb25af66, murmur3_hash("abcdefghi", 9, 8));
    TEST_ASSERT_EQUAL_UINT32(0x3e0f0fe3, murmur3_hash("abcdefghij", 10, 9));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_murmur3_basic);

    return UNITY_END();
}
