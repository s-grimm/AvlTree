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
			}

			~avltree()
			{
				delete( _header );
			}
		};
}//end namespace avl
#endif