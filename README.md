# Treest

The Treest Library is a lightweight and versatile C++ library for creating and manipulating tree data structures. It supports both leaf and subtree nodes, allowing for hierarchical data representation. The library also provide a DFS-preorder iterator for traversing tree, including both mutable and immutable tree traversal.

## Features

- **Generic Tree Structure**: The tree supports storing any data type as leaf  and sub-tree nodes and allows building complex tree structures.
- **C++ Standard Library**: Utilizes modern C++ features such as `std::variant`, `std::unique_ptr`, and `std::list`.
- **Header-Only Library**: The tree is implemented as a header-only library, making it easy to integrate into other projects.
- **Unit Testing**: The project includes unit tests written using Google Test.

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
    Tree<int> tree;
    tree.addChild(1); // Add a leaf
    tree.addChild(2); // Add a leaf

    Tree<int> subTree;
    subTree.addChild(3); // Add a leaf
    tree.addChild(subTree); // Add a subtree

    std::cout << tree.toString() << std::endl;

    return 0;
}

// output: "{1,2,{3}}"
```


### With Leafs and Node types

```cpp
#include <string>
#include "tree.hpp"

int main() {
    Tree<int, std::string> tree("This is a Node");
    tree.addChild(1);
    tree.addChild(2);
}

// output: "This is a Node{1,2}"

```

### Iterator

```cpp
#include <string>
#include "tree.hpp"

int main() {
    using Tree = Tree<int, std::string> 
    Tree tree("This is a Node");
    tree.addChild(1);
    tree.addChild(2);

    // mutable iterator
     for (Tree::Node& node: tree) {
        std::visit(overload{
            [&](const Tree::Leaf& leaf)    { leaf++; }, // increment value of leaf
            [&](const Tree::SubTree& subTree) { std::cout << subTree;  }, // print subTree
        }, node);
    }

    // const iterator
    for (const Tree::Node& node: tree) {
        std::visit(overload{
            [&](const Tree::Leaf& leaf)    { std::cout << leaf; },    // print leaf      
            [&](const Tree::SubTree& tree) { std::cout << subTree; }, // print subTree
        }, node);
    }
}

```


## Documentation

The library consists of two main components: the Tree class and the Iterator class.

### Tree Class

The Tree class represents a generic tree structure that supports both leaf and subtree nodes. The main methods are:
```cpp
   + void addChild(const Leaf& leaf): Adds a leaf node to the tree.
   + void addChild(const SubTree& subtree): Adds a subtree node to the tree.
   + auto begin(), auto end(): Returns iterators for tree traversal.
   + auto cbegin() const, auto cend() const: Returns const iterators for immutable tree traversal.
```

### Iterator Class

The TreeIterator class is used to traverse the Tree. It supports both mutable and const traversal:

```cpp
   + Iterator(Tree<T>& tree, bool end = false): Constructs an iterator, optionally pointing to the end.
   + Iterator& operator++(): Advances the iterator.
   + Node& operator*(): Dereferences the iterator to access the current node.
   + bool operator==(const TreeIterator& other) const: Compares iterators.
   + bool operator!=(const TreeIterator& other) const: Compares iterators.
```

## Contributing

Contributions are welcome! Feel free to fork the repository and submit a pull request. For major changes, please open an issue first to discuss what should be changed.

## License

This project is licensed under the GPL License - see the [LICENSE](https://github.com/VPRamon/treest/blob/main/LICENSE) file for details.
