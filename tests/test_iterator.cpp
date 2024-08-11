#include <gtest/gtest.h>
#include "tree.hpp"
#include "iterator.hpp"

#define Tree Tree<int>
#define Leaf Tree::Leaf
#define SubTree Tree::SubTree
#define Node Tree::Node

TEST(IteratorTest, IterateOneLevel) {
    Tree tree;
    tree.addChild(1);
    tree.addChild(2);

    for (auto& node: tree) {
        std::visit(overload{
            [](const Leaf& leaf)    { std::cout << leaf; },
            [](const SubTree& tree) { std::cout << *tree; },
        }, node);
    }
}
