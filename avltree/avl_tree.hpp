// ***********************************************************************
// Assembly         : avltree
// Author           : Shane Grimminck
// Created          : 02-21-2013
//
// Last Modified By : Shane Grimminck
// Last Modified On : 03-01-2013
// ***********************************************************************
// <summary>The implementation of the avltree class</summary>
// ***********************************************************************
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
	/// <summary>
	/// Class avltree
	/// </summary>
	template < class Key, class Type, class Traits = std::less<Key>, class Allocator = std::allocator< std::pair< Key const, Type> > >
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
		typedef typename tree::value_type*									pointer;
		typedef typename avl_node< tree >									node;
		typedef typename node::node_ptr										node_ptr;
		typedef typename node::const_node_ptr								const_node_ptr;
		typedef typename avl_utilities< tree >								utilities;
		typedef typename avl_iterator< tree >								iterator;
		typedef typename const_avl_iterator< tree >							const_iterator;
		typedef typename std::reverse_iterator<iterator>					reverse_iterator;
		typedef typename std::reverse_iterator<const_iterator>				const_reverse_iterator;
	private:
		/// <summary>
		/// The _header node
		/// </summary>
		node_ptr _header;
		/// <summary>
		/// The size of the tree
		/// </summary>
		std::size_t _size;
		/// <summary>
		/// The key comparer
		/// </summary>
		key_compare	_keyComparison;
		/// <summary>
		/// The allocator
		/// </summary>
		allocator_type _alloc;
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		avltree() {
			utilities::init_header( _header );
			_size = 0;
		}
		/// <summary>
		/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		/// <param name="_Right">The _ right.</param>
		avltree( const avltree& _Right ) {
			utilities::init_header( _header );
			_size = 0;
			for ( auto it = _Right.cbegin(); it != _Right.cend(); ++it ) {
				insert( *it );
			}
		}
		/// <summary>
		/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		/// <param name="_Right">The _ right.</param>
		avltree( avltree&& _Right )	{
			utilities::init_header( _header );
			_size = 0;
			for ( auto it = _Right.cbegin(); it != _Right.cend(); ++it ) {
				insert( std::move(*it) );
			}
			_Right.clear();
		}
		/// <summary>
		/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		/// <param name="_First">The _ first.</param>
		/// <param name="_Last">The _ last.</param>
		template<class InputIterator>
		avltree( InputIterator _First, InputIterator _Last ) {
			utilities::init_header( _header );
			_size = 0;
			for (; _First != _Last; ++_First) {
				insert( *_First );
			}
			insert( *_Last );
		}
		/// <summary>
		/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <param name="alloc">The alloc.</param>
		avltree( key_compare key, allocator_type alloc ) {
			utilities::init_header( _header );
			_size = 0;
			_keyComparison = key;
			_alloc = alloc;
		}
		/// <summary>
		/// Finalizes an instance of the <see cref="avltree{Key, Type, Traits, Allocator}"/> class.
		/// </summary>
		~avltree()
		{
			utilities::clear_tree( node::get_parent( _header ) );
			delete( _header );
		}

		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>tree &.</returns>
		tree& operator = ( tree const & rhs ) {
			clear();
			delete( _header );//delete the header and re init it to prevent memory leaks
			utilities::init_header( _header );
			for ( auto it = rhs.begin(); it != rhs.end() ; ++it) {
				insert( *it );
			}
			return *this;
		}
		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>tree &.</returns>
		tree& operator = ( tree&& rhs ) {
			clear();
			delete( _header ); //delete the header and re init it to prevent memory leaks
			utilities::init_header( _header );
			for ( auto it = rhs.begin(); it != rhs.end() ; ++it) {
				insert( std::move(*it) );
			}
			return *this;
		}

		/// <summary>
		/// Begins this instance.
		/// </summary>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator				begin()			{ return iterator( node::get_left( _header ) ); }
		/// <summary>
		/// Begins this instance.
		/// </summary>
		/// <returns>const_iterator.</returns>
		const_iterator			begin() const	{ return const_iterator( node::get_left( _header ) ); }
		/// <summary>
		/// Cbegins this instance.
		/// </summary>
		/// <returns>const_iterator.</returns>
		const_iterator			cbegin() const	{ return const_iterator( node::get_left( _header ) ); }
		/// <summary>
		/// Ends this instance.
		/// </summary>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator				end()			{ return iterator( _header ); }
		/// <summary>
		/// Ends this instance.
		/// </summary>
		/// <returns>const_iterator.</returns>
		const_iterator			end() const		{ return const_iterator( _header ); }
		/// <summary>
		/// Cends this instance.
		/// </summary>
		/// <returns>const_iterator.</returns>
		const_iterator			cend() const	{ return const_iterator( _header ); }

		/// <summary>
		/// Rbegins this instance.
		/// </summary>
		/// <returns>std.reverse_iterator{_RanIt}.</returns>
		reverse_iterator		rbegin()		{ return reverse_iterator( _header ); }
		/// <summary>
		/// Rbegins this instance.
		/// </summary>
		/// <returns>const_reverse_iterator.</returns>
		const_reverse_iterator	rbegin() const	{ return const_reverse_iterator( _header ); }
		/// <summary>
		/// Crbegins this instance.
		/// </summary>
		/// <returns>const_reverse_iterator.</returns>
		const_reverse_iterator	crbegin() const { return const_reverse_iterator( _header ); }
		/// <summary>
		/// Rends this instance.
		/// </summary>
		/// <returns>std.reverse_iterator{_RanIt}.</returns>
		reverse_iterator		rend()			{ return reverse_iterator( node::get_left( _header ) ); }
		/// <summary>
		/// Rends this instance.
		/// </summary>
		/// <returns>const_reverse_iterator.</returns>
		const_reverse_iterator	rend() const	{ return const_reverse_iterator( node::get_left( _header ) ); }
		/// <summary>
		/// Crends this instance.
		/// </summary>
		/// <returns>const_reverse_iterator.</returns>
		const_reverse_iterator	crend() const	{ return const_reverse_iterator( node::get_left( _header ) ); }

		/// <summary>
		/// Empties this instance.
		/// </summary>
		/// <returns>bool.</returns>
		bool empty() const _NOEXCEPT {	// return true only if sequence is empty
			return (size() == 0);
		}

		/// <summary>
		/// Emplaces the specified value.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<iterator, bool> emplace( value_type&& value) {
			iterator newNode = find(value.first);
			if(newNode == end()) {
				return insert(std::move(value));
			}
			return std::pair<iterator, bool> (newNode,false);
		}
		/// <summary>
		/// Emplace_hints the specified where.
		/// </summary>
		/// <param name="where">The where.</param>
		/// <param name="value">The value.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<iterator, bool> emplace_hint (iterator where, value_type&& value) {
			iterator newNode = find(value.first);
			if (newNode == end()) {
				return std::pair<iterator,bool>(insert(where,value), true);
			}
			else {
				return std::pair<iterator,bool>(newNode, false);
			}
		}

		/// <summary>
		/// Swaps the specified right.
		/// </summary>
		/// <param name="right">The right.</param>
		void swap( tree& right)	{
			node_ptr tmp =  _header;
			size_type size = _size;

			_header = right._header;
			_size = right._size;

			right._header = tmp;
			right._size = size;
		}

		/// <summary>
		/// Sizes this instance.
		/// </summary>
		/// <returns>size_type.</returns>
		size_type size() const _NOEXCEPT {
			return _size;
		}

		/// <summary>
		/// Ats the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>Type &.</returns>
		Type& at( const Key& key ) {
			auto it = find(key);
			if (it != end() ) {
				return it->second;
			}
			throw std::out_of_range("Out of Range");
		}
		/// <summary>
		/// Ats the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>const Type &.</returns>
		const Type& at( const Key& key ) const {
			auto it = find(key);
			if (it != end() ) {
				return it->second;
			}
			throw std::out_of_range("Out of Range");
		}

		/// <summary>
		/// Operator[]s the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>Type &.</returns>
		Type& operator[]( const Key& key ) {
			iterator itr = find(key);
			if(itr != end() && key == itr->first) {
				return itr->second;
			} else {
				std::pair< iterator, bool > inserted =  insert( value_type( key, mapped_type() ) );
				itr = inserted.first;
			}
			return itr->second;
		}
		/// <summary>
		/// Operator[]s the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>Type &.</returns>
		Type& operator[]( Key&& key) {
			iterator itr = find(key);
			if(itr != end() && key == itr->first) {
				return itr->second;
			} else {
				std::pair<iterator,bool> inserted =  insert( value_type( std::move( key ), mapped_type() ) );
				itr = inserted.first;
			}
			return itr->second;
		}

		/// <summary>
		/// Counts the specified _key type.
		/// </summary>
		/// <param name="_keyType">Type of the _key.</param>
		/// <returns>size_type.</returns>
		size_type count( const key_type& _keyType ) const {
			return find( _keyType ) != end() ? 1 : 0;
		}

		/// <summary>
		/// Inserts the specified value.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<iterator,bool> insert( const value_type& value ) {
			iterator it = find( value.first );
			if ( it != end() ) {
				return std::pair<iterator, bool>( it, false );
			}

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
				bool compare = _keyComparison( currentNode->_value.first, newNode->_value.first );

				if ( compare ) {
					if( !node::get_right( currentNode ) ) {
						node::set_parent( newNode, currentNode );
						node::set_right( currentNode, newNode );
						_size++;

						if ( _keyComparison( newNode->_value.first, node::get_left( _header )->_value.first ) ) {
							node::set_left( _header, newNode );
						} else if ( !_keyComparison( newNode->_value.first, node::get_right( _header )->_value.first ) ) {
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

						if ( _keyComparison( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
							node::set_left( _header, newNode );
						} else if ( !_keyComparison( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
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
		/// <summary>
		/// Inserts the specified value.
		/// </summary>
		/// <param name="value">The value.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<iterator,bool> insert(value_type&& value) {
			iterator it = find( value.first);
			if ( it != end() ) {
				return std::pair<iterator, bool>( it, false );
			}

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
				bool compare = _keyComparison( currentNode->_value.first, newNode->_value.first );

				if ( compare ) {
					if( !node::get_right( currentNode ) ) {
						node::set_parent( newNode, currentNode );
						node::set_right( currentNode, newNode );
						_size++;

						if ( _keyComparison( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
							node::set_left( _header, newNode );
						} else if ( !_keyComparison( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
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

						if ( _keyComparison( newNode->_value.first, node::get_left( _header)->_value.first ) ) {
							node::set_left( _header, newNode );
						} else if ( !_keyComparison( newNode->_value.first, node::get_right( _header)->_value.first ) ) {
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
		/// <summary>
		/// Inserts the specified first.
		/// </summary>
		/// <param name="first">The first.</param>
		/// <param name="last">The last.</param>
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last) {
			for (; first != last; ++first) {
				insert(*first);
			}
		}
		/// <summary>
		/// Inserts the specified where.
		/// </summary>
		/// <param name="where">The where.</param>
		/// <param name="value">The value.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator insert(iterator hint, const value_type& value)
		{
			if (find(value.first) != end()) {
				return find(value.first);
			}
			else if (empty()) {
				return insert(value).first;
			}

			if(hint == end()) {
				--hint;
			}
			while(hint != begin() && _keyComparison(value.first, hint->first)) {
				--hint;
			}
			while(hint != end() && !_keyComparison(value.first, hint->first)) {
				++hint;
			}
			if(hint == end()) {
				--hint;
			}
			return insert(value).first;
		}

		/// <summary>
		/// Erases the specified where.
		/// </summary>
		/// <param name="where">The where.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator erase ( iterator _iterator ) {
			key_type oldKey = _iterator->first;
			if (erase(oldKey) == 1) {
				for (auto it = begin(); it != end(); ++it) {
					if (it->first > oldKey) {
						return it;
					}
				}
			}
			return end();
		}
		/// <summary>
		/// Erases the specified first.
		/// </summary>
		/// <param name="first">The first.</param>
		/// <param name="last">The last.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator erase (iterator first, iterator last ) {
			key_type oldKey;
			if (last == end()) {
				oldKey = rbegin()->first;
			}
			else {
				oldKey = last->first;
			}
			for (; first != last; ) {
				if (first == last) {
					break;
				}
				erase(first++->first);
			}
			for (auto it = begin(); it != end(); ++it) {
				if (empty()) {
					return end();
				}
				if (it->first > oldKey) {
					return it;
				}
			}
			return end();
		}
		/// <summary>
		/// Erases the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>size_type.</returns>
		size_type erase( const key_type& key ) {
			node_ptr node = utilities::find_node( node::get_parent( _header ), key );
			node_ptr oldNode = node;
			if ( node ) {
				node_ptr left = node::get_left( node );
				node_ptr right = node::get_right( node );

				if ( !left ) {
					if ( !right ) {
						if ( node == node::get_parent( _header ) ) {
							delete( node);
							delete( _header);
							utilities::init_header( _header );
						} else {
							node_ptr parent = node::get_parent( node );
							if ( node::get_left( parent ) == node ) {
								delete( node::get_left( parent ) );
								node::set_left( parent, nullptr );
								utilities::delete_balance( parent, -1 );
							} else {
								delete( node::get_right( parent ) );
								node::set_right( parent, nullptr );
								utilities::delete_balance( parent, 1 );
							}
						}
					} else {
						utilities::succeed( node, right );
						utilities::delete_balance( node, 0 );
					}
				} else if ( !right ) {
					utilities::succeed( node, left );
					utilities::delete_balance( node, 0 );
				} else {
					node_ptr successor = right;
					if ( !node::get_left( successor ) ) {
						node_ptr parent = node::get_parent( node );
						node::set_parent( successor, parent );
						node::set_left( successor, left );
						node::set_balance( successor, node::get_balance( node ) );

						if ( left ) {
							node::set_parent( left, successor );
						}

						if ( node == node::get_parent( _header ) ) {
							node::set_parent( _header, successor );
							node::set_parent( successor, _header );
						} else {
							if ( node::get_left( parent ) == node ) {
								node::set_left( parent, successor );
							} else {
								node::set_right( parent, successor );
							}
						}
						utilities::delete_balance( successor, 1 );
						delete( oldNode );
					} else {
						successor = utilities::minimum( successor );
						node_ptr parent = node::get_parent( node );
						node_ptr successorParent = node::get_parent( successor );
						node_ptr successorRight = node::get_right( successor );

						if ( node::get_left( successorParent ) == successor ) {
							node::set_left( successorParent, successorRight );
						} else {
							node::set_right( successorParent, successorRight );
						}

						if ( successorRight ) {
							node::set_parent( successorRight, successorParent );
						}

						node::set_parent( successor, parent );
						node::set_left( successor, left );
						node::set_balance( successor, node::get_balance( node ) );
						node::set_right( successor, right );
						node::set_parent( right, successor );

						if ( left ) {
							node::set_parent( left, successor );
						}

						if ( node == node::get_parent( _header ) ) {
							node::set_parent( _header, successor );
							node::set_parent( successor, _header );
						} else {
							if ( node::get_left( parent ) == node ) {
								node::set_left( parent, successor );
							} else {
								node::set_right( parent, successor );
							}
						}
						utilities::delete_balance( successorParent, -1 );
						delete( oldNode );
					}
				}
				--_size;
				return 1;
			}
			return 0;
		}

		/// <summary>
		/// Finds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator find( const key_type& key ) {
			if( node::get_parent( _header ) ) {
				node_ptr currentNode = node::get_parent( _header );

				while ( currentNode ) {
					if ( key == currentNode->_value.first ) {
						return iterator( currentNode );
					}

					bool compare = _keyComparison( currentNode->_value.first, key );
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
		/// <summary>
		/// Finds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>const_iterator.</returns>
		const_iterator find( const key_type& key ) const {
			if( node::get_parent( _header ) ) {
				node_ptr currentNode = node::get_parent( _header );

				while ( currentNode ) {
					if ( key == currentNode->_value.first ) {
						return const_iterator( currentNode );
					}

					bool compare = _keyComparison( currentNode->_value.first, key );
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

		/// <summary>
		/// Lower_bounds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator lower_bound( const key_type& key )
		{
			iterator bound = this->find(key);
			if (bound != end()) {
				return bound;
			}

			for(bound = this->begin(); bound != this->end(); ++bound) {
				if (!_keyComparison(bound->first, key)) {
					return bound;
				}
			}

			return bound;
		}
		/// <summary>
		/// Lower_bounds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>const_iterator.</returns>
		const_iterator lower_bound( const key_type& key ) const
		{
			const_iterator cbound = this->find(key);
			if (cbound != end()) {
				return cbound;
			}

			const_iterator bound;
			for(bound = this->cbegin(); bound != this->cend(); ++bound) {
				if (!_keyComparison(bound->first, key)) {
					const_iterator newcbound = bound;
					return newcbound;
				}
			}

			return bound;
		}

		/// <summary>
		/// Upper_bounds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>std.iterator{_Category, _Ty, _Diff, _Pointer, _Reference}.</returns>
		iterator upper_bound( const key_type& key )
		{
			iterator bound = this->find(key);
			if (bound != end()) {
				return ++bound;
			}

			for(bound = this->begin(); bound != this->end(); ++bound) {
				if (!_keyComparison(bound->first, key)) {
					return bound;
				}
			}

			return bound;
		}
		/// <summary>
		/// Upper_bounds the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>const_iterator.</returns>
		const_iterator upper_bound( const key_type& key ) const
		{
			const_iterator cbound = this->find(key);
			if (cbound != cend()) {
				const_iterator nextcbound = ++cbound;
				return nextcbound;
			}

			const_iterator bound;
			for(bound = this->cbegin(); bound != this->cend(); ++bound) {
				if (!_keyComparison(bound->first, key)) {
					const_iterator newcbound = bound;
					return newcbound;
				}
			}

			return bound;
		}

		/// <summary>
		/// Equal_ranges the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<const_iterator, const_iterator> equal_range ( const key_type& key ) const
		{
			return std::pair <const_iterator, const_iterator>(lower_bound(key),upper_bound(key));
		}
		/// <summary>
		/// Equal_ranges the specified key.
		/// </summary>
		/// <param name="key">The key.</param>
		/// <returns>std.pair{_Ty1, _Ty2}.</returns>
		std::pair<iterator, iterator> equal_range ( const key_type& key )
		{
			return std::pair<iterator, iterator>(lower_bound(key),upper_bound(key));
		}

		/// <summary>
		/// Max_sizes this instance.
		/// </summary>
		/// <returns>size_type.</returns>
		size_type max_size () const {
			return _alloc.max_size();
		}

		/// <summary>
		/// Get_allocators this instance.
		/// </summary>
		/// <returns>allocator_type.</returns>
		allocator_type get_allocator() const {
			return _alloc;
		}

		/// <summary>
		/// Clears this instance.
		/// </summary>
		void clear(){
			utilities::clear_tree( node::get_parent( _header ) );
			_size = 0;
			delete( _header );
			utilities::init_header( _header );
		}

		/// <summary>
		/// Class value_compare
		/// </summary>
		class value_compare	: public std::binary_function<value_type, value_type, bool>
		{
		public:
			/// <summary>
			/// Operator()s the specified _ left.
			/// </summary>
			/// <param name="_Left">The _ left.</param>
			/// <param name="_Right">The _ right.</param>
			/// <returns>bool.</returns>
			bool operator()( const value_type& _Left,
				const value_type& _Right ) const
			{	// test if _Left precedes _Right by comparing just keys
				return (comp(_Left.first, _Right.first));
			}

			/// <summary>
			/// Initializes a new instance of the <see cref="avltree{Key, Type, Traits, Allocator}.value_compare"/> class.
			/// </summary>
			/// <param name="_Pred">The _ pred.</param>
			value_compare( key_compare _Pred )
				: comp(_Pred)
			{	// construct with specified predicate
			}
		protected:
			/// <summary>
			/// The comp
			/// </summary>
			key_compare comp;	// the comparator predicate for keys
		};
		/// <summary>
		/// Value_comps this instance.
		/// </summary>
		/// <returns>avl.avltree{Key, Type, Traits, Allocator}.value_compare.</returns>
		value_compare value_comp() const
		{	// return object for comparing values
			return (value_compare(key_comp()));
		}

		/// <summary>
		/// Key_comps this instance.
		/// </summary>
		/// <returns>key_compare.</returns>
		key_compare key_comp( ) const
		{	// return object for comparing values
			return _keyComparison;
		}
	};

	/// <summary>
	/// Operator==s the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator == ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		if(left.size() != right.size())	{
			return false;
		}
		avltree<Key,Type>::const_iterator lhs = left.cbegin();
		avltree<Key,Type>::const_iterator rhs = right.cbegin();
		while(lhs != left.cend() && rhs != right.cend() ) {
			if(lhs->first != rhs->first || lhs->second != rhs->second) {
				return false;
			}
			++lhs;
			++rhs;
		}
		return true;
	}
	/// <summary>
	/// Operator!=s the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator != ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		return (!(left == right));
	}
	/// <summary>
	/// Operators the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator < ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		avltree<Key,Type>::const_iterator lhs = left.cbegin();
		avltree<Key,Type>::const_iterator rhs = right.cbegin();
		while(lhs != left.cend() && rhs != right.cend() ) {
			if(lhs->first != rhs->first || lhs->second != rhs->second) {
				if(lhs->first < rhs->first || lhs->second < rhs->second) {
					return true;
				}
			}
			++lhs;
			++rhs;
		}
		return false;
	}
	/// <summary>
	/// Operator>s the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator > ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		return ( right < left );
	}
	/// <summary>
	/// Operators the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator <= ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		return ( !(right < left) );
	}
	/// <summary>
	/// Operator>=s the specified left.
	/// </summary>
	/// <param name="left">The left.</param>
	/// <param name="right">The right.</param>
	/// <returns>bool.</returns>
	template < class Key, class Type >
	bool operator >= ( const avltree< Key, Type >& left, const avltree< Key, Type >& right ) {
		return ( !(left < right) );
	}
}//end namespace avl
#endif