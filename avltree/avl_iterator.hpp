#if !defined (GUARD_GRIMMINCKavl_iterator_20130202_)
#define GUARD_GRIMMINCKavl_iterator_20130202_

namespace avl{
	template <class tree>
	class avl_iterator {
	public:
		typedef typename tree::node				node;
		typedef typename tree::node_ptr			node_ptr;
		typedef typename tree::const_node_ptr	const_node_ptr;
		typedef typename tree::utilities		utilities;
		typedef typename tree::value_type		value_type;
	private:
		node_ptr _node;
	public:
		avl_iterator() : _node()  { }
		avl_iterator( const node_ptr node ) : _node ( node ) { }
		~avl_iterator() { _node = NULL; }

		avl_iterator& operator=(const avl_iterator& rhs) {
			_node = rhs._node;
			return (*this);
		}
		bool operator == ( const avl_iterator& rhs ) { return ( _node == rhs._node); }
		bool operator != ( const avl_iterator& rhs ) { return ( _node != rhs._node); }

		avl_iterator& operator++()
		{
			_node = utilities::next_node( _node );
			return (*this);
		}
		avl_iterator& operator ++( int ) {
			avl_iterator temp(*this);
			++(*this);
			return(temp);
		}

		avl_iterator& operator -- () {
			_node = utilities::prev_node( _node );
			return (*this);
		}

		avl_iterator& operator -- ( int ) {
			avl_iterator temp(*this);
			--(*this);
			return(temp);
		}

		value_type& operator * () const {
			return *operator->();
		}

		value_type* operator -> () const {
			return NULL;

		}
	};
}//end namespace avl
#endif