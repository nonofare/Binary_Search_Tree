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

			Node(T inData, size_t inIndex) {
				data = inData;
				index = inIndex;
				parent = nullptr;
				left = nullptr;
				right = nullptr;
			}
		};

		size_t size;
		size_t next_index;

		Node<T>* root;

		int HeightOf(Node<T>* node) const {
			if (node == nullptr) {
				return 0;
			}

			int rightCount = 0, leftCount = 0;
			if (node->right != nullptr) {
				rightCount = HeightOf(node->right);
			}
			if (node->left != nullptr) {
				leftCount = HeightOf(node->left);
			}

			return ((leftCount > rightCount) ? leftCount : rightCount) + 1;
		}

		bool FindSpot(Node<T>* seeker, Node<T>* current, bool (*cmp)(T, T)) {
			if (seeker == nullptr) {
				return false;
			}

			if (current == nullptr) {
				if (root == nullptr) {
					root = seeker;
					size++;
					return true;
				}
				return false;
			}

			if (cmp != nullptr) {
				if (cmp(seeker->data, current->data)) {
					if (current->right == nullptr) {
						current->right = seeker;
						seeker->parent = current;
					}
					else {
						return FindSpot(seeker, current->right, cmp);
					}
				}
				else {
					if (current->left == nullptr) {
						current->left = seeker;
						seeker->parent = current;
					}
					else {
						return FindSpot(seeker, current->left, cmp);
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (seeker->data > current->data) {
					if (current->right == nullptr) {
						current->right = seeker;
						seeker->parent = current;
					}
					else {
						return FindSpot(seeker, current->right, cmp);
					}
				}
				else {
					if (current->left == nullptr) {
						current->left = seeker;
						seeker->parent = current;
					}
					else {
						return FindSpot(seeker, current->left, cmp);
					}
				}
			}
			else {
				return false;
			}

			size++;
			return true;
		}

		bool Remove(Node<T>* node) {
			if (node == nullptr) {
				return false;
			}

			Node<T>* temp = nullptr;
			if (node->left != nullptr) {
				temp = MaxRight(node->left);

				if (temp != nullptr) {
					node->left->parent = temp;
					temp->left = node->left;
				}
			}
			else if (node->right != nullptr) {
				temp = MaxLeft(node->right);

				if (temp != nullptr) {
					node->right->parent = temp;
					temp->right = node->right;
				}
			}

			if (node->parent != nullptr) {
				if (node->parent->right == node) {
					node->parent->right = temp;
				}
				else {
					node->parent->left = temp;
				}
				if (temp != nullptr) {
					temp->parent = node->parent;
				}
			}
			else {
				root = temp;
			}

			delete node;
			size--;

			return true;
		}

		bool FlushUnder(Node<T>* node) {
			if (node == nullptr) {
				return false;
			}

			if (node->left != nullptr) {
				FlushUnder(node->left);
			}
			if (node->right != nullptr) {
				FlushUnder(node->right);
			}

			if (node->parent != nullptr) {
				if (node->parent->right == node) {
					node->parent->right = nullptr;
				}
				else {
					node->parent->left = nullptr;
				}
			}
			else {
				root = nullptr;
			}

			delete node;
			size--;

			return true;
		}

		Node<T>* SearchFor(T data, Node<T>* node, bool (*cmp)(T, T)) const {
			if (node->data == data || node == nullptr) {
				return node;
			}

			if (cmp != nullptr) {
				if (cmp(data, node->data)) {
					return SearchFor(data, node->right, cmp);
				}
				else {
					return SearchFor(data, node->left, cmp);
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (data > node->data) {
					return SearchFor(data, node->right, cmp);
				}
				else {
					return SearchFor(data, node->left, cmp);
				}
			}
			else {
				return nullptr;
			}
		}

		Node<T>* MaxRight(Node<T>* node) const {
			if (node == nullptr) {
				return nullptr;
			}

			if (node->right == nullptr) {
				if (node->left != nullptr) {
					return MaxRight(node->left);
				}
				return node;
			}
			else {
				return MaxRight(node->right);
			}
		}

		Node<T>* MaxLeft(Node<T>* node) const {
			if (node == nullptr) {
				return nullptr;
			}

			if (node->left == nullptr) {
				if (node->right != nullptr) {
					return MaxLeft(node->right);
				}
				return node;
			}
			else {
				return MaxLeft(node->left);
			}
		}

		std::string PreorderTraversal(Node<T>* node) const {
			if (node == nullptr) {
				return "";
			}

			std::string text = "[ Node: *";
			text += std::to_string(int(node->index));
			text += " ]\n";

			if (node->left != nullptr) {
				text += PreorderTraversal(node->left);
			}
			if (node->right != nullptr) {
				text += PreorderTraversal(node->right);
			}

			return text;
		}

		std::string InorderTraversal(Node<T>* node) const {
			if (node == nullptr) {
				return "";
			}

			std::string text = "";
			if (node->left != nullptr) {
				text += InorderTraversal(node->left);
			}

			text += "[ Node: *";
			text += std::to_string(int(node->index));
			text += " ]\n";

			if (node->right != nullptr) {
				text += InorderTraversal(node->right);
			}

			return text;
		}

		std::string CollectStrings(Node<T>* node, bool limited, std::string(*str)(T), int operation) const {
			if (node == nullptr) {
				return "";
			}

			const int OPERATION_LIMIT = 2;

			std::string text = "[ Node: *";
			text += std::to_string(int(node->index));

			text += " | Data: ";
			if (str != nullptr) {
				text += str(node->data);
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				text += std::to_string(node->data);
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			text += " | Parent: *";
			if (node->parent != nullptr) {
				text += std::to_string(int(node->parent->index));
			}
			else {
				text += "NL";
			}

			text += " | Left: *";
			if (node->left != nullptr) {
				text += std::to_string(int(node->left->index));
			}
			else {
				text += "NL";
			}

			text += " | Right: *";
			if (node->right != nullptr) {
				text += std::to_string(int(node->right->index));
			}
			else {
				text += "NL";
			}

			text += " ]\n";

			if (limited && operation > OPERATION_LIMIT) {
				return text;
			}

			if (node->left != nullptr) {
				text += CollectStrings(node->left, limited, str, operation++);
			}
			if (node->right != nullptr) {
				text += CollectStrings(node->right, limited, str, operation++);
			}

			return text;
		}

	public:
		BinSerTree() {
			size = 0;
			next_index = 0;
			root = nullptr;
		}

		~BinSerTree() {
			FlushUnder(root);
		}

		size_t Size() const {
			return size;
		}

		size_t Height() const {
			return HeightOf(root);
		}

		bool IsEmpty() const {
			return size == 0;
		}

		bool Push(T data, bool (*cmp)(T, T) = nullptr) {
			Node<T>* node = new Node<T>(data, next_index++);

			if (FindSpot(node, root, cmp)) {
				return true;
			}
			else {
				delete node;
				return false;
			}
		}

		bool Pop(Node<T>* node) {
			return Remove(node);
		}

		bool Erase() {
			return FlushUnder(root);
		}

		Node<T>* Find(T data, bool (*cmp)(T, T) = nullptr) const {
			return SearchFor(data, root, cmp);
		}

		std::string Preorder() const {
			std::string text = "Preorder:\n";

			text += "{\n";
			text += PreorderTraversal(root);
			text += "}\n";

			return text;
		}

		std::string Inorder() const {
			std::string text = "Inorder:\n";

			text += "{\n";
			text += InorderTraversal(root);
			text += "}\n";

			return text;
		}

		std::string ToString(bool limited = false, std::string(*str)(T) = nullptr) const {
			std::string text = "Binary Search Tree:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "height: " + std::to_string(int(HeightOf(root))) + "\n";
			text += "{\n";

			text += CollectStrings(root, limited, str, 1);

			if (limited) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}