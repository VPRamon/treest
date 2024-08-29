#include <gtest/gtest.h>
#include "list_node.hpp"
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

TEST(ListTreeTest, SerializeTree) {
    TEST_OUT_TREE<ListTree<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<ListTree<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<ListTree<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<ListTree<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(ListTreeTest, IterateTree) {
    TEST_ITERATE_TREE<ListTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<ListTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<ListTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<ListTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(ListTreeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<ListTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<ListTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<ListTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<ListTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
