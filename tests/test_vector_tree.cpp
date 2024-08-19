#include <gtest/gtest.h>
#include "common_tree.hpp"

using namespace rvp;

#define VectorTree VectorTree<int>

TEST(VectorTreeTest, MakeLeaf) {
    VectorTree leaf(1);
    ASSERT_TRUE(leaf.isLeaf());
    ASSERT_TRUE(leaf.hasValue());
    ASSERT_EQ(leaf.value(), 1);
}

TEST(VectorTreeTest, MakeRootedTree) {
    VectorTree leaf_1(1);
    VectorTree leaf_2(2);

    std::vector<VectorTree> children = {leaf_1, leaf_2};

    VectorTree rooted_tree(children);
    ASSERT_FALSE(rooted_tree.isLeaf());
    ASSERT_FALSE(rooted_tree.hasValue());

    auto it = rooted_tree.begin();
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), 1);

    it++;
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), 2);
}
