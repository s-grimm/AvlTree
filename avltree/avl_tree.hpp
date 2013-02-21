#if !defined (GUARD_GRIMMINCKavl_tree_20130202_)
#define GUARD_GRIMMINCKavl_tree_20130202_

#include <functional> // std::less
#include <memory> // std::allocator
#include <utility> // std::pair
#include <iterator> //std::reverse_iterator
#include "avl_node.hpp"
#include "avl_utilities.hpp"

namespace avl{
	template <
		class Key,
		class Type,
		class Traits = std::less<Key>,
		class Allocator = std::allocator<std::pair<Key const, Type>>
		>
		class avltree {
		private:
			typedef avltree< Key, Type, Traits, Allocator>						tree;
		public:
			typedef std::pair<const Key, Type>									value_type;
			typedef Allocator													allocator_type;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::reference							reference;
			typedef Key															key_type;
			typedef Type														mapped_type;
			typedef Traits														key_compare;
			typedef typename avl_node< tree >									node;
			typedef typename node::node_ptr										node_ptr;
			typedef typename node::const_node_ptr								const_node_ptr;
			typedef typename avl_utilities< tree >								utilities;
		private:
			node_ptr _header;
			std::size_t _size;
			key_compare	_comparer;
		public:
			avltree()
			{
				utilities::init_header( _header );
				node_ptr n = new node(2, 1);
				node::set_parent( n, _header  );
				std::cout << "1st Check" << std::endl;
				std::cout << "_header " << utilities::is_header( _header ) << std::endl;
				std::cout << "n " << utilities::is_header( n ) << std::endl;
				node::set_parent( _header, n  );
				node::set_left( _header, n );
				node::set_right( _header, n );
				std::cout << "2nd Check" << std::endl;
				std::cout << "_header " << utilities::is_header( _header ) << std::endl;
				std::cout << "n " << utilities::is_header( n ) << std::endl;
				node_ptr l = new node(1,1);
				node::set_parent( l, n  );
				node::set_left( _header, l );
				node::set_left( n, l );
				node_ptr r = new node(3,1);
				node::set_parent( r, n  );
				node::set_right( _header, r );
				node::set_right( n, r );
				std::cout << "3rd Check" << std::endl;
				std::cout << "_header " << utilities::is_header( _header ) << std::endl;
				std::cout << "n " << utilities::is_header( n ) << std::endl;
				std::cout << "l " << utilities::is_header( l ) << std::endl;
				std::cout << "r " << utilities::is_header( r ) << std::endl;
				std::cout << "****************************************" << std::endl;
				std::cout << node::get_right( _header )->first << std::endl;
			}

			~avltree()
			{
				delete( _header );
			}
		};
}//end namespace avl
#endif