#if !defined (GUARD_GRIMMINCKavl_utilities_20130202_)
#define GUARD_GRIMMINCKavl_utilities_20130202_

namespace avl{
	template <class tree>
	class avl_utilities{
		typedef typename tree::key_type			Key;
		typedef typename tree::mapped_type		Type;
		typedef typename tree::value_type		value_type;

		typedef typename tree::node				node;
		typedef typename tree::node_ptr			node_ptr;
		typedef typename tree::const_node_ptr	const_node_ptr;

	public:
		static void init_header( node_ptr& header ) {
			header = new node();
		}

		static bool is_header( const const_node_ptr & p ) {
			node_ptr p_left (node::get_left(p));
			node_ptr p_right (node::get_right(p));
			if(!node::get_parent(p) || //Header condition when empty tree
				(p_left && p_right &&         //Header always has leftmost and rightmost
				(p_left == p_right ||      //Header condition when only node
				(node::get_parent(p_left)  != p ||
				node::get_parent(p_right) != p ))
				//When tree size > 1 headers can't be leftmost's
				//and rightmost's parent
				)) {
					return true;
			}
			return false;
		}

		static node_ptr get_header(const const_node_ptr & node) {
			node_ptr h = node::to_ptr( node );
			if(node::get_parent(node)) {
				h = node::get_parent(node);
				while(!is_header(h)) {
					h = node::get_parent(h);
				}
			}
			return h;
		}

		static node_ptr get_root( const node_ptr& node ) {
			return ( node::get_parent( node::get_header ( node ) ) );
		}

		static node_ptr next_node( const node_ptr & node ) {
			node_ptr p_right( node::get_right( node ) );
			if( p_right ) {
				return minimum( p_right );
			}
			else {
				node_ptr p(node);
				node_ptr x = node::get_parent(p);
				while( p == node::get_right(x) ) {
					p = x;
					x = node::get_parent(x);
				}
				return node::get_right(p) != x ? x : p;
			}
		}

		static node_ptr prev_node( const node_ptr & node ) {
			if( is_header( node ) ) {
				return node::get_right(node);
			}
			else if( node::get_left( node ) ) {
				return maximum( node::get_left( node ) );
			}
			else {
				node_ptr p(node);
				node_ptr x = node::get_parent(p);
				while(p == node::get_left(x)){
					p = x;
					x = node::get_parent(x);
				}
				return x;
			}
		}

		static node_ptr minimum ( node_ptr node ) {
			for(node_ptr p_left = node::get_left(node)
				;p_left
				;p_left = node::get_left(node)) {
					node = p_left;
			}
			return node;
		}

		static node_ptr maximum( node_ptr node ) {
			for(node_ptr p_right = node::get_right(node)
				;p_right
				;p_right = node::get_right(node)) {
					node = p_right;
			}
			return node;
		}

		static node_ptr rotate_left( node_ptr node ) {
			node_ptr right ( node::get_right( node ) );
			node_ptr rightLeft ( node::get_left( right ) );
			node_ptr parent ( node::get_parent( node ) );

			node::set_parent( right, parent );
			node::set_left( right, node );
			node::set_right( node, rightLeft );
			node::set_parent( node, right );

			if ( rightLeft ) {
				node::set_parent( rightLeft, node );
			}

			if ( is_header( node::get_parent( right ) ) ) {			// node was root
				node::set_parent( get_header( node ), right );
			} else if ( node::get_right( parent ) == node ) {		// node was right branch of parent node
				node::set_right( parent, right );
			} else {												// node was left branch of parent node
				node::set_left( parent, right )
			}

			node::set_balance( right, ( node::get_balance( right ) + 1 ) );
			node::set_balance( node, -( node::get_balance( right ) ) );

			return right;
		}

		static node_ptr rotate_right( node_ptr node ) {
			node_ptr left = node::get_left( node );
			node_ptr leftRight = node::get_right( left );
			node_ptr parent = node::get_parent( node );

			node::set_parent( left, parent );
			node::set_right( left, node );
			node::set_left( node, leftRight );
			node::set_parent( node, left );

			if ( leftRight ) {
				node::setParent( leftRight, node );
			}

			if ( is_header( node::get_parent( left ) ) ) {			// node was root
				node::set_parent( get_header( node ), left );		
			} else if ( node::get_left( parent ) == node ) {		// node was left branch of parent node
				node::set_left( parent, left );
			} else {												// node was right branch of parent node
				node::set_right( parent, left );				
			}

			node::set_balance( left, ( node::get_balance( left ) + 1 ) );
			node::set_balance( node, -( node::get_balance( left ) ) );

			return left;
		}

		//Clears node and all children of node recursively
		//param node - node from which to start
		static void clear_tree ( node_ptr& node ) {
			if( node != NULL ){
				node_ptr p_left (node::get_left(node));
				node_ptr p_right(node::get_right(node));
				if ( p_left ) {
					clearHelper( p_left );
				}
				if ( p_right ) {
					clearHelper( p_right );
				}
				delete( node );
			}
		}
	};
}//end namespace avl
#endif