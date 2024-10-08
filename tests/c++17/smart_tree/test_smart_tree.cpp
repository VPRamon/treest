#include "smart_tree_test_fixture.hpp"
#include <variant>

class SmartTreeTest : public SmartTreeTestFixture { };


TEST_F(SmartTreeTest, TestVariantNode) {
    smart::Tree<std::variant<int, std::string>> variantTree(42);
    auto& root = variantTree.getRoot();

    size_t child1 = variantTree.addChild(variantTree.getRoot().index(), std::string("Child1"));
    size_t child2 = variantTree.addChild(variantTree.getRoot().index(), 84);

    EXPECT_TRUE(std::holds_alternative<int>(variantTree.getNode(child2).value()));
    EXPECT_TRUE(std::holds_alternative<std::string>(variantTree.getNode(child1).value()));
}