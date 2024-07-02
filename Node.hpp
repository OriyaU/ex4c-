//oriya7914@gmail.come

#pragma once
#include <vector>
#include <stdexcept>
#include "Complex.hpp"

template <typename T>
class Node {
public:
    T value;                        // Value stored in the node
    std::vector<Node<T>*> children; // Vector of child nodes

    Node(T val) : value(val) {}     // Constructor to initialize with a value

    T get_value() const {
        return value;
    }

    const std::vector<Node<T>*>& get_children() const {
        return children;
    }

    void add_child(Node<T>* child) {
        children.push_back(child);  // Adds a child node pointer to the vector
    }

    size_t children_count() const {
        return children.size();     // Returns the number of children
    }

  
};
