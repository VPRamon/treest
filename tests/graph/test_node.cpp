#include <gtest/gtest.h>
#include "node.hpp"
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
    auto node = std::make_shared<Node<int>>(0, graph_, 5);
    EXPECT_EQ(node->index(), 0);
    EXPECT_TRUE(node->hasValue());
    EXPECT_EQ(node->value(), 5);
}

// Test constructor without value
TEST_F(NodeTest, ConstructorWithoutValue) {
    auto node = std::make_shared<Node<int>>(1, graph_);
    EXPECT_EQ(node->index(), 1);
    EXPECT_FALSE(node->hasValue());
}

// Test emplace method
TEST_F(NodeTest, EmplaceValue) {
    auto node = std::make_shared<Node<int>>(2, graph_);
    EXPECT_FALSE(node->hasValue());

    node->emplace(10);
    EXPECT_TRUE(node->hasValue());
    EXPECT_EQ(node->value(), 10);
}

// Test ostream operator (<<) for node with value
TEST_F(NodeTest, OutputStreamOperatorWithValue) {
    auto node = std::make_shared<Node<int>>(3, graph_, 15);
    std::stringstream output;
    output << *node;
    EXPECT_EQ(output.str(), "15");
}

// Test ostream operator (<<) for node without value
TEST_F(NodeTest, OutputStreamOperatorWithoutValue) {
    auto node = std::make_shared<Node<int>>(4, graph_);
    std::stringstream output;
    output << *node;
    EXPECT_EQ(output.str(), "None");
}

// Test addEdge and degree methods
TEST_F(NodeTest, AddEdgeAndDegree) {
    size_t idx_1 = graph_->emplace_back(1);
    size_t idx_2 = graph_->emplace_back(2);

    graph_->addEdge(idx_1, idx_2);
    EXPECT_EQ(graph_->getNode(idx_1).degree(), 1);
    EXPECT_EQ(graph_->getNode(idx_1).edges().at(0), idx_2);
}

// Test getNeighbour method
TEST_F(NodeTest, GetNeighbour) {
    size_t idx_1 = graph_->emplace_back(1);
    size_t idx_2 = graph_->emplace_back(2);
    
    graph_->addEdge(idx_1, idx_2);
    Node<int>& neighbour = graph_->getNode(idx_1).getNeighbour(0);
    EXPECT_EQ(neighbour.index(), idx_2);
    EXPECT_EQ(neighbour.value(), 2);
}

// Test exception when accessing value in a node without a value
TEST_F(NodeTest, ValueAccessThrowsException) {
    auto node = std::make_shared<Node<int>>(5, graph_);
    EXPECT_THROW(node->value(), std::bad_optional_access);
}

// Test graph pointer
TEST_F(NodeTest, GraphPointer) {
    auto node = std::make_shared<Node<int>>(6, graph_, 20);
    EXPECT_EQ(node->graph(), graph_);
}

// Test operator* dereferencing
TEST_F(NodeTest, DereferenceOperator) {
    Node<int> node(7, graph_, 25);
    EXPECT_EQ(*node, 25);
}

// Test operator-> for access to value
TEST_F(NodeTest, ArrowOperator) {
    auto node = std::make_shared<Node<int>>(8, graph_, 30);
    EXPECT_EQ(node->operator->(), &node->value());
}
