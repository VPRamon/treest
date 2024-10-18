#include "binary_tree.hpp"
#include <gtest/gtest.h>
#include <string>

//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6

using namespace vpr;
using Tree = lightweight::BinaryTree<std::string>;
using Node = Tree::Node;

class BinTreeTestFixture : public ::testing::Test {
protected:
    Tree tree{"0"};

    virtual void SetUp() override {

        auto root = tree.getRoot();
        size_t child1_id = tree.addChild(root.index(), "1");
        size_t child2_id = tree.addChild(root.index(), "2");

        tree.addChild(child1_id, "3");
        tree.addChild(child1_id, "4");

        tree.addChild(child2_id, "5");
        tree.addChild(child2_id, "6");
    }
};
