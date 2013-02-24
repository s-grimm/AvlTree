#include <iostream>
#include "avl_tree.hpp"
#include <map>

int main ( int argc, const char* argv[] )
{
	typedef std::pair<int,int> intPair;
	try {
		std::cout << "The Map\n";
		std::map<int, int> myMap;
		myMap.insert(intPair(1, 1));
		myMap.insert(intPair(2, 2));
		myMap.insert(intPair(3, 3));
		myMap.insert(intPair(4, 4));
		myMap.insert(intPair(5, 5));

		for( auto it = myMap.begin(); it != myMap.end(); ++it ) {
			std::cout << it->first << ":" << it->second;
			std::cout << "\t\t" << (*it).first << ":" << (*it).second << std::endl;
		}
		
		std::cout << "\nThe Tree\n";
		using namespace avl;
		avltree<int, int> myTree;
		myTree.insert(intPair(1, 1));
		myTree.insert(intPair(2, 2));
		myTree.insert(intPair(3, 3));
		myTree.insert(intPair(4, 4));
		myTree.insert(intPair(5, 5));

		avltree<int, int> myTreeConst;
		myTreeConst.insert(myTree.begin(), --myTree.end());

		std::cout << "The Tree (at)" << std::endl;
		std::cout << myTree.at(2) << std::endl;
		myTree.at(2) = 5;
		std::cout << myTree.at(2) << std::endl;

		std::cout << "The Tree (at) const" << std::endl;
		std::cout << myTreeConst.at(2) << std::endl;

		//for( auto it = myTree.begin(); it != myTree.end(); ++it ) {
		//	std::cout << it->first << ":" << it->second << std::endl;
		//	/*std::cout << "\t\t" << (*it).first << ":" << (*it).second << std::endl;*/
		//}

		//*******************************************************
		//Jovan Test Area
		//*******************************************************
		std::cout << "JOVAN TEST AREA" << std::endl;
		//avltree<int, int> jovanTree;
		std::map<int, int> jovanTree;
		std::cout << "Round one" << std::endl;
		jovanTree[1] = 1;
		jovanTree[2] = 1;
		jovanTree[3] = 1;
		jovanTree[4] = 1;
		jovanTree[5] = 1;
		for( auto it = jovanTree.begin(); it != jovanTree.end(); ++it ) {
			std::cout << it->first << ":" << it->second;
			std::cout << "\t\t" << (*it).first << ":" << (*it).second << std::endl;
		}
		std::cout << "Round Two" << std::endl;
		jovanTree[1] = 1;
		jovanTree[2] = 2;
		jovanTree[3] = 3;
		jovanTree[4] = 4;
		jovanTree[5] = 5;
		for( auto it = jovanTree.begin(); it != jovanTree.end(); ++it ) {
			std::cout << it->first << ":" << it->second;
			std::cout << "\t\t" << (*it).first << ":" << (*it).second << std::endl;
		}
		std::cout << "Round Three" << std::endl;
		for(size_t i = 0; i < jovanTree.size(); ++i)
		{
			std::cout << i << ":" << jovanTree[i] << std::endl;
		}


		std::cout << "END OF JOVAN TEST AREA" << std::endl;
		//*******************************************************
		//end of	Jovan Test Area
		//*******************************************************






	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}