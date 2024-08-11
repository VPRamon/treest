#include <gtest/gtest.h>
#include "tree.hpp"
#include "iterator.hpp"

#define Tree Tree<int>
#define Leaf Tree::Leaf
#define SubTree Tree::SubTree
#define Node Tree::Node

void traverseTree(Tree& tree) {
    for (auto& node: tree) {
        std::visit(overload{
            [](const Leaf& leaf)    { std::cout << leaf << std::endl; },
            [](const SubTree& tree) { std::cout << *tree << std::endl; },
        }, node);
    }
}

TEST(IteratorTest, Iterate1Level) {
    Tree tree;
    tree.addChild(1);
    tree.addChild(2);

    traverseTree(tree);
}

TEST(IteratorTest, Iterate2Level) {
    Tree tree;
    tree.addChild(1);
    auto subTree = std::make_unique<Tree>();
    subTree->addChild(3);
    subTree->addChild(4);
    tree.addChild(std::move(subTree));

    traverseTree(tree);
}
