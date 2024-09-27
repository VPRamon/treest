#include <gtest/gtest.h>
#include "flat_node.hpp"

using namespace vpr;

TEST(FlatTreeTest, MakeLeaf) {
    vpr::FlatBinaryTree<int> tree;

    // Add root
    int rootIndex = tree.addRoot(1);

    // Add children
    int parent = tree.addChild(rootIndex, 2);
    tree.addChild(parent, 3);
    tree.addChild(parent, 4);
    parent = tree.addChild(rootIndex, 5);
    tree.addChild(parent, 6);
    tree.addChild(parent, 7);

    // Traverse and print using pre-order iterator
    tree.printPreOrder();

}
