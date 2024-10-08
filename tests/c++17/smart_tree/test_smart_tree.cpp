#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <functional>
#include "smart_tree.hpp"
#include "smart_tree_node.hpp"

#include <variant>

/*
TEST_F(SmartTreeTest, TestVariantNode) {
    smart::Tree<std::variant<int, std::string>> variantTree(42);
    auto& root = variantTree.getRoot();

    size_t child1 = variantTree.addChild(variantTree.getRoot().index(), std::string("Child1"));
    size_t child2 = variantTree.addChild(variantTree.getRoot().index(), 84);

    EXPECT_TRUE(std::holds_alternative<int>(variantTree.getNode(child2).value()));
    EXPECT_TRUE(std::holds_alternative<std::string>(variantTree.getNode(child1).value()));
}
*/

using namespace vpr::smart;
using namespace vpr::smart::tree;

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
inline T getValue(int n) {
    return static_cast<T>(n);
}

// Template specialization for std::string
template <>
inline std::string getValue<std::string>(int n) {
    return "Node" + std::to_string(n);
}

/**
 * @brief Test fixture for the Smart Tree class.
 *
 * This fixture sets up a Smart Tree instance before each test and cleans up afterward.
 */
template <typename T>
class SmartTreeTest : public ::testing::Test {
protected:
    // Smart Tree instance to be used in tests
    Tree<T> tree{getValue<T>(0)};

    // Setup before each test
    void SetUp() override {
        // Initialize the tree with a root node
        T rootValue = getValue<T>(0);
        tree = Tree<T>(rootValue);
    }

    // Tear down after each test
    void TearDown() override {
        // Clean up if necessary
    }
};

// Define the types to be tested (e.g., int, std::string)
typedef ::testing::Types<int, std::string> Implementations;

// Register the test types
TYPED_TEST_SUITE(SmartTreeTest, Implementations);

/**
 * @brief Test constructing a Smart Tree with a root node.
 */
TYPED_TEST(SmartTreeTest, ConstructTreeWithRoot) {
    typedef TypeParam T;

    // Verify that the root node has the correct value
    T expectedValue = getValue<T>(0);
    EXPECT_EQ(this->tree.getRoot().value(), expectedValue);

    // Verify that the tree has only one node (the root)
    EXPECT_EQ(this->tree.size(), 1);
}

/**
 * @brief Test adding child nodes using Node::addChild.
 */
TYPED_TEST(SmartTreeTest, AddChildNodes) {
    typedef TypeParam T;

    // Add child nodes to the root using Node::addChild
    T childValue1 = getValue<T>(1);
    T childValue2 = getValue<T>(2);

    size_t childIndex1 = this->tree.getRoot().addChild(childValue1);
    size_t childIndex2 = this->tree.getRoot().addChild(childValue2);

    // Verify that the children were added correctly
    EXPECT_EQ(this->tree.getNode(childIndex1).value(), childValue1);
    EXPECT_EQ(this->tree.getNode(childIndex2).value(), childValue2);

    // Verify the parent-child relationships
    const auto& rootEdges = this->tree.getRoot().edges();
    EXPECT_NE(std::find(rootEdges.begin(), rootEdges.end(), childIndex1), rootEdges.end());
    EXPECT_NE(std::find(rootEdges.begin(), rootEdges.end(), childIndex2), rootEdges.end());

    // Verify that the tree size is updated
    EXPECT_EQ(this->tree.size(), 3);
}

/**
 * @brief Test retrieving children using Node::getChildren.
 */
TYPED_TEST(SmartTreeTest, GetChildren) {
    typedef TypeParam T;

    // Add child nodes to the root
    T childValue1 = getValue<T>(1);
    T childValue2 = getValue<T>(2);

    this->tree.getRoot().addChild(childValue1);
    this->tree.getRoot().addChild(childValue2);

    // Retrieve children using getChildren()
    auto children = this->tree.getRoot().getChildren();

    // Verify that the correct number of children is retrieved
    EXPECT_EQ(children.size(), 2);

    // Verify the values of the children
    std::vector<T> expectedValues = {childValue1, childValue2};
    std::vector<T> actualValues;
    for (const auto& childRef : children) {
        actualValues.push_back(childRef.get().value());
    }

    // Since the order might not be guaranteed, sort the vectors before comparison
    std::sort(expectedValues.begin(), expectedValues.end());
    std::sort(actualValues.begin(), actualValues.end());

    EXPECT_EQ(actualValues, expectedValues);
}

/**
 * @brief Test adding multiple levels of child nodes.
 */
TYPED_TEST(SmartTreeTest, AddMultipleLevels) {
    typedef TypeParam T;

    // Add child nodes to the root
    T childValue1 = getValue<T>(1);
    size_t childIndex1 = this->tree.getRoot().addChild(childValue1);

    // Add children to the first child
    Node<T>& childNode1 = this->tree.getNode(childIndex1);
    T grandchildValue1 = getValue<T>(2);
    T grandchildValue2 = getValue<T>(3);
    childNode1.addChild(grandchildValue1);
    childNode1.addChild(grandchildValue2);

    // Verify tree size
    EXPECT_EQ(this->tree.size(), 4);

    // Verify the grandchildren
    auto grandchildren = childNode1.getChildren();
    EXPECT_EQ(grandchildren.size(), 2);
}

/**
 * @brief Test copy and move semantics of the Smart Tree.
 */
TYPED_TEST(SmartTreeTest, CopyAndMoveTree) {
    typedef TypeParam T;

    // Build a sample tree
    this->tree.getRoot().addChild(getValue<T>(1));
    this->tree.getRoot().addChild(getValue<T>(2));

    // Copy the tree
    Tree<T> copiedTree = this->tree;

    // Verify that the copied tree has the same structure
    EXPECT_EQ(copiedTree.size(), this->tree.size());
    EXPECT_EQ(copiedTree.getRoot().value(), this->tree.getRoot().value());

    // Move the tree
    Tree<T> movedTree = std::move(this->tree);

    // Verify that the moved tree has the correct structure
    EXPECT_EQ(movedTree.size(), copiedTree.size());
    EXPECT_EQ(movedTree.getRoot().value(), copiedTree.getRoot().value());

    // Original tree should be in a valid but unspecified state
    // Depending on your implementation, you might check if it's empty
    //EXPECT_EQ(this->tree.size(), 0);
}

/**
 * @brief Test emplace method for constructing node values in place.
 */
TYPED_TEST(SmartTreeTest, EmplaceNodeValue) {
    typedef TypeParam T;

    // Emplace a new value in the root node
    T newValue = getValue<T>(10);
    this->tree.getRoot().emplace(newValue);

    // Verify that the value was updated
    EXPECT_EQ(this->tree.getRoot().value(), newValue);
}

/**
 * @brief Test tree size after various operations.
 */
TYPED_TEST(SmartTreeTest, TreeSize) {
    typedef TypeParam T;

    // Initial size should be 1 (root node)
    EXPECT_EQ(this->tree.size(), 1);

    // Add child nodes
    this->tree.getRoot().addChild(getValue<T>(1));
    EXPECT_EQ(this->tree.size(), 2);

    this->tree.getRoot().addChild(getValue<T>(2));
    EXPECT_EQ(this->tree.size(), 3);

    // Add a child to one of the child nodes
    size_t childIndex = this->tree.getRoot().edges()[0];
    this->tree.getNode(childIndex).addChild(getValue<T>(3));
    EXPECT_EQ(this->tree.size(), 4);
}

/**
 * @brief Test that the root node is correctly identified.
 */
TYPED_TEST(SmartTreeTest, GetRootNode) {
    typedef TypeParam T;

    // Verify that the root node has index 0
    EXPECT_EQ(this->tree.getRoot().index(), 0);

    // Verify that the root node has the correct value
    T expectedValue = getValue<T>(0);
    EXPECT_EQ(this->tree.getRoot().value(), expectedValue);
}

/**
 * @brief Test traversing the tree using getChildren recursively.
 */
TYPED_TEST(SmartTreeTest, RecursiveTraversal) {
    typedef TypeParam T;

    // Build a sample tree
    auto& root = this->tree.getRoot();
    size_t childIndex1 = root.addChild(getValue<T>(1));
    size_t childIndex2 = root.addChild(getValue<T>(2));

    auto& child1 = this->tree.getNode(childIndex1);
    child1.addChild(getValue<T>(3));
    child1.addChild(getValue<T>(4));

    auto& child2 = this->tree.getNode(childIndex2);
    child2.addChild(getValue<T>(5));

    // Function to recursively collect values
    std::function<void(const Node<T>&, std::vector<T>&)> collectValues;
    collectValues = [&](const Node<T>& node, std::vector<T>& values) {
        values.push_back(node.value());
        for (const auto& childRef : node.getChildren()) {
            collectValues(childRef.get(), values);
        }
    };

    // Collect values starting from root
    std::vector<T> traversalValues;
    collectValues(root, traversalValues);

    // Expected values in pre-order traversal
    std::vector<T> expectedValues = {
        getValue<T>(0),
        getValue<T>(1),
        getValue<T>(3),
        getValue<T>(4),
        getValue<T>(2),
        getValue<T>(5)
    };

    EXPECT_EQ(traversalValues, expectedValues);
}

/**
 * @brief Test handling of adding a child to a non-existent parent node.
 */
TYPED_TEST(SmartTreeTest, AddChildToInvalidParent) {
    typedef TypeParam T;

    T childValue = getValue<T>(1);

    // Attempt to add a child to a non-existent parent node
    size_t invalidParentIndex = 100; // Assuming this index is invalid

    // Depending on your implementation, this might throw an exception or assert
    // For demonstration, let's assume it throws a std::out_of_range exception
    EXPECT_THROW(this->tree.addChild(invalidParentIndex, childValue), std::out_of_range);
}

/**
 * @brief Test node-specific methods after copying the tree.
 */
TYPED_TEST(SmartTreeTest, NodeMethodsAfterCopy) {
    typedef TypeParam T;

    // Build a sample tree
    auto& root = this->tree.getRoot();
    root.addChild(getValue<T>(1));
    root.addChild(getValue<T>(2));

    // Copy the tree
    Tree<T> copiedTree = this->tree;

    // Verify that node-specific methods work on the copied tree
    auto& copiedRoot = copiedTree.getRoot();
    auto children = copiedRoot.getChildren();

    // Verify that the correct number of children is retrieved
    EXPECT_EQ(children.size(), 2);

    // Add a child to the copied tree's root
    copiedRoot.addChild(getValue<T>(3));
    EXPECT_EQ(copiedTree.size(), this->tree.size() + 1);
}

/**
 * @brief Test node-specific methods after moving the tree.
 */
TYPED_TEST(SmartTreeTest, NodeMethodsAfterMove) {
    typedef TypeParam T;

    // Build a sample tree
    auto& root = this->tree.getRoot();
    root.addChild(getValue<T>(1));
    root.addChild(getValue<T>(2));

    // Move the tree
    Tree<T> movedTree = std::move(this->tree);

    // Verify that node-specific methods work on the moved tree
    auto& movedRoot = movedTree.getRoot();
    auto children = movedRoot.getChildren();

    // Verify that the correct number of children is retrieved
    EXPECT_EQ(children.size(), 2);

    // Add a child to the moved tree's root
    movedRoot.addChild(getValue<T>(3));
    EXPECT_EQ(movedTree.size(), 4);

    // Original tree should be in a valid but unspecified state
    // Accessing nodes from the original tree might be undefined
}

/**
 * @brief Test that nodes correctly reference their tree after copying.
 */
TYPED_TEST(SmartTreeTest, NodeTreeReferenceAfterCopy) {
    typedef TypeParam T;

    // Build a sample tree
    auto& root = this->tree.getRoot();
    root.addChild(getValue<T>(1));

    // Copy the tree
    Tree<T> copiedTree = this->tree;

    // Add a child to the copied tree's root
    auto& copiedRoot = copiedTree.getRoot();
    size_t newChildIndex = copiedRoot.addChild(getValue<T>(2));

    // Verify that the new child is added to the copied tree
    EXPECT_EQ(copiedTree.size(), this->tree.size() + 1);

    // Verify that the new child exists in the copied tree
    EXPECT_EQ(copiedTree.getNode(newChildIndex).value(), getValue<T>(2));
}

/**
 * @brief Test that nodes correctly reference their tree after moving.
 */
TYPED_TEST(SmartTreeTest, NodeTreeReferenceAfterMove) {
    typedef TypeParam T;

    // Build a sample tree
    auto& root = this->tree.getRoot();
    root.addChild(getValue<T>(1));

    // Move the tree
    Tree<T> movedTree = std::move(this->tree);

    // Add a child to the moved tree's root
    auto& movedRoot = movedTree.getRoot();
    size_t newChildIndex = movedRoot.addChild(getValue<T>(2));

    // Verify that the new child is added to the moved tree
    EXPECT_EQ(movedTree.size(), 3);

    // Verify that the new child exists in the moved tree
    EXPECT_EQ(movedTree.getNode(newChildIndex).value(), getValue<T>(2));
}

/**
 * @brief Test that getChildren() returns the correct type and values.
 */
TYPED_TEST(SmartTreeTest, GetChildrenTypeAndValues) {
    typedef TypeParam T;

    // Add child nodes to the root
    T childValue1 = getValue<T>(1);
    T childValue2 = getValue<T>(2);

    this->tree.getRoot().addChild(childValue1);
    this->tree.getRoot().addChild(childValue2);

    // Retrieve children using getChildren()
    auto children = this->tree.getRoot().getChildren();

    // Verify the type of the returned value
    EXPECT_TRUE((std::is_same<decltype(children), std::vector<std::reference_wrapper<Node<T>>>>::value));

    // Verify the values of the children
    std::vector<T> expectedValues = {childValue1, childValue2};
    std::vector<T> actualValues;
    for (const auto& childRef : children) {
        actualValues.push_back(childRef.get().value());
    }

    EXPECT_EQ(actualValues, expectedValues);
}
