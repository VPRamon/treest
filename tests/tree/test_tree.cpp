#ifndef TREE_TEST_HPP
#define TREE_TEST_HPP

#include "test_fixture.hpp"

#include "tree_variant.hpp"

class TreeTest : public TestFixture { };

TEST_F(TreeTest, TestTreeInitialization) {
    EXPECT_EQ(tree.size(), 7); // Root + 3 children + 5 grandchildren + initial reserve
    EXPECT_EQ(tree.getRoot().value(), "0");
}

TEST_F(TreeTest, TestAddChild) {
    size_t newChild = tree.addChild(tree.getRoot().index(), "7");
    EXPECT_EQ(tree.size(), 8);
    EXPECT_EQ(tree.getNode(newChild).value(), "7");
}

TEST_F(TreeTest, TestGetNode) {
    EXPECT_EQ(tree.getNode(0).value(), "0");
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
}

TEST_F(TreeTest, TestNodeProperties) {
    auto& root = tree.getRoot();
    EXPECT_TRUE(root.isRoot());
    EXPECT_FALSE(root.isLeaf());
    EXPECT_EQ(root.nChildren(), 2);

    auto& child1 = tree.getNode(1);
    EXPECT_FALSE(child1.isRoot());
    EXPECT_FALSE(child1.isLeaf());
    EXPECT_EQ(child1.nChildren(), 2);

    auto& grandchild1 = tree.getNode(4);
    EXPECT_FALSE(grandchild1.isRoot());
    EXPECT_TRUE(grandchild1.isLeaf());
    EXPECT_EQ(grandchild1.nChildren(), 0);
}

TEST_F(TreeTest, TestGetChildren) {
    auto& child1 = tree.getNode(1);
    auto children = child1.getChildren();
    EXPECT_EQ(children.size(), 2);
    //EXPECT_EQ(children[0].get().value(), "3");
    //EXPECT_EQ(children[1].get().value(), "4");
}

TEST_F(TreeTest, TestExceptionSafety) {
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
    //EXPECT_THROW(tree.getRoot().getChild(-1), std::out_of_range);
    //EXPECT_THROW(tree.getRoot().getChild(100), std::out_of_range);
}

TEST_F(TreeTest, TestOperatorOverloading) {
    std::stringstream ss;
    ss << tree;
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(TreeTest, TestVariantNode) {
    vpr::TreeVariant<int, std::string> variantTree(42);
    auto& root = variantTree.getRoot();
    EXPECT_TRUE(root.hasValue());

    size_t child1 = variantTree.addChild(variantTree.getRoot().index(), std::string("Child1"));
    size_t child2 = variantTree.addChild(variantTree.getRoot().index(), 84);

    EXPECT_TRUE(std::holds_alternative<int>(variantTree.getNode(child2).value()));
    EXPECT_TRUE(std::holds_alternative<std::string>(variantTree.getNode(child1).value()));
}

#endif // TREE_TEST_HPP
