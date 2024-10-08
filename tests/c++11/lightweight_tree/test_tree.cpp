#ifndef LIGHTWEIGHT_TREE_TEST_HPP
#define LIGHTWEIGHT_TREE_TEST_HPP

#include "test_fixture.hpp"
#include <variant>

class LightweightTreeTest : public TestFixture { };

TEST_F(LightweightTreeTest, TestTreeInitialization) {
    EXPECT_EQ(tree.size(), 7); // Root + 3 children + 5 grandchildren + initial reserve
    EXPECT_EQ(tree.getRoot().value(), "0");
}

TEST_F(LightweightTreeTest, TestAddChild) {
    size_t newChild = tree.addChild(tree.getRoot().index(), "7");
    EXPECT_EQ(tree.size(), 8);
    EXPECT_EQ(tree.getNode(newChild).value(), "7");
}

TEST_F(LightweightTreeTest, TestGetNode) {
    EXPECT_EQ(tree.getNode(0).value(), "0");
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
}

TEST_F(LightweightTreeTest, TestNodeProperties) {
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

TEST_F(LightweightTreeTest, TestGetChildren) {
    auto& child1 = tree.getNode(1);
    EXPECT_EQ(child1.edges().size(), 2);
    //EXPECT_EQ(children[0].get().value(), "3");
    //EXPECT_EQ(children[1].get().value(), "4");
}

TEST_F(LightweightTreeTest, TestExceptionSafety) {
    EXPECT_THROW(tree.getNode(-1), std::out_of_range);
    EXPECT_THROW(tree.getNode(100), std::out_of_range);
    //EXPECT_THROW(tree.getRoot().getChild(-1), std::out_of_range);
    //EXPECT_THROW(tree.getRoot().getChild(100), std::out_of_range);
}

TEST_F(LightweightTreeTest, TestOperatorOverloading) {
    std::stringstream ss;
    ss << tree;
    std::string output = ss.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("0"), std::string::npos);
}

TEST_F(LightweightTreeTest, TestVariantNode) {
    vpr::lightweight::Tree<std::variant<int, std::string>> variantTree(42);
    auto& root = variantTree.getRoot();

    size_t child1 = variantTree.addChild(variantTree.getRoot().index(), std::string("Child1"));
    size_t child2 = variantTree.addChild(variantTree.getRoot().index(), 84);

    EXPECT_TRUE(std::holds_alternative<int>(variantTree.getNode(child2).value()));
    EXPECT_TRUE(std::holds_alternative<std::string>(variantTree.getNode(child1).value()));
}

/*
TEST_F(LightweightTreeTest, TestShouldNotCompile) {
    auto root = tree.getRoot();
    size_t root_child_id = root.getChildren()[0];
    tree.addEdge(root_child_id, root.index());
}
*/

#endif // LIGHTWEIGHT_TREE_TEST_HPP
