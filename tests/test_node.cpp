#include <gtest/gtest.h>
#include <string>
#include "tree.hpp"

using namespace rvp;

#define Tree Tree<int, std::string>

TEST(NodeTest, AddNodeString) {
    Tree tree("This is a Node");
    tree.addChild(1);
    tree.addChild(2);

    // Expect 2 children in the tree
    ASSERT_EQ(tree.toString(), "This is a Node{1,2}");
}
