#include <gtest/gtest.h>
#include "digraph_node.hpp"
#include "digraph.hpp"
#include <optional>
#include <vector>
#include <memory>

using namespace vpr;


// Test fixture
class DigraphNodeTest : public ::testing::Test {
protected:
    Digraph<int>* graph_;

    void SetUp() override {
        graph_ = new Digraph<int>;
    }

    void TearDown() override {
        delete graph_;
    }
};

// Test constructor with optional value
TEST_F(DigraphNodeTest, ConstructorWithOptionalValue) {
    DigraphNode<int> node(0, 5);
    EXPECT_EQ(node.index(), 0);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 5);
}

// Test constructor without value
TEST_F(DigraphNodeTest, ConstructorWithoutValue) {
    DigraphNode<int> node(1);
    EXPECT_EQ(node.index(), 1);
    EXPECT_FALSE(node.hasValue());
}

// Test emplace method
TEST_F(DigraphNodeTest, EmplaceValue) {
    DigraphNode<int> node(2);
    EXPECT_FALSE(node.hasValue());

    node.emplace(10);
    EXPECT_TRUE(node.hasValue());
    EXPECT_EQ(node.value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(DigraphNodeTest, OutputStreamOperatorWithValue) {
    DigraphNode<int> node(3, 15);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "15");
}

// Test ostream operator (<<) for node without value
TEST_F(DigraphNodeTest, OutputStreamOperatorWithoutValue) {
    DigraphNode<int> node(4);
    std::stringstream output;
    output << node;
    EXPECT_EQ(output.str(), "None");
}

// Test addEdge and degree methods
TEST_F(DigraphNodeTest, AddEdgeAndDegree) {
    size_t idx_1 = graph_->emplace_node(1);
    size_t idx_2 = graph_->emplace_node(2);

    graph_->addEdge(idx_1, idx_2);

    EXPECT_EQ(graph_->getNode(idx_1).totalDegree(), 1);
    EXPECT_EQ(graph_->getNode(idx_1).inDegree(), 0);
    EXPECT_EQ(graph_->getNode(idx_1).outDegree(), 1);

    EXPECT_EQ(graph_->getNode(idx_2).totalDegree(), 1);
    EXPECT_EQ(graph_->getNode(idx_2).inDegree(), 1);
    EXPECT_EQ(graph_->getNode(idx_2).outDegree(), 0);

    EXPECT_EQ(graph_->getNode(idx_1).inEdges(),  std::vector<size_t>{});
    EXPECT_EQ(graph_->getNode(idx_2).inEdges(),  std::vector<size_t>{idx_1});
    EXPECT_EQ(graph_->getNode(idx_1).outEdges(), std::vector<size_t>{idx_2});
    EXPECT_EQ(graph_->getNode(idx_2).outEdges(), std::vector<size_t>{});
}


// Test exception when accessing value in a node without a value
TEST_F(DigraphNodeTest, ValueAccessThrowsException) {
    DigraphNode<int> node(5);
    EXPECT_THROW(node.value(), std::bad_optional_access);
}


// Test operator* dereferencing
TEST_F(DigraphNodeTest, DereferenceOperator) {
    DigraphNode<int> node(7, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(DigraphNodeTest, ArrowOperator) {
    struct something { int a; int b; };
    DigraphNode<something> node(8, something{30, 70});
    EXPECT_EQ(node->a, 30);
    EXPECT_EQ(node->b, 70);
}
