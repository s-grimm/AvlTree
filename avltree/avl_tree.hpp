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
			avltree( const avltree& _Right )
			{
				utilities::init_header( _header );
				for ( auto it = _Right.cbegin(); it != _Right.cend(); ++it ) {
					insert( *it );
				}

			}
			template<class InputIterator>
			avltree( InputIterator _First, InputIterator _Last ){
				utilities::init_header( _header );				
				insert(_First,_Last );
				
			}
			~avltree()
			{
				delete( _header );
			}

			// operator overloads
			tree& operator = ( tree const & rhs ) {
				utilities::init_header( _header );
				for ( auto it = rhs.begin(); it != rhs.end() ; ++it) {
					insert( *it );
				}
				return *this;
			}
			

			// iterator
			iterator				begin()			{ return iterator( node::get_left( _header ) ); }
			const_iterator			begin() const	{ return const_iterator( node::get_left( _header ) ); }
			const_iterator			cbegin() const	{ return const_iterator( node::get_left( _header ) ); }
			iterator				end()			{ return iterator( _header ); }
			const_iterator			end() const		{ return const_iterator( _header ); }
			const_iterator			cend() const	{ return const_iterator( _header ); }

			reverse_iterator		rbegin()		{ return reverse_iterator( end() ); }
			const_reverse_iterator	rbegin() const	{ return const_reverse_iterator( end() ); }
			const_iterator			crbegin() const { return const_reverse_iterator( end() ); }
			reverse_iterator		rend()			{ return reverse_iterator( begin() ); }
			const_reverse_iterator	rend() const	{ return const_reverse_iterator( begin() ); }
			const_iterator			crend() const	{ return const_reverse_iterator( begin() ); }

			//*******************************************************
			//Empty
			//*******************************************************
			bool empty() const _NOEXCEPT
			{	// return true only if sequence is empty
			return (size() == 0);
			}
			//*******************************************************
			//Swap
			//*******************************************************
			void swap( tree& right)
			{	
				tree tempTree = right;
				right = *this;
				*this = tempTree;
			}
			//*******************************************************
			//SIZE
			//*******************************************************
			size_type size() const _NOEXCEPT
			{	// return length of sequence
			return _size;
			}
			//*******************************************************
			//AT
			//*******************************************************
			Type& at( const Key& key ) {
				return this->find(key)->second;
			}
			//*******************************************************
			//AT
			//*******************************************************
			const Type& at( const Key& key ) const {
				return this->find(key)->second;
			}
			//*******************************************************
			//ARRAY
			//*******************************************************
			Type& operator[](const Key& key)
			{
				iterator itr = find(key);
				if(itr != end() && key == itr->first)
				{
					return itr->second;
				}
				else
				{
					std::pair<iterator,bool> inserted =  insert(value_type(key,mapped_type()));
					itr = inserted.first;
					
				}
				return itr->second;
			}
			Type& operator[]( Key&& key)
			{
				
				iterator itr = find(key);
				if(itr != end() && key == itr->first)
				{
					return itr->second;
				}
				else
				{
					std::pair<iterator,bool> inserted =  insert(value_type(std::move(key),mapped_type()));
					itr = inserted.first;
					
				}
				return itr->second;
			}
			//*******************************************************
			//INSERT
			//*******************************************************
			std::pair<iterator,bool> insert( const value_type& value ) {
				/*iterator it = find( value.first);
				if ( it != end() ) {
				return std::pair<iterator, bool>( it, false );
				}*/

				node_ptr newNode = new node( value );

				if ( !node::get_parent( _header ) ) {
					node::set_parent( newNode, _header  );
					node::set_parent( _header, newNode  );
					node::set_left( _header, newNode );
					node::set_right( _header, newNode );
					_size++;
					return std::pair<iterator,bool>( iterator( newNode ), true );
				}
				node_ptr currentNode = node::get_parent( _header );

				while ( currentNode && !utilities::is_header( currentNode ) ) {
					bool compare = _comparer( currentNode->_value.first, newNode->_value.first );

					if ( compare ) {
						if( !node::get_right( currentNode ) ) {
							node::set_parent( newNode, currentNode );
							node::set_right( currentNode, newNode );
							_size++;

							if ( _comparer( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
								node::set_left( _header, newNode );
							} else if ( !_comparer( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
								node::set_right( _header, newNode );
							}
							utilities::insert_balance( currentNode, -1 );
							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = node::get_right( currentNode );
						}// end else
					} else {
						if( !node::get_left( currentNode ) ) {
							node::set_parent( newNode, currentNode );
							node::set_left( currentNode, newNode );
							_size++;

							if ( _comparer( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
								node::set_left( _header, newNode );
							} else if ( !_comparer( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
								node::set_right( _header, newNode );
							}
							utilities::insert_balance( currentNode, 1 );
							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = node::get_left( currentNode );
						}
					} //end else compare
				} // end while
				return std::pair<iterator,bool>( iterator( newNode ), false ); // a nice little level 4 warning about not all code paths returning a value
			}
			//*******************************************************
			//INSERT
			//*******************************************************
			std::pair<iterator,bool> insert(value_type&& value)
			{
				node_ptr newNode = new node( std::move(value) );

				if ( !node::get_parent( _header ) ) {
					node::set_parent( newNode, _header  );
					node::set_parent( _header, newNode  );
					node::set_left( _header, newNode );
					node::set_right( _header, newNode );
					_size++;
					return std::pair<iterator,bool>( iterator( newNode ), true );
				}
				node_ptr currentNode = node::get_parent( _header );

				while ( currentNode && !utilities::is_header( currentNode ) ) {
					bool compare = _comparer( currentNode->_value.first, newNode->_value.first );

					if ( compare ) {
						if( !node::get_right( currentNode ) ) {
							node::set_parent( newNode, currentNode );
							node::set_right( currentNode, newNode );
							_size++;

							if ( _comparer( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
								node::set_left( _header, newNode );
							} else if ( !_comparer( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
								node::set_right( _header, newNode );
							}
							utilities::insert_balance( currentNode, -1 );
							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = node::get_right( currentNode );
						}// end else
					} else {
						if( !node::get_left( currentNode ) ) {
							node::set_parent( newNode, currentNode );
							node::set_left( currentNode, newNode );
							_size++;

							if ( _comparer( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
								node::set_left( _header, newNode );
							} else if ( !_comparer( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
								node::set_right( _header, newNode );
							}
							utilities::insert_balance( currentNode, 1 );
							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = node::get_left( currentNode );
						}
					} //end else compare
				} // end while
				return std::pair<iterator,bool>( iterator( newNode ), false ); // a nice little level 4 warning about not all code paths returning a value
			}
			
			//*******************************************************
			//INSERT
			//*******************************************************
			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{			
			for (; first != last; ++first)
				insert(*first);
			}			

			//*******************************************************
			//Find
			//*******************************************************
			iterator find( const key_type& key ) {
				if( node::get_parent( _header ) ) {
					node_ptr currentNode = node::get_parent( _header );

					while ( currentNode ) {
						if ( key == currentNode->_value.first ) {
							return iterator( currentNode );
						}

						bool compare = _comparer( currentNode->_value.first, key );
						if ( compare ) {
							if ( !node::get_right( currentNode ) ) {
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
				return end();
			}
			//*******************************************************
			//Find
			//*******************************************************
			const_iterator find( const key_type& key ) const {				
				if( node::get_parent( _header ) ) {
					node_ptr currentNode = node::get_parent( _header );

					while ( currentNode ) {
						if ( key == currentNode->_value.first ) {
							return const_iterator( currentNode );
						}

						bool compare = _comparer( currentNode->_value.first, key );
						if ( compare ) {
							if ( !node::get_right( currentNode ) ) {
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
				return cend();
			}
		};
}//end namespace avl
#endif