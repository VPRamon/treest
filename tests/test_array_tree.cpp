#include <gtest/gtest.h>
#include "array_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(ArrayTreeTest, MakeLeaf) {
    TEST_LEAF<ArrayTree<int>>(1);
    TEST_LEAF<ArrayTree<float>>(1.5);
    TEST_LEAF<ArrayTree<char>>('A');
    TEST_LEAF<ArrayTree<std::string>>(std::string("This is a string"));
}

TEST(ArrayTreeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<ArrayTree<int>>(1, 2);
    TEST_ROOTED_TREE<ArrayTree<float>>(1.5, 3.);
    TEST_ROOTED_TREE<ArrayTree<char>>('A', 'B');
    TEST_ROOTED_TREE<ArrayTree<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(ArrayTreeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<ArrayTree<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<ArrayTree<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<ArrayTree<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(ArrayTreeTest, SerializeTree) {
    TEST_OUT_TREE<ArrayTree<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<ArrayTree<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<ArrayTree<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<ArrayTree<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(ArrayTreeTest, IterateTree) {
    TEST_ITERATE_TREE<ArrayTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<ArrayTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<ArrayTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<ArrayTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(ArrayTreeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<ArrayTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<ArrayTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<ArrayTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<ArrayTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

/*TEST(ArrayTreeTest, CustomTree) {
    ArrayTree<char> char_node('A');
    CustomNode<ArrayTree<char>, int> int_node(1, char_node);

    std::cout << "CHAR_NODE: ";
    std::cout << char_node;

    std::cout << "\nINT_NODE: ";
    std::cout << int_node;

}*/
