#include <iostream>
#include "avl_tree.hpp"

int main ( int argc, const char* argv[] )
{
	typedef std::pair<int,int> intPair;
	try{
		using namespace avl;
		avltree<int,int> tree;
		tree.insert(intPair(1,1));
		tree.insert(intPair(2,1));
		tree.insert(intPair(3,1));
		tree.insert(intPair(4,1));
		tree.insert(intPair(5,1));
		tree.insert(intPair(6,1));
		tree.insert(intPair(7,1));
		tree.insert(intPair(8,1));
		tree.insert(intPair(9,1));
		tree.insert(intPair(10,1));
		tree.insert(intPair(11,1));
		tree.insert(intPair(12,1));

		avltree<int,int>::iterator it;
		for( it = tree.begin(); it != tree.end(); ++it )
		{
			std::cout<< it->first << " : ";
		}
		std::cout << std::endl;
		for( it = tree.end(); it != tree.begin(); --it )
		{
			std::cout<< it->first << " : ";
		}
		std::cout << std::endl;
	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}