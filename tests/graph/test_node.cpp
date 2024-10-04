#include <gtest/gtest.h>
#include "graph_node.hpp"
#include "graph.hpp"
#include <optional>
#include <vector>
#include <memory>

using namespace vpr;
using namespace vpr::graph;

// Test fixture
class NodeTest : public ::testing::Test {
protected:
    Graph<int> graph_;

    void SetUp() override { }

    void TearDown() override { }
};

// Test constructor with optional value
TEST_F(NodeTest, ConstructorWithOptionalValue) {
    Node<int> node(0, 5);
    EXPECT_EQ(node.index(), 0);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 5);
}

// Test constructor without value
TEST_F(NodeTest, ConstructorWithoutValue) {
    Node<int> node(1);
    EXPECT_EQ(node.index(), 1);
    EXPECT_FALSE(node.hasValue());
}

// Test emplace method
TEST_F(NodeTest, EmplaceValue) {
    Node<int> node(2);
    EXPECT_FALSE(node.hasValue());

    node.emplace(10);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(NodeTest, OutputStreamOperatorWithValue) {
    Node<int> node(3, 15);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "15");
}

// Test ostream operator (<<) for node without value
TEST_F(NodeTest, OutputStreamOperatorWithoutValue) {
    Node<int> node(4);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "None");
}

// Test addEdge and degree methods
TEST_F(NodeTest, AddEdgeAndDegree) {
    size_t idx_1 = graph_.emplace_node(1);
    size_t idx_2 = graph_.emplace_node(2);
    size_t idx_3 = graph_.emplace_node(3);

    graph_.addEdge(idx_1, idx_2);
    EXPECT_EQ(graph_.getNode(idx_1).degree(), 1);
    EXPECT_EQ(graph_.getNode(idx_2).degree(), 1);
    EXPECT_EQ(graph_.getNode(idx_3).degree(), 0);
    EXPECT_EQ(graph_.getNode(idx_1).edges().at(0), idx_2);
    EXPECT_EQ(graph_.getNode(idx_2).edges().at(0), idx_1);
}


// Test exception when accessing value in a node without a value
TEST_F(NodeTest, ValueAccessThrowsException) {
    Node<int> node(5);
    EXPECT_THROW(node.value(), std::bad_optional_access);
}

// Test exception when accessing an out of range node
TEST_F(NodeTest, NodeAccessThrowsException) {
    EXPECT_THROW(graph_.getNode(999), std::out_of_range);
}

// Test operator* dereferencing
TEST_F(NodeTest, DereferenceOperator) {
    Node<int> node(7, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(NodeTest, ArrowOperator) {
    struct something { int a; int b; };
    Node<something> node(8, something{30, 70});
    EXPECT_EQ(node->a, 30);
    EXPECT_EQ(node->b, 70);
}
