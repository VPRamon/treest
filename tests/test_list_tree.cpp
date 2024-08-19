#include <gtest/gtest.h>
#include "list_tree.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(ListTreeTest, MakeLeaf) {
    TEST_LEAF<ListTree<int>>(1);
    TEST_LEAF<ListTree<float>>(1.5);
    TEST_LEAF<ListTree<char>>('A');
    TEST_LEAF<ListTree<std::string>>(std::string("This is a string"));
}

TEST(ListTreeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<ListTree<int>>(1, 2);
    TEST_ROOTED_TREE<ListTree<float>>(1.5, 3.);
    TEST_ROOTED_TREE<ListTree<char>>('A', 'B');
    TEST_ROOTED_TREE<ListTree<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(ListTreeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<ListTree<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<ListTree<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<ListTree<std::variant<char, std::string>>>('A', std::string("Test"));
}
