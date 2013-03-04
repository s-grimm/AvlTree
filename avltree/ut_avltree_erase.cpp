/**	@file: ut_avltree_erase.cpp
@author Garth Santor
@author gsantor@fanshaweonline.ca
@author http://www.gats.ca/
@date 2013-01-16
@version 0.0.0
@note Developed for C++ 11
@brief avltree<T>::erase() unit tests.
*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avl_tree.hpp"
using namespace avl;

/**	iterator erase( iterator ) */
BOOST_AUTO_TEST_CASE( ut_erase_iterator ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::erase(iterator)\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		avltree<char,int>::iterator it = tree.find('a');
		tree.erase(it);
		BOOST_CHECK_EQUAL( std::distance(it = tree.find('a'), tree.end()), 0 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::erase(iterator)\n" );
	}
}

/**	iterator erase( iterator, iterator ) */
BOOST_AUTO_TEST_CASE( ut_erase_iterator_iterator ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::erase(iterator,iterator)\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		avltree<char,int>::iterator it = tree.find('a');
		tree.erase(it,tree.end());
		BOOST_CHECK_EQUAL( tree.empty(), true );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::erase(iterator,iterator)\n" );
	}
}

/**	size_type erase( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_erase_key ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::erase(key)\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		tree.insert(std::pair<char,int>('c',3));
		tree.insert(std::pair<char,int>('d',4));
		tree.insert(std::pair<char,int>('e',5));
		int count = tree.erase('b');
		BOOST_CHECK_EQUAL( count, 1 );
		count = tree.erase('a');
		BOOST_CHECK_EQUAL( count, 1 );
		count = tree.erase('z');
		BOOST_CHECK_EQUAL( count, 0 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::erase(key)\n" );
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