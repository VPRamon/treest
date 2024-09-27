# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [x.y.z]

### Added

* Creation of basic tree with DFS iterator
* Const-correctness support in TreeIterator by templating it on node pointer type (NodePtr).
* Type aliases (e.g., ChildrenContainer) to improve code readability.

### Changed

* Return type of getChildren() method from const C`hildrenType&` to const `U&` and `U&` for `non-const` versions.
* Replaced `node->getChildren()->` with `node->getChildren()`. throughout the code to access the container correctly.
* Modified `operator<<` overload in NodeInterface to remove unnecessary dereferencing

### Deprecated

### Removed

* Redundant `std::optional` usage for children_, replaced with std::unique_ptr management.

### Fixed

* Missing const child access in BinaryNode
* Incorrect dereferencing of std::unique_ptr in ArrayTree methods.
* Compilation errors by properly handling nullptr checks for children_ in various methods.
* Const-correctness violations in TreeIterator when pushing const nodes into a stack.

### Security

## [2.0.0]

### Added

* Introduction of Friendly Node and Tree Definitions

    Several new typedefs and class templates were introduced for specialized tree structures:

    ArrayNode and ArrayTree: Introduced a template for nodes that use std::array for storing children, as well as ArrayTree to represent trees where nodes have a fixed number of children.
        New functionality: child<Index>() method for accessing children based on an index, with bounds checking using static_assert.
    BinaryNode and BinaryTree: Introduced for binary trees, allowing easy access to left() and right() children through specific methods.
        Simplifies binary tree traversal and manipulation with clear child access methods (left(), right()).
    DequeNode and DequeTree: Added to represent trees where children are stored in a std::deque.
    VectorNode and VectorTree: Added to represent trees where children are stored in a std::vector, allowing a dynamic number of children.
    ListNode and ListTree: Similar to VectorNode, but uses std::list for managing children, offering different performance characteristics.

### Changed

* Modify access operators for Node values.
* Updated NodeInterface

    Constructor Overloads: The new NodeInterface class includes multiple constructors that accept either data (NodeType), children (ChildrenType), or both.
    Children Access: The methods getChildren() and value() are more robust with added assertions to ensure correct access.
    Overloaded Stream Operator: The operator<< overload is included to print nodes and their children in a user-friendly format.

* Enhanced Flexibility with Template-Based Tree Structures

    The updated README now reflects how the library allows users to define tree structures using different container types, such as std::array, std::deque, std::vector, and std::list, providing a lot of flexibility in how trees are structured and used.

### Deprecated

### Removed

### Fixed
* Internal Adjustments in Tree Copying and Assignment

    The Tree class now handles copying and assignment, making deep copies of trees by cloning both the data and children, ensuring that nodes are managed correctly when trees are copied.

* Missing Headers

### Security


## [1.0.0]

### Added

* Creation of basic tree with DFS iterator

### Changed

### Deprecated

### Removed

### Fixed

### Security
