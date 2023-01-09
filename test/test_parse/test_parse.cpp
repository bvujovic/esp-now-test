#include <unity.h>

void setUp(void) {}

void tearDown(void) {}

void test_1()
{
  TEST_ASSERT_EQUAL(2, 2);
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();

  RUN_TEST(test_1);

  UNITY_END();
  return 0;
}