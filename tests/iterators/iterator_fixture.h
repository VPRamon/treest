#ifndef ITERATOR_FIXTURE_HPP
#define ITERATOR_FIXTURE_HPP

#include <gtest/gtest.h>
#include <tree.hpp>

#define Tree Tree<int>
#define Leaf Tree::Leaf
#define SubTree Tree::SubTree
#define Node Tree::Node

using namespace rvp;


class IteratorFixture : public ::testing::Test {
protected:
    void SetUp() override {};
    void TearDown() override {};

    void ASSERT_DFS(Tree& tree, int expected) { // increments as we traverse the tree
        for (Node& node: tree) {
            std::visit(overload{
                [&](const Leaf& leaf)    { ASSERT_EQ(Tree::getLeaf(node), expected++); },
                [&](const SubTree& tree) { ASSERT_DFS(*Tree::getSubTree(node), expected); },
            }, node);
        }
    }

    void ASSERT_CONST_DFS(const Tree& tree, int expected) { // increments as we traverse the tree
        for (const Node& node: tree) {
            std::visit(overload{
                [&](const Leaf& leaf)    { ASSERT_EQ(Tree::getLeaf(node), expected++); },
                [&](const SubTree& tree) { ASSERT_DFS(*Tree::getSubTree(node), expected); },
            }, node);
        }
    }

    void ASSERT_LEAF(Tree::Iterator it, Leaf expected) {
        ASSERT_TRUE(Tree::isLeaf(*it));
        ASSERT_EQ(Tree::getLeaf(*it), expected);
    }

    void ASSERT_SUBTREE(Tree::Iterator it) {
        ASSERT_TRUE(Tree::isSubTree(*it));
    }

    void ASSERT_LEAF(Tree::ConstIterator it, Leaf expected) {
        ASSERT_TRUE(Tree::isLeaf(*it));
        ASSERT_EQ(Tree::getLeaf(*it), expected);
    }

    void ASSERT_SUBTREE(Tree::ConstIterator it) {
        ASSERT_TRUE(Tree::isSubTree(*it));
    }

public:

    Tree tree;

};

#endif
