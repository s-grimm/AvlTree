#if !defined (GUARD_GRIMMINCKavl_iterator_20130202_)
#define GUARD_GRIMMINCKavl_iterator_20130202_

namespace avl{
	template <class tree>
	class avl_iterator {
	public:
		typedef typename tree::node				node;
		typedef typename tree::node_ptr			node_ptr;
		typedef typename tree::const_node_ptr	const_node_ptr;
	};
}//end namespace avl
#endif