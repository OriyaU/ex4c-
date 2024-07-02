#include <iostream>
#include <string>
#include "Node.hpp"
#include "Tree.hpp"
#include <SFML/Graphics.hpp>
#include "Complex.hpp"

using namespace std;

int main()
{
     // Creating nodes with complex numbers
    Node<Complex> root_nodec(Complex(1.0, 2.0));
    Node<Complex> node111(Complex(3.0, 4.0));
    Node<Complex> node222(Complex(5.0, 6.0));
    Node<Complex> node333(Complex(7.0, 8.0));

    // Creating a Tree of Complex numbers
    Tree<Complex> complex_tree;

    // Adding nodes to the tree
    complex_tree.add_root(root_nodec);
    complex_tree.add_sub_node(root_nodec, node111);
    complex_tree.add_sub_node(root_nodec, node222);
    complex_tree.add_sub_node(node111, node333);

    complex_tree.visualize();

    // Printing the tree in in-order traversal
    std::cout << "In-Order traversal of Complex Tree:" << std::endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        std::cout << node->get_value().getReal() << " + " << node->get_value().getImaginary() << "i" << std::endl;
    }

    
    Node<double> root_node(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    tree.visualize();

    // The tree should look like:
    // /**
    //  *       root = 1.1
    //  *     /       \
    //  *    1.2      1.3
    //  *   /  \      /
    //  *  1.4  1.5  1.6
    //  */
    cout << "begin_pre_order" << endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "begin_dfs_scan" << endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6

    cout << "begin_post_order" << endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1

    cout << "begin_in_order" << endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    Node<int> root1(8);
    Tree<int> tree1(4); // 4-ary tree

    tree1.add_root(root1);

    Node<int> n11(2);
    Node<int> n21(3);
    Node<int> n31(4);
    Node<int> n41(5);
    Node<int> n51(6);
    Node<int> n61(7);
    Node<int> n71(1);
    Node<int> n81(9);

    tree1.add_sub_node(root1, n11);
    tree1.add_sub_node(root1, n21);
    tree1.add_sub_node(root1, n31);
    tree1.add_sub_node(root1, n41);

    tree1.add_sub_node(n11, n51);
    tree1.add_sub_node(n11, n61);
    tree1.add_sub_node(n11, n81);

    tree1.add_sub_node(n61, n71);

  
 
    std::cout << "Pre-order traversal: " << endl;
    for (auto node = tree1.begin_pre_order(); node != tree1.end_pre_order(); ++node)
    {
        cout << node->get_value() << endl;
    }
    std::cout << std::endl;

    std::cout << "Post-order traversal: " << endl;
    for (auto node = tree1.begin_post_order(); node != tree1.end_post_order(); ++node)
    {
        cout << node->get_value() << endl;
    }
    std::cout << std::endl; // 8, 2, 6, 7, 1, 9, 3, 4, 5

    std::cout << "in-order traversal: " << endl;
    for (auto node = tree1.begin_in_order(); node != tree1.end_in_order(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    std::cout << "bfs traversal: " << endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << endl;
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

   std::cout << "Heap traversal: " << std::endl;
for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
    std::cout << (node)->get_value() << std::endl; // Adjust based on your Node<T> structure
}

    // for (auto node : tree)
    // {
    //     cout << node.get_value() << endl;
    // } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    Node<int> root3(8);
    Tree<int> tree3(2); // Binary tree

    tree3.add_root(root3);

    Node<int> n13(2);
    Node<int> n23(3);
    Node<int> n33(4);
    Node<int> n43(5);
    Node<int> n53(6);
    Node<int> n63(7);
    Node<int> n73(1);
    Node<int> n83(9);

    tree3.add_sub_node(root3, n13);
    tree3.add_sub_node(root3, n23);

    tree3.add_sub_node(n13, n33);
    tree3.add_sub_node(n13, n43);

    tree3.add_sub_node(n23, n53);
    tree3.add_sub_node(n23, n63);

    tree3.add_sub_node(n43, n73);
    tree3.add_sub_node(n53, n83);

   

   cout << "begin_pre_order" << endl;
for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
{
    cout << (*node)->get_value() << endl;
} // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6


    // cout << tree; // Should print the graph using GUI.

    // Tree<double,3> three_ary_tree; // 3-ary tree.
    // three_ary_tree.add_root(root_node);
    // three_ary_tree.add_sub_node(root_node, n1);
    // three_ary_tree.add_sub_node(root_node, n2);
    // three_ary_tree.add_sub_node(root_node, n3);
    // three_ary_tree.add_sub_node(n1, n4);
    // three_ary_tree.add_sub_node(n2, n5);

    //  // The tree should look like:
    // /**
    //  *       root = 1.1
    //  *     /      |     \
    //  *    1.2    1.3    1.4
    //  *   /        |
    //  *  1.5      1.6
    //  */
}
