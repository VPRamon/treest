#include <gtest/gtest.h>
#include "binary_tree.hpp"
#include "templates.hpp"

using namespace vpr;

template <typename T>
void TEST_ROOTED_BIN_TREE(T value_1, T value_2) {
    using ContainerType = BinaryTree<T>;

    ContainerType leaf_1(value_1);
    ContainerType leaf_2(value_2);

    ContainerType children({leaf_1, leaf_2});

    ContainerType rooted_tree(children);
    ASSERT_FALSE(rooted_tree.isLeaf());
    ASSERT_FALSE(rooted_tree.hasValue());

    ASSERT_TRUE(rooted_tree.left().hasValue());
    ASSERT_EQ(rooted_tree.left().value(), value_1);

    ASSERT_TRUE(rooted_tree.right().hasValue());
    ASSERT_EQ(rooted_tree.right().value(), value_2);
}


TEST(BinaryTreeTest, MakeLeaf) {
    TEST_LEAF<BinaryTree<int>>(1);
    TEST_LEAF<BinaryTree<float>>(1.5);
    TEST_LEAF<BinaryTree<char>>('A');
    TEST_LEAF<BinaryTree<std::string>>(std::string("This is a string"));
}

TEST(BinaryTreeTest, MakeRootedTree) {
    TEST_ROOTED_BIN_TREE(1, 2);
    TEST_ROOTED_BIN_TREE(1.5, 3.);
    TEST_ROOTED_BIN_TREE('A', 'B');
    TEST_ROOTED_BIN_TREE(std::string("This is a string"), std::string("This is another string"));
}

TEST(BinaryTreeTest, MakeVariantLeaf) {
    using Tree = BinaryTree<std::variant<int, char>>;
   
    Tree int_leaf(1);
    ASSERT_TRUE(int_leaf.isLeaf());
    ASSERT_TRUE(int_leaf.hasValue());

    auto int_value = int_leaf.value();
    ASSERT_EQ(*std::get_if<int>(&int_value), 1);
    ASSERT_EQ(std::get_if<char>(&int_value), nullptr);
    ASSERT_EQ(std::get<int>(int_value), 1);

    Tree char_leaf('A');
    ASSERT_TRUE(char_leaf.isLeaf());
    ASSERT_TRUE(char_leaf.hasValue());

    auto char_value = char_leaf.value();
    ASSERT_EQ(*std::get_if<char>(&char_value), 'A');
    ASSERT_EQ(std::get_if<int>(&char_value), nullptr);
    ASSERT_EQ(std::get<char>(char_value), 'A');
}
