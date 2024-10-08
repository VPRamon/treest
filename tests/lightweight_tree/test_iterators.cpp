#ifndef ITERATOR_TEST_HPP
#define ITERATOR_TEST_HPP

#include "test_fixture.hpp"

//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6

class IteratorTest : public TestFixture {
public:
    static const std::vector<std::string> INORDER, PREORDER, R_PREORDER, POSTORDER, BFS, R_BFS, DFS;
};

// TODO: const std::vector<std::string> IteratorTest::INORDER    = std::vector<std::string> {"3", "1", "4", "0", "5", "2", "6"};
const std::vector<std::string> IteratorTest::PREORDER   = std::vector<std::string> {"0", "1", "3", "4", "2", "5", "6"};
const std::vector<std::string> IteratorTest::R_PREORDER = std::vector<std::string> {"0", "2", "6", "5", "1", "4", "3"};
const std::vector<std::string> IteratorTest::POSTORDER  = std::vector<std::string> {"3", "4", "1", "5", "6", "2", "0"};
const std::vector<std::string> IteratorTest::BFS        = std::vector<std::string> {"0", "1", "2", "3", "4", "5", "6"};
const std::vector<std::string> IteratorTest::R_BFS      = std::vector<std::string> {"0", "2", "1", "6", "5", "4", "3"};
const std::vector<std::string> IteratorTest::DFS = PREORDER;
/*
template <typename T>
void CHECK_ITERATOR(T begin, T end, std::vector<std::string> expected) {
    std::vector<std::string> result;

    for (auto it = begin; it != end; ++it) {
        result.push_back(it->value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(IteratorTest, TestPreOrderTraversal) {
    CHECK_ITERATOR(tree.pre_order_begin(), tree.pre_order_end(), PREORDER);
}

TEST_F(IteratorTest, TestPostOrderTraversal) {
    CHECK_ITERATOR(tree.post_order_begin(), tree.post_order_end(), POSTORDER);
}

TEST_F(IteratorTest, TestBFSTraversal) {
    CHECK_ITERATOR(tree.bfs_begin(), tree.bfs_end(), BFS);
}

TEST_F(IteratorTest, TestReverseBFSTraversal) {
    CHECK_ITERATOR(tree.bfs_rbegin(), tree.bfs_rend(), R_BFS);
}

TEST_F(IteratorTest, TestReversePreOrderTraversal) {
    CHECK_ITERATOR(tree.pre_order_rbegin(), tree.pre_order_rend(), R_PREORDER);
}

TEST_F(IteratorTest, TestConstIterator) {
    const auto& constTree = tree;
    CHECK_ITERATOR(tree.pre_order_begin(), tree.pre_order_end(), PREORDER);
}

TEST_F(IteratorTest, TestStandardAlgorithms) {
    auto it = std::find_if(
        tree.pre_order_begin(), tree.pre_order_end(),
        [](const vpr::tree::Node<std::string>& node) {
            return node.value() == "6";
        }
    );

    EXPECT_NE(it, tree.pre_order_end());
    EXPECT_EQ(it->value(), "6");
}

*/
#endif // TREE_TEST_HPP
