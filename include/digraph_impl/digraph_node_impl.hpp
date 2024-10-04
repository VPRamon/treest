#ifndef DIGRAPH_NODE_IMPL_HPP
#define DIGRAPH_NODE_IMPL_HPP

#include "node_impl.hpp"

namespace vpr {

template <typename U> class GraphImpl;

namespace digraph_impl {

template <typename T>
class Node : public NodeImpl<T> {
    using Base = NodeImpl<T>;
    friend GraphImpl<Node<T>>;

    std::vector<size_t>& out_edges_;
    std::vector<size_t> in_edges_;

public:

    Node(size_t index, std::optional<T> v = std::nullopt)
        : Base(index, v), out_edges_(Base::edges_), in_edges_()
    {}

    const std::vector<size_t>& inEdges()  const { return in_edges_;  }
    const std::vector<size_t>& outEdges() const { return out_edges_; }

    size_t inDegree() const { return inEdges().size(); }
    size_t outDegree() const { return outEdges().size(); }
    size_t totalDegree() const { return inDegree() + outDegree(); }


    void addInEdge(size_t fromIndex) { in_edges_.push_back(fromIndex); }
    void addOutEdge(size_t fromIndex) { out_edges_.push_back(fromIndex); }

    bool isolated() const { return inEdges().empty() && outEdges().empty(); }

};

} // namespace digraph_impl
} // namespace vpr

#endif // DIGRAPH_NODE_HPP
