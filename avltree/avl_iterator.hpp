// ***********************************************************************
// Assembly         : avltree
// Author           : Shane Grimminck
// Created          : 02-21-2013
//
// Last Modified By : Shane Grimminck
// Last Modified On : 03-01-2013
// ***********************************************************************
// <summary>Implementation of iterator and const iterator</summary>
// ***********************************************************************
#if !defined (GUARD_GRIMMINCKavl_iterator_20130202_)
#define GUARD_GRIMMINCKavl_iterator_20130202_
#include <assert.h>
namespace avl{
	template <class tree>
	class const_avl_iterator;

	/// <summary>
	/// Class avl_iterator
	/// </summary>
	template <class tree>
	class avl_iterator {
	public:
		typedef typename tree::node_ptr				node_ptr;
		typedef typename tree::value_type*			pointer;// for std reverse iterator
		typedef typename tree::value_type&			reference;
		typedef typename tree::const_node_ptr		const_node_ptr;
		typedef typename tree::utilities			utilities;
		typedef typename tree::value_type			value_type;
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef std::ptrdiff_t						difference_type;

	private:
		friend class const_avl_iterator<tree>;
		/// <summary>
		/// The _node
		/// </summary>
		node_ptr _node;
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_iterator{tree}"/> class.
		/// </summary>
		avl_iterator() : _node()  { }
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_iterator{tree}"/> class.
		/// </summary>
		/// <param name="node">The node.</param>
		avl_iterator( const node_ptr node ) : _node ( node ) { }
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_iterator{tree}"/> class.
		/// </summary>
		/// <param name="iterator">The iterator.</param>
		avl_iterator( const avl_iterator& iterator ) {
			(*this) = iterator;
		}
		/// <summary>
		/// Finalizes an instance of the <see cref="avl_iterator{tree}"/> class.
		/// </summary>
		~avl_iterator() { _node = NULL; }

		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>avl.avl_iterator{tree} &.</returns>
		avl_iterator& operator=(const avl_iterator& rhs) {
			_node = rhs._node;
			return (*this);
		}
		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>avl.avl_iterator{tree} &.</returns>
		avl_iterator& operator=(const const_avl_iterator<tree>& rhs) {
			_node = rhs._node;
			return (*this);
		}

		/// <summary>
		/// Operator==s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>bool.</returns>
		bool operator == ( const avl_iterator& rhs ) const { return ( _node == rhs._node); }
		/// <summary>
		/// Operator!=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>bool.</returns>
		bool operator != ( const avl_iterator& rhs ) const { return ( _node != rhs._node); }

		/// <summary>
		/// Operator++s this instance.
		/// </summary>
		/// <returns>avl.avl_iterator{tree} &.</returns>
		avl_iterator& operator++()
		{
			_node = utilities::next_node( _node );
			return (*this);
		}
		/// <summary>
		/// Operator++s the specified .
		/// </summary>
		/// <param name="">The .</param>
		/// <returns>avl.avl_iterator{tree}.</returns>
		avl_iterator operator ++( int ) {
			avl_iterator temp(*this);
			++(*this);
			return(temp);
		}

		/// <summary>
		/// Operator--s this instance.
		/// </summary>
		/// <returns>avl.avl_iterator{tree} &.</returns>
		avl_iterator& operator -- () {
			_node = utilities::prev_node( _node );
			return (*this);
		}

		/// <summary>
		/// Operator--s the specified .
		/// </summary>
		/// <param name="">The .</param>
		/// <returns>avl.avl_iterator{tree}.</returns>
		avl_iterator operator -- ( int ) {
			avl_iterator temp(*this);
			--(*this);
			return(temp);
		}

		/// <summary>
		/// Operator*s this instance.
		/// </summary>
		/// <returns>reference.</returns>
		reference operator * () const {
			assert( ! utilities::is_header( _node ) );
			return _node->_value;
		}

		/// <summary>
		/// Operator->s this instance.
		/// </summary>
		/// <returns>pointer.</returns>
		pointer operator -> () const {
			assert( ! utilities::is_header( _node ) );
			return &_node->_value;
		}
	};

	/// <summary>
	/// Class const_avl_iterator
	/// </summary>
	template <class tree>
	class const_avl_iterator {
	public:
		typedef typename tree::node_ptr						node_ptr;
		typedef typename tree::value_type*					pointer;// for std reverse iterator
		typedef typename tree::value_type&					reference;
		typedef typename tree::const_node_ptr				const_node_ptr;
		typedef typename tree::utilities					utilities;
		typedef typename tree::value_type					value_type;
		typedef std::bidirectional_iterator_tag				iterator_category;
		typedef std::ptrdiff_t								difference_type;
	private:
		friend class avl_iterator<tree>;
		/// <summary>
		/// The _node
		/// </summary>
		node_ptr _node;
	public:
		/// <summary>
		/// Initializes a new instance of the <see cref="const_avl_iterator{tree}"/> class.
		/// </summary>
		const_avl_iterator() : _node()  { }
		/// <summary>
		/// Initializes a new instance of the <see cref="const_avl_iterator{tree}"/> class.
		/// </summary>
		/// <param name="node">The node.</param>
		const_avl_iterator( const node_ptr node ) : _node ( node ) { }
		/// <summary>
		/// Initializes a new instance of the <see cref="const_avl_iterator{tree}"/> class.
		/// </summary>
		/// <param name="iterator">The iterator.</param>
		const_avl_iterator( const const_avl_iterator& iterator ) {
			(*this) = iterator;
		}
		/// <summary>
		/// Finalizes an instance of the <see cref="const_avl_iterator{tree}"/> class.
		/// </summary>
		~const_avl_iterator() { _node = NULL; }

		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>avl.const_avl_iterator{tree} &.</returns>
		const_avl_iterator& operator=(const const_avl_iterator& rhs) {
			_node = rhs._node;
			return (*this);
		}

		/// <summary>
		/// Operator=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>avl.const_avl_iterator{tree} &.</returns>
		const_avl_iterator& operator=(const avl_iterator<tree>& rhs) {
			_node = rhs._node;
			return (*this);
		}

		/// <summary>
		/// Operator==s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>bool.</returns>
		bool operator == ( const const_avl_iterator& rhs ) const { return ( _node == rhs._node); }
		/// <summary>
		/// Operator!=s the specified RHS.
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>bool.</returns>
		bool operator != ( const const_avl_iterator& rhs ) const { return ( _node != rhs._node); }

		/// <summary>
		/// Operator++s this instance.
		/// </summary>
		/// <returns>avl.const_avl_iterator{tree} &.</returns>
		const_avl_iterator& operator++()
		{
			_node = utilities::next_node( _node );
			return (*this);
		}
		/// <summary>
		/// Operator++s the specified .
		/// </summary>
		/// <param name="">The .</param>
		/// <returns>avl.const_avl_iterator{tree}.</returns>
		const_avl_iterator operator ++( int ) {
			const_avl_iterator temp(*this);
			++(*this);
			return(temp);
		}

		/// <summary>
		/// Operator--s this instance.
		/// </summary>
		/// <returns>avl.const_avl_iterator{tree} &.</returns>
		const_avl_iterator& operator -- () {
			_node = utilities::prev_node( _node );
			return (*this);
		}

		/// <summary>
		/// Operator--s the specified .
		/// </summary>
		/// <param name="">The .</param>
		/// <returns>avl.const_avl_iterator{tree}.</returns>
		const_avl_iterator operator -- ( int ) {
			const_avl_iterator temp(*this);
			--(*this);
			return(temp);
		}

		/// <summary>
		/// Operator*s this instance.
		/// </summary>
		/// <returns>const reference.</returns>
		const reference operator * () const {
			assert( ! utilities::is_header( _node ) );
			return _node->_value;
		}

		/// <summary>
		/// Operator->s this instance.
		/// </summary>
		/// <returns>const pointer.</returns>
		const pointer operator -> () const {
			assert( ! utilities::is_header( _node ) );
			return &_node->_value;
		}
	};
}//end namespace avl
#endif