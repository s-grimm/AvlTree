#include <iostream>
#include "avl_tree.hpp"

int main ( int argc, const char* argv[] )
{
	typedef std::pair<int,int> intPair;
	try{
		
		using namespace avl;
		avltree<std::string,int> tree;
	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}