#include <iostream>
#include "avltree.hpp"

int main ( int argc, const char* argv[] )
{
	typedef std::pair<int,int> intPair;
	try{
		avltree<int,int, std::less<int> > tree;
		avltree<int,int, std::less<int> >::iterator it;
		/*auto a = tree.insert(intPair(9,1));
		a = tree.insert(intPair(6,1));
		a = tree.insert(intPair(1,1));
		a = tree.insert(intPair(4,44));
		a = tree.insert(intPair(2,1));
		tree.insert(intPair(7,13));
		tree.insert(intPair(8,1));
		tree.insert(intPair(3,1));
		tree.insert(intPair(5,21));
		tree.insert(intPair(1,10));
		tree.insert(intPair(2,20));
		tree.insert(intPair(3,30));*/
		//it = tree.find(5);
		//std::cout << it->second() << std::endl;
		//it = tree.find(4);
		//std::cout << it->second() << std::endl;
		//it = tree.find(7);
		//std::cout << it->second() << std::endl;
		//it = tree.find(20);
		//if(it != tree.end())
		//	std::cout << "Something fucked up" << std::endl;
		//else
		//	std::cout << "it == end" << std::endl;
		//for(int i = 1; i <= 1000; ++i)
		//{
		//	tree.insert(intPair(i,i));
		//}
		/*int count = 0;
		for(it = tree.begin(); it != tree.end(); ++it )
		{
		std::cout << it->first()  << " : " << it->second() << std::endl;
		++count;
		}
		std::cout<< "Total Count : " << count << std::endl;*/

		it = tree.end();
		it--;
		it--;


		int count = 0;
		for (int i = 0; i < 50; ++i)
		{
			tree.insert(intPair(i,1));
		}
		for (it = tree.find(44); it != tree.end(); ++it)
		{
			std::cout << it->first() << " : " << it->second() << std::endl;
			++count;
		}
		std::cout << "Total count: " << count << std::endl;

		//tree.clear();
	}
	catch(...)
	{
		std::cout<<"Catch Block\n";
	}
}