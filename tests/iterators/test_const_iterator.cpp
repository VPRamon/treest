#include "iterator_fixture.h"

TEST_F(IteratorFixture, ConstIterate1Level) {
    tree.addChild(1);
    tree.addChild(2);

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_CONST_DFS(tree, expected);
}

TEST_F(IteratorFixture, ConstIterate2Level) {
    tree.addChild(1);
    Tree subTree;
    subTree.addChild(2);
    subTree.addChild(3);
    tree.addChild(subTree);

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_CONST_DFS(tree, expected);
}

TEST_F(IteratorFixture, ManualConstIterator) {
    tree.addChild(1);
    Tree subTree;
    subTree.addChild(2);
    subTree.addChild(3);
    tree.addChild(subTree);

    auto it = tree.begin();

    ASSERT_LEAF(it++, 1);
    ASSERT_SUBTREE(it++);
    ASSERT_LEAF(it++, 2);
    ASSERT_LEAF(it++, 3);
    ASSERT_EQ(it, tree.end());
}
