#include "iterator_fixture.h"

TEST_F(IteratorFixture, Iterate1Level) {
    tree.addChild(1);
    tree.addChild(2);

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_DFS(tree, expected);
}

TEST_F(IteratorFixture, Iterate2Level) {
    tree.addChild(1);
    Tree subTree;
    subTree.addChild(2);
    subTree.addChild(3);
    tree.addChild(subTree);

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_DFS(tree, expected);
}

TEST_F(IteratorFixture, ManualIterator) {
    tree.addChild(1);
    Tree subTree;
    subTree.addChild(2);
    subTree.addChild(3);
    tree.addChild(subTree);

    auto it = tree.begin();
    ASSERT_TRUE(Tree::isLeaf(*it));
    ASSERT_EQ(Tree::getLeaf(*it), 1);

    it++;
    ASSERT_TRUE(Tree::isSubTree(*it));

    it++;
    ASSERT_TRUE(Tree::isLeaf(*it));
    ASSERT_EQ(Tree::getLeaf(*it), 2);

    it++;
    ASSERT_TRUE(Tree::isLeaf(*it));
    ASSERT_EQ(Tree::getLeaf(*it), 3);

    it++;
    ASSERT_EQ(it, tree.end());
}