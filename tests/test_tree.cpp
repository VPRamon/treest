#include <gtest/gtest.h>
#include "tree.hpp"

TEST(TreeTest, AddChildLeaf) {
    Tree<int> tree;
    tree.addChild(1);
    tree.addChild(2);

    // Expect 2 children in the tree
    // (We could add a method to return number of children)
}

TEST(TreeTest, AddChildSubTree) {
    Tree<int> tree;
    
    auto subTree = std::make_unique<Tree<int>>();
    subTree->addChild(3);
    subTree->addChild(4);
    
    tree.addChild(std::move(subTree));

    // Expect 1 child in the tree (the subtree)
}

TEST(TreeTest, PrintTree) {
    Tree<int> tree;
    tree.addChild(1);
    
    auto subTree = std::make_unique<Tree<int>>();
    subTree->addChild(2);
    subTree->addChild(3);
    
    tree.addChild(std::move(subTree));

    std::string out = tree.toString();
    ASSERT_EQ(out, "{1,{2,3}}");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
