/**	@file: ut_avltree_bound.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T>::bound() unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include "avltree.hpp"
#include <iostream>

/**	iterator lower_bound( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_lower_bound_key )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::lower_bound(Key)\n";

	try {
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(std::pair<char,int>('c',5));
		myTree.insert(std::pair<char,int>('e',7));
		BOOST_CHECK_EQUAL( myTree.lower_bound('c')->second, 5 );
		BOOST_CHECK_EQUAL( myTree.lower_bound('d')->second, 7 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::lower_bound(Key)\n" );
	}

}



/**	const_iterator lower_bound( Key const& ) const */
BOOST_AUTO_TEST_CASE( ut_lower_bound_key_const )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::lower_bound(Key) const\n";

	try {
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(std::pair<char,int>('c',5));
		myTree.insert(std::pair<char,int>('e',7));
		const avltree<char,int> myTree2(myTree);
		BOOST_CHECK_EQUAL( myTree2.lower_bound('c')->second, 5 );
		BOOST_CHECK_EQUAL( myTree2.lower_bound('d')->second, 7 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::lower_bound(Key) const\n" );
	}
}



/**	iterator upper_bound( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_upper_bound_key )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::upper_bound(Key)\n";

	try {
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(std::pair<char,int>('c',5));
		myTree.insert(std::pair<char,int>('e',7));
		BOOST_CHECK_EQUAL( myTree.upper_bound('c')->second, 7 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::upper_bound(Key)\n" );
	}
}



/**	const_iterator upper_bound( Key const& ) const */
BOOST_AUTO_TEST_CASE( ut_upper_bound_key_const )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::upper_bound(Key) const\n";

	try {
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		myTree.insert(std::pair<char,int>('c',5));
		myTree.insert(std::pair<char,int>('e',7));
		const avltree<char,int> myTree2(myTree);
		BOOST_CHECK_EQUAL( myTree2.upper_bound('c')->second, 7 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::upper_bound(Key) const\n" );
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