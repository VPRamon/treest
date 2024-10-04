#ifndef DIGRAPH_NODE_HPP
#define DIGRAPH_NODE_HPP

#include "node_impl.hpp"

namespace vpr {

template <typename T>
class DigraphNode : public NodeImpl<T> {
    using Base = NodeImpl<T>;

    std::vector<size_t>& out_edges_;
    std::vector<size_t> in_edges_;

public:

    DigraphNode(size_t index, std::optional<T> v = std::nullopt)
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

} // namespace vpr

#endif // DIGRAPH_NODE_HPP
