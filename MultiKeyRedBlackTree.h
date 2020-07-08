#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>

enum Color :bool { Black = 0, Red = 1 };

template<typename Tk, typename Tv>
struct Node {
	std::pair<Tk, Tv> _myval;
	Node* parent;
	Node* left;
	Node* right;
	bool is_nil;
	bool color;
	Node(){}
	Node(Tk key) { _myval.first = key; }
	Node(Tk k, Tv v, Node* p = nullptr, Node* l = nullptr, Node* r = nullptr)
		:_myval(k, v), parent(p), left(l), right(r), is_nil(0), color(Red) {
	}
	Node(const Node& temp) {
		this->color = temp.color;
		this->left = temp.left;
		this->right = temp.right;
		this->parent = temp.parent;
		this->_myval.first = temp._myval.first;
		this->_myval.second = temp._myval.second;

	}
};

template<typename Tk, typename Tv>
class RedBlackTree {
private:
	int _count;
	Node<Tk, Tv>* _root;
	Node<Tk, Tv>* _sentinelNill;
	void binarySearchTreeInsert(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void leftRotate(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void rightRotate(Node<Tk, Tv>*, Node<Tk, Tv>*);
	void fixRbtInsert(Node<Tk, Tv>*);
	void fixRbtDelete(Node<Tk, Tv>*);
	void DeleteTree(Node<Tk, Tv>*);
	Node<Tk, Tv>* treeSuccessor(Node <Tk, Tv>*);
	void transplant(Node <Tk, Tv>*, Node <Tk, Tv>*);


public:
	class iterator {
		std::stack<Node<Tk, Tv>*> storage;
	public:
		iterator(Node<Tk, Tv>* node) {
			while (node != nullptr) {
				storage.push(node);
				node = node->left;
			}
		}
		Node<Tk, Tv>* current() { return storage.top(); }
		//implement here the usual operators 
		// for the iterator, i.e.: ++,--, ==,!=,*,->
		/*void overload operator++() {
			auto current = storage.top()->right;
			storage.pop();
			while (current != nullptr) {
				storage.push;
				current = current->left;
			}*/

	};
	RedBlackTree();
	void insert(std::pair<Tk, Tv>);
	void insert(Node<Tk, Tv>*);
	void remove(Tk);
	Node<Tk, Tv>* Find(Tk);
	std::string print();
	const Node<Tk, Tv>* inOrderTraversal(const Node<Tk, Tv>*, std::ostream& os);
	const Node<Tk, Tv>* GetRoot() { return _root; }
	Node<Tk, Tv>* findMin( Node<Tk, Tv>*);
	Node<Tk, Tv>* findMax( Node<Tk, Tv>*);


	~RedBlackTree() {
		DeleteTree(_root);
		delete _sentinelNill;
	}
};
#pragma region CtorDtor

template<typename Tk, typename Tv>
RedBlackTree<Tk, Tv>::RedBlackTree() {
	_count = 0;
	_root = nullptr;
	_sentinelNill = new Node<Tk, Tv>();
	_sentinelNill->is_nil = true;
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

#pragma region PrivateMethods

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::binarySearchTreeInsert(Node<Tk, Tv>* node, Node<Tk, Tv>* element) {
	//utility function used to perform binary search tree insert

	//empty tree
	if (node == nullptr) {
		element->color = Black;
		_root = element;
		return;
	}

	if (element->_myval.first < node->_myval.first && !node->left->is_nil)
		binarySearchTreeInsert(node->left, element);
	else if (element->_myval.first < node->_myval.first && node->left->is_nil)
	{
		node->left = element;
		element->parent = node;
	}
	else if (element->_myval.first > node->_myval.first && !node->right->is_nil)
		binarySearchTreeInsert(node->right, element);
	else if (element->_myval.first > node->_myval.first && node->right->is_nil)
	{
		node->right = element;
		element->parent = node;
	}
}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::leftRotate(Node<Tk, Tv>* x, Node<Tk, Tv>* y)
{
	auto temp = y->right;
	y->right = temp->left;
	if (y->right != _sentinelNill)
		temp->left->parent = y;
	temp->parent = y->parent;
	if (y->parent == _sentinelNill)
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
	if (y->left != _sentinelNill)
		temp->right->parent = y;
	temp->parent = y->parent;
	if (y->parent == _sentinelNill)
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
inline void RedBlackTree<Tk, Tv>::fixRbtDelete(Node<Tk, Tv>* x)
{
	while (x != _root && x->color == Black)
	{
		if (x == x->parent->left)
		{
			auto w = x->parent->right;
			if (w->color == Red) {
				//case 1
				w->color = Black;
				x->parent->color = Red;
				leftRotate(_root, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == Black && w->right->color == Black)
			{
				//case 2
				w->color = Red;
				x = x->parent;
			}
			else if (w->right->color == Black) {
				//case 3
				w->left->color = Black;
				w->color = Red;
				rightRotate(_root, w);
				w = x->parent->right;
			}
			else {
				//case 4
				w->color = x->parent->color;
				x->parent->color = Black;
				w->right->color = Black;
				leftRotate(_root, x->parent);
			}
			x = _root;
		}
		else {
			auto w = x->parent->left;
			if (w->color == Red) {
				//case 1
				w->color = Black;
				x->parent->color = Red;
				rightRotate(_root, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == Black && w->left->color == Black)
			{
				//case 2
				w->color = Red;
				x = x->parent;
			}
			else if (w->left->color == Black) {
				//case 3
				w->right->color = Black;
				w->color = Red;
				leftRotate(_root, w);
				w = x->parent->left;
			}
			else {
				//case 4
				w->color = x->parent->color;
				x->parent->color = Black;
				w->left->color = Black;
				rightRotate(_root, x->parent);
			}
			x = _root;
		}
	}
	x->color = Black;
}
template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::transplant(Node <Tk, Tv>*u, Node <Tk, Tv>*v) {
	if (u->parent == _sentinelNill)
		_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
	{
		u->parent->right = v;
		v->parent = u->parent;
	}
}
#pragma endregion

#pragma region Operations
template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::insert(const std::pair<Tk, Tv> element) {
	Node<Tk, Tv>* temporal_node = new Node<Tk, Tv>(element.first, element.second);
	//point to _sentinal
	temporal_node->right = temporal_node->left = _sentinelNill;

	binarySearchTreeInsert(_root, temporal_node);
	_count++;
	//check red black tree for violation
	//do not fix if we insert root
	if (_count > 1)
		fixRbtInsert(temporal_node);
	else
		_root->parent = _sentinelNill;
}
template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::insert(Node<Tk, Tv>* node) {
	node->right = node->left = _sentinelNill;
	binarySearchTreeInsert(_root, node);
	_count++;
	//check red black tree for violation
	//do not fix if we insert root
	if (_count > 1)
		fixRbtInsert(node);
	else
		_root->parent = _sentinelNill;
}
template<typename Tk, typename Tv>
inline Node<Tk, Tv>* RedBlackTree<Tk, Tv>::Find(Tk key) {
	auto node = _root;
	if (_root == nullptr) return nullptr;
	while (node != _sentinelNill) {
		if (key < node->_myval.first) {
			std::cout << "At node " << node->_myval.first << " going left\n";
			node = node->left;
		}
		else if (key > node->_myval.first) {
			std::cout << "At node " << node->_myval.first << " going right\n";
			node = node->right;
		}
		else {
			std::cout << "Found node " << node->_myval.first << " terminated\n";
			return node;
		}
	}
	std::cout << "The tree does not contain node with key:" << key << "\n";
	return nullptr;
}
template<typename Tk, typename Tv>
inline Node<Tk, Tv>* RedBlackTree<Tk, Tv>::findMin(Node<Tk, Tv>* node) {
	auto temp = node;
	while (temp->left != _sentinelNill)
		temp = temp->left;
	return temp;
}
template<typename Tk, typename Tv>
inline Node<Tk, Tv>* RedBlackTree<Tk, Tv>::findMax(Node<Tk, Tv>* node) {
	auto temp = node;
	while (temp->right != _sentinelNill)
		temp = temp->right;
	return temp;
}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::remove(Tk key)
{
	auto node = Find(key);
	//no node with given key
	if (node == _sentinelNill || node == nullptr) return;

	auto y = node;
	bool y_original_color = y->color;

	Node<Tk, Tv>* x;
	if (node->left == _sentinelNill) {
		x = node->right;
		transplant(node, node->right);
	}
	else if (node->right == _sentinelNill) {
		x = node->left;
		transplant(node, node->left);
	}
	else {
		y = findMin(node->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == node) {
			x->parent = y;
		}
		else {
			transplant(y, y->right);
			y->right = node->right;
			y->right->parent = y;
		}
		transplant(node, y);
		y->left = node->left;
		y->left->parent = y;
		y->color = node->color;
	}
	if (y_original_color == Black)
		fixRbtDelete(x);

}
#pragma endregion


#pragma region Traversal

template<typename Tk, typename Tv>
Node<Tk, Tv>* RedBlackTree<Tk, Tv>::treeSuccessor(Node<Tk, Tv>* node) {

	if (_root == nullptr)
		return nullptr;

	if (node->right != nullptr)
		return findMin(node->right);

	auto temp = node->parent;

	while (temp != nullptr && node == temp->right) {
		node = temp;
		temp = temp->parent;
	}
	return temp;
}


template<typename Tk, typename Tv>
std::string RedBlackTree<Tk, Tv>::print() {

	std::stringstream ss;
	std::queue<Node<Tk, Tv>*> q;

	q.push(_root);
	// ss<<root->_myval.first<<"("<<root->height<<")("<<root->balance<<")"<<' ';
	ss << _root->_myval.first << "(" << _root->color << ")" << ' ';
	while (!q.empty()) {
		Node<Tk, Tv>* t = q.front();
		Node<Tk, Tv>* left = t->left;
		Node<Tk, Tv>* right = t->right;
		if (left != NULL) {
			q.push(left);
			// ss<<left->_myval.first<<"("<<left->height<<")("<<left->balance<<")"<<' ';
			ss << left->_myval.first << "(" << left->color << ")" << ' ';
		}
		else {
			ss << -1 << ' ';
		}
		if (right != NULL) {
			q.push(right);
			//ss<<right->_myval.first<<"("<<right->height<<")("<<right->balance<<")"<<' ';
			ss << right->_myval.first << "(" << right->color << ")" << ' ';
		}
		else {
			ss << -1 << ' ';
		}

		q.pop();
	}
	return ss.str();
}

template<typename Tk, typename Tv>
const Node<Tk, Tv>* RedBlackTree<Tk, Tv>::inOrderTraversal(const Node<Tk, Tv>* node, std::ostream& os)
{
	if (node == nullptr || node->is_nil)
		return nullptr;

	inOrderTraversal(node->left, os);
	os << node->_myval.first << "=>";
	inOrderTraversal(node->right, os);
}

#pragma endregion

#pragma region Iterator

#pragma endregion

