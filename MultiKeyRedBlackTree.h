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
	if (y->right != nullptr)
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
	if (y->left != nullptr)
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
		auto sib = x->parent->right;
		if (x == x->parent->left) {
			//case 1
			if (sib->color == Red) {
				sib->color = Black;
				x->parent->color = Red;
				leftRotate(_root, x->parent);
				sib = x->parent->right;
			}
			if (sib->left->color == Black && sib->right->color == Black) {
				sib->color = Red;
				x = x->parent;
			}
			else if (sib->right->color == Black) {
				sib->left->color = Black;
				sib->color = Red;
				rightRotate(_root, sib);
				sib = x->parent->right;
			}
			else {
				sib->color = x->parent->color;
				x->parent->color = Black;
				sib->right->color = Black;
				leftRotate(_root, x->parent);
				x = _root;
			}
		}
		else {
			if (sib->color == Red) {
				sib->color = Black;
				x->parent->color = Red;
				rightRotate(_root, x->parent);
				sib = x->parent->left;
			}
			if (sib->right->color == Black && sib->left->color == Black) {
				sib->color = Red;
				x = x->parent;
			}
			else if (sib->left->color == Black) {
				sib->right->color = Black;
				sib->color = Red;
				leftRotate(_root, sib);
				sib = x->parent->left;
			}
			else {
				sib->color = x->parent->color;
				x->parent->color = Black;
				sib->left->color = Black;
				rightRotate(_root, x->parent);
				x = _root;
			}
		}
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
}
template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::insert(Node<Tk, Tv>* node) {
	binarySearchTreeInsert(_root, node);
	_count++;
	//check red black tree for violation
	//do not fix if we insert root
	if (_count > 1)
		fixRbtInsert(node);
}
template<typename Tk, typename Tv>
inline Node<Tk, Tv>* RedBlackTree<Tk, Tv>::Find(Tk key) {
	auto node = _root;
	if (_root == nullptr) return nullptr;
	while (node != nullptr) {
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
	while (temp->left != nullptr)
		temp = temp->left;
	return temp;
}
template<typename Tk, typename Tv>
inline Node<Tk, Tv>* RedBlackTree<Tk, Tv>::findMax(Node<Tk, Tv>* node) {
	auto temp = node;
	while (temp->right != nullptr)
		temp = temp->right;
	return temp;
}

template<typename Tk, typename Tv>
inline void RedBlackTree<Tk, Tv>::remove(Tk key)
{
	if (_root == nullptr)return;
	Node<Tk,Tv>* temp = Find(key);
	if (temp == nullptr)return;
	else {
		Node<Tk, Tv>* x;
		Node<Tk, Tv>* y;
		if (temp->left == nullptr || temp->right == nullptr)
			y = temp;
		else
			//get the inorder successor of the current node
			y = treeSuccessor(temp);
		if (y->left != nullptr)
			x = y->left;
		else
			x = y->right;
		x->parent = y->parent;
		if (y->parent == nullptr)
			_root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;

		if (y != temp) {
			temp = nullptr;
			temp=y;
		}
		if (y->color == Black)
			fixRbtDelete(x);
		_count--;
		//return y;
		delete y;
	}

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

