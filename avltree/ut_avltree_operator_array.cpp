/**	@file: ut_avltree_operator_array.cpp
	@author Garth Santor
	@author gsantor@fanshaweonline.ca
	@author http://www.gats.ca/
	@date 2013-01-16
	@version 0.0.0
	@note Developed for C++ 11
	@brief avltree<T>::operator[] unit tests.
	*/

#include <boost/test/auto_unit_test.hpp>
#include <iostream>
#include "avltree.hpp"


/**	Type& operator[]( Key const& ) */
BOOST_AUTO_TEST_CASE( ut_operator_array_key_ref ) {
	avltree<int,std::string> tree;
	tree.insert(std::pair<int,std::string>(1,"Stuff and Junk"));

	BOOST_CHECK(tree[1] == "Stuff and Junk");
	//std::cout << "NOT IMPLEMENTED: operator [&]\n";
}



/**	Type& operator[]( Key && ) */
BOOST_AUTO_TEST_CASE( ut_operator_array_key_move ) {
	// c2[move(str)] 
	std::cout << "NOT IMPLEMENTED: operator [&&]\n";
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