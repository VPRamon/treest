#ifndef TREE_HPP
#define TREE_HPP

#include <tree_impl.hpp>

template <typename T>
class Tree : public TreeImpl<T> {

public:

    Tree() = default;
    virtual ~Tree() = default;

};


#endif // TREE_HPP
