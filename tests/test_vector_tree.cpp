#include <gtest/gtest.h>
#include "vector_node.hpp"
#include "templates.hpp"

using namespace vpr;

TEST(VectorTreeTest, MakeLeaf) {
    TEST_LEAF<VectorTree<int>>(1);
    TEST_LEAF<VectorTree<float>>(1.5);
    TEST_LEAF<VectorTree<char>>('A');
    TEST_LEAF<VectorTree<std::string>>(std::string("This is a string"));
}

TEST(VectorTreeTest, MakeRootedTree) {
    TEST_ROOTED_TREE<VectorTree<int>>(1, 2);
    TEST_ROOTED_TREE<VectorTree<float>>(1.5, 3.);
    TEST_ROOTED_TREE<VectorTree<char>>('A', 'B');
    TEST_ROOTED_TREE<VectorTree<std::string>>(std::string("This is a string"), std::string("This is another string"));
}

TEST(VectorTreeTest, MakeVariantLeaf) {
    TEST_VARIANT_LEAF<VectorTree<std::variant<int, char>>>(1, 'A');
    TEST_VARIANT_LEAF<VectorTree<std::variant<char, int>>>('A', 1);
    TEST_VARIANT_LEAF<VectorTree<std::variant<char, std::string>>>('A', std::string("Test"));
}

TEST(VectorTreeTest, SerializeTree) {
    TEST_OUT_TREE<VectorTree<int>>(1, 2, 3, "[[1, 2], 3]");
    TEST_OUT_TREE<VectorTree<float>>(1.2, 2.3, 3.4, "[[1.2, 2.3], 3.4]");
    TEST_OUT_TREE<VectorTree<char>>('A', 'B', 'C', "[[A, B], C]");
    TEST_OUT_TREE<VectorTree<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}

TEST(VectorTreeTest, IterateTree) {
    TEST_ITERATE_TREE<VectorTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_ITERATE_TREE<VectorTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_ITERATE_TREE<VectorTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_ITERATE_VARIANT_TREE<VectorTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(VectorTreeTest, ConstIterateTree) {
    TEST_CONST_ITERATE_TREE<VectorTree<int>>(std::array<int, 3>{1, 2, 3});
    TEST_CONST_ITERATE_TREE<VectorTree<float>>(std::array<float, 3>{1.2, 2.3, 3.4});
    TEST_CONST_ITERATE_TREE<VectorTree<char>>(std::array<char, 3>{'A', 'B', 'C'});
    TEST_CONST_ITERATE_VARIANT_TREE<VectorTree<std::variant<int, char>>>(std::array<int, 3>{1, 2, 3});
}

TEST(VectorTreeTest, CustomTree) {
    using Tree = VectorTree<std::variant<int, char>>;

    Tree root;
    {
        Tree leaf_1(1);
        Tree leaf_2(2);
        root = Tree({leaf_1, leaf_2});
    }

    std::ostringstream oss;
    oss << root;

    std::string out(oss.str());
    std::cout << out;
}
