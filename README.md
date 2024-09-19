# Treest

The Treest Library is a lightweight and versatile C++ library for creating and manipulating tree data structures. It supports both leaf and subtree nodes, allowing for hierarchical data representation. The library also provide a DFS-preorder iterator for traversing tree, including both mutable and immutable tree traversal.

## Features

- **Generic Tree Structure**: Supports storing any data type as leaf and subtree nodes, allowing for complex tree structures.
- **C++ Standard Library**: Utilizes modern C++ features such as `std::vector`, `std::list`, `std::array`, `std::deque`, and`std::unique_ptr` for memory management.
- **Header-Only Library**: Implemented as a header-only library, making integration into other projects simple and efficient.
- **Unit Testing**: Includes unit tests written using Google Test to ensure reliability.

## Requirements

- C++20 or later
- CMake 3.10 or later
- Google Test (included as a submodule for testing)

## Building the Project

1. **Clone the repository**:
    ```bash
    git clone https://github.com/VPRamon/treest.git
    cd treest
    ```

2. **Initialize the Google Test submodule**:
    ```bash
    git submodule update --init --recursive
    ```

3. **Create a build directory**:
    ```bash
    mkdir build
    cd build
    ```

4. **Run CMake to configure the project**:
    ```bash
    cmake ..
    ```

5. **Build the project**:
    ```bash
    cmake --build .
    ```

## Running Tests

After building the project, you can run the unit tests using CTest:

```bash
ctest -V
```

## Usage Example

### With Leafs only

```cpp
#include "tree.hpp"

int main() {

    VectorTree<int> leaf(1);

    assert(leaf.isLeaf() == true);
    assert(leaf.hasValue() == true);
    assert(leaf.value() == 1);

    std::cout << leaf << std::endl;

    return 0;
}

// output: "{1}"
```


### With Leafs and Node types

```cpp
#include <string>
#include "tree.hpp"

int main() {

    VectorTree<std::string> leaf("This is a leaf");
    VectorTree<std::string> root("This is the rooot", leaf);

    assert(root.isLeaf() == false);
    assert(root.hasValue() == true);
    assert(root.value() == "This is the rooot");

    std::cout << root << std::endl;
}

// output: {"This is the rooot"{"This is a leaf"}"}

```

### Iterator

```cpp
#include <string>
#include "tree.hpp"

int main() {
    using Tree = VectorTree<std::string> 
    Tree leaf_A("A");
    Tree leaf_B("B");
    Tree tree("ROOT", {leaf_A, leaf_B});

    // const iterator
    for (const Tree::Node& node: tree) {
        std::cout << node <<  " ";
    }

    // mutable iterator
    for (auto& node : tree_root) {
        node += "x"
        std::cout << node <<  " ";
    }
}
// output: "ROOT A B"
// output: "ROOTx Ax Bx"

```

## Documentation

The library provides several flexible tree data structures through the `NodeInterface` and `Tree` class templates, which allow for various container types as children. The library also includes specialized types for common tree structures, such as binary trees and array-based trees.

### `NodeInterface` Class Template

The `NodeInterface` class template represents a generic node that can either store a value (`NodeType`) or children (`ChildrenType`). This allows nodes to act as either leaf nodes (with data) or internal nodes (with children).

#### Template Parameters

- **`ChildrenType`**: The type representing the node’s children (e.g., `std::array`, `std::deque`, `std::vector`, etc.).
- **`NodeType`**: The type of data stored in the node (e.g., `int`, `std::string`, etc.).

#### Main Methods

```cpp
// Constructor: Initializes a node with optional data and children.
NodeInterface(const std::optional<NodeType>& data, std::optional<ChildrenType> children);

// Constructor: Initializes a node with optional data only.
NodeInterface(const std::optional<NodeType>& data);

// Constructor: Initializes a node with optional children only.
NodeInterface(std::optional<ChildrenType> children);
```

### Specialized Node and Tree Types

The library includes friendly typedefs and classes for commonly used tree structures. These types make it easier to work with specific kinds of trees, such as binary trees, array trees, and trees with various container types.

#### `ArrayNode` and `ArrayTree`

`ArrayNode` is a node with children stored in a `std::array`, and `ArrayTree` represents a tree structure where each node has a fixed number of children.

```cpp
template <typename T, std::size_t N>
class ArrayTree : public vpr::Tree<T, std::array<ArrayTree<T, N>, N>> {
public:
    // Access child at a specific index
    template <std::size_t Index>
    ArrayTree& child();
    
    template <std::size_t Index>
    const ArrayTree& child() const;
};
```

#### `BinaryNode` and `BinaryTree`

`BinaryNode` is a node specifically designed for binary trees, with exactly two children (left and right). `BinaryTree` is a binary tree implementation.

```cpp
template <typename T>
class BinaryTree : public ArrayTree<T, 2> {
public:
    BinaryTree& left(); // Access the left child
    BinaryTree& right(); // Access the right child

    const BinaryTree& left() const; // Access the left child (const version)
    const BinaryTree& right() const; // Access the right child (const version)
};
```

#### `DequeNode` and `DequeTree`

`DequeNode` is a node whose children are stored in a `std::deque`, and `DequeTree` is a tree structure using this node type.

```cpp
template <typename T>
class DequeTree : public vpr::Tree<T, std::deque<DequeTree<T>>> {
    // Inherits functionality from vpr::Tree
};
```

#### `VectorNode` and `VectorTree`

`VectorNode` uses a `std::vector` to store children, allowing for a dynamic number of children. `VectorTree` is a tree implementation using this structure.

```cpp
template <typename T>
class VectorTree : public vpr::Tree<T, std::vector<VectorTree<T>>> {
    // Inherits functionality from vpr::Tree
};
```

#### `ListNode` and `ListTree`

`ListNode` stores children in a `std::list`, making it suitable for tree structures where efficient insertions and deletions are important. `ListTree` is the corresponding tree type.

```cpp
template <typename T>
class ListTree : public vpr::Tree<T, std::list<ListTree<T>>> {
    // Inherits functionality from vpr::Tree
};
```

### Example Usage

Here are some practical examples of how to use the provided tree types:

#### Binary Tree Example

```cpp
BinaryTree<int> root(1);
root.left() = BinaryTree<int>(2);
root.right() = BinaryTree<int>(3);

std::cout << root << std::endl; // Output: 1[2, 3]
```

#### Array Tree Example

```cpp
ArrayTree<int, 3> root(10);
root.child<0>() = ArrayTree<int, 3>(20);
root.child<1>() = ArrayTree<int, 3>(30);
root.child<2>() = ArrayTree<int, 3>(40);

std::cout << root << std::endl; // Output: 10[20, 30, 40]
```

#### Deque Tree Example

```cpp
DequeTree<int> root(10);
root.getChildren().emplace_back(20);
root.getChildren().emplace_back(30);

std::cout << root << std::endl; // Output: 10[20, 30]
```

### Key Features

- **Leaf Nodes**: Nodes without children can be detected using the `isLeaf()` method.
- **Subtree Nodes**: Internal nodes with children can be accessed via container-based member functions like `getChildren()`.
- **Pre-order Traversal**: The `TreeIterator` class enables pre-order traversal for both mutable and constant trees.



## Contributing

Contributions are welcome! Feel free to fork the repository and submit a pull request. For major changes, please open an issue first to discuss what should be changed.

## License

This project is licensed under the GPL License - see the [LICENSE](https://github.com/VPRamon/treest/blob/main/LICENSE) file for details.
