#pragma once
#include <iostream>
#include <algorithm>
enum Color :bool { Black = 0, Red = 1 };

template<typename Tk, typename Tv>
struct Node {
	std::pair<Tk, Tv> _myval;
	Node* parent;
	Node* left;
	Node* right;
	bool color;
	bool is_nil;
	Node(Tk k, Tv v, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
		:_myval(k, v), parent(p), left(l), right(r), color(1), is_nil(0) {}
};

#pragma region ClassConDest

template<typename Tk, typename Tv>
class RedBlackTree {
private:
	int _count;
	Node<Tk, Tv>* _root;
	void binarySearchTreeInsert(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void leftRotate(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void rightRotate(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void fixRbtInsert(Node<Tk, Tv>*);
	void fixRbtDelete(Node<Tk, Tv>*);
	void DeleteTree(Node<Tk, Tv>*);


public:
	RedBlackTree();
	void insert(std::pair<Tk, Tv>);
	void remove(std::pair<Tk, Tv>);
	const Node<Tk, Tv>* Find(std::pair<Tk, Tv>);
	const Node<Tk, Tv>* inOrderTraversal(const Node<Tk, Tv>*);
	const Node<Tk, Tv>* GetRoot() { return _root; }


	~RedBlackTree() {
		DeleteTree(_root);
	}
};
template<typename Tk, typename Tv>
RedBlackTree<Tk, Tv>::RedBlackTree() {
	_count = 0;
	_root = nullptr;
}

template<typename Tk, typename Tv>
void RedBlackTree<Tk, Tv>::DeleteTree(Node<Tk, Tv>* t) {
	//post order traversal
	if (t == nullptr)return;
	DeleteTree(t->left);
	DeleteTree(t->right);
	delete t;
}

#pragma endregion
#pragma region Rotations
template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::leftRotate(Node<Tk, Tv>* x, Node<Tk, Tv>* y)
{
	auto temp = y->right;
	y->right = temp->left;
	temp->left->parent = y;
	temp->parent = y->parent;
	if (y->parent == nullptr)
		x->parent = temp;
	else if (y == y->parent->left)
		y->parent->left = temp;
	else
		y->parent->right = temp;

	temp->left = y;
	y->parent = temp;
	//why???? not working if rotating the root
	if (x == y)
		_root = temp;

}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::rightRotate(Node<Tk, Tv>* x, Node<Tk, Tv>* y)
{
	auto temp = y->left;
	y->left = temp->right;
	temp->right->parent = y;
	temp->parent = y->parent;
	if (y->parent == nullptr)
		x->parent = temp;
	else if (y == y->parent->right)
		y->parent->right = temp;
	else
		y->parent->left = temp;

	temp->right = y;
	y->parent = temp;
	//why???? not working if sending root root
	if (x == y)
		_root = temp;
}

#pragma endregion
#pragma region RBTFix

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::fixRbtInsert(Node<Tk, Tv>* node)
{
	while (node->parent != nullptr && node->parent->color == Red) {
		if (node->parent == node->parent->parent->left)
		{
			auto uncle = node->parent->parent->right;
			if (uncle != nullptr && uncle->color == Red) {
				//case1
				node->parent->color = Black;
				uncle->color = Black;
				node->parent->parent->color = Red;
				node = node->parent->parent;
			}
			else if (node == node->parent->right) {
				//case2
				node = node->parent;
				leftRotate(_root, node);

			}
			else {
				node->parent->color = Black;
				node->parent->parent->color = Red;
				rightRotate(_root, node->parent->parent);
			}

		}
		else {

			auto uncle = node->parent->parent->left;
			if (uncle != nullptr && uncle->color == Red) {
				//case1
				node->parent->color = Black;
				uncle->color = Black;
				node->parent->parent->color = Red;
				node = node->parent->parent;
			}
			else if (node == node->parent->left) {
				//case2
				node = node->parent;
				rightRotate(_root, node);

			}
			else {
				node->parent->color = Black;
				node->parent->parent->color = Red;
				leftRotate(_root, node->parent->parent);
			}

		}

	}
	_root->color = Black;
}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::fixRbtDelete(Node<Tk, Tv>*)
{
	//TODO
}

#pragma endregion
#pragma region Methods

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::binarySearchTreeInsert(Node<Tk, Tv>* node, Node<Tk, Tv>* element) {
	//utility function used to perform binary search tree insert

	//empty tree
	if (node == nullptr) {
		element->color = Black;
		_root = element;
		return;
	}

	if (element->_myval.first < node->_myval.first && node->left != nullptr)
		binarySearchTreeInsert(node->left, element);
	else if (element->_myval.first < node->_myval.first && node->left == nullptr)
	{
		node->left = element;
		element->parent = node;
	}
	else if (element->_myval.first > node->_myval.first && node->right != nullptr)
		binarySearchTreeInsert(node->right, element);
	else if (element->_myval.first > node->_myval.first && node->right == nullptr)
	{
		node->right = element;
		element->parent = node;
	}
}



template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::insert(std::pair<Tk, Tv> element) {
	Node<Tk, Tv>* temporal_node = new Node<Tk, Tv>(element.first,element.second);
	binarySearchTreeInsert(_root, temporal_node);
	_count++;
	//check red black tree for violation
	//do not fix if we insert root
	if (_count > 1)
		fixRbtInsert(temporal_node);
}

template<typename Tk, typename Tv>
inline const Node<Tk, Tv>* RedBlackTree<Tk, Tv>::Find(std::pair<Tk, Tv> element) {
	auto node = _root;
	if (_root == nullptr) return nullptr;
	while (node != nullptr) {
		if (element.first < node->_myval.first) {
			std::cout << "At node " << node->_myval.first << " going left\n";
			node = node->left;
		}
		else if (element.first > node->_myval.first) {
			std::cout << "At node " << node->_myval.first << " going right\n";
			node = node->right;
		}
		else {
			std::cout << "Found node " << node->_myval.first << " terminated\n";
			return node;
		}
	}
	std::cout << "The tree does not contain node with key:" << element.first <<" and value:"<<element.second<< "\n";
	return nullptr;
}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::remove(std::pair<Tk, Tv> element)
{
	if (_root == nullptr)return;
	auto temp = Find(element);
	if (temp == nullptr)return;
	else {
		//TODO
		_count--;
	}

}

template<typename Tk, typename Tv>
const Node<Tk, Tv>* RedBlackTree<Tk, Tv>::inOrderTraversal( const Node<Tk, Tv>* node)
{
	if (node == NULL)
		return nullptr;

	inOrderTraversal(node->left);
	std::cout << node->_myval.first << "  ";
	inOrderTraversal(node->right);
}
#pragma endregion




