#if !defined (GUARD_GRIMMINCKavl_tree_20130202_)
#define GUARD_GRIMMINCKavl_tree_20130202_

#include <functional> // std::less
#include <memory> // std::allocator
#include <utility> // std::pair
#include <iterator> //std::reverse_iterator
#include "avl_node.hpp"
#include "avl_utilities.hpp"
#include "avl_iterator.hpp"

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
			typedef typename avl_iterator< tree >								iterator;
			typedef typename const avl_iterator< tree >							const_iterator;
			typedef std::reverse_iterator<iterator>								reverse_iterator;
			typedef std::reverse_iterator<const_iterator>						const_reverse_iterator;
		private:
			node_ptr _header;
			std::size_t _size;
			key_compare	_comparer;
		public:
			avltree()
			{
				utilities::init_header( _header );
				_size = 0;
			}

			~avltree()
			{
				delete( _header );
			}

			//insert
			//std::pair<iterator,bool> insert( std::pair<Key,Type> value ) {
			void insert( const value_type& value ) {
				/*iterator it = find( value.first);
				if ( it != end() ) {
				return std::pair<iterator, bool>( it, false );
				}*/

				node_ptr newNode = new node( value.first, value.second );

				if ( !node::get_parent( _header ) ) {
					node::set_parent( newNode, _header  );
					node::set_parent( _header, newNode  );
					node::set_left( _header, newNode );
					node::set_right( _header, newNode );
					_size++;
					return;
				} else {
					node_ptr currentNode = node::get_parent( _header );

					while ( currentNode && !utilities::is_header( currentNode ) ) {
						bool compare = _comparer( currentNode->first, newNode->first );

						if ( compare ) {
							if( !node::get_right( currentNode ) ) {
								node::set_parent( newNode, currentNode );
								node::set_right( currentNode, newNode );
								_size++;

								if ( _comparer( newNode->first, node::get_left( _header)->first ) ) {
									node::set_left( _header, newNode );
								} else if ( !_comparer( newNode->first, node::get_right( _header)->first ) ) {
									node::set_right( _header, newNode );
								}
								utilities::insert_balance( currentNode, -1 );
								return;
								//		return std::pair<iterator,bool>( iterator( newNode ), true );
							} else {
								currentNode = node::get_right( currentNode );
							}// end else
						} else {
							if( !node::get_left( currentNode ) ) {
								node::set_parent( newNode, currentNode );
								node::set_left( currentNode, newNode );
								_size++;

								if ( _comparer( newNode->first, node::get_left( _header)->first ) ) {
									node::set_left( _header, newNode );
								} else if ( !_comparer( newNode->first, node::get_right( _header)->first ) ) {
									node::set_right( _header, newNode );
								}
								utilities::insert_balance( currentNode, 1 );
								return;
								//		//return std::pair<iterator,bool>( iterator( newNode ), true );
							} else {
								currentNode = node::get_left( currentNode );
							}
						} //end else compare
					} // end while
				} // end else;

				//should never hit this, but just incase it is here;
				//return std::pair<iterator, bool>(iterator( NULL ), false );
			}

			// iterator find( const key_type& key )
			void find( const key_type& key ) {
				if( node::get_parent( _header ) ) {
					node_ptr currentNode = node::get_parent( _header );

					while ( currentNode && !utilities::is_header( currentNode ) ) {
						if ( key == currentNode->first ) {
							// return iterator( currentNode )
							return;
						}

						bool compare = _comparer( currentNode->first, key );
						if ( compare ) {
							if ( node::get_right( currentNode ) ) {
								break;
							} else {
								currentNode = node::get_right( currentNode );
							}
						} else {
							if ( !node::get_left( currentNode ) ) {
								break;
							} else {
								currentNode = node::get_left( currentNode );
							}
						}
					}
				}
				return;
				// return end();
			}

			// const_iterator find ( const Key& key ) const {
			void const_find( const key_type& key ) {				// this definition needs to be changed
				if( node::get_parent( _header ) ) {
					node_ptr currentNode = node::get_parent( _header );

					while ( currentNode && !utilities::is_header( currentNode ) ) {
						if ( key == currentNode->first ) {
							// return const_iterator( currentNode )
							return;
						}

						bool compare = _comparer( currentNode->first, key );
						if ( compare ) {
							if ( node::get_right( currentNode ) ) {
								break;
							} else {
								currentNode = node::get_right( currentNode );
							}
						} else {
							if ( !node::get_left( currentNode ) ) {
								break;
							} else {
								currentNode = node::get_left( currentNode );
							}
						}
					}
				}
				return;
				// return cend();
			}
		};
}//end namespace avl
#endif