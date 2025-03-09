#pragma once
#include <string>
#include <cmath>

namespace BST {
    struct Node;

    template<typename T>
    class BinSearTree {
    public:
        struct Node {
            T data;
            Node *parent;
            Node *left;
            Node *right;

            explicit Node(T data) : data(data), parent(nullptr), left(nullptr), right(nullptr) {
            }

            ~Node() = default;
        };

    private:
        size_t size;
        Node *root;

    protected:
        int height_of(Node *node) const {
            if (!node) return 0;

            int right_count = 0, left_count = 0;

            if (node->right) right_count = height_of(node->right);
            if (node->left) left_count = height_of(node->left);

            return (left_count > right_count ? left_count : right_count) + 1;
        }

        void insert(Node *node, Node *current, bool (*cmp_lgreater)(T, T)) {
            if (!node) throw std::invalid_argument("Node was null");

            if (!root) {
                root = node;
                size++;
                return;
            }

            if (cmp_lgreater) {
                if (cmp_lgreater(node->data, current->data)) {
                    if (!current->right) {
                        current->right = node;
                        node->parent = current;
                        size++;
                    } else {
                        insert(node, current->right, cmp_lgreater);
                    }
                } else {
                    if (!current->left) {
                        current->left = node;
                        node->parent = current;
                        size++;
                    } else {
                        insert(node, current->left, cmp_lgreater);
                    }
                }
            } else if constexpr (std::is_arithmetic_v<T>) {
                if (node->data > current->data) {
                    if (!current->right) {
                        current->right = node;
                        node->parent = current;
                        size++;
                    } else {
                        insert(node, current->right, cmp_lgreater);
                    }
                } else {
                    if (!current->left) {
                        current->left = node;
                        node->parent = current;
                        size++;
                    } else {
                        insert(node, current->left, cmp_lgreater);
                    }
                }
            } else {
                throw std::invalid_argument("T was not arithmetic and no comparator was provided\n");
            }
        }

        void remove(Node *node) {
            if (!node) throw std::invalid_argument("Node was null");

            Node *temp = nullptr;

            if (node->right && node->left) {
                temp = min_right(node->right);

                if (temp->parent != node) {
                    if (temp->right) temp->right->parent = temp->parent;
                    temp->parent->left = temp->right;
                    temp->right = node->right;
                    node->right->parent = temp;
                }

                temp->left = node->left;
                node->left->parent = temp;
            } else if (node->right) {
                temp = max_left(node->right);

                if (temp->parent != node) {
                    if (temp->right) temp->right->parent = temp->parent;
                    temp->parent->left = temp->right;
                    temp->right = node->right;
                    node->right->parent = temp;
                }
            } else if (node->left) {
                temp = max_right(node->left);

                if (temp->parent != node) {
                    if (temp->left) temp->left->parent = temp->parent;
                    temp->parent->right = temp->left;
                    temp->left = node->left;
                    node->left->parent = temp;
                }
            }

            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = temp;
                } else {
                    node->parent->right = temp;
                }
            } else {
                root = temp;
            }

            if (temp) temp->parent = node->parent;

            delete node;
            size--;
        }

        void remove_all_under(Node *node) {
            if (!node) return;

            remove_all_under(node->left);
            remove_all_under(node->right);

            if (node->parent) {
                if (node->parent->left == node) {
                    node->parent->left = nullptr;
                } else {
                    node->parent->right = nullptr;
                }
            } else {
                root = nullptr;
            }

            delete node;
            size--;
        }

        Node *search_for(T data, Node *node, bool (*cmp_lgreater)(T, T), bool (*cmp_equal)(T, T)) const {
            if (!node) return nullptr;

            if (cmp_equal) {
                if (cmp_equal(data, node->data)) return node;

                if (cmp_lgreater(data, node->data)) {
                    return search_for(data, node->right, cmp_lgreater, cmp_equal);
                } else {
                    return search_for(data, node->left, cmp_lgreater, cmp_equal);
                }
            } else if constexpr (std::is_arithmetic_v<T>) {
                if (data == node->data) return node;

                if (data > node->data) {
                    return search_for(data, node->right, cmp_lgreater, cmp_equal);
                } else {
                    return search_for(data, node->left, cmp_lgreater, cmp_equal);
                }
            } else {
                return nullptr;
            }
        }

        Node *max_right(Node *node) const {
            if (!node) throw std::invalid_argument("Node was null");
            if (!node->right) return node;
            return max_right(node->right);
        }

        Node *max_left(Node *node) const {
            if (!node) throw std::invalid_argument("Node was null");
            if (!node->left) return node;
            return max_left(node->left);
        }

        Node *min_right(Node *node) const {
            if (!node) throw std::invalid_argument("Node was null");
            if (!node->left) return node;
            return min_right(node->left);
        }

        Node *min_left(Node *node) const {
            if (!node) throw std::invalid_argument("Node was null");
            if (!node->right) return node;
            return min_left(node->right);
        }

        std::string str_collect(Node *node, const unsigned int limit, std::string (*fun_str)(T)) const {
            if (!node) throw std::invalid_argument("Node was null");
            if (limit == 0) return "";

            std::string text = "[ Data: ";
            if (fun_str) {
                text += fun_str(node->data);

                text += " | Parent: ";
                if (node->parent) {
                    text += fun_str(node->parent->data);
                } else {
                    text += "NULL";
                }

                text += " | Left: ";
                if (node->left) {
                    text += fun_str(node->left->data);
                } else {
                    text += "NULL";
                }

                text += " | Right: ";
                if (node->right) {
                    text += fun_str(node->right->data);
                } else {
                    text += "NULL";
                }
            } else if constexpr (std::is_arithmetic_v<T>) {
                text += std::to_string(node->data);

                text += " | Parent: ";
                if (node->parent) {
                    text += std::to_string(node->parent->data);
                } else {
                    text += "NULL";
                }

                text += " | Left: ";
                if (node->left) {
                    text += std::to_string(node->left->data);
                } else {
                    text += "NULL";
                }

                text += " | Right: ";
                if (node->right) {
                    text += std::to_string(node->right->data);
                } else {
                    text += "NULL";
                }
            } else {
                text = "T was not arithmetic nad no function was provided\n";
            }
            text += " ]\n";

            if (node->left) text += str_collect(node->left, limit - 1, fun_str);
            if (node->right) text += str_collect(node->right, limit - 1, fun_str);

            return text;
        }

    public:
        BinSearTree() : size(0), root(nullptr) {
        }

        ~BinSearTree() {
            erase();
        }

        size_t get_size() const {
            return size;
        }

        size_t get_height() const {
            return height_of(root);
        }

        bool is_empty() const {
            return size == 0;
        }

        void push(T data, bool (*cmp_lgreater)(T, T) = nullptr) {
            Node *node = new Node(data);
            insert(node, root, cmp_lgreater);
        }

        void pop(Node *node) {
            remove(node);
        }

        void erase() {
            remove_all_under(root);
        }

        Node *find(T data, bool (*cmp_lgreater)(T, T) = nullptr, bool (*cmp_equal)(T, T) = nullptr) const {
            return search_for(data, root, cmp_lgreater, cmp_equal);
        }

        std::string to_str(unsigned int limit = 0, std::string (*fun_str)(T) = nullptr) const {
            std::string text = "Binary Search Tree:\n";
            text += "size: " + std::to_string(static_cast<int>(size)) + "\n";
            text += "height: " + std::to_string(height_of(root)) + "\n";
            text += "log2size: " + std::to_string(log2(size)) + "\n";
            text += "size to height ratio: " + std::to_string(static_cast<double>(size) / height_of(root)) + "\n";
            text += "height to log2size ratio: " + std::to_string(static_cast<double>(height_of(root)) / log2(size)) +
                    "\n";

            text += "{\n";

            if (limit <= 0) limit = size;
            text += str_collect(root, limit, fun_str);
            if (limit < size) text += "[...]\n";

            text += "}\n";

            return text;
        }
    };
}
