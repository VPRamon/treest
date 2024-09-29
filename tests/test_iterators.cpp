#ifndef ITERATOR_TEST_HPP
#define ITERATOR_TEST_HPP

#include "tree.hpp"
#include "tree_variant.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

#include "test_fixture.hpp"

//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6

class IteratorTest : public TestFixture {
public:
    static const std::vector<std::string> INORDER, PREORDER, R_PREORDER, POSTORDER, BFS, DFS;
};

const std::vector<std::string> IteratorTest::INORDER    = std::vector<std::string> {"3", "1", "4", "0", "5", "2", "6" };
const std::vector<std::string> IteratorTest::PREORDER   = std::vector<std::string> {"0", "1", "3", "4", "2", "5", "6" };
const std::vector<std::string> IteratorTest::R_PREORDER = std::vector<std::string> {"0", "2", "6", "5", "1", "4", "3" };
const std::vector<std::string> IteratorTest::POSTORDER  = std::vector<std::string> {"3", "4", "1", "5", "6", "2", "0" };
const std::vector<std::string> IteratorTest::BFS        = std::vector<std::string> {"0", "1", "2", "3", "4", "5", "6" };
const std::vector<std::string> IteratorTest::DFS = PREORDER;

TEST_F(IteratorTest, TestPreOrderTraversal) {
    std::vector<std::string> result;

    for (auto it = tree.pre_order_begin(); it != tree.pre_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, PREORDER);
}

TEST_F(IteratorTest, TestPostOrderTraversal) {
    std::vector<std::string> result;

    for (auto it = tree.post_order_begin(); it != tree.post_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, POSTORDER);
}

TEST_F(IteratorTest, TestBFSTraversal) {
    std::vector<std::string> result;

    for (auto it = tree.bfs_begin(); it != tree.bfs_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, BFS);
}

TEST_F(IteratorTest, TestReversePreOrderTraversal) {
    std::vector<std::string> result;

    for (auto it = tree.pre_order_rbegin(); it != tree.pre_order_rend(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, R_PREORDER);
}

TEST_F(IteratorTest, TestConstIterator) {
    const auto& constTree = tree;
    std::vector<std::string> result;

    for (auto it = constTree.pre_order_begin(); it != constTree.pre_order_end(); ++it) {
        result.push_back(it->value.value());
    }

    EXPECT_EQ(result, PREORDER);
}

TEST_F(IteratorTest, TestStandardAlgorithms) {
    auto it = std::find_if(
        tree.pre_order_begin(), tree.pre_order_end(),
        [](const vpr::TreeNode<std::string>& node) {
            return node.value.value() == "6";
        }
    );

    EXPECT_NE(it, tree.pre_order_end());
    EXPECT_EQ(it->value.value(), "6");
}


#endif // TREE_TEST_HPP
