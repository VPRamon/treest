#include <gtest/gtest.h>
#include "tree.hpp"

using namespace rvp;

#define BinaryTree BinaryTree<int>

TEST(BinaryTreeTest, MakeLeaf) {
    BinaryTree leaf(1);
    ASSERT_TRUE(leaf.isLeaf());
    ASSERT_TRUE(leaf.hasValue());
    ASSERT_EQ(leaf.value(), 1);
}

TEST(BinaryTreeTest, MakeRootedTree) {
    BinaryTree leaf_left(1);
    BinaryTree leaf_right(2);

    std::pair<BinaryTree, BinaryTree> children(std::move(leaf_left), std::move(leaf_right));
    ASSERT_TRUE(children.first.hasValue());
    ASSERT_TRUE(children.second.hasValue());

    BinaryTree rooted_tree(children);
    ASSERT_FALSE(rooted_tree.isLeaf());
    ASSERT_FALSE(rooted_tree.hasValue());

    ASSERT_TRUE(rooted_tree.left().hasValue());
    ASSERT_EQ(rooted_tree.left().value(), 1);
    ASSERT_TRUE(rooted_tree.right().hasValue());
    ASSERT_EQ(rooted_tree.right().value(), 2);
}
