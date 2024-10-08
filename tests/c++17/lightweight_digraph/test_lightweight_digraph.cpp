// tests/test_lightweight_digraph.cpp

#include <gtest/gtest.h>
#include <string>
#include <sstream>  // For std::ostringstream
#include <algorithm> // For std::find, std::count
#include <type_traits> // For std::is_same
#include "lightweight_digraph.hpp"

using namespace vpr::lightweight;

/**
 * @brief Helper function to get values for different types.
 * 
 * This function returns appropriate values based on the type `T`.
 * - For `int`: Returns the integer value directly.
 * - For `std::string`: Returns a string like "Node1", "Node2", etc.
 * 
 * @tparam T The type of the value.
 * @param n The integer used to generate the value.
 * @return The generated value of type `T`.
 */
template <typename T>
T getValue(int n) {
    return static_cast<T>(n);
}

// Template specialization for std::string
template <>
inline std::string getValue<std::string>(int n) {
    return "Node" + std::to_string(n);
}

/**
 * @brief Test fixture for the Digraph class.
 * 
 * This fixture sets up a Digraph instance before each test and cleans up afterward.
 */
template <typename T>
class DigraphTest : public ::testing::Test {
protected:
    // Type alias for convenience
    typedef Digraph<T> DigraphType;

    // Digraph instance to be used in tests
    DigraphType graph;

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
TYPED_TEST_SUITE(DigraphTest, Implementations);

/**
 * @brief Test adding a single node to the digraph.
 */
TYPED_TEST(DigraphTest, AddSingleNode) {
    typedef TypeParam T;
    T value = getValue<T>(1);

    size_t nodeIndex = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value));

    // Verify that the node was added correctly
    EXPECT_EQ(nodeIndex, 0);
    EXPECT_EQ(this->graph.getNode(nodeIndex).value(), value);
    EXPECT_EQ(this->graph.getNode(nodeIndex).degree(), 0);
}

/**
 * @brief Test adding multiple nodes and verifying their indices and values.
 */
TYPED_TEST(DigraphTest, AddMultipleNodes) {
    typedef TypeParam T;
    std::vector<T> values;
    for (int i = 1; i <= 3; ++i) {
        values.push_back(getValue<T>(i));
    }

    std::vector<size_t> indices;
    for (size_t i = 0; i < values.size(); ++i) {
        indices.push_back(this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(i, values[i])));
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
 * @brief Test adding a directed edge between two nodes and verifying the connection.
 */
TYPED_TEST(DigraphTest, AddEdge) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));

    // Add directed edge from index1 to index2
    this->graph.addEdge(index1, index2);

    // Verify that node1 has one outgoing edge
    EXPECT_EQ(this->graph.getNode(index1).degree(), 1);
    // Verify that node2 has zero outgoing edges
    EXPECT_EQ(this->graph.getNode(index2).degree(), 0);

    // Verify that node1's edges include node2
    const auto& edges1 = this->graph.getNode(index1).edges();
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());

    // Verify that node2's edges do not include node1
    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_EQ(std::find(edges2.begin(), edges2.end(), index1), edges2.end());
}

/**
 * @brief Test adding multiple directed edges and verifying degrees and connections.
 */
TYPED_TEST(DigraphTest, AddMultipleEdges) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);
    T value3 = getValue<T>(3);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));
    size_t index3 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(2, value3));

    // Add directed edges: index1 -> index2, index1 -> index3
    this->graph.addEdge(index1, index2);
    this->graph.addEdge(index1, index3);

    // Verify degrees
    EXPECT_EQ(this->graph.getNode(index1).degree(), 2); // Two outgoing edges
    EXPECT_EQ(this->graph.getNode(index2).degree(), 0); // No outgoing edges
    EXPECT_EQ(this->graph.getNode(index3).degree(), 0); // No outgoing edges

    // Verify connections for index1
    const auto& edges1 = this->graph.getNode(index1).edges();
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index3), edges1.end());

    // Verify that index2 and index3 do not have edges back to index1
    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_EQ(std::find(edges2.begin(), edges2.end(), index1), edges2.end());

    const auto& edges3 = this->graph.getNode(index3).edges();
    EXPECT_EQ(std::find(edges3.begin(), edges3.end(), index1), edges3.end());
}

/**
 * @brief Test graph isolation (nodes with no outgoing edges).
 */
TYPED_TEST(DigraphTest, IsolatedNodes) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);
    T value3 = getValue<T>(3);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));
    size_t index3 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(2, value3));

    // No edges added; all nodes should be isolated (no outgoing edges)
    EXPECT_TRUE(this->graph.getNode(index1).isolated());
    EXPECT_TRUE(this->graph.getNode(index2).isolated());
    EXPECT_TRUE(this->graph.getNode(index3).isolated());
}

/**
 * @brief Test reserving edge capacity and adding directed edges.
 */
TYPED_TEST(DigraphTest, ReserveEdges) {
    typedef TypeParam T;

    T value = getValue<T>(1);
    size_t index = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value));

    // Reserve space for 5 outgoing edges
    this->graph.getNode(index).reserveEdges(5);

    // Add 5 directed edges from index to new nodes
    for (int i = 1; i <= 5; ++i) {
        T nodeValue = getValue<T>(i + 1);
        size_t newIndex = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(i, nodeValue));
        this->graph.addEdge(index, newIndex);
    }

    // Verify degree
    EXPECT_EQ(this->graph.getNode(index).degree(), 5);

    // Verify connections
    const auto& edges = this->graph.getNode(index).edges();
    for (int i = 1; i <= 5; ++i) {
        size_t expectedIndex = i;
        EXPECT_NE(std::find(edges.begin(), edges.end(), expectedIndex), edges.end());
    }
}

/**
 * @brief Test adding duplicate directed edges and verifying that duplicates are handled.
 */
TYPED_TEST(DigraphTest, AddDuplicateEdges) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));

    // Add the same directed edge twice: index1 -> index2
    this->graph.addEdge(index1, index2);
    this->graph.addEdge(index1, index2);

    // Verify degrees
    EXPECT_EQ(this->graph.getNode(index1).degree(), 2); // Two outgoing edges
    EXPECT_EQ(this->graph.getNode(index2).degree(), 0); // No outgoing edges

    // Verify that both edges exist in index1's edges
    const auto& edges1 = this->graph.getNode(index1).edges();
    int count1 = std::count(edges1.begin(), edges1.end(), index2);
    EXPECT_EQ(count1, 2);

    // Verify that index2's edges do not include index1
    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_EQ(std::find(edges2.begin(), edges2.end(), index1), edges2.end());
}

/**
 * @brief Test handling of invalid node indices when adding directed edges.
 * 
 * This test assumes that the `addEdge` method throws a `std::out_of_range` exception 
 * when attempting to add an edge with a non-existent target node index.
 */
TYPED_TEST(DigraphTest, AddEdgeInvalidIndices) {
    typedef TypeParam T;

    T value = getValue<T>(1);
    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value));

    // Attempt to add a directed edge to a non-existent node
    size_t invalidIndex = 100; // Assuming this is out of bounds

    // Depending on your implementation, `addEdge` should handle this appropriately.
    // For demonstration, let's assume it throws a `std::out_of_range` exception.
    EXPECT_THROW(this->graph.addEdge(index1, invalidIndex), std::out_of_range);
}

/**
 * @brief Test the digraph with different data types (int and std::string).
 * 
 * This test ensures that the `Digraph` class works correctly with different data types.
 */
TYPED_TEST(DigraphTest, DigraphWithDifferentDataTypes) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));

    // Add directed edge from index1 to index2
    this->graph.addEdge(index1, index2);

    // Verify values and connections
    EXPECT_EQ(this->graph.getNode(index1).value(), value1);
    EXPECT_EQ(this->graph.getNode(index2).value(), value2);

    EXPECT_EQ(this->graph.getNode(index1).degree(), 1);
    EXPECT_EQ(this->graph.getNode(index2).degree(), 0);

    // Verify that index1's edges include index2
    const auto& edges1 = this->graph.getNode(index1).edges();
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());

    // Verify that index2's edges do not include index1
    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_EQ(std::find(edges2.begin(), edges2.end(), index1), edges2.end());
}

/**
 * @brief Test digraph copy and move semantics.
 * 
 * This test ensures that the `Digraph` can be copied and moved correctly.
 * Note: This requires that the base `Graph` class supports copy and move operations.
 */
TEST(DigraphCopyMoveTest, CopyAndMoveDigraph) {
    typedef std::string T; // Example with std::string
    Digraph<T> originalGraph;

    // Add some nodes and directed edges
    size_t index1 = originalGraph.addNode(typename Digraph<T>::Node(0, "A"));
    size_t index2 = originalGraph.addNode(typename Digraph<T>::Node(1, "B"));
    size_t index3 = originalGraph.addNode(typename Digraph<T>::Node(2, "C"));
    originalGraph.addEdge(index1, index2);
    originalGraph.addEdge(index1, index3);

    // Copy the digraph
    Digraph<T> copiedGraph = originalGraph;

    // Verify that the copied digraph has the same structure
    EXPECT_EQ(copiedGraph.size(), originalGraph.size());
    EXPECT_EQ(copiedGraph.getNode(index1).value(), "A");
    EXPECT_EQ(copiedGraph.getNode(index2).value(), "B");
    EXPECT_EQ(copiedGraph.getNode(index3).value(), "C");

    EXPECT_EQ(copiedGraph.getNode(index1).degree(), 2);
    EXPECT_EQ(copiedGraph.getNode(index2).degree(), 0);
    EXPECT_EQ(copiedGraph.getNode(index3).degree(), 0);

    // Verify connections in the copied graph
    const auto& edgesCopied1 = copiedGraph.getNode(index1).edges();
    EXPECT_NE(std::find(edgesCopied1.begin(), edgesCopied1.end(), index2), edgesCopied1.end());
    EXPECT_NE(std::find(edgesCopied1.begin(), edgesCopied1.end(), index3), edgesCopied1.end());

    const auto& edgesCopied2 = copiedGraph.getNode(index2).edges();
    EXPECT_EQ(std::find(edgesCopied2.begin(), edgesCopied2.end(), index1), edgesCopied2.end());

    const auto& edgesCopied3 = copiedGraph.getNode(index3).edges();
    EXPECT_EQ(std::find(edgesCopied3.begin(), edgesCopied3.end(), index1), edgesCopied3.end());

    // Move the digraph
    Digraph<T> movedGraph = std::move(originalGraph);

    // Verify that the moved digraph has the correct structure
    EXPECT_EQ(movedGraph.size(), 3);
    EXPECT_EQ(movedGraph.getNode(index1).value(), "A");
    EXPECT_EQ(movedGraph.getNode(index2).value(), "B");
    EXPECT_EQ(movedGraph.getNode(index3).value(), "C");

    EXPECT_EQ(movedGraph.getNode(index1).degree(), 2);
    EXPECT_EQ(movedGraph.getNode(index2).degree(), 0);
    EXPECT_EQ(movedGraph.getNode(index3).degree(), 0);

    // Original digraph should be in a valid but unspecified state
    // Depending on your implementation, you might check if it's empty or not
    // Here, we'll assume it's empty after move
    EXPECT_EQ(originalGraph.size(), 0);
}

/**
 * @brief Test emplace method for constructing node values in place.
 */
TYPED_TEST(DigraphTest, EmplaceNodeValue) {
    typedef TypeParam T;
    T initialValue = getValue<T>(10);
    typename DigraphTest<T>::DigraphType::Node node(0, initialValue);
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
TEST(DigraphOperatorTest, NodeOutputOperator) {
    typedef std::string T;
    Digraph<T> graph;

    size_t index = graph.addNode(typename Digraph<T>::Node(0, "NodeA"));

    std::ostringstream oss;
    oss << graph.getNode(index);

    EXPECT_EQ(oss.str(), "NodeA");
}

/**
 * @brief Test retrieving edges from a node and ensuring directed connections.
 */
TYPED_TEST(DigraphTest, RetrieveEdges) {
    typedef TypeParam T;

    T value1 = getValue<T>(1);
    T value2 = getValue<T>(2);
    T value3 = getValue<T>(3);

    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, value1));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, value2));
    size_t index3 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(2, value3));

    // Add directed edges: index1 -> index2, index1 -> index3
    this->graph.addEdge(index1, index2);
    this->graph.addEdge(index1, index3);

    // Retrieve edges of index1
    const auto& edges1 = this->graph.getNode(index1).edges();
    EXPECT_EQ(edges1.size(), 2);
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index2), edges1.end());
    EXPECT_NE(std::find(edges1.begin(), edges1.end(), index3), edges1.end());

    // Retrieve edges of index2 (should have no outgoing edges)
    const auto& edges2 = this->graph.getNode(index2).edges();
    EXPECT_EQ(edges2.size(), 0);

    // Retrieve edges of index3 (should have no outgoing edges)
    const auto& edges3 = this->graph.getNode(index3).edges();
    EXPECT_EQ(edges3.size(), 0);
}

/**
 * @brief Test graph size after various operations.
 */
TYPED_TEST(DigraphTest, DigraphSize) {
    typedef TypeParam T;
    EXPECT_EQ(this->graph.size(), 0);

    // Add nodes
    size_t index1 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(0, getValue<T>(1)));
    size_t index2 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(1, getValue<T>(2)));
    EXPECT_EQ(this->graph.size(), 2);

    // Add another node
    size_t index3 = this->graph.addNode(typename DigraphTest<T>::DigraphType::Node(2, getValue<T>(3)));
    EXPECT_EQ(this->graph.size(), 3);
}
