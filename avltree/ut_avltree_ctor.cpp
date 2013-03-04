/**	@file: ut_avltree_ctor.cpp
@author Garth Santor
@author gsantor@fanshaweonline.ca
@author http://www.gats.ca/
@date 2013-01-16
@version 0.0.0
@note Developed for C++ 11
@brief avltree<T>::ctor() unit tests.
*/

#include <boost/test/auto_unit_test.hpp>
#include "avl_tree.hpp"
#include <iostream>
using namespace avl;
/**	avltree() */
BOOST_AUTO_TEST_CASE( ut_ctor_default )
{
	//std::cout << "NOT IMPLEMENTED: avltree<T>::avltree()\n";
	try {
		avltree<char,int> tree;
		BOOST_CHECK( tree.empty() );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree()\n" );
	}
}

/**	explicit avltree( Traits const& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_traits_ref )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree( Traits& )\n";
	try {
		avltree<char,int,std::greater<char>> tree;
		tree.insert(std::pair<char,int>('b',20));
		tree.insert(std::pair<char,int>('a',10));
		tree.insert(std::pair<char,int>('c',30));
		auto it = tree.begin();
		BOOST_CHECK_EQUAL( it->second, 30 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED:  avltree<T>::avltree( Traits& )\n" );
	}
}

/**	avltree( Traits const&, Allocator const& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_traits_ref_allocator_ref )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree( traits&, allocator& )\n";
	try	{
		avltree<int,int> tree = avltree<int,int>();
		avltree<int, int>::allocator_type treeAllocator;
		treeAllocator = tree.get_allocator();
		avltree<int,int> tree2(std::less<int>(), treeAllocator);
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree( traits&, allocator& )\n" );
	}
}

/**	avltree( avltree& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_avltree_ref )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree(avltree&)\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));

		avltree<char,int> copyTree(tree);
		BOOST_CHECK_EQUAL( copyTree['a'], tree['a'] );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree(avltree&)\n" );
	}
}

/**	avltree( InputIterator, InputIterator ) */
BOOST_AUTO_TEST_CASE( ut_ctor_iterator_iterator )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree(iterator,iterator)\n";
	try {
		avltree<char,int> tree;

		tree.insert(std::pair<char,int>('a',100));
		tree.insert(std::pair<char,int>('b',200));
		tree.insert(std::pair<char,int>('c',300));
		tree.insert(std::pair<char,int>('d',400));
		tree.insert(std::pair<char,int>('e',500));

		avltree<char,int>::iterator it = tree.find('b');
		avltree<char,int>::iterator it2 = tree.find('e');

		avltree<char,int> rangeTree (it, it2);
		avltree<char,int>::iterator it3 = rangeTree.begin();
		BOOST_CHECK( it3->second == 200 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree(iterator,iterator)\n" );
	}
}

/**	avltree( InputIterator, InputIterator, Traits const& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_iterator_iterator_traits )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree(iterator,iterator,traits)\n";
	try {
		avltree<char,int,std::greater<char>> tree;

		tree.insert(std::pair<char,int>('a',100));
		tree.insert(std::pair<char,int>('b',200));
		tree.insert(std::pair<char,int>('c',300));
		tree.insert(std::pair<char,int>('d',400));
		tree.insert(std::pair<char,int>('e',500));

		avltree<char,int,std::greater<char>>::iterator it = tree.find('b');
		avltree<char,int,std::greater<char>>::iterator it2 = tree.find('e');

		avltree<char,int,std::greater<char>> rangeTree (it2, it);
		avltree<char,int,std::greater<char>>::iterator it3 = rangeTree.begin();
		BOOST_CHECK_EQUAL( it3->second, 500 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree(iterator,iterator)\n" );
	}
}

/**	avltree( InputIterator, InputIterator, Traits const&, allocator& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_iterator_iterator_traits_allocator )
{
	//std::cout << "NOT IMPLEMENTED: avltree<T>::avltree(iterator,iterator,traits,allocator)\n";
	try {
		avltree<char,int,std::less<char>,std::allocator<std::pair<const char,int>>> tree;

		tree.insert(std::pair<char,int>('a',100));
		tree.insert(std::pair<char,int>('b',200));
		tree.insert(std::pair<char,int>('c',300));
		tree.insert(std::pair<char,int>('d',400));
		tree.insert(std::pair<char,int>('e',500));

		avltree<char,int,std::less<char>,std::allocator<std::pair<const char,int>>>::iterator it = tree.find('b');
		avltree<char,int,std::less<char>,std::allocator<std::pair<const char,int>>>::iterator it2 = tree.find('e');

		avltree<char,int,std::greater<char>> rangeTree (it, it2);
		avltree<char,int,std::greater<char>>::iterator it3 = rangeTree.begin();
		BOOST_CHECK_EQUAL( it3->second, 500 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree(iterator,iterator)\n" );
	}
}

/**	avltree( avltree&& ) */
BOOST_AUTO_TEST_CASE( ut_ctor_avltree_move )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::avltree(avltree&&)\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',100));
		avltree<char,int> moveTree (std::move(tree));

		BOOST_CHECK( moveTree.find('a')->second == 100 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::avltree(avltree&&)\n" );
	}
}

/*=============================================================

Revision History

Version 0.0.0: 2013-01-16
Alpha release.

=============================================================

Copyright Garth Santor

The copyright to the computer program(s) herein
is the property of Garth Santor of Canada.
The program(s) may be used and/or copied only with
the written permission of Garth Santor
or in accordance with the terms and conditions
stipulated in the agreement/contract under which
the program(s) have been supplied.
=============================================================*/