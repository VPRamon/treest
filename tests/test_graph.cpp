// test_graph.cpp
#include "gtest/gtest.h"
#include "graph.hpp"
#include "graph_node.hpp"

namespace vpr {

// Test Fixture for Graph
class GraphTest : public ::testing::Test {
protected:
    Graph<std::string> graph;

    void SetUp() override {
        // Initialize a graph with some nodes
        graph.addNode("Node0"); // Index 0
        graph.addNode("Node1"); // Index 1
        graph.addNode("Node2"); // Index 2
        graph.addNode("Node3"); // Index 3
    }
};

// Test adding nodes
TEST_F(GraphTest, AddNode) {
    size_t initialSize = graph.size();
    size_t newNodeIndex = graph.addNode("Node4");
    EXPECT_EQ(newNodeIndex, initialSize);
    EXPECT_EQ(graph.size(), initialSize + 1);
    EXPECT_EQ(graph.getNode(newNodeIndex).value.value(), "Node4");
}

// Test adding edges
TEST_F(GraphTest, AddEdge) {
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    EXPECT_EQ(graph.getNode(0).nOutgoingEdges(), 2);
    EXPECT_EQ(graph.getNode(1).nOutgoingEdges(), 1);
    EXPECT_EQ(graph.getNode(2).nOutgoingEdges(), 1);
    EXPECT_EQ(graph.getNode(3).nOutgoingEdges(), 0);

    // Verify connections
    EXPECT_EQ(graph.getNode(0).getEdge(0).index(), 1);
    EXPECT_EQ(graph.getNode(0).getEdge(1).index(), 2);
    EXPECT_EQ(graph.getNode(1).getEdge(0).index(), 2);
    EXPECT_EQ(graph.getNode(2).getEdge(0).index(), 3);
}

// Test retrieving nodes
TEST_F(GraphTest, GetNode) {
    EXPECT_EQ(graph.getNode(0).value.value(), "Node0");
    EXPECT_EQ(graph.getNode(1).value.value(), "Node1");
    EXPECT_EQ(graph.getNode(2).value.value(), "Node2");
    EXPECT_EQ(graph.getNode(3).value.value(), "Node3");

    // Test out-of-range access
    EXPECT_THROW(graph.getNode(4), std::out_of_range);
}

// Test edge addition with invalid indices
TEST_F(GraphTest, AddEdgeInvalidIndices) {
    // Negative indices are not possible with size_t, but indices beyond current size should throw
    EXPECT_THROW(graph.addEdge(0, 4), std::out_of_range);
    EXPECT_THROW(graph.addEdge(4, 0), std::out_of_range);
    EXPECT_THROW(graph.addEdge(4, 5), std::out_of_range);
}

// Test graph with no nodes
TEST(GraphEmptyTest, EmptyGraph) {
    Graph<int> emptyGraph;
    EXPECT_EQ(emptyGraph.size(), 0);

    // Adding an edge in an empty graph should throw
    EXPECT_THROW(emptyGraph.addEdge(0, 1), std::out_of_range);

    // Accessing any node should throw
    EXPECT_THROW(emptyGraph.getNode(0), std::out_of_range);
}

// Test graph with nodes but no edges
TEST(GraphNoEdgeTest, NodesNoEdges) {
    Graph<int> graph;
    graph.addNode(10);
    graph.addNode(20);
    graph.addNode(30);

    EXPECT_EQ(graph.size(), 3);
    for (size_t i = 0; i < graph.size(); ++i) {
        EXPECT_FALSE(graph.getNode(i).getOutgoingEdges().size() > 0);
        EXPECT_EQ(graph.getNode(i).nOutgoingEdges(), 0);
    }
}

// Test multiple edges to the same node
TEST_F(GraphTest, MultipleEdgesToSameNode) {
    graph.addEdge(0, 1);
    graph.addEdge(0, 1);
    graph.addEdge(0, 1);

    EXPECT_EQ(graph.getNode(0).nOutgoingEdges(), 3);
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(graph.getNode(0).getEdge(i).index(), 1);
    }
}

// Test self-loop
TEST_F(GraphTest, SelfLoop) {
    graph.addEdge(2, 2); // Node2 points to itself

    EXPECT_EQ(graph.getNode(2).nOutgoingEdges(), 1);
    EXPECT_EQ(graph.getNode(2).getEdge(0).index(), 2);
}

// Test graph with variant types
TEST(VariantGraphTest, VariantNodes) {
    using VarGraph = Graph<std::variant<int, double, std::string>>;
    VarGraph graph;
    graph.addNode(42);
    graph.addNode(std::string("Hello"));
    graph.addNode(3.14);

    EXPECT_EQ(graph.size(), 3);
    EXPECT_TRUE(std::get<int>(graph.getNode(0).value.value()) == 42);
    EXPECT_TRUE(std::get<std::string>(graph.getNode(1).value.value()) == "Hello");
    EXPECT_TRUE(std::get<double>(graph.getNode(2).value.value()) == 3.14);
}

} // namespace vpr
