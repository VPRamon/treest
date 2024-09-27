#include <gtest/gtest.h>
#include <variant>
#include "flat_tree_variant.hpp"
#include "flat_tree.hpp"

using namespace vpr;

TEST(FlatTreeTest, CustomTree) {
    // Example with single-type tree
    vpr::FlatTree<int> singleTypeTree;
    int rootIndex = singleTypeTree.addRoot(10);
    int leftChildSingle = singleTypeTree.addChild(rootIndex, 20);
    int rightChildSingle = singleTypeTree.addChild(rootIndex, 30);

    //std::cout << "Single-Type Tree Pre-order Traversal:" << std::endl;
    //std::cout << singleTypeTree << std::endl;
    // Expected Output:
    // 10 20 30 

    // Example with multi-type tree using std::variant
    vpr::FlatTreeVariant<int, char> multiTypeTree;
    int rootMulti = multiTypeTree.addRoot(10);          // int
    int leftChildMulti = multiTypeTree.addChild(rootMulti, 'A'); // char
    int rightChildMulti = multiTypeTree.addChild(rootMulti, 20); // int

    // Adding more children
    multiTypeTree.addChild(leftChildMulti, 30);        // int
    multiTypeTree.addChild(leftChildMulti, 'B');      // char

    std::cout << "\nMulti-Type Tree Pre-order Traversal:" << std::endl;
    std::cout << multiTypeTree << std::endl;
    // Expected Output:
    // 10 A 30 B 20 

    for (auto node : multiTypeTree) {
        std::cout << node << std::endl;
    }
}


TEST(FlatTreeTest, BuildTree) {
    vpr::FlatTree<int> tree;

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
    std::cout << "\nTree Pre-order Traversal:" << std::endl;
    std::cout << tree << std::endl;

}
