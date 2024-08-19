#include <gtest/gtest.h>
#include "common_tree.hpp"

using namespace rvp;

#define ListTree ListTree<int>

TEST(ListTreeTest, MakeLeaf) {
    ListTree leaf(1);
    ASSERT_TRUE(leaf.isLeaf());
    ASSERT_TRUE(leaf.hasValue());
    ASSERT_EQ(leaf.value(), 1);
}

TEST(ListTreeTest, MakeRootedTree) {
    ListTree leaf_1(1);
    ListTree leaf_2(2);

    std::list<ListTree> children = {leaf_1, leaf_2};

    ListTree rooted_tree(children);
    ASSERT_FALSE(rooted_tree.isLeaf());
    ASSERT_FALSE(rooted_tree.hasValue());

    auto it = rooted_tree.begin();
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), 1);

    it++;
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), 2);
}
