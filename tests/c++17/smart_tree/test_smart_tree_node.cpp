#include <gtest/gtest.h>
#include "lightweight_tree_node.hpp"
#include "lightweight_tree.hpp"

using namespace vpr;
using lightweight::tree::Node;

// Test fixture
class SmartTreeNodeTest : public ::testing::Test {
protected:
    lightweight::Tree<int> tree_{0};

    void SetUp() override { }

    void TearDown() override { }
};

// Test constructor with optional value
TEST_F(SmartTreeNodeTest, ConstructorWithOptionalValue) {
    Node<std::optional<int>> node(0, 0, 5);
    EXPECT_EQ(node.index(), 0);
    EXPECT_TRUE(node->has_value());
    EXPECT_EQ(node->value(), 5);
}
