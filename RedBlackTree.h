#pragma once
#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
enum Color :bool { Black = 0, Red = 1 };
template<typename T>
struct Node {
	T data;
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;
	bool color;
	Node(const T&);
	~Node();
};
template<typename T>
Node<T>::Node(const T& element) {
	data = element;
	color = Red;
	parent = left = right = nullptr;
}
template<typename T>
Node<T>::~Node() {
	//Todo 1_ex
	std::cout << "node with data:" << data << " deleted\n";
}

template<typename T>
class RedBlackTree {
private:
	int _count;
	Node<T>* _root;
	void binarySearchTreeInsert(Node<T>*,Node<T>*);
	void leftRotate(Node<T>*, Node<T>*);
	void rightRotate(Node<T>*, Node<T>*);
	void fixRbtInsert(Node<T>*);
	void fixRbtDelete(Node<T>*);
	void DeleteTree(Node<T>*);
public:
	RedBlackTree();
	void insert(T);
	void remove(T);
	std::string print();
	
	~RedBlackTree() {
		DeleteTree(_root);
	}
};

template<typename T>
void RedBlackTree<T>::DeleteTree(Node<T>* t) {
	//post order traversal
	if (t == nullptr)return;
	DeleteTree(t->left);
	DeleteTree(t->right);
	delete t;
}
template<typename T>
std::string RedBlackTree<T>::print() {

	std::stringstream ss;
	std::queue<Node<T>*> q;

	q.push(_root);
	// ss<<root->data<<"("<<root->height<<")("<<root->balance<<")"<<' ';
	ss << _root->data << "(" << _root->color << ")" << ' ';
	while (!q.empty()) {
		Node<T>* t = q.front();
		Node<T>* left = t->left;
		Node<T>* right = t->right;
		if (left != NULL) {
			q.push(left);
			// ss<<left->data<<"("<<left->height<<")("<<left->balance<<")"<<' ';
			ss << left->data <<"("<<left->color<<")"<< ' ';
		}
		else {
			ss << -1 << ' ';
		}
		if (right != NULL) {
			q.push(right);
			//ss<<right->data<<"("<<right->height<<")("<<right->balance<<")"<<' ';
			ss << right->data << "(" << right->color << ")" << ' ';
		}
		else {
			ss << -1 << ' ';
		}

		q.pop();
	}
	return ss.str();
}
template<typename T>
RedBlackTree<T>::RedBlackTree() {
	_count = 0;
	_root = nullptr;
}

template<typename T>
inline void RedBlackTree<T>::binarySearchTreeInsert(Node<T>* node, Node<T>* element) {
	//utility function used to perform binary search tree insert
	
	//empty tree
	if (node == nullptr) {
		element->color = Black;
		_root = element;
		return;
	}

	if (element->data < node->data && node->left != nullptr)
		binarySearchTreeInsert(node->left, element);
	else if (element->data < node->data && node->left == nullptr)
	{
		node->left = element;
		element->parent = node;
	}
	else if (element->data > node->data && node->right != nullptr)
		binarySearchTreeInsert(node->right, element);
	else if (element->data > node->data && node->right == nullptr)
	{
		node->right = element;
		element->parent = node;
	}
}

template<typename T>
inline void RedBlackTree<T>::leftRotate(Node<T>*x, Node<T>*y)
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

template<typename T>
inline void RedBlackTree<T>::rightRotate(Node<T>*x, Node<T>*y)
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

template<typename T>
inline void RedBlackTree<T>::fixRbtInput(Node<T>*node)
{
	while (  node->parent != nullptr && node->parent->color == Red) {
		if (node->parent == node->parent->parent->left)
		{
			auto uncle = node->parent->parent->right;
			if (uncle !=nullptr && uncle->color == Red){
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
				rightRotate(_root,node->parent->parent);
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
				rightRotate(_root,node);
				
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


template<typename T>
inline void RedBlackTree<T>::insert(const T element) {
	Node<T>* temporal_node = new Node<T>(element);
	binarySearchTreeInsert(_root,temporal_node);
	_count++;
	//check red black tree for violation
	//do not fix if we insert root
	if(_count >1)
	fixRBTInsert(temporal_node);
}


template<typename T>
inline void RedBlackTree<T>::fixRbtDelete(Node<T>*)
{
}
template<typename T>
inline void RedBlackTree<T>::remove(T)
{

}


