#include "iterator_fixture.h"

TEST_F(IteratorFixture, ConstIterate1Level) {
    tree.addChild(1);
    tree.addChild(2);

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_CONST_DFS(tree, expected);
}

TEST_F(IteratorFixture, ConstIterate2Level) {
    tree.addChild(1);
    auto subTree = std::make_unique<Tree>();
    subTree->addChild(2);
    subTree->addChild(3);
    tree.addChild(std::move(subTree));

    constexpr int expected = 1; // increments as we traverse the tree
    ASSERT_CONST_DFS(tree, expected);
}

TEST_F(IteratorFixture, ManualConstIterator) {
    tree.addChild(1);
    auto subTree = std::make_unique<Tree>();
    subTree->addChild(2);
    subTree->addChild(3);
    tree.addChild(std::move(subTree));

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
