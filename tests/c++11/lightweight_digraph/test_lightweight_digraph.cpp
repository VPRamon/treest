#include <gtest/gtest.h>
#include "lightweight_digraph.hpp"

using namespace vpr;

using Digraph = lightweight::Digraph<int>;
using Node = Digraph::Node;

// Test fixture
class DigraphTest : public ::testing::Test {
protected:
    Digraph digraph;

    // Setup code executed before each test
    void SetUp() override {
        // Initialize with some nodes for use in various tests
        digraph.emplace_node(1);   // Node 0
        digraph.emplace_node(2);   // Node 1
        digraph.emplace_node(3);   // Node 2
    }
};

// Test for adding nodes to the digraph
TEST_F(DigraphTest, AddNode) {
    // Add a new node and verify its index
    size_t newIndex = digraph.emplace_node(4);
    EXPECT_EQ(newIndex, 3);
    EXPECT_EQ(digraph.size(), 4);
}

// Test for adding nodes using emplace_node
TEST_F(DigraphTest, EmplaceNode) {
    size_t newIndex = digraph.emplace_node(5);
    EXPECT_EQ(newIndex, 3);
    EXPECT_EQ(digraph.size(), 4);
    EXPECT_EQ(digraph.getNode(3).value(), 5);
}

// Test adding an edge and checking node's edges
TEST_F(DigraphTest, AddEdge) {
    digraph.addEdge(0, 1); // Add an edge from node 0 to node 1

    // Check that the edge has been added to node 0
    Node& node0 = digraph.getNode(0);
    EXPECT_EQ(node0.degree(), 1);
    EXPECT_EQ(node0.edges().at(0), 1);
    EXPECT_EQ(digraph.getNode(1).degree(), 0);
}

// Test digraph copy constructor
TEST_F(DigraphTest, CopyConstructor) {
    Digraph copiedGraph = digraph;  // Use copy constructor
    EXPECT_EQ(copiedGraph.size(), digraph.size());

    // Ensure nodes are the same
    for (size_t i = 0; i < copiedGraph.size(); ++i) {
        EXPECT_EQ(copiedGraph.getNode(i).value(), digraph.getNode(i).value());
    }
}

// Test digraph move constructor
TEST_F(DigraphTest, MoveConstructor) {
    Digraph movedGraph = std::move(digraph);  // Use move constructor
    EXPECT_EQ(movedGraph.size(), 3);  // Ensure the digraph has the correct size
    EXPECT_EQ(digraph.size(), 0);  // Original digraph should be empty after move
}

// Test digraph copy assignment operator
TEST_F(DigraphTest, CopyAssignment) {
    Digraph anotherGraph;
    anotherGraph = digraph;  // Use copy assignment operator

    EXPECT_EQ(anotherGraph.size(), digraph.size());

    // Ensure nodes are the same
    for (size_t i = 0; i < anotherGraph.size(); ++i) {
        EXPECT_EQ(anotherGraph.getNode(i).value(), digraph.getNode(i).value());
    }
}

// Test digraph move assignment operator
TEST_F(DigraphTest, MoveAssignment) {
    Digraph anotherGraph;
    anotherGraph = std::move(digraph);  // Use move assignment operator

    EXPECT_EQ(anotherGraph.size(), 3);
    EXPECT_EQ(digraph.size(), 0);  // Original digraph should be empty after move
}

// Test getNode method and accessing valid/invalid nodes
TEST_F(DigraphTest, GetNode) {
    Node& node = digraph.getNode(1);
    EXPECT_EQ(node.value(), 2);

    // Test out-of-range access (should throw an exception)
    EXPECT_THROW(digraph.getNode(5), std::out_of_range);
}

// Test adding edges with invalid node indices
TEST_F(DigraphTest, AddEdgeInvalidIndex) {
    EXPECT_THROW(digraph.addEdge(0, 5), std::out_of_range);  // Invalid "to" index
    EXPECT_THROW(digraph.addEdge(5, 1), std::out_of_range);  // Invalid "from" index
}

// Test the size method
TEST_F(DigraphTest, SizeMethod) {
    EXPECT_EQ(digraph.size(), 3);
    digraph.emplace_node(10);
    EXPECT_EQ(digraph.size(), 4);
}

// Test ostream operator for digraph
TEST_F(DigraphTest, OutputStreamOperator) {
    std::stringstream output;
    output << digraph;

    // Output should be "1 2 3 " (because we added nodes with values 1, 2, 3)
    EXPECT_EQ(output.str(), "1 2 3 ");
}

// Test iterator methods
TEST_F(DigraphTest, IteratorMethods) {
    // Forward iteration over digraph nodes
    int sum = 0;
    for (auto it = digraph.begin(); it != digraph.end(); ++it) {
        sum += (*it).value();
    }
    EXPECT_EQ(sum, 6);  // 1 + 2 + 3 = 6

    // Reverse iteration over digraph nodes
    sum = 0;
    for (auto it = digraph.rbegin(); it != digraph.rend(); ++it) {
        sum += (*it).value();
    }
    EXPECT_EQ(sum, 6);  // Same result for reverse iteration
}
