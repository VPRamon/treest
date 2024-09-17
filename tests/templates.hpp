#include "generic_node.hpp"

using namespace vpr;

#define DECLARE_ROOTED_TREE(root, value_1, value_2) \
    ContainerType root;                             \
    {                                               \
        ContainerType leaf_1(value_1);              \
        ContainerType leaf_2(value_2);              \
        root = ContainerType({leaf_1, leaf_2});     \
    }

template <typename ContainerType, typename T>
void TEST_LEAF(T value) {
    ContainerType leaf(value);
    ASSERT_TRUE(leaf.isLeaf() && leaf.hasValue());
    ASSERT_EQ(leaf.value(), value);
}

template <typename Node, typename T>
void ASSERT_VARIANT(const Node& node, T expected_value) {
    ASSERT_TRUE(node.hasValue());
    ASSERT_EQ(*std::get_if<T>(&(node.value())), expected_value);
}

template <typename ContainerType, typename T, typename AssertFunc>
void TEST_TREE_COMMON(std::array<T, 3> values, AssertFunc assertFunc, bool isConst = false) {
    DECLARE_ROOTED_TREE(subtree, values[0], values[1]);
    DECLARE_ROOTED_TREE(root, subtree, values[2]);

    auto& tree_root = isConst ? static_cast<const ContainerType&>(root) : root;
    unsigned int i = 0;

    for (auto& node : tree_root) {
        if (!node.isLeaf()) continue;
        ASSERT_TRUE(node.hasValue());
        assertFunc(node, values[i++]);
    }
}

template <typename ContainerType, typename T>
void TEST_ITERATE_TREE(std::array<T, 3> values) {
    TEST_TREE_COMMON<ContainerType>(values, [](auto& node, const T& value) {
        ASSERT_EQ(node.value(), value);
    });
}

template <typename ContainerType, typename T>
void TEST_ITERATE_VARIANT_TREE(std::array<T, 3> values) {
    TEST_TREE_COMMON<ContainerType>(values, [](auto& node, const T& value) {
        ASSERT_VARIANT(node, value);
    });
}

template <typename ContainerType, typename T>
void TEST_CONST_ITERATE_TREE(std::array<T, 3> values) {
    TEST_TREE_COMMON<ContainerType>(values, [](auto& node, const T& value) {
        ASSERT_EQ(node.value(), value);
    }, true);
}

template <typename ContainerType, typename T>
void TEST_CONST_ITERATE_VARIANT_TREE(std::array<T, 3> values) {
    TEST_TREE_COMMON<ContainerType>(values, [](auto& node, const T& value) {
        ASSERT_VARIANT(node, value);
    }, true);
}

template <typename ContainerType, typename T>
void TEST_ROOTED_TREE(T value_1, T value_2) {
    DECLARE_ROOTED_TREE(root, value_1, value_2);

    ASSERT_FALSE(root.isLeaf() || root.hasValue());

    auto it = root.begin();
    ASSERT_FALSE(it->isLeaf() || it->hasValue());

    ++it;
    ASSERT_TRUE(it->isLeaf() && it->hasValue());
    ASSERT_EQ(it->value(), value_1);

    ++it;
    ASSERT_TRUE(it->isLeaf() && it->hasValue());
    ASSERT_EQ(it->value(), value_2);
}

template <typename ContainerType, typename T, typename U>
void TEST_VARIANT_LEAF(T value_1, U value_2) {
    DECLARE_ROOTED_TREE(root, value_1, value_2);

    auto it = root.begin();
    ASSERT_FALSE(it->isLeaf() || it->hasValue());

    ++it;
    ASSERT_TRUE(it->isLeaf());
    ASSERT_VARIANT(*it, value_1);

    ++it;
    ASSERT_TRUE(it->isLeaf());
    ASSERT_VARIANT(*it, value_2);
}

template <typename ContainerType, typename T>
void TEST_OUT_TREE(T value_1, T value_2, T value_3, const std::string& expected) {
    DECLARE_ROOTED_TREE(subtree, value_1, value_2);
    DECLARE_ROOTED_TREE(root, subtree, value_3);

    std::ostringstream oss;
    oss << root;

    ASSERT_EQ(oss.str(), expected);
}
