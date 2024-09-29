#ifndef TEST_FIXTURE_HPP
#define TEST_FIXTURE_HPP

#include "tree.hpp"
#include "tree_variant.hpp"
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

class TestFixture : public ::testing::Test {
protected:
    vpr::Tree<std::string> tree;

    virtual void SetUp() override {
        // Set up a common tree structure for all tests
        tree = vpr::Tree<std::string>("0");

        size_t child1 = tree.getRoot().addChild("1");
        size_t child2 = tree.getRoot().addChild("2");

        tree.getNode(child1).addChild("3");
        tree.getNode(child1).addChild("4");

        tree.getNode(child2).addChild("5");
        tree.getNode(child2).addChild("6");
    }
};

#endif // TREE_TEST_HPP
