#include <gtest/gtest.h>
#include "deque_tree.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(DequeTreeTest, MakeLeaf) {
    TEST_LEAF<DequeTree<int>>(1);
    TEST_LEAF<DequeTree<float>>(1.5);
    TEST_LEAF<DequeTree<char>>('A');
    TEST_LEAF<DequeTree<std::string>>(std::string("This is a string"));
}

TEST(DequeTreeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<DequeTree<int>>(1, 2);
    TEST_ROOTED_TREE<DequeTree<float>>(1.5, 3.);
    TEST_ROOTED_TREE<DequeTree<char>>('A', 'B');
    TEST_ROOTED_TREE<DequeTree<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(DequeTreeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<DequeTree<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<DequeTree<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<DequeTree<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(DequeTreeTest, SerializeTree) {
    TEST_OUT_TREE<DequeTree<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<DequeTree<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<DequeTree<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<DequeTree<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(DequeTreeTest, IterateTree) {
    TEST_ITERATE_TREE<DequeTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<DequeTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<DequeTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<DequeTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(DequeTreeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<DequeTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<DequeTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<DequeTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<DequeTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}
