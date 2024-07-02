//oriya7914@gmail.come

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include "Node.hpp"



// Test for a specific tree structure
TEST_CASE("Testing specific  4 nodes tree structure") {
    Node<int> root(8);
    Tree<int> tree(4); // 4-ary tree

    tree.add_root(root);

    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);
    Node<int> n6(7);
    Node<int> n7(1);
    Node<int> n8(9);

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);
    tree.add_sub_node(root, n3);
    tree.add_sub_node(root, n4);

    tree.add_sub_node(n1, n5);
    tree.add_sub_node(n1, n6);
    tree.add_sub_node(n1, n8);

    tree.add_sub_node(n6, n7);

    std::cout << "Specific Tree structure before traversals:" << std::endl;
    //tree.visualize();

    SUBCASE("Pre-order traversal") {
        std::vector<int> expected_pre_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
        auto it = expected_pre_order.begin();
        std::cout << "Pre-order traversal: ";
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("Post-order traversal") {
        std::vector<int> expected_post_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
        auto it = expected_post_order.begin();
        std::cout << "Post-order traversal: ";
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("In-order traversal") {
        std::vector<int> expected_in_order = {8, 2, 6, 7, 1, 9, 3, 4, 5};
        auto it = expected_in_order.begin();
        std::cout << "In-order traversal: ";
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("Heap order traversal (only for binary trees)") {
        std::vector<int> expected_heap_order = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        auto it = expected_heap_order.begin();
        std::cout << "Heap order traversal: ";
        try {
            for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
                std::cout << (node)->get_value() << " ";
                CHECK((node)->get_value() == *it++);
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Error: " << e.what() << std::endl;
            CHECK(true); // Test passed because an error was expected
        }
        std::cout << std::endl;
    }
    
}
// Helper function to print tree structure (optional)
void print_tree_structure(Node<int>* node, int depth = 0) {
    if (!node)
        return;
    for (int i = 0; i < depth; ++i)
        std::cout << "  ";
    std::cout << node->get_value() << std::endl;
    for (auto child : node->get_children()) {
        print_tree_structure(child, depth + 1);
    }
}



// Test for a binary tree with Complex nodes
TEST_CASE("Testing binary tree with Complex nodes") {
    Node<Complex> root(Complex(8, 0));
    Tree<Complex> tree(2); // Binary tree

    tree.add_root(root);

    Node<Complex> n1(Complex(2, 1));
    Node<Complex> n2(Complex(3, 2));
    Node<Complex> n3(Complex(4, 3));
    Node<Complex> n4(Complex(5, 4));
    Node<Complex> n5(Complex(6, 5));
    Node<Complex> n6(Complex(7, 6));

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);

    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << "Binary tree with Complex nodes structure before traversals:" << std::endl;
    // print_tree_structure(&root); // Optional visualization

    SUBCASE("Pre-order traversal") {
        std::vector<Complex> expected_pre_order = {Complex(8, 0), Complex(2, 1), Complex(4, 3), Complex(5, 4), Complex(3, 2), Complex(6, 5), Complex(7, 6)};
        auto it = expected_pre_order.begin();
        std::cout << "Pre-order traversal: ";
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            std::cout << node->get_value().to_string() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }


    SUBCASE("Post-order traversal") {
        std::vector<Complex> expected_post_order = {Complex(4, 3), Complex(5, 4), Complex(2, 1), Complex(6, 5), Complex(7, 6), Complex(3, 2), Complex(8, 0)};
        auto it = expected_post_order.begin();
        std::cout << "Post-order traversal: ";
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            std::cout << node->get_value().to_string() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("In-order traversal") {
        std::vector<Complex> expected_in_order = {Complex(4, 3), Complex(2, 1), Complex(5, 4), Complex(8, 0), Complex(6, 5), Complex(3, 2), Complex(7, 6)};
        auto it = expected_in_order.begin();
        std::cout << "In-order traversal: ";
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            std::cout << node->get_value().to_string() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }


    SUBCASE("Heap order traversal (only for binary trees)") {
        std::vector<Complex> expected_heap_order = {Complex(2, 1), Complex(3, 2), Complex(4, 3), Complex(5, 4), Complex(6, 5), Complex(8, 0), Complex(7, 6)};
        auto it = expected_heap_order.begin();
        std::cout << "Heap order traversal: ";
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
            std::cout << node->get_value().to_string() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }
}

// Test for a binary tree with string nodes
TEST_CASE("Testing binary tree with string nodes") {
    Node<std::string> root("root");
    Tree<std::string> tree(2); // Binary tree

    tree.add_root(root);

    Node<std::string> n1("left");
    Node<std::string> n2("right");
    Node<std::string> n3("left.left");
    Node<std::string> n4("left.right");
    Node<std::string> n5("right.left");
    Node<std::string> n6("right.right");

    tree.add_sub_node(root, n1);
    tree.add_sub_node(root, n2);

    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);

    tree.add_sub_node(n2, n5);
    tree.add_sub_node(n2, n6);

    std::cout << "Binary tree with string nodes structure before traversals:" << std::endl;
    // print_tree_structure(&root); // Optional visualization

    SUBCASE("Pre-order traversal") {
        std::vector<std::string> expected_pre_order = {"root", "left", "left.left", "left.right", "right", "right.left", "right.right"};
        auto it = expected_pre_order.begin();
        std::cout << "Pre-order traversal: ";
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("Post-order traversal") {
        std::vector<std::string> expected_post_order = {"left.left", "left.right", "left", "right.left", "right.right", "right", "root"};
        auto it = expected_post_order.begin();
        std::cout << "Post-order traversal: ";
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }


    SUBCASE("In-order traversal") {
        std::vector<std::string> expected_in_order = {"left.left", "left", "left.right", "root", "right.left", "right", "right.right"};
        auto it = expected_in_order.begin();
        std::cout << "In-order traversal: ";
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("Heap order traversal (only for binary trees)") {
        std::vector<std::string> expected_heap_order = {"left", "left.left", "left.right", "right", "right.left", "right.right", "root"};
        auto it = expected_heap_order.begin();
        std::cout << "Heap order traversal: ";
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }
}
// Test for a tree with maxChildren = 1 (degenerate tree/linked list)
TEST_CASE("Testing tree with maxChildren = 1") {
    Node<int> root(1);
    Tree<int> tree(1); // Tree with maxChildren = 1

    tree.add_root(root);

    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Node<int> n5(5);

    tree.add_sub_node(root, n2);
    tree.add_sub_node(n2, n3);
    tree.add_sub_node(n3, n4);
    tree.add_sub_node(n4, n5);

    std::cout << "Tree with maxChildren = 1 structure before traversals:" << std::endl;
    // print_tree_structure(&root); // Optional visualization

    SUBCASE("Pre-order traversal") {
        std::vector<int> expected_pre_order = {1 ,2 ,3 ,4 ,5};
        auto it = expected_pre_order.begin();
        std::cout << "Pre-order traversal: ";
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("Post-order traversal") {
        std::vector<int> expected_post_order = {1 ,2 ,3 ,4 ,5};
        auto it = expected_post_order.begin();
        std::cout << "Post-order traversal: ";
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }

    SUBCASE("In-order traversal") {
        std::vector<int> expected_in_order = {1, 2, 3, 4, 5};
        auto it = expected_in_order.begin();
        std::cout << "In-order traversal: ";
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
            std::cout << node->get_value() << " ";
            CHECK(node->get_value() == *it++);
        }
        std::cout << std::endl;
    }
}
// TEST_CASE("Add sub-node with different type throws error") {
//     // Setup: Create a k-ary tree with a root node of type int
//     Tree<int> tree;  // Replace with your actual k-ary tree class and type

//     Node<int> root(1);   // Create a root node with value 1
//     tree.add_root(root); // Set this node as the root of the tree

//     // Create a node with a different type (char in this case)
//     Node<char> child('a');
//     tree.add_sub_node(root, child);

//     // Attempt to add the child node to the root node
//     // This should throw an exception since the types are different
   
// }


