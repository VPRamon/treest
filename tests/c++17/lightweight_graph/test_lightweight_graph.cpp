// tests/test_lightweight_graph.cpp

#include <gtest/gtest.h>
#include <string>
#include <sstream>  // For std::ostringstream
#include "lightweight_graph.hpp"

using namespace vpr::lightweight;

// Helper function to get values for different types
template <typename T>
T getValue(int n) {
    return static_cast<T>(n);
}

template <>
std::string getValue<std::string>(int n) {
    return "Node" + std::to_string(n);
}

/**
 * @brief Test fixture for the Graph class.
 * 
 * This fixture sets up a Graph instance before each test and cleans up afterward.
 */
template <typename T>
class GraphTest : public ::testing::Test {
protected:
    // Type alias for convenience
    using GraphType = Graph<T>;

    // Graph instance to be used in tests
    GraphType graph;

    // Setup before each test
    void SetUp() override {
        // Optionally, initialize the graph with some nodes or edges
    }

    // Tear down after each test
    void TearDown() override {
        // Clean up if necessary
    }
};

// Define the types to be tested (e.g., int, std::string)
typedef ::testing::Types<int, std::string> Implementations;

// Register the test types
TYPED_TEST_SUITE(GraphTest, Implementations);

/**
 * @brief Test adding a single node to the graph.
 */
TYPED_TEST(GraphTest, AddSingleNode) {
    using T = TypeParam;
    T value = getValue<T>(1);

    size_t nodeIndex = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value));

    // Verify that the node was added correctly
    EXPECT_EQ(nodeIndex, 0);
    EXPECT_EQ(this->graph.getNode(nodeIndex).value(), value);
    EXPECT_EQ(this->graph.getNode(nodeIndex).degree(), 0);
}

/**
 * @brief Test adding multiple nodes and verifying their indices and values.
 */
TYPED_TEST(GraphTest, AddMultipleNodes) {
    using T = TypeParam;
    std::vector<T> values;
    for (int i = 1; i <= 3; ++i) {
        values.push_back(getValue<T>(i));
    }

    std::vector<size_t> indices;
    for (size_t i = 0; i < values.size(); ++i) {
        indices.push_back(this->graph.addNode(typename GraphTest<T>::GraphType::Node(i, values[i])));
    }

    // Verify indices and values
    for (size_t i = 0; i < indices.size(); ++i) {
        EXPECT_EQ(indices[i], i);
        EXPECT_EQ(this->graph.getNode(indices[i]).value(), values[i]);
    }

    // Verify the total number of nodes
    EXPECT_EQ(this->graph.size(), values.size());
}

/**
 * @brief Test adding an edge between two nodes and verifying bidirectional connection.
 */
TYPED_TEST(GraphTest, AddEdge) {
    using T = TypeParam;
    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(1, value2));

    // Add edge between index1 and index2
    this->graph.addEdge(index1, index2);

    // Verify that both nodes have the correct degree
    EXPECT_EQ(this->graph.getNode(index1).degree(), 1);
    EXPECT_EQ(this->graph.getNode(index2).degree(), 1);

    // Verify that the edges are correctly added
    const auto& edges1 = this->graph.getNode(index1).edges();
    const auto& edges2 = this->graph.getNode(index2).edges();

    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());
    EXPECT_NE(std::find(edges2.begin(), edges2.end(), index1), edges2.end());
}

/**
 * @brief Test adding multiple edges and verifying degrees.
 */
TYPED_TEST(GraphTest, AddMultipleEdges) {
    using T = TypeParam;
    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);
    T value3 = getValue<T>(3);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(1, value2));
    size_t index3 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(2, value3));

    // Add edges: index1 - index2, index1 - index3
    this->graph.addEdge(index1, index2);
    this->graph.addEdge(index1, index3);

    // Verify degrees
    EXPECT_EQ(this->graph.getNode(index1).degree(), 2);
    EXPECT_EQ(this->graph.getNode(index2).degree(), 1);
    EXPECT_EQ(this->graph.getNode(index3).degree(), 1);

    // Verify connections
    const auto& edges1 = this->graph.getNode(index1).edges();
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index3), edges1.end());

    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_NE(std::find(edges2.begin(), edges2.end(), index1), edges2.end());

    const auto& edges3 = this->graph.getNode(index3).edges();
    EXPECT_NE(std::find(edges3.begin(), edges3.end(), index1), edges3.end());
}

/**
 * @brief Test graph isolation (nodes with no edges).
 */
TYPED_TEST(GraphTest, IsolatedNodes) {
    using T = TypeParam;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);
    T value3 = getValue<T>(3);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(1, value2));
    size_t index3 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(2, value3));

    // Verify isolation
    EXPECT_TRUE(this->graph.getNode(index1).isolated());
    EXPECT_TRUE(this->graph.getNode(index2).isolated());
    EXPECT_TRUE(this->graph.getNode(index3).isolated());
}

/**
 * @brief Test reserving edge capacity and adding edges.
 */
TYPED_TEST(GraphTest, ReserveEdges) {
    using T = TypeParam;
    T value = getValue<T>(1);

    size_t index = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value));

    // Reserve space for 5 edges
    this->graph.getNode(index).reserveEdges(5);

    // Add 5 edges
    for (int i = 1; i <= 5; ++i) {
        T nodeValue = getValue<T>(i + 1);
        size_t newIndex = this->graph.addNode(typename GraphTest<T>::GraphType::Node(i, nodeValue));
        this->graph.addEdge(index, newIndex);
    }

    // Verify degree
    EXPECT_EQ(this->graph.getNode(index).degree(), 5);
}

/**
 * @brief Test adding duplicate edges and verifying that duplicates are handled.
 */
TYPED_TEST(GraphTest, AddDuplicateEdges) {
    using T = TypeParam;
    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(1, value2));

    // Add the same edge twice
    this->graph.addEdge(index1, index2);
    this->graph.addEdge(index1, index2);

    // Verify degrees
    EXPECT_EQ(this->graph.getNode(index1).degree(), 2);
    EXPECT_EQ(this->graph.getNode(index2).degree(), 2);

    // Verify that both edges exist
    const auto& edges1 = this->graph.getNode(index1).edges();
    int count1 = std::count(edges1.begin(), edges1.end(), index2);
    EXPECT_EQ(count1, 2);

    const auto& edges2 = this->graph.getNode(index2).edges();
    int count2 = std::count(edges2.begin(), edges2.end(), index1);
    EXPECT_EQ(count2, 2);
}

/**
 * @brief Test handling of invalid node indices when adding edges.
 * 
 * This test assumes that the `addEdge` method throws an exception when invalid indices are used.
 */
TYPED_TEST(GraphTest, AddEdgeInvalidIndices) {
    using T = TypeParam;
    T value = getValue<T>(1);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value));

    // Attempt to add an edge to a non-existent node
    size_t invalidIndex = 100; // Assuming this is out of bounds

    // Depending on your implementation, this might throw an exception, assert, or do nothing.
    // For demonstration, let's assume it throws an exception.
    EXPECT_THROW(this->graph.addEdge(index1, invalidIndex), std::out_of_range);
}

/**
 * @brief Test the graph with different data types (int and std::string).
 * 
 * This is implicitly covered by the typed tests, but you can add specific tests 
 * if behavior differs based on the data type.
 */
TYPED_TEST(GraphTest, GraphWithDifferentDataTypes) {
    using T = TypeParam;
    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename GraphTest<T>::GraphType::Node(1, value2));

    // Add edge between them
    this->graph.addEdge(index1, index2);

    // Verify values and connections
    EXPECT_EQ(this->graph.getNode(index1).value(), value1);
    EXPECT_EQ(this->graph.getNode(index2).value(), value2);

    EXPECT_EQ(this->graph.getNode(index1).degree(), 1);
    EXPECT_EQ(this->graph.getNode(index2).degree(), 1);
}

/**
 * @brief Test emplace method for constructing node values in place.
 */
TYPED_TEST(GraphTest, EmplaceNodeValue) {
    using T = TypeParam;
    T initialValue = getValue<T>(10);
    typename GraphTest<T>::GraphType::Node node(0, initialValue);
    this->graph.addNode(std::move(node));

    // Emplace a new value
    T newValue = getValue<T>(20);
    this->graph.getNode(0).emplace(newValue);

    // Verify that the value was updated
    EXPECT_EQ(this->graph.getNode(0).value(), newValue);
}

/**
 * @brief Test operator<< for Node.
 * 
 * This test verifies that the `operator<<` correctly outputs the node's value.
 */
TEST(GraphOperatorTest, NodeOutputOperator) {
    using T = std::string;
    Graph<T> graph;

    size_t index = graph.addNode(typename Graph<T>::Node(0, "NodeA"));

    std::ostringstream oss;
    oss << graph.getNode(index);

    EXPECT_EQ(oss.str(), "NodeA");
}
