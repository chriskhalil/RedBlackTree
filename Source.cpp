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
	//std::cout<<dt.print()<<"\n";
	dt.insert(4);
	std::cout << dt.print() << "\n";
	return 0;
}

