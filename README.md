# Treest

This project implements a reusable, generic tree structure in C++ using `std::variant`. The tree structure can store either leaf nodes of a specified type or subtrees, making it flexible for various hierarchical data representations.

## Features

- **Generic Tree Structure**: The tree supports storing any data type as leaf nodes and allows building complex tree structures.
- **C++ Standard Library**: Utilizes modern C++ features such as `std::variant`, `std::unique_ptr`, and `std::list`.
- **Header-Only Library**: The tree is implemented as a header-only library, making it easy to integrate into other projects.
- **Unit Testing**: The project includes unit tests written using Google Test.


## Requirements

- C++17 or later
- CMake 3.10 or later
- Google Test (included as a submodule)

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
