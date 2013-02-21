#if !defined (GUARD_GRIMMINCKavl_tree_20130202_)
#define GUARD_GRIMMINCKavl_tree_20130202_

#include <functional> // std::less
#include <memory> // std::allocator
#include <utility> // std::pair
#include <iterator> //std::reverse_iterator
#include "avl_node.hpp"
namespace avl{
	template <
		class Key,
		class Type,
		class Traits = std::less<Key>,
		class Allocator = std::allocator<std::pair<Key const, Type>>
		>
		class avltree {
		public:
			typedef std::pair<const Key, Type>									value_type;
			typedef Allocator													allocator_type;
			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::reference							reference;
			typedef Key															key_type;
			typedef Type														mapped_type;
			typedef Traits														key_compare;
			typedef typename avl_node< avltree< Key, Type, Traits, Allocator> >	node;
			typedef typename node::node_ptr										node_ptr;
			typedef typename node::const_node_ptr								const_node_ptr;

		private:
			node_ptr header;
		public:
			avltree()
			{
				init_header( header );
			}

			~avltree()
			{
				delete( header );
			}


		private:
			static void init_header( node_ptr& header ) {
				header = new node();
			}
		};
}//end namespace avl
#endif