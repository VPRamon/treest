#include "iterator_fixture.h"


TEST_F(IteratorFixture, ConstIterate1Level) {
    tree.addChild(1);
    tree.addChild(2);

    traverseTreeConst(tree);
}

TEST_F(IteratorFixture, ConstIterate2Level) {
    tree.addChild(1);
    auto subTree = std::make_unique<Tree>();
    subTree->addChild(3);
    subTree->addChild(4);
    tree.addChild(std::move(subTree));

    traverseTreeConst(tree);
}
