//#include "RedBlackTree.h"
#include "MultiKeyRedBlackTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define  p std::pair<int,int>

int main() {
	RedBlackTree<int,int> dt;
	std::stringstream ss;
	//std::vector<int> v = {8,18,5,15,17,25,40,80}; //pass inorderT std::vector<int> as = {5,8,15,17,18,25,40,80};
	//std::vector<int> v = {38,13,51,10,12,40,84,25}; //pass inorder 10  12  13  25  38  40  51  84
	//std::vector<std::pair<int,int>> v =std::vector<std::pair<int,int>> v = {p(38,1),p(13,1),p(51,1),p(10,1),p(12,1),p(40,1),p(84,1),p(25,1)}; //pass inorder 10  12  13  25  38  40  51  84
	//std::vector<std::pair<std::string,int>> v = {p("38",1),p("13",1),p("51",1),p("10",1),p("12",1),p("40",1),p("84",1),p("25",1)}; //pass inorder 10  12  13  25  38  40  51  84
	
	std::vector<std::pair<int,int>> v = {p(11,1),p(15,1),p(14,1),p(1,1),p(7,1),p(5,1),p(8,1)};

	for (auto& x : v)
		dt.insert(x);

	ss.str(std::string());
	std::cout << "Without key 2\n";
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(), ss);
	std::cout << ss.str();

	std::cout << "\n---------------------------------------------\n";
	
	ss.str(std::string());
	std::cout << "Insert key 2\n";
	dt.insert(p(2, 1));
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(), ss);
	std::cout << ss.str();

	std::cout << "\n---------------------------------------------\n";

	ss.str(std::string());

	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(),ss);
	std::cout << ss.str();
	std::cout << "\n---------------------------------------------\n";

	ss.str(std::string());
	std::cout << "Insert key 4\n";
	dt.insert(p(4, 1));
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(), ss);
	std::cout << ss.str();

	std::cout << "\n---------------------------------------------\n";
	ss.str(std::string());
	std::cout << "Deleted key 4\n";
	dt.remove(4);
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(), ss);
	std::cout << ss.str();
	std::cout << "\n---------------------------------------------\n";


	std::cout << "\n---------------------------------------------\n";
	ss.str(std::string());
	std::cout << "Deleted key 2\n";
	dt.remove(2);
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot(), ss);
	std::cout << ss.str();
	std::cout << "\n---------------------------------------------\n";
	return 0;
}

