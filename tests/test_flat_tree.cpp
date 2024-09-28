#ifndef FLAT_TREE_TEST_HPP
#define FLAT_TREE_TEST_HPP

#include "flat_tree.hpp"
#include "flat_tree_variant.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6

#define INORDER std::vector<std::string> {"3", "1", "4", "0", "5", "2", "6" }
#define PREORDER std::vector<std::string> {"0", "1", "3", "4", "2", "5", "6" }
#define R_PREORDER std::vector<std::string> { "0", "2", "6", "5", "1", "4", "3" }
#define POSTORDER std::vector<std::string> {"3", "4", "1", "5", "6", "2", "0" }
#define BFS std::vector<std::string> {"0", "1", "2", "3", "4", "5", "6" }
#define DFS PREORDER

class FlatTreeTestFixture : public ::testing::Test {
protected:
    vpr::FlatTree<std::string> tree;

    virtual void SetUp() override {
        // Set up a common tree structure for all tests
        tree = vpr::FlatTree<std::string>("0");

        int child1 = tree.getRoot().addChild("1");
        int child2 = tree.getRoot().addChild("2");

        tree.getNode(child1).addChild("3");
        tree.getNode(child1).addChild("4");

        tree.getNode(child2).addChild("5");
        tree.getNode(child2).addChild("6");
    }
};


TEST_F(FlatTreeTestFixture, TestTreeInitialization) {
    EXPECT_EQ(tree.size(), 7); // Root + 3 children + 5 grandchildren + initial reserve
    EXPECT_EQ(tree.getRoot().value.value(), "0");
}

TEST_F(FlatTreeTestFixture, TestAddChild) {
    int newChild = tree.getRoot().addChild("7");
    EXPECT_EQ(tree.size(), 8);
    EXPECT_EQ(tree.getNode(newChild).value.value(), "7");
}

TEST_F(FlatTreeTestFixture, TestGetNode) {
    EXPECT_EQ(tree.getNode(0).value.value(), "0");
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
}

TEST_F(FlatTreeTestFixture, TestIteratorPreOrderTraversal) {
    std::vector<std::string> expected = PREORDER;
    std::vector<std::string> result;

    for (auto it = tree.pre_order_begin(); it != tree.pre_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(FlatTreeTestFixture, TestIteratorPostOrderTraversal) {
    std::vector<std::string> expected = POSTORDER;
    std::vector<std::string> result;

    for (auto it = tree.post_order_begin(); it != tree.post_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(FlatTreeTestFixture, TestIteratorLevelOrderTraversal) {
    std::vector<std::string> expected = BFS;
    std::vector<std::string> result;

    for (auto it = tree.bfs_begin(); it != tree.bfs_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(FlatTreeTestFixture, TestReversePreOrderTraversal) {
    std::vector<std::string> expected = R_PREORDER;

    std::vector<std::string> result;

    for (auto it = tree.pre_order_rbegin(); it != tree.pre_order_rend(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(FlatTreeTestFixture, TestConstIterator) {
    const auto& constTree = tree;
    std::vector<std::string> expected = PREORDER;
    std::vector<std::string> result;

    for (auto it = constTree.pre_order_begin(); it != constTree.pre_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(FlatTreeTestFixture, TestNodeProperties) {
    auto& root = tree.getRoot();
    EXPECT_TRUE(root.isRoot());
    EXPECT_FALSE(root.isLeaf());
    EXPECT_EQ(root.nChildren(), 2);

    auto& child1 = tree.getNode(1);
    EXPECT_FALSE(child1.isRoot());
    EXPECT_FALSE(child1.isLeaf());
    EXPECT_EQ(child1.nChildren(), 2);

    auto& grandchild1 = tree.getNode(4);
    EXPECT_FALSE(grandchild1.isRoot());
    EXPECT_TRUE(grandchild1.isLeaf());
    EXPECT_EQ(grandchild1.nChildren(), 0);
}

TEST_F(FlatTreeTestFixture, TestGetChildren) {
    auto& child1 = tree.getNode(1);
    auto children = child1.getChildren();
    EXPECT_EQ(children.size(), 2);
    EXPECT_EQ(children[0].get().value.value(), "3");
    EXPECT_EQ(children[1].get().value.value(), "4");
}

TEST_F(FlatTreeTestFixture, TestExceptionSafety) {
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
    EXPECT_THROW(tree.getRoot().getChild(-1), std::out_of_range);
    EXPECT_THROW(tree.getRoot().getChild(100), std::out_of_range);
}

TEST_F(FlatTreeTestFixture, TestOperatorOverloading) {
    std::stringstream ss;
    ss << tree;
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(FlatTreeTestFixture, TestVariantNode) {
    vpr::FlatTreeVariant<int, std::string> variantTree(42);
    auto& root = variantTree.getRoot();
    EXPECT_TRUE(root.value.has_value());

    int child1 = root.addChild(std::string("Child1"));
    int child2 = root.addChild(84);

    EXPECT_TRUE(std::holds_alternative<int>(variantTree.getNode(child2).value.value()));
    EXPECT_TRUE(std::holds_alternative<std::string>(variantTree.getNode(child1).value.value()));
}

TEST_F(FlatTreeTestFixture, TestIteratorStandardAlgorithms) {
    auto it = std::find_if(
        tree.pre_order_begin(), tree.pre_order_end(),
        [](const vpr::FlatTreeNode<std::string>& node) {
            return node.value.value() == "6";
        }
    );

    EXPECT_NE(it, tree.pre_order_end());
    EXPECT_EQ(it->value.value(), "6");
}


#endif // FLAT_TREE_TEST_HPP
