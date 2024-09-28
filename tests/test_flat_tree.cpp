#include <gtest/gtest.h>
#include <optional>
#include <vector>
#include <variant>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "flat_tree.hpp"
#include "flat_tree_variant.hpp"

using namespace vpr;

// Test Suite for FlatTreeNode with simple types
TEST(FlatTreeNodeTest, DefaultConstructor) {
    FlatTreeNode<int> node;
    EXPECT_FALSE(node.value.has_value());
    EXPECT_EQ(node.parentIndex, -1);
    EXPECT_TRUE(node.childIndices.empty());
}

TEST(FlatTreeNodeTest, ConstructorWithValue) {
    FlatTreeNode<int> node(std::make_optional(42), 1);
    ASSERT_TRUE(node.value.has_value());
    EXPECT_EQ(node.value.value(), 42);
    EXPECT_EQ(node.parentIndex, 1);
    EXPECT_TRUE(node.childIndices.empty());
}

TEST(FlatTreeNodeTest, OperatorOutputWithValue) {
    FlatTreeNode<int> node(std::make_optional(100), 2);
    std::ostringstream oss;
    oss << node;
    EXPECT_EQ(oss.str(), "100");
}

TEST(FlatTreeNodeTest, OperatorOutputWithoutValue) {
    FlatTreeNode<int> node;
    std::ostringstream oss;
    oss << node;
    EXPECT_EQ(oss.str(), "None");
}

TEST(FlatTreeNodeTest, OperatorOutputWithVariant) {
    using VarType = std::variant<int, std::string>;
    FlatTreeNode<VarType> node(std::make_optional<VarType>(std::string("VariantValue")), 3);
    std::ostringstream oss;
    oss << node;
    EXPECT_EQ(oss.str(), "VariantValue");
}

// Test Suite for FlatTree with simple types
TEST(FlatTreeTest, DefaultConstructor) {
    FlatTree<int> tree;
    EXPECT_TRUE(tree.nodes.empty());
}

TEST(FlatTreeTest, AddRootWithoutValue) {
    FlatTree<int> tree;
    int rootIndex = tree.addRoot();
    ASSERT_EQ(rootIndex, 0);
    ASSERT_EQ(tree.nodes.size(), 1);
    EXPECT_FALSE(tree.nodes[rootIndex].value.has_value());
    EXPECT_EQ(tree.nodes[rootIndex].parentIndex, -1);
}

TEST(FlatTreeTest, AddRootWithValue) {
    FlatTree<int> tree;
    int rootIndex = tree.addRoot(std::make_optional(10));
    ASSERT_EQ(rootIndex, 0);
    ASSERT_EQ(tree.nodes.size(), 1);
    EXPECT_TRUE(tree.nodes[rootIndex].value.has_value());
    EXPECT_EQ(tree.nodes[rootIndex].value.value(), 10);
    EXPECT_EQ(tree.nodes[rootIndex].parentIndex, -1);
}

TEST(FlatTreeTest, AddChildSuccessfully) {
    FlatTree<int> tree;
    int root = tree.addRoot(std::make_optional(1));
    int child1 = tree.addChild(root, std::make_optional(2));
    int child2 = tree.addChild(root, std::make_optional(3));

    ASSERT_EQ(tree.nodes.size(), 3);
    EXPECT_EQ(tree.nodes[child1].parentIndex, root);
    EXPECT_EQ(tree.nodes[child2].parentIndex, root);
    EXPECT_EQ(tree.nodes[root].childIndices.size(), 2);
    EXPECT_EQ(tree.nodes[root].childIndices[0], child1);
    EXPECT_EQ(tree.nodes[root].childIndices[1], child2);
}

TEST(FlatTreeTest, GetNodeValidIndex) {
    FlatTree<int> tree;
    int root = tree.addRoot(std::make_optional(5));
    int child = tree.addChild(root, std::make_optional(10));

    FlatTreeNode<int>& retrievedRoot = tree.getNode(root);
    FlatTreeNode<int>& retrievedChild = tree.getNode(child);

    EXPECT_EQ(retrievedRoot.value.value(), 5);
    EXPECT_EQ(retrievedChild.value.value(), 10);
}

TEST(FlatTreeTest, GetNodeInvalidIndexThrows) {
    FlatTree<int> tree;
    tree.addRoot();

    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(1), std::out_of_range); // Only root exists at index 0
}

TEST(FlatTreeTest, HasValueTrue) {
    FlatTree<int> tree;
    int root = tree.addRoot(std::make_optional(20));
    EXPECT_TRUE(tree.hasValue(root));
}

TEST(FlatTreeTest, HasValueFalse) {
    FlatTree<int> tree;
    int root = tree.addRoot();
    EXPECT_FALSE(tree.hasValue(root));
}

TEST(FlatTreeTest, AddChildInvalidParentThrows) {
    FlatTree<int> tree;
    tree.addRoot();

    EXPECT_THROW(tree.addChild(-1, std::make_optional(1)), std::out_of_range);
    EXPECT_THROW(tree.addChild(10, std::make_optional(2)), std::out_of_range);
}

TEST(FlatTreeTest, OperatorOutput) {
    FlatTree<int> tree;
    tree.addRoot(std::make_optional(1));
    int child1 = tree.addChild(0, std::make_optional(2));
    int child2 = tree.addChild(0);
    tree.addChild(child1, std::make_optional(3));

    std::ostringstream oss;
    oss << tree;
    // Expected output: "1 2 None 3 "
    EXPECT_EQ(oss.str(), "1 2 None 3 ");
}

// Assuming FlatTreeIterator is correctly implemented for pre-order traversal
TEST(FlatTreeTest, IteratorTraversal) {
    FlatTree<int> tree;
    int root = tree.addRoot(std::make_optional(1));
    int child1 = tree.addChild(root, std::make_optional(2));
    int child2 = tree.addChild(root, std::make_optional(3));
    tree.addChild(child1, std::make_optional(4));
    tree.addChild(child1, std::make_optional(5));
    tree.addChild(child2, std::make_optional(6));

    std::vector<int> expectedValues = {1, 2, 4, 5, 3, 6};
    std::vector<int> actualValues;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        if (it->value.has_value()) {
            actualValues.push_back(it->value.value());
        }
    }

    EXPECT_EQ(actualValues, expectedValues);
}

TEST(FlatTreeTest, EmptyTreeIterator) {
    FlatTree<int> tree;
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST(FlatTreeTest, SingleNodeIterator) {
    FlatTree<int> tree;
    tree.addRoot(std::make_optional(100));

    std::vector<int> expectedValues = {100};
    std::vector<int> actualValues;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        if (it->value.has_value()) {
            actualValues.push_back(it->value.value());
        }
    }

    EXPECT_EQ(actualValues, expectedValues);
}

// Test Suite for FlatTreeVariant
TEST(FlatTreeVariantTest, AddRootWithDifferentTypes) {
    FlatTreeVariant<int, std::string> tree;
    int rootInt = tree.addRoot(std::make_optional<std::variant<int, std::string>>(42));
    int rootStr = tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("Root")));

    ASSERT_EQ(tree.nodes.size(), 2);
    EXPECT_TRUE(tree.nodes[rootInt].value.has_value());
    EXPECT_TRUE(std::holds_alternative<int>(tree.nodes[rootInt].value.value()));
    EXPECT_EQ(std::get<int>(tree.nodes[rootInt].value.value()), 42);

    EXPECT_TRUE(tree.nodes[rootStr].value.has_value());
    EXPECT_TRUE(std::holds_alternative<std::string>(tree.nodes[rootStr].value.value()));
    EXPECT_EQ(std::get<std::string>(tree.nodes[rootStr].value.value()), "Root");
}

TEST(FlatTreeVariantTest, AddChildWithDifferentTypes) {
    FlatTreeVariant<int, std::string> tree;
    int root = tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("Root")));
    int child1 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(100));
    int child2 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(std::string("Child")));

    ASSERT_EQ(tree.nodes.size(), 3);
    EXPECT_EQ(tree.nodes[root].childIndices.size(), 2);

    // Verify child1
    EXPECT_TRUE(std::holds_alternative<int>(tree.nodes[child1].value.value()));
    EXPECT_EQ(std::get<int>(tree.nodes[child1].value.value()), 100);

    // Verify child2
    EXPECT_TRUE(std::holds_alternative<std::string>(tree.nodes[child2].value.value()));
    EXPECT_EQ(std::get<std::string>(tree.nodes[child2].value.value()), "Child");
}

TEST(FlatTreeVariantTest, OperatorOutputWithDifferentTypes) {
    FlatTreeVariant<int, std::string> tree;
    int root = tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("Root")));
    int child1 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(100));
    int child2 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(std::string("Child")));
    tree.addChild(child1, std::make_optional<std::variant<int, std::string>>());

    std::ostringstream oss;
    oss << tree;
    // Expected output: "Root 100 Child None "
    EXPECT_EQ(oss.str(), "Root 100 Child None ");
}

TEST(FlatTreeVariantTest, IteratorTraversalWithVariants) {
    FlatTreeVariant<int, std::string> tree;
    int root = tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("Root")));
    int child1 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(100));
    int child2 = tree.addChild(root, std::make_optional<std::variant<int, std::string>>("Child"));
    tree.addChild(child1, std::make_optional<std::variant<int, std::string>>(200));
    tree.addChild(child1, std::make_optional<std::variant<int, std::string>>());
    tree.addChild(child2, std::make_optional<std::variant<int, std::string>>("Grandchild"));

    std::vector<std::optional<std::variant<int, std::string>>> expectedValues = {
        std::variant<int, std::string>(std::string("Root")),
        std::variant<int, std::string>(100),
        std::variant<int, std::string>(200),
        std::nullopt,
        std::variant<int, std::string>("Child"),
        std::variant<int, std::string>("Grandchild")
    };
    std::vector<std::variant<int, std::string>> actualValues;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actualValues.push_back(it->value.value_or(std::variant<int, std::string>()));
    }

    // Since std::variant cannot hold std::nullopt, we'll interpret "None" as a default-constructed variant
    // Adjust the expectedValues accordingly
    std::vector<std::variant<int, std::string>> adjustedExpectedValues = {
        std::string("Root"), 100, 200, std::variant<int, std::string>(), "Child", "Grandchild"
    };

    EXPECT_EQ(actualValues, adjustedExpectedValues);
}

TEST(FlatTreeVariantTest, GetNodeWithVariant) {
    FlatTreeVariant<int, std::string> tree;
    int root = tree.addRoot(std::make_optional<std::variant<int, std::string>>("RootNode"));
    int child = tree.addChild(root, std::make_optional<std::variant<int, std::string>>(123));

    FlatTreeNode<std::variant<int, std::string>>& retrievedRoot = tree.getNode(root);
    FlatTreeNode<std::variant<int, std::string>>& retrievedChild = tree.getNode(child);

    EXPECT_TRUE(retrievedRoot.value.has_value());
    EXPECT_TRUE(std::holds_alternative<std::string>(retrievedRoot.value.value()));
    EXPECT_EQ(std::get<std::string>(retrievedRoot.value.value()), "RootNode");

    EXPECT_TRUE(retrievedChild.value.has_value());
    EXPECT_TRUE(std::holds_alternative<int>(retrievedChild.value.value()));
    EXPECT_EQ(std::get<int>(retrievedChild.value.value()), 123);
}

TEST(FlatTreeVariantTest, AddChildInvalidParentThrows) {
    FlatTreeVariant<int, std::string> tree;
    tree.addRoot();

    EXPECT_THROW(tree.addChild(-1, std::make_optional<std::variant<int, std::string>>(10)), std::out_of_range);
    EXPECT_THROW(tree.addChild(10, std::make_optional<std::variant<int, std::string>>("Invalid")), std::out_of_range);
}

TEST(FlatTreeVariantTest, HasValueWithVariants) {
    FlatTreeVariant<int, std::string> tree;
    int root = tree.addRoot(std::make_optional<std::variant<int, std::string>>(42));
    int child = tree.addChild(root, std::make_optional<std::variant<int, std::string>>());

    EXPECT_TRUE(tree.hasValue(root));
    EXPECT_FALSE(tree.hasValue(child));
}

TEST(FlatTreeVariantTest, OperatorOutputEmptyTree) {
    FlatTreeVariant<int, std::string> tree;
    std::ostringstream oss;
    oss << tree;
    EXPECT_EQ(oss.str(), "");
}

TEST(FlatTreeVariantTest, SingleNodeOperatorOutput) {
    FlatTreeVariant<int, std::string> tree;
    tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("OnlyRoot")));

    std::ostringstream oss;
    oss << tree;
    EXPECT_EQ(oss.str(), "OnlyRoot ");
}

TEST(FlatTreeVariantTest, IteratorTraversalEmptyTree) {
    FlatTreeVariant<int, std::string> tree;
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST(FlatTreeVariantTest, IteratorTraversalSingleNode) {
    FlatTreeVariant<int, std::string> tree;
    tree.addRoot(std::make_optional<std::variant<int, std::string>>(std::string("Root")));

    std::vector<std::variant<int, std::string>> expectedValues = {std::string("Root")};
    std::vector<std::variant<int, std::string>> actualValues;

    for (auto it = tree.begin(); it != tree.end(); ++it) {
        actualValues.push_back(it->value.value_or(std::variant<int, std::string>()));
    }

    EXPECT_EQ(actualValues, expectedValues);
}
