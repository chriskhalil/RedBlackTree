//#include "RedBlackTree.h"
#include "MultiKeyRedBlackTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define  p std::pair<std::string,int>

int main() {
	RedBlackTree<std::string,int> dt;

	//std::vector<int> v = {8,18,5,15,17,25,40,80}; //pass inorderT std::vector<int> as = {5,8,15,17,18,25,40,80};
	//std::vector<int> v = {38,13,51,10,12,40,84,25}; //pass inorder 10  12  13  25  38  40  51  84
	//std::vector<std::pair<int,int>> v =std::vector<std::pair<int,int>> v = {p(38,1),p(13,1),p(51,1),p(10,1),p(12,1),p(40,1),p(84,1),p(25,1)}; //pass inorder 10  12  13  25  38  40  51  84
	std::vector<std::pair<std::string,int>> v = {p("38",1),p("13",1),p("51",1),p("10",1),p("12",1),p("40",1),p("84",1),p("25",1)}; //pass inorder 10  12  13  25  38  40  51  84

	for (auto& x : v)
		dt.insert(x);

	
	/*std::cout << "---------------------------------------------\n";
	dt.Find(5);
	std::cout << "---------------------------------------------\n";
	dt.Find(400);
	std::cout << "---------------------------------------------\n";*/
	std::cout << "InOrder Traversal: ";
	dt.inOrderTraversal(dt.GetRoot());
	std::cout << "\n---------------------------------------------\n";
	return 0;
}

