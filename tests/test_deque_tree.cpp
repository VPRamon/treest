#include <gtest/gtest.h>
#include "deque_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(DequeNodeTest, MakeLeaf) {
    TEST_LEAF<DequeNode<int>>(1);
    TEST_LEAF<DequeNode<float>>(1.5);
    TEST_LEAF<DequeNode<char>>('A');
    TEST_LEAF<DequeNode<std::string>>(std::string("This is a string"));
}

TEST(DequeNodeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<DequeNode<int>>(1, 2);
    TEST_ROOTED_TREE<DequeNode<float>>(1.5, 3.);
    TEST_ROOTED_TREE<DequeNode<char>>('A', 'B');
    TEST_ROOTED_TREE<DequeNode<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(DequeNodeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<DequeNode<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<DequeNode<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<DequeNode<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(DequeNodeTest, SerializeTree) {
    TEST_OUT_TREE<DequeNode<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<DequeNode<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<DequeNode<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<DequeNode<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(DequeNodeTest, IterateTree) {
    TEST_ITERATE_TREE<DequeNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<DequeNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<DequeNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<DequeNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(DequeNodeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<DequeNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<DequeNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<DequeNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<DequeNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
