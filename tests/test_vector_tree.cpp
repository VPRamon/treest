#include <gtest/gtest.h>
#include "vector_tree.hpp"
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
    TEST_OUT_TREE<VectorTree<char>>('A', 'B', 'C', "[[A, B], C]"); // outs ASCII
    TEST_OUT_TREE<VectorTree<std::variant<int, char>>>(1, 2, 3, "[[1, 2], 3]");
}
