/**	@file: ut_avltree_operator_assignment.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T> assignment operator unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include "avltree.hpp"
#include <iostream>



/**	avltree& operator=( avltree const& ) */
BOOST_AUTO_TEST_CASE( ut_operator_assign_copy )
{
	// std::cout << "NOT IMPLEMENTED: operator =(&)\n";
	avltree<char,int> myTree;
	myTree.insert( std::pair<char,int>('a',1) );
	avltree<char,int> myTree2 = myTree;
	BOOST_CHECK_EQUAL( myTree2.find('a')->second, 1 );
	BOOST_CHECK_EQUAL( myTree.find('a')->second, 1 );
}



/**	avltree& operator=( avltree && ) */
BOOST_AUTO_TEST_CASE( ut_operator_assign_move )
{
	// std::cout << "NOT IMPLEMENTED: operator =(&&)\n";
	avltree<char,int> myTree;
	myTree.insert( std::pair<char,int>('a',1) );
	avltree<char,int> myTree2 = std::move(myTree);
	BOOST_CHECK_EQUAL( myTree2.find('a')->second, 1 );
	BOOST_CHECK_NO_THROW( myTree.find('a') );
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