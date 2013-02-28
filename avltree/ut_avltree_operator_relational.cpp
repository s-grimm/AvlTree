/**	@file: ut_avltree_operator_relational.cpp
@author Garth Santor
@author gsantor@fanshaweonline.ca
@author http://www.gats.ca/
@date 2013-01-16
@version 0.0.0
@note Developed for C++ 11
@brief avltree<T> relational operator unit tests.
*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avl_tree.hpp"
using namespace avl;

typedef std::pair<int,int> intPair;
/**	operator != */
BOOST_AUTO_TEST_CASE( ut_inequality ) {
	std::cout << "NOT IMPLEMENTED: operator !=\n";
}

/**	operator == */
BOOST_AUTO_TEST_CASE( ut_equality ) {
	//avltree<int,int> tree = avltree<int,int>();

	//tree.insert(intPair(1,10) );

	//avltree<int,int> treeL = avltree<int,int>();

	//treeL.insert(intPair(1,10) );

	//if(tree == treeL)
	//		std::cout << "NOT IMPLEMENTED: operator ==\n";
	//	else
	//		BOOST_FAIL("NOT IMPLEMENTED: operator ==\n");


	std::cout << "NOT IMPLEMENTED: operator ==\n";
}

/**	operator < */
BOOST_AUTO_TEST_CASE( ut_less ) {
	std::cout << "NOT IMPLEMENTED: operator <\n";
}

/**	operator <= */
BOOST_AUTO_TEST_CASE( ut_less_equal ) {
	std::cout << "NOT IMPLEMENTED: operator <=\n";
}

/**	operator > */
BOOST_AUTO_TEST_CASE( ut_greater ) {
	std::cout << "NOT IMPLEMENTED: operator >\n";
}

/**	operator >= */
BOOST_AUTO_TEST_CASE( ut_greater_equal ) {
	std::cout << "NOT IMPLEMENTED: operator >=\n";
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