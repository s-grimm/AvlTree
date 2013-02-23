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
	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}