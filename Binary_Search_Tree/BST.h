#include <string>
#include <cmath>

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
			if (!node) {
				return 0;
			}

			int rightCount = 0, leftCount = 0;
			if (node->right) {
				rightCount = HeightOf(node->right);
			}
			if (node->left) {
				leftCount = HeightOf(node->left);
			}

			return ((leftCount > rightCount) ? leftCount : rightCount) + 1;
		}

		bool Accommodate(Node<T>* seeker, Node<T>* current, bool (*cmp)(T, T)) {
			if (!seeker) {
				return false;
			}

			if (!current) {
				if (!root) {
					root = seeker;
					size++;
					return true;
				}
				return false;
			}

			if (cmp) {
				if (cmp(seeker->data, current->data)) {
					if (!current->right) {
						current->right = seeker;
						seeker->parent = current;
					}
					else {
						return Accommodate(seeker, current->right, cmp);
					}
				}
				else {
					if (!current->left) {
						current->left = seeker;
						seeker->parent = current;
					}
					else {
						return Accommodate(seeker, current->left, cmp);
					}
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (seeker->data > current->data) {
					if (!current->right) {
						current->right = seeker;
						seeker->parent = current;
					}
					else {
						return Accommodate(seeker, current->right, cmp);
					}
				}
				else {
					if (!current->left) {
						current->left = seeker;
						seeker->parent = current;
					}
					else {
						return Accommodate(seeker, current->left, cmp);
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
			if (!node) {
				return false;
			}

			Node<T>* temp = nullptr;

			if (node->right && node->left) {
				temp = MinRight(node->right);

				if (temp) {
					if (temp->parent != node) {
						if (temp->right) {
							temp->right->parent = temp->parent;
						}
						temp->parent->left = temp->right;
						temp->right = node->right;
						node->right->parent = temp;
					}

					temp->left = node->left;
					node->left->parent = temp;
				}
				else {
					return false;
				}
			}
			else if (node->right) {
				temp = MaxLeft(node->right);

				if (temp) {
					if (temp->parent != node) {
						if (temp->right) {
							temp->right->parent = temp->parent;
						}
						temp->parent->left = temp->right;
						temp->right = node->right;
						node->right->parent = temp;
					}
				}
				else {
					return false;
				}
			}
			else if (node->left) {
				temp = MaxRight(node->left);

				if (temp) {
					if (temp->parent != node) {
						if (temp->left) {
							temp->left->parent = temp->parent;
						}
						temp->parent->right = temp->left;
						temp->left = node->left;
						node->left->parent = temp;
					}
				}
				else {
					return false;
				}
			}

			if (node->parent) {
				if (node->parent->right == node) {
					node->parent->right = temp;
				}
				else {
					node->parent->left = temp;
				}
			}
			else {
				root = temp;
			}

			if (temp) {
				temp->parent = node->parent;
			}

			delete node;
			size--;

			return true;
		}

		bool RemoveAllUnder(Node<T>* node) {
			if (!node) {
				return false;
			}

			if (node->left) {
				RemoveAllUnder(node->left);
			}
			if (node->right) {
				RemoveAllUnder(node->right);
			}

			if (node->parent) {
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

		Node<T>* SearchFor(T data, Node<T>* node, bool (*cmp1)(T, T), bool (*cmp2)(T, T)) const {
			if (!node) {
				return nullptr;
			}

			if (cmp2) {
				if (cmp2(data, node->data)) {
					return node;
				}

				if (cmp1(data, node->data)) {
					return SearchFor(data, node->right, cmp1, cmp2);
				}
				else {
					return SearchFor(data, node->left, cmp1, cmp2);
				}
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				if (data == node->data) {
					return node;
				}

				if (data > node->data) {
					return SearchFor(data, node->right, cmp1, cmp2);
				}
				else {
					return SearchFor(data, node->left, cmp1, cmp2);
				}
			}
			else {
				return nullptr;
			}
		}

		Node<T>* MaxRight(Node<T>* node) const {
			if (!node || !node->right) {
				return node;
			}
			else {
				return MaxRight(node->right);
			}
		}

		Node<T>* MaxLeft(Node<T>* node) const {
			if (!node || !node->left) {
				return node;
			}
			else {
				return MaxLeft(node->left);
			}
		}

		Node<T>* MinRight(Node<T>* node) const {
			if (!node || !node->left) {
				return node;
			}
			else {
				return MinRight(node->left);
			}
		}

		Node<T>* MinLeft(Node<T>* node) const {
			if (!node || !node->right) {
				return node;
			}
			else {
				return MinLeft(node->right);
			}
		}

		std::string PreorderTraversal(Node<T>* node) const {
			if (!node) {
				return "";
			}

			std::string text = "[ Index: ";
			text += std::to_string(int(node->index));
			text += " ]\n";

			if (node->left) {
				text += PreorderTraversal(node->left);
			}
			if (node->right) {
				text += PreorderTraversal(node->right);
			}

			return text;
		}

		std::string InorderTraversal(Node<T>* node) const {
			if (!node) {
				return "";
			}

			std::string text = "";
			if (node->left) {
				text += InorderTraversal(node->left);
			}

			text += "[ Index: ";
			text += std::to_string(int(node->index));
			text += " ]\n";

			if (node->right) {
				text += InorderTraversal(node->right);
			}

			return text;
		}

		std::string CollectStrings(Node<T>* node, unsigned int limit, std::string(*str)(T)) const {
			if (!node || limit == 0) {
				return "";
			}

			std::string text = "[ Index: ";
			text += std::to_string(int(node->index));

			text += " | Data: ";
			if (str) {
				text += str(node->data);
			}
			else if constexpr (std::is_arithmetic_v<T>) {
				text += std::to_string(node->data);
			}
			else {
				text = "Data type is not supported and no method was provided";
			}

			text += " | Parent: *";
			if (node->parent) {
				text += std::to_string(int(node->parent->index));
			}
			else {
				text += "NL";
			}

			text += " | Left: *";
			if (node->left) {
				text += std::to_string(int(node->left->index));
			}
			else {
				text += "NL";
			}

			text += " | Right: *";
			if (node->right) {
				text += std::to_string(int(node->right->index));
			}
			else {
				text += "NL";
			}
			text += " ]\n";

			if (node->left) {
				text += CollectStrings(node->left, limit - 1, str);
			}
			if (node->right) {
				text += CollectStrings(node->right, limit - 1, str);
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
			RemoveAllUnder(root);
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

			if (Accommodate(node, root, cmp)) {
				return true;
			}

			delete node;
			return false;
		}

		bool Pop(Node<T>* node) {
			return Remove(node);
		}

		bool Erase() {
			if (RemoveAllUnder(root)) {
				next_index = 0;
				return true;
			}
			
			return false;
		}

		Node<T>* Find(T data, bool (*cmp1)(T, T) = nullptr, bool (*cmp2)(T, T) = nullptr) const {
			return SearchFor(data, root, cmp1, cmp2);
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

		std::string ToString(unsigned int limit = 0, std::string(*str)(T) = nullptr) const {
			std::string text = "Binary Search Tree:\n";
			text += "size: " + std::to_string(int(size)) + "\n";
			text += "height: " + std::to_string(int(HeightOf(root))) + "\n";
			text += "log2size: " + std::to_string(log2(size)) + "\n";
			text += "size to height ratio: " + std::to_string(double(size) / HeightOf(root)) + "\n";
			text += "height to log2size ratio: " + std::to_string(double(HeightOf(root)) / log2(size)) + "\n";
			text += "{\n";

			if (limit == 0) {
				limit = size;
			}

			text += CollectStrings(root, limit, str);

			if (limit < size) {
				text += "[...]\n";
			}

			text += "}\n";

			return text;
		}
	};
}