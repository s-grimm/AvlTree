#if !defined (GUARD_GRIMMINCKavltree_20130202_)
#define GUARD_GRIMMINCKavltree_20130202_

#include <functional> // std::less
#include <memory> // std::allocator
#include <utility> // std::pair
#include <iterator> //std::reverse_iterator

// to remove
#include <map>
//!  AvlTree Class
/*!
A Binary Search Tree Implementation
*/
template <
	class Key,
	class Type,
	class Traits = std::less<Key>,
	class Allocator = std::allocator<std::pair<Key const, Type>>
	>
	class avltree : public std::map<Key,Type> {
		//non iterator typedefs
	public:
		typedef std::pair<const Key, Type>					value_type;
		typedef Allocator									allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::reference			reference;
		typedef Key											key_type;
		typedef Type										mapped_type;
		typedef Traits										key_compare;
	private:
		//!  AvlNode
		/*!
		Class for storing data in the AvlTree class.
		*/
		class AvlNode {
		public:
			AvlNode(const Key& key, const Type& val) : _parent(0), _left(0), _right(0), balance(0), key(key), data(val) {};
			AvlNode(const std::pair<Key, Type>& kp) : _parent(0), _left(0), _right(0), balance(0), key(kp.first), data(kp.second) {};
			Key first() { return key; }
			Type second() { return data; }
			AvlNode* getParent()			{ return _parent; }
			AvlNode* getRight()				{ return _right; }
			AvlNode* getLeft()				{ return _left;	}
			int getBalance()				{ return balance; }
			void setRight(AvlNode* node)	{ _right = node; }
			void setLeft(AvlNode* node)		{ _left = node; }
			void setParent(AvlNode* node)	{ _parent = node; }
			void setBalance( int bal )		{ balance = bal; }

			bool hasLeft() { return _left != NULL; }
			bool hasRight() { return _right != NULL; }
			bool hasParent() { return _parent != NULL; }

			void destroyNode() {
				_parent = _left = _right = NULL;
				key = NULL;
				data = NULL;
				balance = NULL;
			}

			AvlNode& operator=( AvlNode& rhs ) {
				balance = rhs.balance;
				data = rhs.data;
				key = rhs.key;
				_parent = rhs._parent;
				_left = rhs._left;
				_right = rhs._right;
			}

			bool operator== ( AvlNode& rhs ) { return ( key == rhs.key ); }
			bool operator!= ( AvlNode& rhs ) { return ( key != rhs.key ); }

		protected:
			Key key;
			Type data;
			int balance;
			AvlNode* _parent;
			AvlNode* _left;
			AvlNode* _right;
		};

	public:
		//!  Iterator Class.
		/*!
		Custom Iterator Class for AvlTree
		*/
		class Iterator {
		protected:
			AvlNode* node;
		private:
			AvlNode* right;
			/*key_compare comparer;*/
			enum TraversalDirection { Right, Left, Parent, End, Begin };
			TraversalDirection _action;

		public:
			Iterator(AvlNode* p) : node(p) {
				right = p;
				_action = p == NULL ? End : Begin;
			}
			Iterator() : node( NULL ) {
				_action = End;
			}
			~Iterator()	{ node = nullptr; }
			Iterator& operator=(const Iterator& rhs) {
				node = rhs.node;
				right = node;
				_action = node == NULL ? End : Begin;
				return (*this);
			}
			bool operator==(const Iterator& rhs) { return (node == rhs.node); }
			bool operator!=(const Iterator& rhs) { return (node != rhs.node); }

			Iterator& operator++()
			{
				bool doEnd = true;
				if( !node->hasRight() && !node->hasLeft() && !node->hasParent() ) //this is the only node.
				{
					_action = End;
					node = NULL;
				}
				switch(_action)
				{
				case Begin:
					node = right;

					right = node->getRight();
					_action = right != NULL ? Right : Parent;

					if(_action == Parent )
					{
						if( node->hasParent() && node->getParent()->getRight() == node ) {
							if( node->getParent()->hasParent() ) {
								node = node->getParent()->getParent();
							} else {
								_action = End;
								node = NULL;
								break;
							}
						} else {
							node = node->getParent();
						}
					} else {
						node = node->getRight();
					}

					right = node->getRight();
					_action = right != NULL ? Right : Parent;

					break;
				case Right:
					node = right;

					while( node->hasLeft() ) {
						node = node->getLeft();
					}

					right = node->getRight();
					_action = right != NULL ? Right : Parent;

					break;

				case Parent:
					while ( node->hasParent() )	{
						AvlNode* prev = node;
						node = node->getParent();
						if( node->getLeft() == prev ) {
							right = node->getRight();
							_action = right != NULL ? Right : Parent;
							doEnd = false;
							break;
						}
					}
					if( doEnd )	{
						_action = End;
						node = NULL;
					}
					break;

				default:
					node = NULL;
					break;
				}
				return (*this);
			}

			Iterator& operator++(int) {
				Iterator tmp(*this);
				++(*this);
				return(tmp);
			}

			Iterator& operator--() {
				return (*this);
			}

			Iterator& operator--(int) {
				Iterator tmp(*this);
				--(*this);
				return(tmp);
			}
			std::pair<Key,Type>& operator*() {
				return std::pair<Key,Type>(node->first(), node->second());
			}
			AvlNode* operator->() const	{
				return node;
			}
		};
	private:
		AvlNode* _root;
		AvlNode* _first;
		AvlNode* _last;
		std::size_t _size;
		key_compare comparer;
		//typedefs
	public:
		typedef Iterator									iterator;
		typedef Iterator const								const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
	public:
		/******************************************** Constructors *******************************************/
		avltree() : map() {
			_root = _first = _last = NULL;
			_size = 0;
		}

		template<class InputIterator>
		avltree(InputIterator First, InputIterator Last) : map( First, Last ) { }

		explicit avltree(const Traits& _Comp) : explicit map( _Comp ) { }

		avltree( const Traits& _Comp, const Allocator& _Al ) : map( _Comp, _Al ) {}

		avltree( const avltree& _Right ) : map( _Right ) {}

		template<class InputIterator>
		avltree( InputIterator _First, InputIterator _Last, const Traits& _Comp ) : map( _First, _Last, _Comp   ) {}

		template<class InputIterator>
		avltree( InputIterator _First, InputIterator _Last, const Traits& _Comp, const Allocator& _Al ) : map (_First, _Last, _Comp, _Al ){}

		avltree(avltree&& _Right) : map( _Right) {}

		~avltree() {
			clear();
			_first = NULL;
			_last = NULL;
			_root = NULL;
		}

		/******************************************** Operators ********************************************/
		// operator[]
		Type& operator[](const Key& _key) {
			return (*(std::map<Key,Type,Traits,Allocator>*)this)[_key];
		}
		Type& operator[](Key&& _key) {
			return (*(std::map<Key,Type,Traits,Allocator>*)this)[_key];
		}

		// operator=
		avltree& operator=(const avltree& _right) {
			*(std::map<Key,Type,Traits,Allocator>*)this=*(std::map<Key,Type,Traits,Allocator>*) &_right;
			return *this;
		}
		avltree& operator= ( avltree&& _right) {
			*(std::map<Key,Type,Traits,Allocator>*)this=std::move(*(std::map<Key,Type,Traits,Allocator>*) &_right );
			return *this;
		}

		// relational operators
		bool avltree::operator==(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this == *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}
		bool avltree::operator!=(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this != *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}
		bool avltree::operator<(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this < *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}
		bool avltree::operator>(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this > *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}
		bool avltree::operator<=(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this <= *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}
		bool avltree::operator>=(const avltree &rhs) const {
			return *(std::map<Key,Type,Traits,Allocator>*)this >= *(std::map<Key,Type,Traits,Allocator>*) &rhs;
		}

		// iterator
		iterator				begin() { return Iterator(_first); }
		const_iterator			begin() const { return Iterator(_first); }
		const_iterator			cbegin() const { return Iterator(_first); }
		iterator				end() { return Iterator(NULL); }
		const_iterator			end() const { return Iterator(NULL); }
		const_iterator			cend() const { return Iterator(NULL); }

		reverse_iterator		rbegin() { return reverse_iterator( end() ); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator( end() ); }
		const_iterator			crbegin() const { return const_reverse_iterator( end() ); }
		reverse_iterator		rend() { return reverse_iterator( begin() ); }
		const_reverse_iterator	rend() const { return const_reverse_iterator( begin() ); }
		const_iterator			crend() const { return const_reverse_iterator( begin() ); }

		/*-------------------------------Functions----------------------------------*/
		std::pair<iterator, bool> insert(std::pair<Key,Type> val) {
			iterator it = find(val.first);
			if( it != end() ) {
				return std::pair<iterator, bool>(it, false);
			}

			AvlNode* n = new AvlNode(val.first,val.second);
			if( _root == NULL ) {
				_root = n;
				_first = n;
				_last = n;
				_size++;
				return std::pair<iterator, bool>( iterator( n ), true );
			}
			else {
				AvlNode* rNode = _root;
				while ( rNode != NULL ) {
					bool compare = comparer( rNode->first(), n->first() );

					if(compare) { // Go Right
						AvlNode* right = rNode->getRight();
						if( right == NULL) {
							n->setParent(rNode);
							rNode->setRight(n);
							_size ++;

							if( comparer( n->first(), _first->first() ) ) {
								_first = n;
							}
							else if( !comparer(  n->first(), _last->first() ) ) {
								_last = n;
							}

							insertBalance( rNode, -1 );

							return std::pair<iterator, bool>( iterator( n ), true );
						}
						else {
							rNode = right;
						}
					}
					else { // Go Left
						AvlNode* left = rNode->getLeft();
						if( left == NULL ) {
							n->setParent(rNode);
							rNode->setLeft(n);
							_size ++;

							if(comparer( n->first(), _first->first() ) ) {
								_first = n;
							}
							else if( !comparer( n->first(), _last->first() ) ) {
								_last = n;
							}

							insertBalance( rNode, 1 );

							return std::pair<iterator, bool>( iterator( n ), true );
						}
						else {
							rNode = left;
						}
					}
				}
			}
		}

		size_type max_size() { return 0; } //todo

		size_type size() { return _size; }


		/*------------------------Find---------------------------*/
		Type at (const Key& _Key) {
			return this->find(_Key)->second();
		}
		//! Find Node at Key.
		const Type at (const Key& _Key) const {
			return this->find(_Key)->second();
		}

		size_type count (const Key& _Key) {
			return this->find(_Key) == NULL ? 0 : 1;
		}
		template<class ValTy>
		std::pair<iterator,bool> emplace (ValTy&& _ValTy) {
			return this->insert(_ValTy);
		}

		iterator find (const Key& _Key) {
			AvlNode* rNode = _root;

			while (rNode != NULL) {
				if (_Key == rNode->first()) {
					return Iterator(rNode);
				}

				bool compare = comparer(rNode->first(), _Key);

				if (compare) {
					AvlNode* right = rNode->getRight();
					if( right == NULL) {
						return iterator(NULL);
					}
					else {
						rNode = right;
					}
				}
				else {
					AvlNode* left = rNode->getLeft();
					if( left == NULL) {
						return iterator(NULL);
					}
					else {
						rNode = left;
					}
				}
			}
			return iterator(NULL);
		}

		const_iterator find (const Key& _Key) const {
			AvlNode* rNode = _root;

			while (rNode != NULL) {
				if (_Key == rNode->first()) {
					return Iterator(rNode);
				}

				bool compare = comparer(rNode->first(), _Key);

				if (compare) {
					AvlNode* right = rNode->getRight();
					if( right == NULL) {
						return iterator(NULL);
					}
					else {
						rNode = right;
					}
				}
				else {
					AvlNode* left = rNode->getLeft();
					if( left == NULL) {
						return iterator(NULL);
					}
					else {
						rNode = left;
					}
				}
			}
			return iterator(NULL);
		}
		/*----------------------Clear------------------------*/
		//! Clears all the nodes of the AvlTree.
		/*!
		\return void
		*/
		void clear() {
			enum choice { Begin, End, Right, Parent };
			choice _action = Begin;
			AvlNode* node = _first;
			AvlNode* right = node;
			AvlNode* prev;
			bool doEnd = true;
			while(node != NULL)
			{
				doEnd = true;
				switch(_action)
				{
				case Begin:
					node = right;

					while( node->hasLeft() )
					{
						node = node->getLeft();
					}

					right = node->getRight();
					_action = right != NULL ? Right : Parent;

					if(_action == Parent )
					{
						if(node->getParent()->getRight() == node)
						{
							node->getParent()->destroyNode();
							node->setParent( NULL );
							_action = End;
							break;
						}
						else
						{
							node = node->getParent();
						}
					}
					else
					{
						node = node->getRight();
					}

					right = node->getRight();
					_action = right != NULL ? Right : Parent;

					if( node->hasLeft() )
					{
						node->getLeft()->destroyNode();
						node->setLeft( NULL );
					}

					break;
				case Right:
					prev = node;
					node = right;

					while( node->hasLeft() )
					{
						node = node->getLeft();
					}

					right = node->getRight();
					_action = right != NULL ? Right : Parent;
					if( _action == Parent )
					{
						if( node->getParent()->getParent() == NULL && node->getParent() == prev )
						{
							node->getParent()->destroyNode();
							node->setParent( NULL );
						}
					}
					if( node->hasLeft() )
					{
						node->getLeft()->destroyNode();
						node->setLeft( NULL );
					}

					break;

				case Parent:
					if(node->hasRight())
					{
						doEnd = false;
					}
					while ( node->hasParent() )
					{
						prev = node;
						node = node->getParent();

						if( prev->hasRight() )
						{
							prev->getRight()->destroyNode();
							prev->setRight( NULL );
						}

						if( node->getLeft() == prev )
						{
							if( node->hasLeft() )
							{
								node->getLeft()->destroyNode();
								node->setLeft( NULL );
							}
							right = node->getRight();
							_action = right != NULL ? Right : Parent;
							doEnd = false;
							break;
						}
					}
					if( doEnd )
					{
						if(node->hasRight())
						{
							right = node->getRight();
							_action = Begin;
						}
						else
						{
							_action = End;
							node->destroyNode();
							node = NULL;
						}
					}
					break;

				default:
					node->destroyNode();
					node = NULL;
					break;
				}
			}
		}
	private:
		/*-----------------------------------------Balancing Methods------------------------------------*/
		//! Balances the AvlTree after an insert.
		/*!
		\param node pointer to the AvlNode being balanced.
		\param balance int +1 if adding a left node / -1 if adding a right node.
		\return void
		*/
		void insertBalance( AvlNode* node, int balance )
		{
			while ( node != NULL )
			{
				node->setBalance( node->getBalance() + balance );
				balance = node->getBalance();

				if ( balance == 0 ) return;
				else if ( balance == 2 )
				{
					if ( node->getLeft()->getBalance() == 1 )
					{
						rotateRight( node );
					}
					else
					{
						rotateLeftRight( node );
					}

					return;
				}
				else if ( balance == -2 )
				{
					if ( node->getRight()->getBalance() == -1 )
					{
						rotateLeft( node );
					}
					else
					{
						rotateRightLeft( node );
					}

					return;
				} // end of rotating

				AvlNode* parent = node->getParent();
				if ( parent != NULL )
				{
					balance = parent->getLeft() == node ? 1 : -1;
				}

				node = parent;
			}
		}
		//! Balances the AvlTree after deletion.
		/*!
		\param node pointer to the AvlNode being balanced.
		\param balance int +1 if deleting a left node / -1 if deleting a right node.
		\return void
		*/
		void deleteBalance( AvlNode* node, int balance )
		{
			while (node != null)
			{
				node->setBalance( node->getBalance() + balance );
				balance = node->getBalance();

				if (balance == 2)
				{
					if (node->hasLeft() && node->getLeft()->getBalance() >= 0)
					{
						node = rotateRight(node);

						if ( node->getBalance() == -1 )
						{
							return;
						}
					}
					else
					{
						node = rotateLeftRight(node);
					}
				}
				else if (balance == -2)
				{
					if (node->hasRight() && node->getRight()->getBalance() <= 0)
					{
						node = rotateLeft(node);

						if (node->getBalance() == 1)
						{
							return;
						}
					}
					else
					{
						node = rotateRightLeft(node);
					}
				}
				else if (balance != 0)
				{
					return;
				}

				AvlNode* parent = node->getParent();

				if (parent != NULL)
				{
					balance = parent->getLeft() == node ? -1 : 1;
				}

				node = parent;
			}
		}
		//For rotating the tree left to balance
		AvlNode* rotateLeft( AvlNode* node )
		{
			AvlNode* right = node->getRight();
			AvlNode* rightLeft = right->getLeft();
			AvlNode* parent = node->getParent();

			right->setParent( parent );
			right->setLeft( node );
			node->setRight( rightLeft );
			node->setParent( right );

			if( rightLeft != NULL )
			{
				rightLeft->setParent( node );
			}
			if ( node == _root )
			{
				_root = right;
			}
			else if ( parent->getRight() == node )
			{
				parent->setRight( right );
			}
			else
			{
				parent->setLeft( right );
			}
			right->setBalance( right-> getBalance() + 1 );
			node->setBalance( -right->getBalance() );
			return right;
		}
		//For rotating the tree right to balance
		AvlNode* rotateRight( AvlNode* node )
		{
			AvlNode* left = node->getLeft();
			AvlNode* leftRight = left->getRight();
			AvlNode* parent = node->getParent();

			left->setParent( parent );
			left->setRight( node );
			node->setLeft( leftRight );
			node->setParent( left );

			if( leftRight != NULL )
			{
				leftRight->setParent( node );
			}
			if ( node == _root )
			{
				_root = left;
			}
			else if ( parent->getLeft() == node )
			{
				parent->setLeft( left );
			}
			else
			{
				parent->setRight( left );
			}
			left->setBalance( left-> getBalance() - 1 );
			node->setBalance( -left->getBalance() );
			return left;
		}
		//For rotating the tree left then right to balance
		AvlNode* rotateLeftRight( AvlNode* node )
		{
			AvlNode* left = node->getLeft();
			AvlNode* leftRight = left->getRight();
			AvlNode* parent = node->getParent();
			AvlNode* leftRightRight = leftRight->getRight();
			AvlNode* leftRightLeft = leftRight->getLeft();

			leftRight->setParent( parent );
			node->setLeft( leftRightRight );
			left->setRight( leftRightLeft );
			leftRight->setLeft( left );
			leftRight->setRight( node );
			left->setParent( leftRight );
			node->setParent( leftRight );

			if( leftRightRight != NULL )
			{
				leftRightRight->setParent( node );
			}
			if( leftRightLeft != NULL )
			{
				leftRightLeft->setParent( left );
			}
			if( node == _root )
			{
				_root = leftRight;
			}
			else if( parent->getLeft() == node )
			{
				parent->setLeft( leftRight );
			}
			else
			{
				parent->setRight( leftRight );
			}

			if( leftRight->getBalance() == -1 )
			{
				node->setBalance( 0 );
				left->setBalance( 1 );
			}
			else if( leftRight->getBalance() == 0 )
			{
				node->setBalance( 0 );
				left->setBalance( 0 );
			}
			else
			{
				node->setBalance( -1 );
				left->setBalance( 0 );
			}

			leftRight->setBalance( 0 );

			return leftRight;
		}
		//For rotating the tree right then left to balance
		AvlNode* rotateRightLeft( AvlNode* node )
		{
			AvlNode* right = node->getRight();
			AvlNode* rightLeft = right->getLeft();
			AvlNode* parent = node->getParent();
			AvlNode* rightLeftLeft = rightLeft->getLeft();
			AvlNode* rightLeftRight = rightLeft->getRight();

			rightLeft->setParent( parent );
			node->setRight( rightLeftLeft );
			right->setLeft( rightLeftRight );
			rightLeft->setRight( right );
			rightLeft->setLeft( node );
			right->setParent( rightLeft );
			node->setParent( rightLeft );

			if ( rightLeftLeft != NULL )
			{
				rightLeftLeft->setParent( node );
			}

			if ( rightLeftRight != NULL )
			{
				rightLeftRight->setParent( right );
			}

			if ( node == _root )
			{
				_root = rightLeft;
			}
			else if ( parent->getRight() == node )
			{
				parent->setRight( rightLeft );
			}
			else
			{
				parent->setLeft( rightLeft );
			}

			if( rightLeft->getBalance() == 1 )
			{
				node->setBalance( 0 );
				right->setBalance( -1 );
			}
			else if ( rightLeft->getBalance() == 0 )
			{
				node->setBalance( 0 );
				right->setBalance( 0 );
			}
			else
			{
				node->setBalance( 1 );
				right->setBalance( 0 );
			}

			rightLeft->setBalance( 0 );

			return rightLeft;
		}
		//used in the delete method to swap nodes
		void replace( AvlNode* target, AvlNode* source )
		{
			AvlNode* left = source->getLeft();
			AvlNode* right = source->getRight();

			target = source;
			if( left != NULL )
			{
				left->setParent( target );
			}
			if( right != NULL )
			{
				right->setParent( target );
			}
			//source->destroyNode();
		}
	};
#endif