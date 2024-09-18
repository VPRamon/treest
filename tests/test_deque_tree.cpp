#include <gtest/gtest.h>
#include "deque_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(SimpleDequeNodeTest, MakeLeaf) {
    TEST_LEAF<SimpleDequeNode<int>>(1);
    TEST_LEAF<SimpleDequeNode<float>>(1.5);
    TEST_LEAF<SimpleDequeNode<char>>('A');
    TEST_LEAF<SimpleDequeNode<std::string>>(std::string("This is a string"));
}

TEST(SimpleDequeNodeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<SimpleDequeNode<int>>(1, 2);
    TEST_ROOTED_TREE<SimpleDequeNode<float>>(1.5, 3.);
    TEST_ROOTED_TREE<SimpleDequeNode<char>>('A', 'B');
    TEST_ROOTED_TREE<SimpleDequeNode<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(SimpleDequeNodeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<SimpleDequeNode<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<SimpleDequeNode<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<SimpleDequeNode<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(SimpleDequeNodeTest, SerializeTree) {
    TEST_OUT_TREE<SimpleDequeNode<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<SimpleDequeNode<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<SimpleDequeNode<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<SimpleDequeNode<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(SimpleDequeNodeTest, IterateTree) {
    TEST_ITERATE_TREE<SimpleDequeNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<SimpleDequeNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<SimpleDequeNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<SimpleDequeNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(SimpleDequeNodeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<SimpleDequeNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<SimpleDequeNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<SimpleDequeNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<SimpleDequeNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
