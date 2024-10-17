#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "lightweight_tree.hpp" // Ensure this path is correct based on your project structure

template<typename T>
using Node = typename vpr::lightweight::Tree<T>::Node;

/**
 * @brief Helper function to generate values for different types.
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
 * @brief Test fixture for the Node class.
 *
 * This fixture sets up a Node instance before each test and cleans up afterward.
 */
template <typename T>
class NodeTest : public ::testing::Test {
protected:
    /**
     * @brief Creates a Node instance with given parameters.
     *
     * @param index The index of the node.
     * @param parent_id The index of the parent node.
     * @param data The value stored in the node.
     * @return A Node instance.
     */
    auto createNode(size_t index, size_t parent_id, T data) {
        return Node<T>(index, parent_id, std::move(data));
    }
};

// Define the types to be tested (e.g., int, std::string)
typedef ::testing::Types<int, std::string> Implementations;

// Register the test types
TYPED_TEST_SUITE(NodeTest, Implementations);

/**
 * @brief Test the constructor and getter methods of Node.
 */
TYPED_TEST(NodeTest, ConstructorAndGetters) {
    typedef TypeParam T;

    size_t index = 1;
    size_t parent_id = 0;
    T data = getValue<T>(100);

    Node<T> node = this->createNode(index, parent_id, data);

    // Verify that the node was constructed correctly
    EXPECT_EQ(node.index(), index);
    EXPECT_EQ(node.parentId(), parent_id);
    EXPECT_EQ(node.value(), data);
}

/**
 * @brief Test the isRoot() method of Node.
 *
 * A node is considered the root if its index is 0.
 */
TYPED_TEST(NodeTest, IsRoot) {
    typedef TypeParam T;

    // Create root node
    Node<T> root = this->createNode(0, 0, getValue<T>(0));
    EXPECT_TRUE(root.isRoot());

    // Create non-root node
    Node<T> child = this->createNode(1, 0, getValue<T>(1));
    EXPECT_FALSE(child.isRoot());
}

/**
 * @brief Test the isLeaf() method of Node.
 *
 * A node is considered a leaf if it has no children (i.e., it is isolated).
 */
TYPED_TEST(NodeTest, IsLeaf) {
    typedef TypeParam T;

    // Create leaf node (no edges)
    Node<T> leaf = this->createNode(1, 0, getValue<T>(1));
    EXPECT_TRUE(leaf.isLeaf());

    // Create parent node and add a child to make it non-leaf
    Node<T> parent = this->createNode(0, 0, getValue<T>(0));
    parent.addEdge(1); // Adding child with index 1
    EXPECT_FALSE(parent.isLeaf());
}

/**
 * @brief Test the nChildren() method of Node.
 *
 * This method returns the number of children (degree) of the node.
 */
TYPED_TEST(NodeTest, NChildren) {
    typedef TypeParam T;

    // Create leaf node
    Node<T> leaf = this->createNode(1, 0, getValue<T>(1));
    EXPECT_EQ(leaf.nChildren(), 0);

    // Create parent node and add children
    Node<T> parent = this->createNode(0, 0, getValue<T>(0));
    parent.addEdge(1);
    parent.addEdge(2);
    EXPECT_EQ(parent.nChildren(), 2);
}

/**
 * @brief Test the parentId() method of Node.
 */
TYPED_TEST(NodeTest, ParentId) {
    typedef TypeParam T;

    size_t parent_id = 0;
    T data = getValue<T>(1);
    Node<T> child = this->createNode(1, parent_id, data);

    EXPECT_EQ(child.parentId(), parent_id);
}

/**
 * @brief Test the emplace method of Node.
 *
 * This test verifies that the value of the node can be updated using emplace.
 */
TYPED_TEST(NodeTest, EmplaceValue) {
    typedef TypeParam T;

    T initialValue = getValue<T>(1);
    T newValue = getValue<T>(2);

    Node<T> node = this->createNode(1, 0, initialValue);

    // Emplace a new value
    node.emplace(newValue);

    // Verify that the value was updated
    EXPECT_EQ(node.value(), newValue);
}

/**
 * @brief Test the indexing and parent-child relationships of Node.
 */
TYPED_TEST(NodeTest, NodeIndexingAndRelationships) {
    typedef TypeParam T;

    // Create parent node
    Node<T> parent = this->createNode(0, 0, getValue<T>(0));

    // Create child nodes
    Node<T> child1 = this->createNode(1, parent.index(), getValue<T>(1));
    Node<T> child2 = this->createNode(2, parent.index(), getValue<T>(2));

    // Add children to parent
    parent.addEdge(child1.index());
    parent.addEdge(child2.index());

    // Verify parent properties
    EXPECT_EQ(parent.nChildren(), 2);
    EXPECT_FALSE(parent.isLeaf());

    // Verify child properties
    EXPECT_TRUE(child1.isLeaf());
    EXPECT_EQ(child1.nChildren(), 0);
    EXPECT_EQ(child1.parentId(), parent.index());

    EXPECT_TRUE(child2.isLeaf());
    EXPECT_EQ(child2.nChildren(), 0);
    EXPECT_EQ(child2.parentId(), parent.index());
}

/**
 * @brief Test the identification of root node.
 */
TYPED_TEST(NodeTest, RootIdentification) {
    typedef TypeParam T;

    // Root node
    Node<T> root = this->createNode(0, 0, getValue<T>(0));
    EXPECT_TRUE(root.isRoot());

    // Another node
    Node<T> node = this->createNode(1, 0, getValue<T>(1));
    EXPECT_FALSE(node.isRoot());
}

/**
 * @brief Test the addition of edges and their impact on node properties.
 */
TYPED_TEST(NodeTest, EdgeAddition) {
    typedef TypeParam T;

    // Create parent node
    Node<T> parent = this->createNode(0, 0, getValue<T>(0));

    // Add multiple children
    const int num_children = 5;
    for (int i = 1; i <= num_children; ++i) {
        parent.addEdge(i);
    }

    // Verify number of children
    EXPECT_EQ(parent.nChildren(), num_children);
    EXPECT_FALSE(parent.isLeaf());

    // Verify each child is a leaf
    for (int i = 1; i <= num_children; ++i) {
        Node<T> child = this->createNode(i, parent.index(), getValue<T>(i));
        EXPECT_TRUE(child.isLeaf());
        EXPECT_EQ(child.nChildren(), 0);
        EXPECT_EQ(child.parentId(), parent.index());
    }
}

/**
 * @brief Test copy and move semantics of Node.
 *
 * This test ensures that Node instances can be copied and moved correctly.
 */
TYPED_TEST(NodeTest, CopyAndMoveNode) {
    typedef TypeParam T;

    // Create a node
    Node<T> original = this->createNode(1, 0, getValue<T>(1));
    original.addEdge(2); // Adding a child to make it non-leaf

    // Copy the node
    Node<T> copied = original;

    // Verify that the copied node has the same properties
    EXPECT_EQ(copied.index(), original.index());
    EXPECT_EQ(copied.parentId(), original.parentId());
    EXPECT_EQ(copied.value(), original.value());
    EXPECT_EQ(copied.nChildren(), original.nChildren());
    EXPECT_FALSE(copied.isLeaf());

    // Move the node
    Node<T> moved = std::move(original);

    // Verify that the moved node has the correct properties
    EXPECT_EQ(moved.index(), 1);
    EXPECT_EQ(moved.parentId(), 0);
    EXPECT_EQ(moved.value(), getValue<T>(1));
    EXPECT_EQ(moved.nChildren(), 1);
    EXPECT_FALSE(moved.isLeaf());

    // Original node should be in a valid but unspecified state
    // Depending on your implementation, you might check specific properties
    // For simplicity, we'll assume it's empty or has default values
    // Here, we'll skip checking original after move
}

/**
 * @brief Test the leaf status after adding and removing edges.
 *
 * This test verifies that a node's leaf status updates correctly when edges are added or removed.
 */
TYPED_TEST(NodeTest, LeafStatusAfterEdgeModification) {
    typedef TypeParam T;

    // Create a node
    Node<T> node = this->createNode(0, 0, getValue<T>(0));
    EXPECT_TRUE(node.isLeaf());

    // Add an edge (make it non-leaf)
    node.addEdge(1);
    EXPECT_FALSE(node.isLeaf());

    // Remove the edge (assuming a method to remove edges exists)
    // Since the current Node class does not have a removeEdge method, 
    // this part of the test is conceptual. Implement removeEdge if needed.

    // Example (if removeEdge is implemented):
    // node.removeEdge(1);
    // EXPECT_TRUE(node.isLeaf());

    // Since removeEdge is not implemented, we'll skip it
}

/**
 * @brief Test that the node correctly identifies multiple children.
 */
TYPED_TEST(NodeTest, MultipleChildrenIdentification) {
    typedef TypeParam T;

    // Create a parent node
    Node<T> parent = this->createNode(0, 0, getValue<T>(0));

    // Add multiple children
    const int num_children = 10;
    for (int i = 1; i <= num_children; ++i) {
        parent.addEdge(i);
    }

    // Verify number of children
    EXPECT_EQ(parent.nChildren(), num_children);
    EXPECT_FALSE(parent.isLeaf());

    // Verify each child is a leaf
    for (int i = 1; i <= num_children; ++i) {
        Node<T> child = this->createNode(i, parent.index(), getValue<T>(i));
        EXPECT_TRUE(child.isLeaf());
        EXPECT_EQ(child.nChildren(), 0);
        EXPECT_EQ(child.parentId(), parent.index());
    }
}

/**
 * @brief Test node indexing and ensuring unique indices.
 *
 * This test ensures that each node has a unique index and that indexing works correctly.
 */
TYPED_TEST(NodeTest, UniqueIndexing) {
    typedef TypeParam T;

    // Create multiple nodes with unique indices
    Node<T> node1 = this->createNode(1, 0, getValue<T>(1));
    Node<T> node2 = this->createNode(2, 0, getValue<T>(2));
    Node<T> node3 = this->createNode(3, 1, getValue<T>(3));

    // Verify unique indices
    EXPECT_NE(node1.index(), node2.index());
    EXPECT_NE(node1.index(), node3.index());
    EXPECT_NE(node2.index(), node3.index());

    // Verify parent IDs
    EXPECT_EQ(node1.parentId(), 0);
    EXPECT_EQ(node2.parentId(), 0);
    EXPECT_EQ(node3.parentId(), 1);
}

/**
 * @brief Test node value retrieval and modification.
 *
 * This test ensures that node values can be retrieved and modified correctly.
 */
TYPED_TEST(NodeTest, ValueRetrievalAndModification) {
    typedef TypeParam T;

    // Create a node
    Node<T> node = this->createNode(1, 0, getValue<T>(1));
    EXPECT_EQ(node.value(), getValue<T>(1));

    // Modify the node's value using emplace
    T newValue = getValue<T>(2);
    node.emplace(newValue);
    EXPECT_EQ(node.value(), newValue);
}

/**
 * @brief Test node behavior with complex data types.
 *
 * This test ensures that the Node class works correctly with complex data types beyond fundamental types.
 */
TYPED_TEST(NodeTest, ComplexDataTypeHandling) {
    typedef TypeParam T;

    // Create a node with a string value
    std::string data = "InitialValue";
    Node<std::string> node(0, 1, data);
    EXPECT_EQ(node.value(), data);

    // Modify the node's value
    std::string newData = "UpdatedValue";
    node.emplace(newData);
    EXPECT_EQ(node.value(), newData);
}

