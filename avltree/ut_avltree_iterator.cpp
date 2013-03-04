/**	@file: ut_avltree_iterator.cpp
@author Garth Santor
@author gsantor@fanshaweonline.ca
@author http://www.gats.ca/
@date 2013-01-16
@version 0.0.0
@note Developed for C++ 11
@brief avltree<T>::iterator unit tests.
*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avl_tree.hpp"
using namespace avl;

typedef std::pair <int, int> intPair;

/**	const_iterator begin() const */
BOOST_AUTO_TEST_CASE( ut_begin_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::begin() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		const avltree<char,int> tree2(tree);

		avltree<char,int>::const_iterator it = tree2.begin();
		BOOST_CHECK_EQUAL( it->second, 1 );
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::begin() const\n" );
	}
}

/**	iterator begin() */
BOOST_AUTO_TEST_CASE( ut_begin ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::begin()\n";
	try {
		avltree<char,int> tree;
		auto it = tree.insert(std::pair<char,int>('a',1)).first;
		BOOST_CHECK_EQUAL( it->second, tree.begin()->second );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::begin()\n" );
	}
}

/**	const_iterator cbegin() const */
BOOST_AUTO_TEST_CASE( ut_cbegin_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::cbegin() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		auto it = tree.cbegin();
		BOOST_CHECK_EQUAL( it->second, 1 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::cbegin() const\n" );
	}
}

/**	const_iterator cend() const */
BOOST_AUTO_TEST_CASE( ut_cend_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::cend() const\n";
	try {
		const avltree<char,int> tree;
		avltree<char,int>::const_iterator it = tree.cend();
		BOOST_CHECK( it == tree.cend() );
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::cend() const\n" );
	}
}

/**	const_reverse_iterator crbegin() const */
BOOST_AUTO_TEST_CASE( ut_crbegin_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::crbegin() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		tree.insert(std::pair<char,int>('c',3));

		avltree<char,int>::const_reverse_iterator crit = tree.crbegin();
		BOOST_CHECK_EQUAL( crit->second, 3);
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::crbegin() const\n" );
	}
}

/**	const_iterator crend() const */
BOOST_AUTO_TEST_CASE( ut_crend_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::crend() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		tree.insert(std::pair<char,int>('c',3));

		avltree<char,int>::const_reverse_iterator crit = tree.crend();
		--crit;
		BOOST_CHECK_EQUAL( crit->second, 1);
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::crend() const\n" );
	}
}

/**	const_iterator end() const */
BOOST_AUTO_TEST_CASE( ut_end_const ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::end() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		const avltree<char,int> tree2(tree);

		avltree<char,int>::const_iterator it = tree2.end();
		--it;
		BOOST_CHECK_EQUAL( it->second, 1 );
	}
	catch(...) {
		BOOST_FAIL( "FAILED: avltree<T>::end() const\n" );
	}
}

/**	iterator end() */
BOOST_AUTO_TEST_CASE( ut_end ) {
	// std::cout << "NOT IMPLEMENTED: avltree<T>::end()\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		auto it = tree.end();
		--it;
		BOOST_CHECK_EQUAL( it->second, tree.begin()->second );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::end()\n" );
	}
}

/**	const_reverse_iterator rbegin() const */
BOOST_AUTO_TEST_CASE( ut_rbegin_const ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::rbegin() const\n";
	try{
		avltree<int, int> tree;

		avltree <int, int> :: const_reverse_iterator it;

		tree.insert ( intPair ( 1, 10 ) );
		tree.insert ( intPair ( 2, 20 ) );
		tree.insert ( intPair ( 3, 30 ) );

		it = tree.crbegin( );
		BOOST_CHECK(it->first == 3);
	}
	catch(...)
	{
		BOOST_FAIL( "FAILED: avltree<T>::rbegin() const \n" );
	}
}

/**	reverse_iterator rbegin() */
BOOST_AUTO_TEST_CASE( ut_rbegin ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::rbegin()\n";
	try{
		avltree<int, int> tree;

		avltree <int, int> :: reverse_iterator it;

		tree.insert ( intPair ( 1, 10 ) );
		tree.insert ( intPair ( 2, 20 ) );
		tree.insert ( intPair ( 3, 30 ) );

		it = tree.rbegin( );
		BOOST_CHECK(it->first == 3);
	}
	catch(...)
	{
		BOOST_FAIL( "FAILED: avltree<T>::rbegin()  \n" );
	}
}

/**	const_reverse_iterator rend() const */
BOOST_AUTO_TEST_CASE( ut_rend_const ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::rend() const\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		tree.insert(std::pair<char,int>('c',3));
		avltree <char, int> :: const_reverse_iterator it = tree.crend();
		--it;
		BOOST_CHECK_EQUAL( it->second, tree.begin()->second );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::end()const\n" );
	}
}

/**	reverse_iterator rend() */
BOOST_AUTO_TEST_CASE( ut_rend ) {
	//std::cout << "NOT IMPLEMENTED: avltree<T>::rend()\n";
	try {
		avltree<char,int> tree;
		tree.insert(std::pair<char,int>('a',1));
		tree.insert(std::pair<char,int>('b',2));
		tree.insert(std::pair<char,int>('c',3));
		avltree <char, int> :: reverse_iterator it = tree.rend();
		--it;
		BOOST_CHECK_EQUAL( it->second, tree.begin()->second );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::end()\n" );
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