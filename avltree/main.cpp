#include <iostream>
#include "avltree.hpp"

int main ( int argc, const char* argv[] )
{
	typedef std::pair<int,int> intPair;
	try{
		
		//using namespace avl;
		avltree<int,int> tree;
		for(int i = 1; i < 11; ++i )
		{
			tree.insert(intPair(i,i));
		}

		tree.find(3);
	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}