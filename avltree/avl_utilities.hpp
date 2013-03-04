// ***********************************************************************
// Assembly         : avltree
// Author           : Shane Grimminck
// Created          : 02-21-2013
//
// Last Modified By : Shane Grimminck
// Last Modified On : 03-01-2013
// ***********************************************************************
// <summary>The utilites for avl tree implementation</summary>
// ***********************************************************************

#if !defined (GUARD_GRIMMINCKavl_utilities_20130202_)
#define GUARD_GRIMMINCKavl_utilities_20130202_

namespace avl{
	/// <summary>
	/// Class avl_utilities
	/// </summary>
	template <class tree>
	class avl_utilities{
		typedef typename tree::key_type			key_type;
		typedef typename tree::key_compare		compare;
		typedef typename tree::value_type		value_type;

		typedef typename tree::node				node;
		typedef typename tree::node_ptr			node_ptr;
		typedef typename tree::const_node_ptr	const_node_ptr;

	public:

		/// <summary>
		/// Initialize the specified header.
		/// </summary>
		/// <param name="header">The header.</param>
		static void init_header( node_ptr& header ) {
			header = new node();
		}

		/// <summary>
		/// Checks to see if node is header
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>bool.</returns>
		static bool is_header( const const_node_ptr & node ) {
			node_ptr node_left (node::get_left(node));
			node_ptr node_right (node::get_right(node));
			if(!node::get_parent(node) ||			//Header will have no parent if it is the only node in the tree (tree is empty)
				( node_left && node_right &&         //Header always has left and right nodes
				( node_left == node_right ||			//Left and Right will be the same if the tree only has one node
				( node::get_parent( node_left )  != node ||
				node::get_parent( node_right ) != node ) ) ) ) { //When the tree is larger than 1 node, header can not be the left and right nodes parent
					return true;
			}
			return false;
		}
		/// <summary>
		/// Return the node with the specified key or header if no node has the key
		/// Uses header as the starting point for the search
		/// </summary>
		/// <param name="key">The key.</param>
		/// <param name="header">The header.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_node( const key_type& key, node_ptr& header) {
			if( node::get_parent( header ) ) {
				node_ptr currentNode = node::get_parent( header );

				while ( currentNode ) {
					if ( key == currentNode->_value.first ) {
						return currentNode ;
					}
					compare _comparer;
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
			return header; //represents end node
		}

		/// <summary>
		/// Gets the header from the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr get_header(const node_ptr & node) {
			node_ptr header = node;
			if(node::get_parent(node)) {			//if we dont have a parent, we are the header in an empty tree.
				header = node::get_parent(node);	//header is always the last parent node
				while(!is_header(header)) {			//get the next parent if the node isn't the header
					header = node::get_parent(header);
				}
			}
			return header;
		}

		/// <summary>
		/// Gets the next node from the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr next_node( const node_ptr & node ) {
			node_ptr node_right( node::get_right( node ) );
			if( node_right ) {
				return minimum( node_right );
			}
			else {
				node_ptr old_node(node);
				node_ptr parent_node = node::get_parent(old_node);
				while( old_node == node::get_right(parent_node) ) { //while we are on the right branch, get the parent node
					old_node = parent_node;
					parent_node = node::get_parent(parent_node);
				}
				return node::get_right(old_node) != parent_node ? parent_node : old_node;
			}
		}

		/// <summary>
		/// gets the previous node from the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr prev_node( const node_ptr & node ) {
			if( is_header( node ) ) {
				return node::get_right(node);
			}
			else if( node::get_left( node ) ) {
				return maximum( node::get_left( node ) );
			}
			else {
				node_ptr old_node(node);
				node_ptr parent_node = node::get_parent(old_node);
				while(old_node == node::get_left(parent_node)){
					old_node = parent_node;
					parent_node = node::get_parent(parent_node);
				}
				return parent_node;
			}
		}

		/// <summary>
		/// Gets the lowest node from the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr minimum ( node_ptr node ) {
			for( node_ptr node_left = node::get_left( node ); node_left; node_left = node::get_left( node ) ) { //while we have a left node, go left
				node = node_left;
			}
			return node;
		}

		/// <summary>
		/// Gets the highest node from the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr maximum( node_ptr node ) {
			for(node_ptr p_right = node::get_right(node)
				;p_right
				;p_right = node::get_right(node)) {
					node = p_right;
			}
			return node;
		}

		/// <summary>
		/// Finds the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="key">The key.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr find_node( node_ptr node, const key_type& key ) {
			while ( node ) {
				if ( key == node->_value.first ) {
					return node;
				}

				compare _comparer;
				bool compare = _comparer( node->_value.first, key );
				if ( compare ) {
					if ( !node::get_right( node ) ) {
						break;
					} else {
						node = node::get_right( node );
					}
				} else {
					if ( !node::get_left( node ) ) {
						break;
					} else {
						node = node::get_left( node );
					}
				}
			}
			return NULL;
		}

		/// <summary>
		/// Insert_balances the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="balance">The balance.</param>
		static void insert_balance( node_ptr node, int balance ) {
			while ( node && !is_header( node ) ) {
				node::set_balance( node, ( node::get_balance( node ) + balance ) );
				balance = node::get_balance( node );

				if ( balance == 0 ) {
					return;
				} else if ( balance == 2 ) {
					if( node::get_balance( node::get_left( node ) ) == 1 ) {
						rotate_right( node );
					} else {
						rotate_left_right( node );
					}
					return;
				} else if ( balance == -2 ) {
					if ( node::get_balance( node::get_right( node ) ) == -1 ) {
						rotate_left( node );
					} else {
						rotate_right_left( node );
					}
					return;
				}

				node_ptr parentNode = node::get_parent( node );
				if ( parentNode && !is_header( parentNode ) ) {
					balance = node::get_left( parentNode ) == node ? 1 : -1;
				}
				node = parentNode;
			}
		}

		/// <summary>
		/// Delete_balances the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <param name="balance">The balance.</param>
		static void delete_balance( node_ptr node, int balance ) {
			while ( node && !is_header( node ) ) {
				node::set_balance( node, ( node::get_balance( node ) + balance ) );
				balance = node::get_balance( node );

				if ( balance == 2 ) {
					if ( node::get_balance( node::get_left( node ) ) >= 0 ) {
						node = rotate_right( node );
						if ( node::get_balance( node ) == -1 ) {
							return;
						}
					} else {
						node = rotate_left_right( node );
					}
				} else if ( balance == -2 ) {
					if ( node::get_balance( node::get_right( node ) ) <= 0 ) {
						node = rotate_left( node );
						if ( node::get_balance( node ) == 1 ) {
							return;
						}
					} else {
						node = rotate_right_left( node );
					}
				} else if ( balance != 0 ) {
					return;
				}

				if ( node::get_parent( node ) ) {
					balance = node::get_left( node::get_parent( node ) ) == node ? -1 : 1;
				}

				node = node::get_parent( node );
			}
		}

		/// <summary>
		/// Rotate_lefts the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr rotate_left( node_ptr node ) {
			node_ptr right ( node::get_right( node ) );
			node_ptr rightLeft ( node::get_left( right ) );
			node_ptr parent ( node::get_parent( node ) );
			bool isHeader = is_header( parent ); //get header before changing links
			node::set_parent( right, parent );
			node::set_left( right, node );
			node::set_right( node, rightLeft );
			node::set_parent( node, right );

			if ( rightLeft ) {
				node::set_parent( rightLeft, node );
			}
			//parent
			if ( isHeader ) {			// node was root
				node::set_parent( parent, right );
			} else if ( node::get_right( parent ) == node ) {		// node was right branch of parent node
				node::set_right( parent, right );
			} else {												// node was left branch of parent node
				node::set_left( parent, right );
			}

			node::set_balance( right, ( node::get_balance( right ) + 1 ) );
			node::set_balance( node, -( node::get_balance( right ) ) );

			return right;
		}

		/// <summary>
		/// Rotate_rights the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr rotate_right( node_ptr node ) {
			node_ptr left = node::get_left( node );
			node_ptr leftRight = node::get_right( left );
			node_ptr parent = node::get_parent( node );
			bool isHeader = is_header( parent );
			node::set_parent( left, parent );
			node::set_right( left, node );
			node::set_left( node, leftRight );
			node::set_parent( node, left );

			if ( leftRight ) {
				node::set_parent( leftRight, node );
			}

			if ( isHeader ) {			// node was root
				node::set_parent( parent, left );
			} else if ( node::get_left( parent ) == node ) {		// node was left branch of parent node
				node::set_left( parent, left );
			} else {												// node was right branch of parent node
				node::set_right( parent, left );
			}

			node::set_balance( left, ( node::get_balance( left ) + 1 ) );
			node::set_balance( node, -( node::get_balance( left ) ) );

			return left;
		}

		/// <summary>
		/// Rotate_left_rights the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr rotate_left_right( node_ptr node ) {
			node_ptr left = node::get_left( node );
			node_ptr leftRight = node::get_right( left );
			node_ptr parent = node::get_parent( node );
			node_ptr leftRightRight = node::get_right( leftRight );
			node_ptr leftRightLeft = node::get_left( leftRight );
			bool isHeader = is_header( parent );
			node::set_parent( leftRight, parent );
			node::set_left( node, leftRightRight );
			node::set_right( left, leftRightLeft );
			node::set_left( leftRight, left );
			node::set_right( leftRight, node );
			node::set_parent( left, leftRight );
			node::set_parent( node, leftRight );

			if ( leftRightRight ) {
				node::set_parent( leftRightRight, node );
			}

			if ( leftRightLeft ) {
				node::set_parent( leftRightLeft, left );
			}

			if ( isHeader ) {			// node was root
				node::set_parent( parent, leftRight );
			} else if ( node::get_left( parent ) == node ) {
				node::set_left( parent, leftRight );
			} else {
				node::set_right( parent, leftRight );
			}

			if ( node::get_balance( leftRight ) == 1 ) {
				node::set_balance( node, 0 );
				node::set_balance( left, 1 );
			} else if ( node::get_balance( leftRight ) == 0 ) {
				node::set_balance( node, 0 );
				node::set_balance( left, 0 );
			} else {
				node::set_balance( node, -1 );
				node::set_balance( left, 0 );
			}

			node::set_balance( leftRight, 0 );

			return leftRight;
		}

		/// <summary>
		/// Rotate_right_lefts the specified node.
		/// </summary>
		/// <param name="node">The node.</param>
		/// <returns>node_ptr.</returns>
		static node_ptr rotate_right_left( node_ptr node ) {
			node_ptr right = node::get_right( node );
			node_ptr rightLeft = node::get_left( right );
			node_ptr parent = node::get_parent( node );
			node_ptr rightLeftLeft = node::get_left( rightLeft );
			node_ptr rightLeftRight = node::get_right( rightLeft );
			bool isHeader = is_header( parent );
			node::set_parent( rightLeft, parent );
			node::set_right( node, rightLeftLeft );
			node::set_left( right, rightLeftRight );
			node::set_right( rightLeft, right );
			node::set_left( rightLeft, node );
			node::set_parent( right, rightLeft );
			node::set_parent( node, rightLeft );

			if ( rightLeftLeft ) {
				node::set_parent( rightLeftLeft, node );
			}

			if ( rightLeftRight ) {
				node::set_parent( rightLeftRight, right );
			}

			if ( isHeader ) {			// node was root
				node::set_parent( parent, rightLeft );
			} else if ( node::get_right( parent ) == node ) {
				node::set_right( parent, rightLeft );
			} else {
				node::set_left( parent, rightLeft );
			}

			if ( node::get_balance( rightLeft ) == 1 ) {
				node::set_balance( node, 0 );
				node::set_balance( right, 1 );
			} else if ( node::get_balance( rightLeft ) == 0 ) {
				node::set_balance( node, 0 );
				node::set_balance( right, 0 );
			} else {
				node::set_balance( node, -1 );
				node::set_balance( right, 0 );
			}

			node::set_balance( rightLeft, 0 );

			return rightLeft;
		}

		/// <summary>
		/// Replaces the old node with the new node
		/// </summary>
		/// <param name="old_node">The old node.</param>
		/// <param name="new_node">The new node.</param>
		static void succeed( node_ptr& old_node, node_ptr& new_node ) {
			//old					//new
			node_ptr left = node::get_left( new_node );
			node_ptr right = node::get_right( new_node );
			node_ptr parent = node::get_parent( old_node );
			node_ptr header = get_header( parent );
			bool isHeader = is_header( parent );
			bool isFirstNode = node::get_left( header ) == old_node;
			bool isLastNode = node::get_right( header ) == old_node;
			delete( old_node );
			old_node = new_node;
			node::set_parent( old_node, parent );
			if ( isHeader ) {
				node::set_parent( parent, old_node );
			}
			if( isFirstNode ){
				node::set_left( parent, old_node );
			}
			if( isLastNode ){
				node::set_right( parent, old_node );
			}
			if ( left ) {
				node::set_parent( left, old_node );
			}
			if ( right ) {
				node::set_parent( right, old_node );
			}
		}

		/// <summary>
		/// Clears node and all children of node recursively
		/// </summary>
		/// <param name="node">The node.</param>
		static void clear_tree ( node_ptr node ) {
			if( node != NULL ){
				node_ptr p_left (node::get_left(node));
				node_ptr p_right(node::get_right(node));
				if ( p_left ) {
					clear_tree( p_left );
				}
				if ( p_right ) {
					clear_tree( p_right );
				}
				delete( node );
			}
		}
	};
}//end namespace avl
#endif