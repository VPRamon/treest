#include <gtest/gtest.h>
#include "list_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(SimpleListNodeTest, MakeLeaf) {
    TEST_LEAF<SimpleListNode<int>>(1);
    TEST_LEAF<SimpleListNode<float>>(1.5);
    TEST_LEAF<SimpleListNode<char>>('A');
    TEST_LEAF<SimpleListNode<std::string>>(std::string("This is a string"));
}

TEST(SimpleListNodeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<SimpleListNode<int>>(1, 2);
    TEST_ROOTED_TREE<SimpleListNode<float>>(1.5, 3.);
    TEST_ROOTED_TREE<SimpleListNode<char>>('A', 'B');
    TEST_ROOTED_TREE<SimpleListNode<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(SimpleListNodeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<SimpleListNode<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<SimpleListNode<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<SimpleListNode<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(SimpleListNodeTest, SerializeTree) {
    TEST_OUT_TREE<SimpleListNode<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<SimpleListNode<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<SimpleListNode<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<SimpleListNode<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(SimpleListNodeTest, IterateTree) {
    TEST_ITERATE_TREE<SimpleListNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<SimpleListNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<SimpleListNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<SimpleListNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(SimpleListNodeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<SimpleListNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<SimpleListNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<SimpleListNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<SimpleListNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
