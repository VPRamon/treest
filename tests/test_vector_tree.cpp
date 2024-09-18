#include <gtest/gtest.h>
#include "vector_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(VectorNodeTest, MakeLeaf) {
    TEST_LEAF<SimpleVectorNode<int>>(1);
    TEST_LEAF<SimpleVectorNode<float>>(1.5);
    TEST_LEAF<SimpleVectorNode<char>>('A');
    TEST_LEAF<SimpleVectorNode<std::string>>(std::string("This is a string"));
}

TEST(VectorNodeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<SimpleVectorNode<int>>(1, 2);
    TEST_ROOTED_TREE<SimpleVectorNode<float>>(1.5, 3.);
    TEST_ROOTED_TREE<SimpleVectorNode<char>>('A', 'B');
    TEST_ROOTED_TREE<SimpleVectorNode<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(VectorNodeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<SimpleVectorNode<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<SimpleVectorNode<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<SimpleVectorNode<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(VectorNodeTest, SerializeTree) {
    TEST_OUT_TREE<SimpleVectorNode<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<SimpleVectorNode<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<SimpleVectorNode<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<SimpleVectorNode<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(VectorNodeTest, IterateTree) {
    TEST_ITERATE_TREE<SimpleVectorNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<SimpleVectorNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<SimpleVectorNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<SimpleVectorNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(VectorNodeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<SimpleVectorNode<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<SimpleVectorNode<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<SimpleVectorNode<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<SimpleVectorNode<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

/*TEST(VectorNodeTest, CustomTree) {
    SimpleVectorNode<char> char_node('A');
    CustomNode<SimpleVectorNode<char>, int> int_node(1, char_node);

    std::cout << "CHAR_NODE: ";
    std::cout << char_node;

    std::cout << "\nINT_NODE: ";
    std::cout << int_node;

}*/
