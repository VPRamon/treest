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

// Test constructor without value
TEST_F(SmartTreeNodeTest, ConstructorWithRawValue) {
    Node<int> node(1, 0, 777);
    EXPECT_EQ(node.index(), 1);
    EXPECT_EQ(node.parentId(), 0);
    EXPECT_EQ(node.value(), 777);
}

// Test emplace method
TEST_F(SmartTreeNodeTest, EmplaceValue) {
    Node<int> node(0, 0, 777);

    EXPECT_EQ(node.value(), 777);
    node.emplace(10);
    EXPECT_EQ(node.value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(SmartTreeNodeTest, OutputStreamOperatorWithValue) {
    Node<int> node(3, 2, 15);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "15");
}

// Test exception when accessing an out of range node
TEST_F(SmartTreeNodeTest, NodeAccessThrowsException) {
    EXPECT_THROW(tree_.getNode(999), std::out_of_range);
}

// Test operator* dereferencing
TEST_F(SmartTreeNodeTest, DereferenceOperator) {
    Node<int> node(7, 1, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(SmartTreeNodeTest, ArrowOperator) {
    struct something { int a; int b; };
    Node<something> node(8, 11, something{30, 70});
    EXPECT_EQ(node->a, 30);
    EXPECT_EQ(node->b, 70);
}

/*
TEST_F(SmartTreeNodeTest, TestShouldNotCompile) {
    size_t idx_1 = tree_.emplace_node(1);
    size_t idx_2 = tree_.emplace_node(2);

    auto node = tree_.getNode(idx_1);
    node.addEdge(idx_2);
}
*/
