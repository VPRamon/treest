#include <gtest/gtest.h>
#include "graph_node.hpp"
#include "graph.hpp"
#include <optional>
#include <vector>
#include <memory>

using namespace vpr;


// Test fixture
class NodeTest : public ::testing::Test {
protected:
    Graph<int>* graph_;

    void SetUp() override {
        graph_ = new Graph<int>;
    }

    void TearDown() override {
        delete graph_;
    }
};

// Test constructor with optional value
TEST_F(NodeTest, ConstructorWithOptionalValue) {
    GraphNode<int> node(0, 5);
    EXPECT_EQ(node.index(), 0);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 5);
}

// Test constructor without value
TEST_F(NodeTest, ConstructorWithoutValue) {
    GraphNode<int> node(1);
    EXPECT_EQ(node.index(), 1);
    EXPECT_FALSE(node.hasValue());
}

// Test emplace method
TEST_F(NodeTest, EmplaceValue) {
    GraphNode<int> node(2);
    EXPECT_FALSE(node.hasValue());

    node.emplace(10);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(NodeTest, OutputStreamOperatorWithValue) {
    GraphNode<int> node(3, 15);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "15");
}

// Test ostream operator (<<) for node without value
TEST_F(NodeTest, OutputStreamOperatorWithoutValue) {
    GraphNode<int> node(4);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "None");
}

// Test addEdge and degree methods
TEST_F(NodeTest, AddEdgeAndDegree) {
    size_t idx_1 = graph_->emplace_node(1);
    size_t idx_2 = graph_->emplace_node(2);

    graph_->addEdge(idx_1, idx_2);
    EXPECT_EQ(graph_->getNode(idx_1).degree(), 1);
    EXPECT_EQ(graph_->getNode(idx_1).edges().at(0), idx_2);
}


// Test exception when accessing value in a node without a value
TEST_F(NodeTest, ValueAccessThrowsException) {
    GraphNode<int> node(5);
    EXPECT_THROW(node.value(), std::bad_optional_access);
}


// Test operator* dereferencing
TEST_F(NodeTest, DereferenceOperator) {
    GraphNode<int> node(7, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(NodeTest, ArrowOperator) {
    struct something { int a; int b; };
    GraphNode<something> node(8, something{30, 70});
    EXPECT_EQ(node->a, 30);
    EXPECT_EQ(node->b, 70);
}
