#include <gtest/gtest.h>
#include "tree.hpp"

using namespace rvp;

TEST(FloatTest, AddChildLeaf) {
    Tree<float> tree;
    tree.addChild(1.2f);
    tree.addChild(2.3f);

    // Expect 2 children in the tree
    ASSERT_EQ(tree.toString(), "{1.2,2.3}");
}

TEST(FloatTest, AddChildSubTree) {
    Tree<float> tree, subTree;
    subTree.addChild(3.4f);
    subTree.addChild(4.5f);
    tree.addChild(subTree);

    // Expect 1 child in the tree (the subtree)
    ASSERT_EQ(tree.toString(), "{{3.4,4.5}}");
}

TEST(FloatTest, PrintTree) {
    Tree<float> tree, subTree;
    tree.addChild(1.2f);
    subTree.addChild(2.3f);
    subTree.addChild(3.4f);
    tree.addChild(subTree);

    ASSERT_EQ(tree.toString(), "{1.2,{2.3,3.4}}");
}
