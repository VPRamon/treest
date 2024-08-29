#include <gtest/gtest.h>
#include "list_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(ListNodeTest, MakeLeaf) {
    TEST_LEAF<ListNode<int>>(1);
    TEST_LEAF<ListNode<float>>(1.5);
    TEST_LEAF<ListNode<char>>('A');
    TEST_LEAF<ListNode<std::string>>(std::string("This is a string"));
}

TEST(ListNodeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<ListNode<int>>(1, 2);
    TEST_ROOTED_TREE<ListNode<float>>(1.5, 3.);
    TEST_ROOTED_TREE<ListNode<char>>('A', 'B');
    TEST_ROOTED_TREE<ListNode<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(ListNodeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<ListNode<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<ListNode<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<ListNode<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(ListNodeTest, SerializeTree) {
    TEST_OUT_TREE<ListNode<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<ListNode<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<ListNode<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<ListNode<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(ListNodeTest, IterateTree) {
    TEST_ITERATE_TREE<ListNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<ListNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<ListNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<ListNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(ListNodeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<ListNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<ListNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<ListNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<ListNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
