# Binary Search Tree Implementation in C++

This project provides a C++ implementation of a templated Binary Search Tree (BST) data structure. The implementation
supports insertion, deletion, searching, and utility functions for generating a detailed string representation of the
tree's structure and metrics.

## Table of Contents

- [Features](#features)
- [API Documentation](#api-documentation)
- [Example Usage](#example-usage)
- [Installation](#installation)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Templated Implementation:** Works with any data type.
- **Flexible Insertion:** Supports insertion with a custom comparator for non-arithmetic types. Defaults to arithmetic
  comparison when applicable.
- **Deletion:** Remove nodes using standard BST deletion methods.
- **Search:** Find elements using either default arithmetic or custom comparison functions.
- **Utility Functions:**
    - Retrieve the tree’s size and height.
    - Generate a detailed string representation including metrics such as log2(size), size-to-height ratio, and more.
- **Memory Management:** Automatically deallocates all nodes when the tree is destroyed.

## API Documentation

### Class: `BinSearTree<T>`

#### Template Parameters:

- `T`: The type of data stored in the tree.

#### Public Methods

##### Constructors:

- `BinSearTree()`: Constructs an empty Binary Search Tree.

##### Destructor:

- `~BinSearTree()`: Automatically deallocates all nodes in the tree.

##### Tree Properties:

- `size_t get_size() const`: Returns the number of nodes in the tree.
- `size_t get_height() const`: Returns the height of the tree.
- `bool is_empty() const`: Checks whether the tree is empty.

##### Insertion:

- `void push(T data, bool (*cmp_lgreater)(T, T) = nullptr)`: Inserts a new node with the given `data` into the tree. An
  optional custom comparator can be provided.

##### Deletion:

- `void pop(Node *node)`: Removes the specified node from the tree.
- `void erase()`: Deletes all nodes, effectively clearing the tree.

##### Search:

- `Node* find(T data, bool (*cmp_lgreater)(T, T) = nullptr, bool (*cmp_equal)(T, T) = nullptr) const`: Searches for a
  node containing `data` and returns a pointer to it. Custom comparator functions for ordering and equality can be
  provided.

##### Visualization:

- `std::string to_str(unsigned int limit = 0, std::string (*fun_str)(T) = nullptr) const`: Returns a string
  representation of the tree. This representation includes metrics such as size, height, and ratios. The optional
  `limit` parameter can restrict the depth of the traversal, and a custom function can be provided to convert node data
  to a string.

## Example Usage

```cpp
#include "BST.h"
#include <iostream>
#include <string>

// Optional: Custom function to convert node data to string
std::string int_to_string(int data) {
    return std::to_string(data);
}

int main() {
    // Create an instance of the Binary Search Tree
    BST::BinSearTree<int> tree;

    // Insert elements into the tree
    tree.push(50);
    tree.push(30);
    tree.push(70);
    tree.push(20);
    tree.push(40);
    tree.push(60);
    tree.push(80);

    // Output the tree structure and metrics
    std::cout << tree.to_str(10, int_to_string) << std::endl;

    // Search for a node with value 40
    BST::BinSearTree<int>::Node* found = tree.find(40);
    if (found) {
        std::cout << "Found: " << found->data << std::endl;
    } else {
        std::cout << "Value not found." << std::endl;
    }

    // Example: Remove the found node
    tree.pop(found);
    std::cout << "After removal:" << std::endl;
    std::cout << tree.to_str(10, int_to_string) << std::endl;

    return 0;
}
```

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/nonofare/Binary_Search_Tree.git
   ```

2. **Include the `BST.h` file in your project.**

3. **Compile your project with a compiler that supports C++17 or later.**

## Contributing

Please open an issue or submit a pull request for any improvements or bug fixes.

## License

This project is licensed under the MIT License. See the LICENSE file for details.