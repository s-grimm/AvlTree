/**	@file: ut_avltree_find.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T>::find() unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avltree.hpp"


/**	iterator find( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_find ) {
	try
	{
		avltree<int,int> tree;
		tree.insert(std::pair<int,int>(1,10));
		tree.insert(std::pair<int,int>(2,20));
		tree.insert(std::pair<int,int>(3,30));

		avltree<int,int>::iterator treeIterator;

		treeIterator = tree.find(2);

		BOOST_CHECK(treeIterator->second == 20);

		treeIterator = tree.find(4);

		BOOST_CHECK(treeIterator == tree.end());
	}
	catch(...)
	{
		BOOST_FAIL("FAILED: avltree<T>::find()\n");
	}
	//std::cout << "NOT IMPLEMENTED: avltree<T>::find()\n";
}



/**	const_iterator find( Key const& ) const */
BOOST_AUTO_TEST_CASE( ut_find_const )
{
	// std::cout << "NOT IMPLEMENTED: avltree<T>::find() const\n";
	try {
		avltree<char,int> myTree;
		myTree.insert(std::pair<char,int>('a',1));
		const avltree<char,int> myTree2(myTree);
		BOOST_CHECK_EQUAL( myTree2.find('a')->second, 1 );
	}
	catch( ... ) {
		BOOST_FAIL( "FAILED: avltree<T>::find() const\n" );
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