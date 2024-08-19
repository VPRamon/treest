#ifndef GENERIC_TREE_HPP
#define GENERIC_TREE_HPP

#include "node.hpp"

#include <cassert>

namespace vpr {

template <typename T, template <typename, typename> class Container>
class GenericTree : public NodeInterface<
                        Container<GenericTree<T, Container>, std::allocator<GenericTree<T, Container>>>,
                        T> {
    using ChildrenType = Container<GenericTree<T, Container>, std::allocator<GenericTree<T, Container>>>;
    using ParentType = NodeInterface<ChildrenType, T>;

public:
    using ParentType::NodeInterface;

};


} // namespace vpr

#endif // GENERIC_TREE_HPP
