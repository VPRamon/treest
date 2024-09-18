#ifndef LIST_TREE_HPP
#define LIST_TREE_HPP

#include "container_node.hpp"
#include <list>

namespace vpr {


template <typename ChildType, typename Type>
using ListNode = vpr::NodeInterface<std::list<ChildType>, Type>;

template <typename T>
class ListTree;

template <typename T>
class ListTree : public vpr::Tree<T, std::list<ListTree<T>>> {
    public:
        using vpr::Tree<T, std::list<ListTree<T>>>::Tree;
};

}

#endif
