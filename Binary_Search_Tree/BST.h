#include <string>

namespace BST {

	template <typename T>
	class BinSerTree {

		template <typename T>
		class Node {
			friend BinSerTree;

			T data;
			size_t index;
			Node<T>* parent;
			Node<T>* left;
			Node<T>* right;

			Node(T d, size_t i) {
				data = d;
				index = i;
				parent = nullptr;
				left = nullptr;
				right = nullptr;
			}
		};

		size_t size;
		size_t max_index;
		Node<T>* root;

		size_t height(Node<T>* current) {
			if (current == nullptr) {
				return 0;
			}

			size_t n1 = 0, n2 = 0;
			if (current->right != nullptr) {
				n1 = height(current->right);
			}
			if (current->left != nullptr) {
				n2 = height(current->left);
			}

			if (n1 > n2) {
				return 1 + n1;
			}
			else {
				return 1 + n2;
			}
		}

		bool dock(Node<T>* newNode, Node<T>* current, bool(*cmp)(T, T)) {
			if (newNode == nullptr) {
				return false;
			}

			if (current == nullptr) {
				if (root == nullptr) {
					root = newNode;
					size++;
					return true;
				}
				return false;
			}

			if (cmp != nullptr) {
				if (cmp(newNode->data, current->data)) {
					if (current->right != nullptr) {
						return dock(newNode, current->right, cmp);
					}
					else {
						current->right = newNode;
						newNode->parent = current;
					}
				}
				else {
					if (current->left != nullptr) {
						return dock(newNode, current->left, cmp);
					}
					else {
						current->left = newNode;
						newNode->parent = current;
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (newNode->data > current->data) {
					if (current->right != nullptr) {
						return dock(newNode, current->right, cmp);
					}
					else {
						current->right = newNode;
						newNode->parent = current;
					}
				}
				else {
					if (current->left != nullptr) {
						return dock(newNode, current->left, cmp);
					}
					else {
						current->left = newNode;
						newNode->parent = current;
					}
				}
			}
			else {
				return false;
			}

			size++;
			return true;
		}

		bool flush(Node<T>* current) {
			if (current == nullptr) {
				return false;
			}

			if (current->left != nullptr) {
				flush(current->left);
			}

			if (current->right != nullptr) {
				flush(current->right);
			}

			if (current->parent != nullptr) {
				if (current->parent->right == current) {
					current->parent->right = nullptr;
				}
				else {
					current->parent->left = nullptr;
				}
			}
			else {
				root = nullptr;
			}

			delete current;
			size--;

			return true;
		}

		bool remove(Node<T>* current) {
			if (current == nullptr) {
				return false;
			}

			Node<T>* temp = nullptr;
			if (current->left != nullptr) {
				temp = max_right(current->left);

				if (temp != nullptr) {
					current->left->parent = temp;
					temp->left = current->left;
				}
			}
			else if (current->right != nullptr) {
				temp = max_left(current->right);

				if (temp != nullptr) {
					current->right->parent = temp;
					temp->right = current->right;
				}
			}

			if (current->parent != nullptr) {
				if (current->parent->right == current) {
					current->parent->right = temp;
				}
				else {
					current->parent->left = temp;
				}
				if (temp != nullptr) {
					temp->parent = current->parent;
				}
			}
			else {
				root = temp;
			}

			delete current;
			size--;

			return true;
		}

		Node<T>* search(T data, Node<T>* current, bool(*cmp)(T, T)) {
			if (current == nullptr || current->data == data) {
				return current;
			}

			if (cmp != nullptr) {
				if (cmp(data, current->data)) {
					return search(data, current->right, cmp);
				}
				else {
					return search(data, current->left, cmp);
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (data > current->data) {
					return search(data, current->right, cmp);
				}
				else {
					return search(data, current->left, cmp);
				}
			}
			else {
				return nullptr;
			}
		}

		Node<T>* max_right(Node<T>* current) {
			if (current == nullptr) {
				return nullptr;
			}

			if (current->right == nullptr) {
				if (current->left != nullptr) {
					return max_right(current->left);
				}
				return current;
			}
			else {
				return max_right(current->right);
			}
		}

		Node<T>* max_left(Node<T>* current) {
			if (current == nullptr) {
				return nullptr;
			}

			if (current->left == nullptr) {
				if (current->right != nullptr) {
					return max_left(current->right);
				}
				return current;
			}
			else {
				return max_left(current->left);
			}
		}

		std::string collect_strings(Node<T>* current, std::string(*out_string)(T), bool limited, size_t operation = 1) {
			if (current == nullptr) {
				return "";
			}

			std::string text = "[ Node: *";
			text += std::to_string(int(current->index));

			text += " | Data: ";
			if (out_string != nullptr) {
				text += out_string(current->data);
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				text += std::to_string(current->data);
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			text += " | Parent: *";
			if (current->parent != nullptr) {
				text += std::to_string(int(current->parent->index));
			}
			else {
				text += "NL";
			}

			text += " | Left: *";
			if (current->left != nullptr) {
				text += std::to_string(int(current->left->index));
			}
			else {
				text += "NL";
			}

			text += " | Right: *";
			if (current->right != nullptr) {
				text += std::to_string(int(current->right->index));
			}
			else {
				text += "NL";
			}

			text += " ]\n";

			if (limited && operation > 2) {
				return text;
			}

			if (current->left != nullptr) {
				text += collect_strings(current->left, out_string, limited, operation++);
			}
			if (current->right != nullptr) {
				text += collect_strings(current->right, out_string, limited, operation++);
			}

			return text;
		}

		std::string preorder_strings(Node<T>* current) {
			if (current == nullptr) {
				return "";
			}

			std::string text = "[ Node: *";
			text += std::to_string(int(current->index));
			text += " ]\n";

			if (current->left != nullptr) {
				text += preorder_strings(current->left);
			}
			if (current->right != nullptr) {
				text += preorder_strings(current->right);
			}

			return text;
		}

		std::string inorder_strings(Node<T>* current) {
			if (current == nullptr) {
				return "";
			}

			std::string text = "";
			if (current->left != nullptr) {
				text += inorder_strings(current->left);
			}

			text += "[ Node: *";
			text += std::to_string(int(current->index));
			text += " ]\n";

			if (current->right != nullptr) {
				text += inorder_strings(current->right);
			}

			return text;
		}

	public:
		BinSerTree() {
			size = 0;
			max_index = 0;
			root = nullptr;
		}

		~BinSerTree() {
			erase();
		}

		bool push(T data, bool(*cmp)(T, T) = nullptr) {
			Node<T>* newNode = new Node<T>(data, max_index++);
			if (dock(newNode, root, cmp)) {
				return true;
			}
			else {
				delete newNode;
				return false;
			}
		}

		Node<T>* find(T data, bool(*cmp)(T, T) = nullptr) {
			return search(data, root, cmp);
		}

		bool pop(Node<T>* node) {
			return remove(node);
		}

		std::string preorder() {
			std::string text = "Preorder:\n";

			text += "{\n";
			text += preorder_strings(root);
			text += "}\n";

			return text;
		}

		std::string inorder() {
			std::string text = "Inorder:\n";

			text += "{\n";
			text += inorder_strings(root);
			text += "}\n";

			return text;
		}

		bool erase() {
			return flush(root);
		}

		bool is_empty() {
			return size == 0;
		}

		size_t get_size() {
			return size;
		}

		size_t get_height() {
			return height(root);
		}

		std::string to_string(bool limited = false, std::string(*out_string)(T) = nullptr) {
			std::string text = "Binary Search Tree:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "height: " + std::to_string(int(get_height())) + "\n";
			text += "{\n";

			text += collect_strings(root, out_string, limited);

			if (limited) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}