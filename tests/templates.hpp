#include "generic_tree.hpp"

using namespace vpr;

#define DECLARE_ROOTED_TREE(root, value_1, value_2) \
    ContainerType root;                             \
    {                                               \
        ContainerType leaf_1(value_1);              \
        ContainerType leaf_2(value_2);              \
        root = ContainerType({leaf_1, leaf_2});     \
    }                                               \

template <typename ContainerType, typename T>
void TEST_LEAF(T value) {
    ContainerType leaf(value);
    ASSERT_TRUE(leaf.isLeaf());
    ASSERT_TRUE(leaf.hasValue());
    ASSERT_EQ(leaf.value(), value);
}

template <typename ContainerType, typename T>
void TEST_ROOTED_TREE(T value_1, T value_2) {
    DECLARE_ROOTED_TREE(root, value_1, value_2)

    ASSERT_FALSE(root.isLeaf());
    ASSERT_FALSE(root.hasValue());

    auto it = root.begin();
    ASSERT_FALSE(it->isLeaf());
    ASSERT_FALSE(it->hasValue());

    it++;
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), value_1);

    it++;
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(it->value(), value_2);
}

template <typename ContainerType, typename T, typename U>
void TEST_VARIANT_LEAF(T value_1, U value_2) {
    DECLARE_ROOTED_TREE(root, value_1, value_2)

    auto it = root.begin();
    ASSERT_FALSE(it->isLeaf());
    ASSERT_FALSE(it->hasValue());

    it++;
    ASSERT_TRUE(it->isLeaf());
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(std::get_if<U>(&(it->value())), nullptr);
    ASSERT_EQ(*std::get_if<T>(&(it->value())), value_1);

    it++;
    ASSERT_TRUE(it->isLeaf());
    ASSERT_TRUE(it->hasValue());
    ASSERT_EQ(std::get_if<T>(&(it->value())), nullptr);
    ASSERT_EQ(*std::get_if<U>(&(it->value())), value_2);
}

template <typename ContainerType, typename T>
void TEST_OUT_TREE(T value_1, T value_2, T value_3, std::string expected) {
    DECLARE_ROOTED_TREE(subtree, value_1, value_2)
    DECLARE_ROOTED_TREE(root, subtree, value_3)

    std::ostringstream oss1;
    oss1 << root;

    std::string str_1 = std::to_string(value_1);
    std::string str_2 = std::to_string(value_2);
    std::string str_3 = std::to_string(value_3);
    ASSERT_EQ(oss1.str(), expected);
}

template <typename ContainerType, typename T>
void TEST_ITERATE_TREE(std::array<T, 3> values) {
    DECLARE_ROOTED_TREE(subtree, values[0], values[1])
    DECLARE_ROOTED_TREE(root, subtree, values[2])

    using Node = typename ContainerType::Node;

    // TODO assert number of childs
    unsigned int i = 0;
    for (Node& node : root) {
        if(!node.isLeaf())
            continue;

        ASSERT_TRUE(node.hasValue());
        ASSERT_EQ(node.value(), values[i]);
        i++;
    }
}

template <typename ContainerType, typename T>
void TEST_CONST_ITERATE_TREE(std::array<T, 3> values) {
    DECLARE_ROOTED_TREE(subtree, values[0], values[1])
    DECLARE_ROOTED_TREE(root, subtree, values[2])

    using Node = typename ContainerType::Node;

    const ContainerType& const_root = root;

    // TODO assert number of childs
    unsigned int i = 0;
    for (const Node& node : const_root) {
        if(!node.isLeaf())
            continue;

        ASSERT_TRUE(node.hasValue());
        ASSERT_EQ(node.value(), values[i]);
        i++;
    }
}
