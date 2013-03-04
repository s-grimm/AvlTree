// ***********************************************************************
// Assembly         : avltree
// Author           : Shane Grimminck
// Created          : 02-21-2013
//
// Last Modified By : Shane Grimminck
// Last Modified On : 03-01-2013
// ***********************************************************************
// <summary>Implementation of the avl node used to store the data for the tree. Each node is its own balanced tree</summary>
// ***********************************************************************
#if !defined (GUARD_GRIMMINCKavl_node_20130202_)
#define GUARD_GRIMMINCKavl_node_20130202_
namespace avl{
	/// <summary>
	/// Struct avl_node
	/// </summary>
	template <class tree>
	struct avl_node {
	private:
		typedef typename tree::value_type		value_type;
	public:
		typedef avl_node*						node_ptr;
		typedef const avl_node*					const_node_ptr;
		/// <summary>
		/// The parent, left and right nodes from this node
		/// </summary>
		node_ptr _parentNode, _leftNode, _rightNode;
		/// <summary>
		/// The balance of the node
		/// </summary>
		int _balance;
		/// <summary>
		/// The data of the node
		/// </summary>
		value_type _value;
		//c'tors
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_node{tree}"/> struct.
		/// </summary>
		avl_node(): _balance(0), _parentNode(NULL), _leftNode(NULL), _rightNode(NULL) {} //header node c'tor
		
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_node{tree}"/> struct.
		/// </summary>
		/// <param name="value">The value.</param>
		avl_node( const value_type& value ) : _value(value), _balance(0), _parentNode(NULL), _leftNode(NULL), _rightNode(NULL) { }
		
		/// <summary>
		/// Initializes a new instance of the <see cref="avl_node{tree}"/> struct.
		/// </summary>
		/// <param name="original">The original.</param>
		avl_node( avl_node && original ) {
			_value = original._value;
			_balance = original._balance;
			_parentNode = original._parentNode;
			_leftNode = original._leftNode;
			_rightNode = original._rightNode;

			original._parentNode = original._leftNode = original._rightNode = nullptr;
			original._value = NULL;
			original._balance = 0;
			delete ( original );
		}
		//d'tors
		/// <summary>
		/// Finalizes an instance of the <see cref="avl_node{tree}"/> class.
		/// </summary>
		~avl_node(){
			_parentNode = _leftNode = _rightNode = nullptr;
			_balance = 0;
		}

		/// <summary>
		/// Assignment Operator for node
		/// </summary>
		/// <param name="rhs">The Right Hand Side.</param>
		/// <returns>avl.avl_node{tree} &.</returns>
		avl_node& operator = ( const node_ptr & rhs ) {
			_balance = rhs->_balance;
			_value = rhs->_value;
			_parentNode = rhs->_parentNode;
			_leftNode = rhs->_leftNode;
			_rightNode = rhs->_rightNode;
		}
		/// <summary>
		/// Assignment operater for const node
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>avl.avl_node{tree} &.</returns>
		avl_node& operator = ( const const_node_ptr & rhs ) {
			_balance = rhs->_balance;
			_value = rhs->_value;
			_parentNode = rhs->_parentNode;
			_leftNode = rhs->_leftNode;
			_rightNode = rhs->_rightNode;
		}
		/// <summary>
		/// Equivalent operator for node 
		/// </summary>
		/// <param name="rhs">The Right Hand Side.</param>
		/// <returns>bool.</returns>
		bool operator == ( const node_ptr& rhs ) { return ( _value.first == rhs->_value.first ); }
		/// <summary>
		/// Equivalent operator for const node.
		/// </summary>
		/// <param name="rhs">The Right Hand Side</param>
		/// <returns>bool.</returns>
		bool operator == ( const const_node_ptr& rhs ) { return ( _value.first == rhs->_value.first ); }
		/// <summary>
		///	Equivalent operator for node 
		/// </summary>
		/// <param name="rhs">The RHS.</param>
		/// <returns>bool.</returns>
		bool operator != ( const node_ptr& rhs ) { return ( _value.first != rhs->_value.first ); }
		/// <summary>
		/// Equivalent operator for const node.
		/// </summary>
		/// <param name="rhs">The Right Hand Side</param>
		/// <returns>bool.</returns>
		bool operator != ( const const_node_ptr& rhs ) { return ( _value.first != rhs->_value.first ); }

		/// <summary>
		/// Gets the parent node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_parent( const const_node_ptr & node ) {
			return node->_parentNode;
		}

		/// <summary>
		/// Gets the parent node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_parent( const node_ptr & node ) {
			return node->_parentNode;
		}

		/// <summary>
		/// Sets the parent node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="parent">The parent.</param>
		static void set_parent( const node_ptr & node, const node_ptr & parent ) {
			node->_parentNode = parent;
		}

		/// <summary>
		/// Gets the left node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_left(const const_node_ptr & node) {
			return node->_leftNode;
		}

		/// <summary>
		/// Gets the left node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_left(const node_ptr & node) {
			return node->_leftNode;
		}

		/// <summary>
		/// Sets the left node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="left">The left.</param>
		static void set_left(const node_ptr & node, const node_ptr & left) {
			node->_leftNode = left;
		}

		/// <summary>
		/// Gets the right node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_right(const const_node_ptr & node) {
			return node->_rightNode;
		}

		/// <summary>
		/// Gets the right node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_right(const node_ptr & node) {
			return node->_rightNode;
		}

		/// <summary>
		/// Sets the right node of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="right">The right.</param>
		static void set_right(const node_ptr & node, const node_ptr & right) {
			node->_rightNode = right;
		}

		/// <summary>
		/// Gets the balance of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>int.</returns>
		static int get_balance(const const_node_ptr & node)	{
			return node->_balance;
		}

		/// <summary>
		/// Gets the balance of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>int.</returns>
		static int get_balance(const node_ptr & node) {
			return node->_balance;
		}

		/// <summary>
		/// Sets the balance of the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="balance">The balance.</param>
		static void set_balance(const node_ptr & node, int balance) {
			node->_balance = balance;
		}

		/// <summary>
		/// Overwrites the value of the specified node.
		/// </summary>
		/// <param name="from">From.</param>
		/// <param name="to">To.</param>
		static void set_value( const node_ptr& from, const node_ptr& to ) {
			to->_value = from->_value;
		}
	};//end avlnode
} //end namespace avl
#endif