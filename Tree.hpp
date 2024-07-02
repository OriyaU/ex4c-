//oriya7914@gmail.come
#pragma once
#include "Node.hpp"
#include <stack>
#include <stdexcept>
#include <queue>
#include <vector>
#include <algorithm> // For std::make_heap
#include <SFML/Graphics.hpp>
#include "Complex.hpp"

template <typename T>
class Tree {
private:
    Node<T>* root; // Pointer to the root node of the tree
    size_t maxChildren;// Maximum number of children each node can have

public:
    Tree(size_t K = 2) : root(nullptr), maxChildren(K) {}

    // Destructor. we dont need to uctually implement adestractor becouse we never did new so it save the trees in the stack and when he done using them it earse otomaticly
    ~Tree()
    {
        // No dynamic memory to delete
    }


    
    void add_root(Node<T>& node) {
        root = &node;
    }
    void add_sub_node(Node<T>& parent, Node<T>& child) {
        if (parent.children_count() >= maxChildren) {
            throw std::overflow_error("Cannot add more children to this node");
        }
        if (root && (typeid(child.get_value()) != typeid(root->get_value()))) {
            throw std::invalid_argument("All nodes of the tree must have the same type");
        }
        parent.add_child(&child);
    }

    Node<T>* get_root() const {
        return root;
    }


   

    // DFS Helper
    void dfs_helper(Node<T>* node, std::vector<Node<T>*>& result) const {
        if (node == nullptr)
            return;
        result.push_back(node);
        for (auto child : node->get_children()) {
            dfs_helper(child, result);
        }
    }

    // BFS Iterator
    class BFSIterator {
    private:
        std::queue<Node<T>*> node_queue;

    public:
        BFSIterator(Node<T>* root) {
            if (root != nullptr) {
                node_queue.push(root);
            }
        }

        bool operator!=(const BFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const BFSIterator& other) const {
            if (node_queue.empty() && other.node_queue.empty()) {
                return true;
            }
            if (node_queue.empty() || other.node_queue.empty()) {
                return false;
            }
            return node_queue.front() == other.node_queue.front();
        }

        Node<T>* operator*() {
            return node_queue.front();
        }

        Node<T>* operator->() {
            return node_queue.front();
        }

        BFSIterator& operator++() {
            Node<T>* current = node_queue.front();
            node_queue.pop();
            const std::vector<Node<T>*>& children = current->get_children();
            for (auto child : children) {
                node_queue.push(child);
            }
            return *this;
        }
    };

    BFSIterator begin_bfs_scan() const {
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan() const {
        return BFSIterator(nullptr);
    }

    // DFS Iterator
    class DFSIterator {
    private:
        std::stack<Node<T>*> node_stack;

    public:
        DFSIterator(Node<T>* root) {
            if (root != nullptr) {
                node_stack.push(root);
            }
        }

        bool operator!=(const DFSIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const DFSIterator& other) const {
            if (node_stack.empty() && other.node_stack.empty()) {
                return true;
            }
            if (node_stack.empty() || other.node_stack.empty()) {
                return false;
            }
            return node_stack.top() == other.node_stack.top();
        }

        Node<T>* operator*() {
            return node_stack.top();
        }

        Node<T>* operator->() {
            return node_stack.top();
        }

        DFSIterator& operator++() {
            Node<T>* current = node_stack.top();
            node_stack.pop();
            const std::vector<Node<T>*>& children = current->get_children();
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                node_stack.push(*it);
            }
            return *this;
        }
    };

    DFSIterator begin_dfs_scan() const {
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan() const {
        return DFSIterator(nullptr);
    }

    // Pre-Order Iterator
    class PreOrderIterator {
    private:
        std::stack<Node<T>*> node_stack;
        size_t maxChildren;

    public:
        PreOrderIterator(Node<T>* root, size_t maxChildren) : maxChildren(maxChildren) {
            if (root != nullptr) {
                node_stack.push(root);
            }
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }

        bool operator==(const PreOrderIterator& other) const {
            if (node_stack.empty() && other.node_stack.empty()) {
                return true;
            }
            if (node_stack.empty() || other.node_stack.empty()) {
                return false;
            }
            return node_stack.top() == other.node_stack.top();
        }

        Node<T>* operator*() {
            return node_stack.top();
        }

        Node<T>* operator->() {
            return node_stack.top();
        }

        PreOrderIterator& operator++() {
            Node<T>* current = node_stack.top();
            node_stack.pop();
            const std::vector<Node<T>*>& children = current->get_children();

            // General tree behavior: use DFS
            for (auto it = children.rbegin(); it != children.rend(); ++it) {
                node_stack.push(*it);
            }

            return *this;
        }
    };

    PreOrderIterator begin_pre_order() const {
        return PreOrderIterator(root, maxChildren);
    }

    PreOrderIterator end_pre_order() const {
        return PreOrderIterator(nullptr, maxChildren);
    }

    // Post-Order Iterator
    class PostOrderIterator {
    private:
        std::stack<Node<T>*> nodeStack;
        Node<T>* current;
        int k;

        void pushLeftmostPath(Node<T>* node) {
            while (node) {
                nodeStack.push(node);
                if (!node->children.empty()) {
                    node = node->children[0];
                } else {
                    break;
                }
            }
        }

    public:
        PostOrderIterator(Node<T>* root, int k) : current(nullptr), k(k) {
            if (root) {
                if (k == 2) {
                    pushLeftmostPath(root);
                } else {
                    nodeStack.push(root);
                }
            }
            ++(*this);
        }

        Node<T>* operator*() {
            return current;
        }

        Node<T>* operator->() {
            return current;
        }

        PostOrderIterator& operator++() {
            if (k == 2) {
                if (!nodeStack.empty()) {
                    Node<T>* node = nodeStack.top();
                    nodeStack.pop();
                    if (!nodeStack.empty()) {
                        Node<T>* parent = nodeStack.top();
                        if (parent->children.size() > 1 && node == parent->children[0]) {
                            pushLeftmostPath(parent->children[1]);
                        }
                    }
                    current = node;
                } else {
                    current = nullptr;
                }
            } else {
                if (!nodeStack.empty()) {
                    Node<T>* node = nodeStack.top();
                    nodeStack.pop();
                    for (auto it = node->children.rbegin(); it != node->children.rend(); ++it) {
                        if (*it) {
                            nodeStack.push(*it);
                        }
                    }
                    current = node;
                } else {
                    current = nullptr;
                }
            }
            return *this;
        }

        bool operator!=(const PostOrderIterator& other) const {
            return current != other.current;
        }
    };

    PostOrderIterator begin_post_order() const {
        return PostOrderIterator(root, maxChildren);
    }

    PostOrderIterator end_post_order() const {
        return PostOrderIterator(nullptr, maxChildren);
    }

    // In-order Iterator
    class InOrderIterator {
    public:
               explicit InOrderIterator(Node<T>* node, size_t k) : k(k) {
            if (node) {
                if (k == 2) {
                    push_left(node);
                } else {
                    nodes.push(node);
                    while (!nodes.empty() && !nodes.top())
                        nodes.pop();
                }
            }
        }

        bool operator!=(const InOrderIterator& other) const {
            return !nodes.empty() != !other.nodes.empty();
        }

        Node<T>* operator->() const {
            return nodes.top();
        }

        Node<T>& operator*() const {
            return *nodes.top();
        }

        InOrderIterator& operator++() {
            if (nodes.empty())
                return *this;

            if (k == 2) {
                Node<T>* node = nodes.top();
                nodes.pop();
                if (node->get_children().size() > 1 && node->get_children()[1] != nullptr) {
                    push_left(node->get_children()[1]);
                }
            } else {
                Node<T>* current = nodes.top();
                nodes.pop();
                for (auto it = current->get_children().rbegin(); it != current->get_children().rend(); ++it) {
                    if (*it != nullptr)
                        nodes.push(*it);
                }
            }
            return *this;
        }

    private:
        std::stack<Node<T>*> nodes;
        size_t k;

        void push_left(Node<T>* node) {
            while (node != nullptr) {
                nodes.push(node);
                if (node->get_children().size() > 0)
                    node = node->get_children()[0];
                else
                    break;
            }
        }
    };

    InOrderIterator begin_in_order() const {
        return InOrderIterator(root, maxChildren);
    }

    InOrderIterator end_in_order() const {
        return InOrderIterator(nullptr, maxChildren);
    }

    // Helper function to push all nodes to the heap vector
    void push_all_nodes(Node<T>* node, std::vector<Node<T>*>& heap) {
        if (node == nullptr) return;
        heap.push_back(node);
        for (auto child : node->get_children()) {
            push_all_nodes(child, heap);
        }
    }

    class HeapIterator {
private:
    std::vector<Node<T>*> heap; // Vector storing node pointers in heap order

    struct CompareNodes {
        bool operator()(const Node<T>* a, const Node<T>* b) const {
            return a->value > b->value;
        }
    };

    void collectNodes(Node<T>* node) {
        if (node) {
            heap.push_back(node);
            for (auto& child : node->children) {
                if (child) {
                    collectNodes(child);
                }
            }
        }
    }

public:
    HeapIterator(Node<T>* root, int k) {
        if (k == 2) {
            if (root) {
                collectNodes(root);
                std::make_heap(heap.begin(), heap.end(), CompareNodes());
            }
        } else if (k > 2) {
            throw std::invalid_argument("HeapIterator is only supported for binary trees (k = 2).");
        }
    }

    HeapIterator(const HeapIterator& other) : heap(other.heap) {}

    T& operator*() const {
        return heap.front()->value; // Assuming value is a member of Node<T>
    }

    Node<T>* operator->() const {
        return heap.front();
    }

    HeapIterator& operator++() {
        std::pop_heap(heap.begin(), heap.end(), CompareNodes());
        heap.pop_back();
        return *this;
    }

    bool operator==(const HeapIterator& other) const {
        return heap == other.heap;
    }

    bool operator!=(const HeapIterator& other) const {
        return !(*this == other);
    }

    HeapIterator& operator=(const HeapIterator& other) {
        if (this != &other) {
            heap = other.heap;
        }
        return *this;
    }
};

    HeapIterator begin_heap() {
        return HeapIterator(root, maxChildren);
    }

    HeapIterator end_heap() {
        return HeapIterator(nullptr, maxChildren);
    }

    void visualize() const {
        if (!root) return;

        sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualization");

        sf::Font font;
        if (!font.loadFromFile("LikhanNormal.ttf")) {
            std::cerr << "Error loading font\n";
            return;
        }

        const float node_radius = 30.f;
        const float horizontal_spacing = 150.f;
        const float vertical_spacing = 100.f;

        std::map<Node<T>*, sf::Vector2f> positions;
        positions[root] = sf::Vector2f(window.getSize().x / 2.f, node_radius + 50.f);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);

            std::queue<Node<T>*> nodes;
            nodes.push(root);

            while (!nodes.empty()) {
                Node<T>* node = nodes.front();
                nodes.pop();

                sf::Vector2f position = positions[node];

                sf::CircleShape circle(node_radius);
                circle.setFillColor(sf::Color::Green);
                circle.setPosition(position - sf::Vector2f(node_radius, node_radius));
                window.draw(circle);

                sf::Text text;
                text.setFont(font);

                // Check the type of node's value and set text accordingly
                if constexpr (std::is_same_v<T, Complex>) {
                    text.setString(node->get_value().to_string());
                } else if constexpr (std::is_integral_v<T>) {
                    text.setString(std::to_string(node->get_value()));
                } else {
                    // Handle other types as needed
                    // text.setString(...);
                }

                text.setCharacterSize(16);
                text.setFillColor(sf::Color::Black);
                sf::FloatRect text_bounds = text.getLocalBounds();
                text.setOrigin(text_bounds.left + text_bounds.width / 2.0f,
                               text_bounds.top + text_bounds.height / 2.0f);
                text.setPosition(position);
                window.draw(text);

                const auto& children = node->get_children();
                float child_x_offset = position.x - (children.size() - 1) * horizontal_spacing / 2.f;
                for (size_t i = 0; i < children.size(); ++i) {
                    Node<T>* child = children[i];
                    if (child) {
                        sf::Vector2f child_position = sf::Vector2f(child_x_offset + i * horizontal_spacing, position.y + vertical_spacing);
                        positions[child] = child_position;
                        nodes.push(child);
                        sf::Vertex line[] = { sf::Vertex(position, sf::Color::Black),
                                              sf::Vertex(child_position, sf::Color::Black) };
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }

            window.display();
        }
    }
};
