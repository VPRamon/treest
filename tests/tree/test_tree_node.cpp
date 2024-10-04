#include <gtest/gtest.h>
#include "tree_node.hpp"
#include "tree.hpp"

using namespace vpr;
using namespace tree;


// Test fixture
class TreeNodeTest : public ::testing::Test {
protected:
    Tree<int> tree_;

    void SetUp() override { }

    void TearDown() override { }
};

// Test constructor with optional value
TEST_F(TreeNodeTest, ConstructorWithOptionalValue) {
    tree::Node<int> node(0, 0, 5);
    EXPECT_EQ(node.index(), 0);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 5);
}

// Test constructor without value
TEST_F(TreeNodeTest, ConstructorWithoutValue) {
    tree::Node<int> node(1, 0);
    EXPECT_EQ(node.index(), 1);
    EXPECT_FALSE(node.hasValue());
}

// Test emplace method
TEST_F(TreeNodeTest, EmplaceValue) {
    tree::Node<int> node(0, 0);
    EXPECT_FALSE(node.hasValue());

    node.emplace(10);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(TreeNodeTest, OutputStreamOperatorWithValue) {
    tree::Node<int> node(3, 2, 15);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "15");
}

// Test ostream operator (<<) for node without value
TEST_F(TreeNodeTest, OutputStreamOperatorWithoutValue) {
    tree::Node<int> node(4, 2);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "None");
}


// Test exception when accessing value in a node without a value
TEST_F(TreeNodeTest, ValueAccessThrowsException) {
    tree::Node<int> node(5, 1);
    EXPECT_THROW(node.value(), std::bad_optional_access);
}

// Test exception when accessing an out of range node
TEST_F(TreeNodeTest, NodeAccessThrowsException) {
    EXPECT_THROW(tree_.getNode(999), std::out_of_range);
}

// Test operator* dereferencing
TEST_F(TreeNodeTest, DereferenceOperator) {
    tree::Node<int> node(7, 1, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(TreeNodeTest, ArrowOperator) {
    struct something { int a; int b; };
    tree::Node<something> node(8, 11, something{30, 70});
    EXPECT_EQ(node->a, 30);
    EXPECT_EQ(node->b, 70);
}

/*
TEST_F(TreeNodeTest, TestShouldNotCompile) {
    size_t idx_1 = tree_.emplace_node(1);
    size_t idx_2 = tree_.emplace_node(2);

    auto node = tree_.getNode(idx_1);
    node.addEdge(idx_2);
}
*/
