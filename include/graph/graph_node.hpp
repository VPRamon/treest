#ifndef GRAPH_NODE_HPP
#define GRAPH_NODE_HPP

#include "node_impl.hpp"

namespace vpr {
namespace graph {

template <typename T>
class Node : public NodeImpl<T> {
    using Base = NodeImpl<T>;

public:

    using Base::NodeImpl;

    virtual size_t degree() const override { return Base::degree(); }

    virtual const std::vector<size_t>& edges() const { return Base::edges(); }

    virtual void addEdge(size_t fromIndex) { Base::addEdge(fromIndex); }

    virtual bool isolated() const { return Base::isolated(); }

};

} // namespace graph
} // namespace vpr

#endif // GRAPH_NODE_HPP
