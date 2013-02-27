/**	@file: ut_avltree_insert.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T>::insert() unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avl_tree.hpp"

/**	pair<iterator,bool> insert( value_type const& ) */
BOOST_AUTO_TEST_CASE( ut_insert_value ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::insert(value)\n";

	try {
		using namespace avl;
		avltree<char,int> myTree;
		auto it = myTree.insert(std::pair<char,int>('a',1));
		BOOST_CHECK_EQUAL( it.first->second, 1 );
	}
	catch(...)
	{
		BOOST_FAIL("FAILED: avltree<T>::insert(value)\n");
	}
}



/**	iterator insert( iterator, value_type const& ) */
BOOST_AUTO_TEST_CASE( ut_insert_iterator_value ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::insert(iterator,value)\n";
	try {
		using namespace avl;
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(myTree.begin(), std::pair<char,int>('b',2));
		auto it = myTree.begin();
		BOOST_CHECK_EQUAL( it->second, 1 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::insert(iterator,value)\n" );
	}
}



/**	template <class InputIterator> void insert( InputIterator, InputIterator ) */
BOOST_AUTO_TEST_CASE( ut_insert_iterator_iterator ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::insert(iterator,iterator)\n";
	try {
		using namespace avl;
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(std::pair<char,int>('b',2));
		myTree.insert(std::pair<char,int>('c',3));
		avltree<char,int> myTree2;
		myTree2.insert(myTree.begin(), myTree.end());
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::insert(iterator,iterator)\n" );
	}
}



/**	template <class ValTy> pair<iterator,bool> insert( ValTy && ) */
BOOST_AUTO_TEST_CASE( ut_insert_T_move ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::insert(&&)\n";
	try {
		using namespace avl;
		avltree<char,int> myTree;
		std::pair<char,int> pair('a',1);
		myTree.insert(std::move(pair));
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::insert(&&)\n" );
	}
}



/**	template <class ValTy> pair<iterator,bool> insert( const_iterator, ValTy && ) */
BOOST_AUTO_TEST_CASE( ut_insert_iterator_T_move ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::insert(iterator,&&)\n";
	try {
		using namespace avl;
		avltree<char,int> myTree;
		std::pair<char,int> pair('a',1), pair2('b',2);
		myTree.insert(std::move(pair));
		myTree.insert(myTree.begin(), std::move(pair2));
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::insert(iterator,&&)\n" );
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