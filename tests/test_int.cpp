#include <gtest/gtest.h>
#include "tree.hpp"

using namespace rvp;

TEST(IntTest, AddChildLeaf) {
    Tree<int> tree;
    tree.addChild(1);
    tree.addChild(2);

    // Expect 2 children in the tree
    ASSERT_EQ(tree.toString(), "{1,2}");
}

TEST(IntTest, AddChildSubTree) {
    Tree<int> tree, subTree;
    subTree.addChild(3);
    subTree.addChild(4);
    tree.addChild(subTree);

    // Expect 1 child in the tree (the subtree)
    ASSERT_EQ(tree.toString(), "{{3,4}}");
}

TEST(IntTest, PrintTree) {
    Tree<int> tree, subTree;
    tree.addChild(1);
    subTree.addChild(2);
    subTree.addChild(3);
    tree.addChild(subTree);

    ASSERT_EQ(tree.toString(), "{1,{2,3}}");
}
