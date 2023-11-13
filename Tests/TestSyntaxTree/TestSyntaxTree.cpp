#include <gtest/gtest.h>

TEST(SimpleMathTest, Addition) {
    int result = 1 + 1;
    EXPECT_EQ(result, 2);
}


class MathOperations {
public:
    int add(int a, int b) {
        return a + b;
    }
};

// Test fixture for math operations
class MathOperationsTest : public ::testing::Test {
protected:
    // Setup function (optional)
    void SetUp() override {
        // Code to run before each test
        mathOperations = std::make_unique<MathOperations>();
    }

    // Teardown function (optional)
    void TearDown() override {
        // Code to run after each test
    }

    // Pointer to the MathOperations instance
    std::unique_ptr<MathOperations> mathOperations;
};

// Test case using TEST_F with the MathOperationsTest fixture
TEST_F(MathOperationsTest, AddTwoNumbers) {
    int result = mathOperations->add(3, 4);
    EXPECT_EQ(result, 7);
}