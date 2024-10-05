# VPR Data Structures Library

The **VPR Data Structures Library** is a lightweight and versatile C++ library for creating and manipulating various graph and tree data structures. It provides implementations for directed graphs, undirected graphs, trees, and offers several traversal algorithms. The library is designed with modern C++ features, ensuring efficiency and ease of integration.

## Features

- **Generic Graph and Tree Structures**: Supports creating directed graphs, undirected graphs, and trees with customizable node types.
- **Traversal Algorithms**: Includes pre-order, post-order, breadth-first, and reverse traversals for trees.
- **Iterator Support**: Provides iterator classes for easy and efficient traversal of data structures.
- **Header-Only Library**: Implemented as a header-only library for simple integration into existing projects.
- **Modern C++**: Utilizes C++17 and C++17 features like templates, `std::optional`, and `constexpr` for enhanced performance and usability.

## Requirements

- **C++17** or later (C++17 recommended for full feature support)
- **CMake** 3.10 or later (for building tests)
- **Google Test** (included as a submodule for unit testing)

## Building the Project

The library is header-only, so you can include it directly in your project without building. However, if you want to run the unit tests or examples, follow these steps:

1. **Clone the repository**:

   ```bash
   git clone git@github.com:VPRamon/treest.git
   cd treest
   ```

2. **Initialize submodules** (if any):

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

## Usage Examples

### Creating a Tree and Adding Nodes

```cpp
#include "tree.hpp"
#include <iostream>

int main() {
    vpr::Tree<int> tree(1); // Create a tree with root value 1

    // Add children to the root node
    size_t child1 = tree.addChild(0, 2);
    size_t child2 = tree.addChild(0, 3);

    // Add a grandchild
    tree.addChild(child1, 4);

    // Traverse the tree using pre-order traversal
    for (const auto& node : tree) {
        std::cout << node.value().value_or(-1) << " ";
    }
    // Output: 1 2 4 3

    return 0;
}
```

### Working with Directed Graphs

```cpp
#include "digraph.hpp"
#include <iostream>

int main() {
    vpr::Digraph<int> graph;

    // Add nodes to the graph
    size_t nodeA = graph.addNode(1);
    size_t nodeB = graph.addNode(2);
    size_t nodeC = graph.addNode(3);

    // Add directed edges
    graph.addEdge(nodeA, nodeB);
    graph.addEdge(nodeB, nodeC);

    // Iterate over the nodes
    for (const auto& node : graph) {
        std::cout << "Node " << node.value().value_or(-1) << " has edges to: ";
        for (auto edge : node.outEdges()) {
            std::cout << graph.getNode(edge).value().value_or(-1) << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
```

### Using Iterators for Traversal

```cpp
#include "tree.hpp"
#include <iostream>

int main() {
    vpr::Tree<std::string> tree("root");

    // Add children
    size_t child1 = tree.addChild(0, "child1");
    size_t child2 = tree.addChild(0, "child2");
    tree.addChild(child1, "grandchild1");

    // Pre-order traversal
    std::cout << "Pre-order traversal:" << std::endl;
    for (auto it = tree.pre_order_begin(); it != tree.pre_order_end(); ++it) {
        std::cout << it->value().value_or("nil") << std::endl;
    }

    // Post-order traversal
    std::cout << "\nPost-order traversal:" << std::endl;
    for (auto it = tree.post_order_begin(); it != tree.post_order_end(); ++it) {
        std::cout << it->value().value_or("nil") << std::endl;
    }

    return 0;
}
```

## Documentation

### Graph Structures

- **vpr::Graph<T>**: Represents an undirected graph where edges are bidirectional.
- **vpr::Digraph<T>**: Represents a directed graph with edges having a direction from one node to another.

### Tree Structure

- **vpr::Tree<T>**: Represents a tree data structure with nodes that can have multiple children but only one parent.

#### Key Methods for `Tree<T>`:

- **addChild(size_t parentIndex, std::optional<T> value = std::nullopt)**: Adds a child to the specified parent node.
- **getRoot() const**: Retrieves the root node of the tree.
- **Traversal Methods**:
  - **pre_order_begin() / pre_order_end()**: Iterators for pre-order traversal.
  - **post_order_begin() / post_order_end()**: Iterators for post-order traversal.
  - **bfs_begin() / bfs_end()**: Iterators for breadth-first traversal.

### Node Classes

- **vpr::graph::Node<T>**: Node class for undirected graphs.
- **vpr::digraph::Node<T>**: Node class for directed graphs, with methods to access incoming and outgoing edges.
- **vpr::tree::Node<T>**: Node class for trees, with methods to access parent and child nodes.

### Traversal Iterators

The library provides iterator classes to traverse trees using different algorithms:

- **PreOrderTraversal**: Traverse nodes in pre-order.
- **PostOrderTraversal**: Traverse nodes in post-order.
- **BFSTraversal**: Traverse nodes in breadth-first order.
- **ReverseBFSTraversal**: Traverse nodes in reverse breadth-first order.
- **ReversePreOrderTraversal**: Traverse nodes in reverse pre-order.

## Contributing

Contributions are welcome! If you have ideas for improvements or find bugs, feel free to open an issue or submit a pull request.

### Steps to Contribute

1. **Fork the repository** on GitHub.
2. **Clone your fork**:

   ```bash
   git clone git@github.com:VPRamon/treest.git
   ```

3. **Create a new branch** for your feature or bugfix:

   ```bash
   git checkout -b feature-or-bugfix-name
   ```

4. **Make your changes** and **commit** them with descriptive messages.

5. **Push to your fork**:

   ```bash
   git push origin feature-or-bugfix-name
   ```

6. **Create a pull request** on the original repository.

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## Contact

For any questions or suggestions, feel free to contact the maintainer at [vallespuigramon@gmail.co](mailto:vallespuigramon@gmail.co).

---

Thank you for using the VPR Data Structures Library! I hope it serves your needs for efficient and flexible data structure implementations in C++.
