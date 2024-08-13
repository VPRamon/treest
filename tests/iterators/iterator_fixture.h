#ifndef ITERATOR_FIXTURE_HPP
#define ITERATOR_FIXTURE_HPP

#include <gtest/gtest.h>
#include <tree.hpp>

#define Tree Tree<int>
#define Leaf Tree::Leaf
#define SubTree Tree::SubTree
#define Node Tree::Node

class IteratorFixture : public ::testing::Test {
protected:
    void SetUp() override {};
    void TearDown() override {};

    void ASSERT_DFS(Tree& tree, int expected) { // increments as we traverse the tree
        for (auto& node: tree) {
            std::visit(overload{
                [&](const Leaf& leaf)    { ASSERT_EQ(Tree::getLeaf(node), expected++); },
                [&](const SubTree& tree) { ASSERT_DFS(*Tree::getSubTree(node), expected); },
            }, node);
        }
    }

    void traverseTree(Tree& tree) {
        for (auto& node: tree) {
            std::visit(overload{
                [](const Leaf& leaf)    { std::cout << leaf << std::endl; },
                [](const SubTree& tree) { std::cout << *tree << std::endl; },
            }, node);
        }
    }

    void traverseTreeConst(Tree& tree) {
        for (const auto& node: tree) {
            std::visit(overload{
                [](const Leaf& leaf)    { std::cout << leaf << std::endl; },
                [](const SubTree& tree) { std::cout << *tree << std::endl; },
            }, node);
        }
    }

    Tree tree;

};

#endif
