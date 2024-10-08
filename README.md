# VPR Data Structures Library

The **VPR Data Structures Library** is a lightweight and versatile C++ library designed for creating and manipulating various tree and graph data structures. It provides efficient implementations for trees and graphs, along with multiple traversal algorithms. The library is built with modern C++ features, ensuring high performance and ease of integration.

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Getting Started](#getting-started)
- [Library Structure](#library-structure)
  - [Lightweight Implementation](#lightweight-implementation)
  - [Smart Implementation](#smart-implementation)
  - [Templates Namespace](#templates-namespace)
- [Usage Examples](#usage-examples)
  - [Lightweight Tree](#lightweight-tree)
  - [Smart Tree](#smart-tree)
  - [Customizing with Templates](#customizing-with-templates)
- [When to Use Each Implementation](#when-to-use-each-implementation)
- [Building and Running Tests](#building-and-running-tests)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgments](#acknowledgments)

## Features

- **Generic Tree Structures**: Create trees with customizable node types.
- **Traversal Algorithms**: Includes pre-order, post-order, breadth-first, and reverse traversals for trees.
- **Iterator Support**: Provides iterator classes for easy and efficient traversal.
- **Lightweight Implementation**: Minimal overhead, ideal for performance-critical applications.
- **Smart Implementation**: Nodes are aware of their parent tree, enabling node-specific operations.
- **Customizable via Templates**: Use the `templates` namespace to create custom structures.
- **Header-Only Library**: Easy to integrate into existing projects.
- **Modern C++**: Utilizes C++11 features like templates and smart pointers for enhanced performance.

## Requirements

- **C++11** or later (C++17 recommended for full feature support)
- **CMake** 3.10 or later (for building tests)
- **Google Test** (for unit testing)

## Getting Started

Since the library is header-only, you can include the necessary headers directly in your project. To explore the full capabilities, including running tests and examples, follow the instructions below.

## Library Structure

The library is organized into several namespaces and implementations to cater to different use cases and performance requirements.

### Lightweight Implementation

- **Namespace**: `vpr::lightweight`
- **Purpose**: Provides a minimalistic tree implementation with low overhead.
- **Use Case**: Ideal for performance-critical applications where you need efficient tree operations without extra features.

### Smart Implementation

- **Namespace**: `vpr::smart`
- **Purpose**: Extends the lightweight implementation by making nodes aware of their parent tree.
- **Use Case**: Suitable when you need nodes to perform operations like adding children directly, or when node-tree interaction is required.

### Templates Namespace

- **Namespace**: `vpr::templates`
- **Purpose**: Contains base templates for creating customized data structures.
- **Use Case**: Use this namespace when you need to create custom structures tailored to specific requirements not covered by the lightweight or smart implementations.

## Usage Examples

### Lightweight Tree

**Header Files Required**:

```cpp
#include "lightweight_tree_node.hpp"
#include "tree_implementation.hpp"
```

**Example**:

```cpp
#include "lightweight_tree_node.hpp"
#include "tree_implementation.hpp"
#include <iostream>

int main() {
    // Create a tree with root value 1
    vpr::templates::Tree<vpr::templates::LightweightTreeNode<int>> tree(1);

    // Add children to the root node
    size_t child1 = tree.addChild(0, 2);
    size_t child2 = tree.addChild(0, 3);

    // Add a grandchild
    tree.addChild(child1, 4);

    // Traverse the tree using pre-order traversal
    std::cout << "Pre-order traversal:" << std::endl;
    for (auto it = tree.pre_order_begin(); it != tree.pre_order_end(); ++it) {
        std::cout << it->value() << " ";
    }
    // Output: Pre-order traversal:
    //         1 2 4 3

    return 0;
}
```

**Usage Context**:

- Use the lightweight tree when you require high performance and minimal memory overhead.
- Suitable for applications where nodes don't need to interact with the tree directly.

### Smart Tree

**Header Files Required**:

```cpp
#include "smart_tree_node.hpp"
#include "smart_tree.hpp"
```

**Example**:

```cpp
#include "smart_tree.hpp"
#include <iostream>

int main() {
    // Create a smart tree with root value "root"
    vpr::smart::Tree<std::string> tree("root");

    // Add children using node methods
    auto& root = tree.getRoot();
    size_t childIndex1 = root.addChild("child1");
    size_t childIndex2 = root.addChild("child2");

    // Add a grandchild
    auto& child1 = tree.getNode(childIndex1);
    child1.addChild("grandchild1");

    // Traverse the tree recursively
    std::function<void(const vpr::smart::tree::Node<std::string>&)> traverse;
    traverse = [&](const vpr::smart::tree::Node<std::string>& node) {
        std::cout << node.value() << " ";
        for (const auto& childRef : node.getChildren()) {
            traverse(childRef.get());
        }
    };

    std::cout << "Recursive traversal:" << std::endl;
    traverse(root);
    // Output: Recursive traversal:
    //         root child1 grandchild1 child2

    return 0;
}
```

**Usage Context**:

- Use the smart tree when you need nodes to interact with the tree, such as adding children directly from a node.
- Ideal for scenarios where node-level operations are frequent, and convenience is preferred over minimal overhead.

### Customizing with Templates

**Header Files Required**:

```cpp
#include "node.hpp"
#include "tree_template.hpp"
```

**Example**:

Suppose you need a tree where each node keeps track of additional metadata, such as a timestamp.

**Custom Node Class**:

```cpp
#include "node.hpp"
#include <chrono>

template <typename T>
class CustomNode : public vpr::templates::Node<T, std::vector> {
    using Base = vpr::templates::Node<T, std::vector>;

    std::chrono::time_point<std::chrono::system_clock> timestamp_;

public:
    CustomNode(size_t index, T data)
        : Base(index, data), timestamp_(std::chrono::system_clock::now()) {}

    auto getTimestamp() const { return timestamp_; }
};
```

**Custom Tree Class**:

```cpp
#include "tree_template.hpp"

template <typename T>
class CustomTree : public vpr::templates::Tree<CustomNode<T>, std::vector> {
    using Base = vpr::templates::Tree<CustomNode<T>, std::vector>;

public:
    explicit CustomTree(T rootValue) {
        this->emplace_node(0, std::move(rootValue));
    }

    size_t addChild(size_t parentIndex, T value) {
        this->validateIndex(parentIndex);
        size_t id = this->emplace_node(std::move(value));
        this->addEdge(parentIndex, id);
        return id;
    }
};
```

**Usage**:

```cpp
#include <iostream>

int main() {
    CustomTree<std::string> tree("root");

    // Add children
    size_t child1 = tree.addChild(0, "child1");
    size_t child2 = tree.addChild(0, "child2");

    // Access custom node properties
    auto& node = tree.getNode(child1);
    std::cout << "Node value: " << node.value() << std::endl;
    std::cout << "Timestamp: " << std::chrono::system_clock::to_time_t(node.getTimestamp()) << std::endl;

    return 0;
}
```

**Usage Context**:

- Use the templates namespace when you need to create a custom tree or graph structure with specific node properties or behaviors.
- Ideal for applications requiring specialized data structures not provided by the default implementations.

## When to Use Each Implementation

### Lightweight Implementation

- **When to Use**:
  - Performance-critical applications.
  - Memory usage needs to be minimal.
  - Nodes do not need to interact with the tree directly.

- **Advantages**:
  - Minimal overhead.
  - High performance.

- **Disadvantages**:
  - Less convenient for node-level operations.
  - Nodes are not aware of the tree.

### Smart Implementation

- **When to Use**:
  - Applications where nodes need to perform operations like adding children.
  - When node-tree interaction enhances code readability and maintainability.

- **Advantages**:
  - Nodes can interact with the tree.
  - More convenient for complex tree manipulations.

- **Disadvantages**:
  - Slightly more overhead than the lightweight implementation.
  - May not be as performant in tight loops or performance-critical sections.

### Customizing with Templates

- **When to Use**:
  - Specific requirements not met by the provided implementations.
  - Need to extend node functionalities or store additional data.

- **Advantages**:
  - Complete control over the data structure.
  - Can tailor the implementation to fit exact needs.

- **Disadvantages**:
  - Requires more effort to set up.
  - Potential for increased complexity.

## Building and Running Tests

The library includes a comprehensive set of unit tests using Google Test. To build and run the tests:

1. **Clone the repository**:

   ```bash
   git clone https://github.com/YourUsername/YourRepository.git
   cd YourRepository
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

6. **Run the tests**:

   ```bash
   ctest -V
   ```

   You should see output indicating the status of each test case.

## Contributing

Contributions are welcome! If you have ideas for improvements or find bugs, feel free to open an issue or submit a pull request.

### Steps to Contribute

1. **Fork the repository** on GitHub.

2. **Clone your fork**:

   ```bash
   git clone https://github.com/YourUsername/YourRepository.git
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

For any questions or suggestions, feel free to contact the maintainer at [vallespuigramon@gmail.com](mailto:vallespuigramon@gmail.com).

## Acknowledgments

- **Contributors**: Thank you to all contributors who have helped improve this library.
- **Community**: Appreciation to the C++ community for providing resources and inspiration for this project.
