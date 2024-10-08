#ifndef SMART_TREE_ITERATOR_TEST_HPP
#define SMART_TREE_ITERATOR_TEST_HPP

#include "smart_tree_test_fixture.hpp"

//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6

class SmartTreeIteratorTest : public SmartTreeTestFixture {
public:
    static const std::vector<std::string> INORDER, PREORDER, R_PREORDER, POSTORDER, BFS, R_BFS, DFS;
};

// TODO: const std::vector<std::string> SmartTreeIteratorTest::INORDER    = std::vector<std::string> {"3", "1", "4", "0", "5", "2", "6"};
const std::vector<std::string> SmartTreeIteratorTest::PREORDER   = std::vector<std::string> {"0", "1", "3", "4", "2", "5", "6"};
const std::vector<std::string> SmartTreeIteratorTest::R_PREORDER = std::vector<std::string> {"0", "2", "6", "5", "1", "4", "3"};
const std::vector<std::string> SmartTreeIteratorTest::POSTORDER  = std::vector<std::string> {"3", "4", "1", "5", "6", "2", "0"};
const std::vector<std::string> SmartTreeIteratorTest::BFS        = std::vector<std::string> {"0", "1", "2", "3", "4", "5", "6"};
const std::vector<std::string> SmartTreeIteratorTest::R_BFS      = std::vector<std::string> {"0", "2", "1", "6", "5", "4", "3"};
const std::vector<std::string> SmartTreeIteratorTest::DFS = PREORDER;

template <typename T>
void CHECK_ITERATOR(T begin, T end, std::vector<std::string> expected) {
    std::vector<std::string> result;

    for (auto it = begin; it != end; ++it) {
        result.push_back(it->value());
    }

    EXPECT_EQ(result, expected);
}

TEST_F(SmartTreeIteratorTest, TestPreOrderTraversal) {
    CHECK_ITERATOR(tree.pre_order_begin(), tree.pre_order_end(), PREORDER);
}

TEST_F(SmartTreeIteratorTest, TestPostOrderTraversal) {
    CHECK_ITERATOR(tree.post_order_begin(), tree.post_order_end(), POSTORDER);
}

TEST_F(SmartTreeIteratorTest, TestBFSTraversal) {
    CHECK_ITERATOR(tree.bfs_begin(), tree.bfs_end(), BFS);
}

TEST_F(SmartTreeIteratorTest, TestReverseBFSTraversal) {
    CHECK_ITERATOR(tree.bfs_rbegin(), tree.bfs_rend(), R_BFS);
}

TEST_F(SmartTreeIteratorTest, TestReversePreOrderTraversal) {
    CHECK_ITERATOR(tree.pre_order_rbegin(), tree.pre_order_rend(), R_PREORDER);
}

TEST_F(SmartTreeIteratorTest, TestConstIterator) {
    const auto& constTree = tree;
    CHECK_ITERATOR(tree.pre_order_begin(), tree.pre_order_end(), PREORDER);
}

TEST_F(SmartTreeIteratorTest, TestStandardAlgorithms) {
    auto it = std::find_if(
        tree.pre_order_begin(), tree.pre_order_end(),
        [](const Node& node) {
            return node.value() == "6";
        }
    );

    EXPECT_NE(it, tree.pre_order_end());
    EXPECT_EQ(it->value(), "6");
}

#endif // TREE_TEST_HPP
