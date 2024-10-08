#include <gtest/gtest.h>
#include "lightweight_graph.hpp"

using namespace vpr;

using Graph = lightweight::Graph<int>;
using Node = Graph::Node;

// Test fixture
class  LightweightGraphTest : public ::testing::Test {
protected:
    Graph graph;

    // Setup code executed before each test
    void SetUp() override {
        // Initialize with some nodes for use in various tests
        graph.emplace_node(1);   // Node 0
        graph.emplace_node(2);   // Node 1
        graph.emplace_node(3);   // Node 2
    }
};

// Test for adding nodes using emplace_node
TEST_F( LightweightGraphTest, EmplaceNode) {
    size_t newIndex = graph.emplace_node(5);
    EXPECT_EQ(newIndex, 3);
    EXPECT_EQ(graph.size(), 4);
    EXPECT_EQ(graph.getNode(3).value(), 5);
}

// Test for adding nodes to the graph
TEST_F( LightweightGraphTest, AddNode) {
    // Add a new node and verify its index
    Node node(4);
    size_t newIndex = graph.addNode(node);
    EXPECT_EQ(newIndex, 3);
    EXPECT_EQ(graph.size(), 4);
}

// Test adding an edge and checking node's edges
TEST_F( LightweightGraphTest, AddEdge) {
    graph.addEdge(0, 1); // Add an edge from node 0 to node 1

    // Check that the edge has been added to node 0
    Node& node0 = graph.getNode(0);
    EXPECT_EQ(node0.degree(), 1);
    EXPECT_EQ(node0.edges().at(0), 1);
}

// Test graph copy constructor
TEST_F( LightweightGraphTest, CopyConstructor) {
    Graph copiedGraph = graph;  // Use copy constructor
    EXPECT_EQ(copiedGraph.size(), graph.size());

    // Ensure nodes are the same
    for (size_t i = 0; i < copiedGraph.size(); ++i) {
        EXPECT_EQ(copiedGraph.getNode(i).value(), graph.getNode(i).value());
    }
}

// Test graph move constructor
TEST_F( LightweightGraphTest, MoveConstructor) {
    Graph movedGraph = std::move(graph);  // Use move constructor
    EXPECT_EQ(movedGraph.size(), 3);  // Ensure the graph has the correct size
    EXPECT_EQ(graph.size(), 0);  // Original graph should be empty after move
}

// Test graph copy assignment operator
TEST_F( LightweightGraphTest, CopyAssignment) {
    Graph anotherGraph;
    anotherGraph = graph;  // Use copy assignment operator

    EXPECT_EQ(anotherGraph.size(), graph.size());

    // Ensure nodes are the same
    for (size_t i = 0; i < anotherGraph.size(); ++i) {
        EXPECT_EQ(anotherGraph.getNode(i).value(), graph.getNode(i).value());
    }
}

// Test graph move assignment operator
TEST_F( LightweightGraphTest, MoveAssignment) {
    Graph anotherGraph;
    anotherGraph = std::move(graph);  // Use move assignment operator

    EXPECT_EQ(anotherGraph.size(), 3);
    EXPECT_EQ(graph.size(), 0);  // Original graph should be empty after move
}

// Test getNode method and accessing valid/invalid nodes
TEST_F( LightweightGraphTest, GetNode) {
    Node& node = graph.getNode(1);
    EXPECT_EQ(node.value(), 2);

    // Test out-of-range access (should throw an exception)
    EXPECT_THROW(graph.getNode(5), std::out_of_range);
}

// Test adding edges with invalid node indices
TEST_F( LightweightGraphTest, AddEdgeInvalidIndex) {
    EXPECT_THROW(graph.addEdge(0, 5), std::out_of_range);  // Invalid "to" index
    EXPECT_THROW(graph.addEdge(5, 1), std::out_of_range);  // Invalid "from" index
}

// Test the size method
TEST_F( LightweightGraphTest, SizeMethod) {
    EXPECT_EQ(graph.size(), 3);
    graph.addNode(10);
    EXPECT_EQ(graph.size(), 4);
}

// Test ostream operator for graph
TEST_F( LightweightGraphTest, OutputStreamOperator) {
    std::stringstream output;
    output << graph;

    // Output should be "1 2 3 " (because we added nodes with values 1, 2, 3)
    EXPECT_EQ(output.str(), "1 2 3 ");
}

// Test iterator methods
TEST_F( LightweightGraphTest, IteratorMethods) {
    // Forward iteration over graph nodes
    int sum = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        sum += (*it).value();
    }
    EXPECT_EQ(sum, 6);  // 1 + 2 + 3 = 6

    // Reverse iteration over graph nodes
    sum = 0;
    for (auto it = graph.rbegin(); it != graph.rend(); ++it) {
        sum += (*it).value();
    }
    EXPECT_EQ(sum, 6);  // Same result for reverse iteration
}
