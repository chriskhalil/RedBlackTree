#include "RedBlackTree.h"
#include <iostream>
int main() {
	RedBlackTree<int> dt;
	dt.insert(11);
	dt.insert(2);
	dt.insert(14);
	dt.insert(1);
	dt.insert(7);
	dt.insert(15);
	dt.insert(5);
	dt.insert(8);
	std::cout<<dt.print()<<"\n";
	dt.insert(4);
	std::cout <<"\nInsert 4\n"<< dt.print() << "\n";
	std::cout << "---------------------------------------------\n";
	dt.Find(5);
	std::cout << "---------------------------------------------\n";
	dt.Find(400);
	std::cout << "---------------------------------------------\n";
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot());
	std::cout << "\n---------------------------------------------\n";
	return 0;
}

