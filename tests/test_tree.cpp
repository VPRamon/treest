#include <gtest/gtest.h>
#include "tree.hpp"

TEST(TreeTest, AddChildLeaf) {
    Tree<int> tree;
    tree.addChild(1);
    tree.addChild(2);

    // Expect 2 children in the tree
    ASSERT_EQ(tree.toString(), "{1,2}");
}

TEST(TreeTest, AddChildSubTree) {
    Tree<int> tree;
    auto subTree = std::make_unique<Tree<int>>();
    subTree->addChild(3);
    subTree->addChild(4);
    tree.addChild(std::move(subTree));

    // Expect 1 child in the tree (the subtree)
    ASSERT_EQ(tree.toString(), "{{3,4}}");
}

TEST(TreeTest, PrintTree) {
    Tree<int> tree;
    tree.addChild(1);
    auto subTree = std::make_unique<Tree<int>>();
    subTree->addChild(2);
    subTree->addChild(3);
    tree.addChild(std::move(subTree));

    ASSERT_EQ(tree.toString(), "{1,{2,3}}");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
