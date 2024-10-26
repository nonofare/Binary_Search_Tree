#include <string>

namespace BST {

	template <typename T>
	class BinSerTree {

		template <typename T>
		class Node {
			friend BinSerTree;

			T data;
			Node<T>* parent;
			Node<T>* left;
			Node<T>* right;

			Node(T data, Node<T>* sender = nullptr) {
				data = data;
				parent = sender;
				left = nullptr;
				right = nullptr;
			}

			~Node() {
				if constexpr (std::is_pointer_v<T>) {
					delete data;
				}
			}
		};

		Node<T>* root;
		size_t size;

		bool dock(Node<T>* current, Node<T>* newNode, bool(*cmp)(T, T)) {
			if (cmp != nullptr) {
				if (cmp(newNode->data, current->data)) {
					if (current->right != nullptr) {
						current = current->right;
						return dock(current, newNode, cmp);
					}
					else {
						current->right = newNode;
					}
				}
				else {
					if (current->left != nullptr) {
						current = current->left;
						return dock(current, newNode, cmp);
					}
					else {
						current->left = newNode;
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (newNode->data > current->data) {
					if (current->right != nullptr) {
						current = current->right;
						return dock(current, newNode, cmp);
					}
					else {
						current->right = newNode;
					}
				}
				else {
					if (current->left != nullptr) {
						current = current->left;
						return dock(current, newNode, cmp);
					}
					else {
						current->left = newNode;
					}
				}
			}
			else {
				return false;
			}
			size++;

			return true;
		}

		size_t height(Node<T>* current) {
			if (current != nullptr) {
				size_t n1, n2;

				if (current->left != nullptr) {
					n1 = height(current->left);
				}
				else if (current->right != nullptr) {
					n2 = height(current->right);
				}
				else {
					return 1;
				}

				if (n1 > n2) {
					return 1 + n1;
				}
				else {
					return 1 + n2;
				}
			}
			else {
				return 0;
			}
		}

		bool flush(Node<T>* current) {
			if (current != nullptr) {
				if (current->left != nullptr) {
					flush(current->left);
				}

				if (current->right != nullptr) {
					flush(current->right);
				}

				if constexpr (std::is_pointer_v<T>) {
					delete current->data;
				}
				delete current;

				return true;
			}
			else {
				return false;
			}
		}

	public:
		BinSerTree() {
			root = nullptr;
			size = 0;
		}

		~BinSerTree() {
			erase();
		}

		bool push(T data, bool(*cmp)(T, T)) {
			if (size == 0) {
				root = new Node<T>(data);
				return true;
			}
			else {
				Node<T>* newNode = new Node<T>(data);
				return dock(root, newNode, cmp);
			}
		}

		Node<T>* find(T data, bool(*cmp)(T, T)) {

		}

		void pop(Node<T>*) {

		}

		void preorder() {

		}

		void inorder() {

		}

		bool erase() {
			return flush(root);
		}

		size_t get_size() {
			return size;
		}

		size_t get_height() {
			return height(root);
		}

		std::string to_string(size_t elements = 0, std::string(*out_string)(T) = nullptr) {
			if (elements <= 0 || elements > size) {
				elements = size;
			}

			std::string text = "Binary Search Tree:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "height: " + std::to_string(int(get_height())) + "\n";

			if (out_string != nullptr) {
				// Dokonczyc
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				// Dokonczyc
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			if (elements < size) {
				text += "[...]\n";
			}

			return text;
		}
	};
}