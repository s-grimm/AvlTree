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
		// private members
		private:
			Key			_key;
			Type		_value;
			int			_balance;
			AvlNode*	_parent;
			AvlNode*	_left;
			AvlNode*	_right;
		public:
			AvlNode( const Key& key, const Type& value ) : _parent(0), _left(0), _right(0), _balance(0), _key(key), _value(value) {};
			AvlNode( const std::pair<Key, Type>& keyValuePair ) : _parent(0), _left(0), _right(0), _balance(0), _key( keyValuePair.first ), _value( keyValuePair.second ) {};
			Key first()						{ return _key; }
			Type second()					{ return _value; }
			AvlNode* getParent()			{ return _parent; }
			AvlNode* getRight()				{ return _right; }
			AvlNode* getLeft()				{ return _left;	}
			int getBalance()				{ return _balance; }
			void setRight(AvlNode* node)	{ _right = node; }
			void setLeft(AvlNode* node)		{ _left = node; }
			void setParent(AvlNode* node)	{ _parent = node; }
			void setBalance(int balance)	{ _balance = balance; }
			void setKey( Key key )			{ _key = key; }
			void setValue( Type value )		{ _value = value; }

			bool hasLeft() { return _left != NULL; }
			bool hasRight() { return _right != NULL; }
			bool hasParent() { return _parent != NULL; }

			void destroyNode() {
				_parent = _left = _right = NULL;
				_key = NULL;
				_value = NULL;
				_balance = NULL;
			}

			AvlNode& operator=( AvlNode& rhs ) {
				_balance = rhs._balance;
				_data = rhs._value;
				_key = rhs._key;
				_parent = rhs._parent;
				_left = rhs._left;
				_right = rhs._right;
			}

			bool operator == ( AvlNode& rhs ) { return ( _key == rhs._key ); }
			bool operator != ( AvlNode& rhs ) { return ( _key != rhs._key ); }

		};

	public:
		//!  Iterator Class.
		/*!
		Custom Iterator Class for AvlTree
		*/
		class Iterator {
		protected:
			AvlNode* _node;
		private:
			/*key_compare comparer;*/
			enum TraversalAction { Right, Left, Parent, End, Begin };
			TraversalAction _action;
			AvlNode* _right;

		public:
			Iterator( AvlNode* node ) : _node( node ) {
				_right = _node;
				_action = _node == NULL ? End : Begin;
			}
			Iterator() : _node( NULL ) {
				_action = End;
			}
			~Iterator()	{ _node = nullptr; }
			Iterator& operator=(const Iterator& rhs) {
				_node = rhs._node;
				_right = _node;
				_action = _node == NULL ? End : Begin;
				return (*this);
			}
			bool operator == ( const Iterator& rhs ) { return ( _node == rhs._node); }
			bool operator != ( const Iterator& rhs ) { return ( _node != rhs._node); }

			Iterator& operator ++ () {
				bool endTraversal = true;
				if ( !_node->hasRight() && !_node->hasLeft() && !_node->hasParent() ) { // this is the only node.
					_action = End;
					_node = NULL;
				}
				switch ( _action ) {
				case Begin:
					_node = _right;

					_right = _node->getRight();
					_action = _right != NULL ? Right : Parent;

					if ( _action == Parent ) {
						if ( _node->hasParent() && _node->getParent()->getRight() == _node ) {
							if ( _node->getParent()->hasParent() ) {
								_node = _node->getParent()->getParent();
							} else {
								_action = End;
								_node = NULL;
								break;
							}
						} else {
							_node = _node->getParent();
						}
					} else {
						_node = _node->getRight();
					}

					_right = _node->getRight();
					_action = _right != NULL ? Right : Parent;

					break;
				case Right:
					_node = _right;

					while ( _node->hasLeft() ) {
						_node = _node->getLeft();
					}

					_right = _node->getRight();
					_action = _right != NULL ? Right : Parent;

					break;

				case Parent:
					while ( _node->hasParent() ) {
						AvlNode* previousNode = _node;
						_node = _node->getParent();
						if ( _node->getLeft() == previousNode ) {
							_right = _node->getRight();
							_action = _right != NULL ? Right : Parent;
							endTraversal = false;
							break;
						}
					}
					if ( endTraversal ) {
						_action = End;
						_node = NULL;
					}
					break;

				default:
					_node = NULL;
					break;
				}
				return (*this);
			}

			Iterator& operator ++( int ) {
				Iterator temp(*this);
				++(*this);
				return(temp);
			}

			Iterator& operator -- () {
				return (*this);
			}

			Iterator& operator -- ( int ) {
				Iterator temp(*this);
				--(*this);
				return(temp);
			}
			std::pair<Key,Type>& operator * () {
				return std::pair<Key,Type>( node->first(), node->second() );
			}
			
			AvlNode* operator -> () const {
				return _node;
			}
		};

		//typedefs
	public:
		typedef Iterator									iterator;
		typedef Iterator const								const_iterator;
		typedef std::reverse_iterator<iterator>				reverse_iterator;
		typedef std::reverse_iterator<const_iterator>		const_reverse_iterator;
	private:
		AvlNode*	_rootNode;
		AvlNode*	_firstNode;
		AvlNode*	_lastNode;
		std::size_t _size;
		key_compare	_comparer;
	public:
		/******************************************** Constructors *******************************************/
		avltree() : map() {
			_rootNode = _firstNode = _lastNode = NULL;
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
			_firstNode = NULL;
			_lastNode = NULL;
			_rootNode = NULL;
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
		iterator				begin() { return Iterator( _firstNode ); }
		const_iterator			begin() const { return Iterator( _firstNode ); }
		const_iterator			cbegin() const { return Iterator( _firstNode ); }
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
		iterator erase ( iterator where ) {
		}
		iterator erase ( iterator first, iterator last ) {
		}
		size_type erase ( const Key& key ) {
			size_type removedNodes = 0;
			iterator it = find( key );
			if ( it == end() ) {
				return removedNodes;
			}
			return removedNodes;
		}

		std::pair<iterator,bool> insert( std::pair<Key,Type> value ) {
			iterator it = find( value.first);
			if ( it != end() ) {
				return std::pair<iterator, bool>( it, false );
			}

			AvlNode* newNode = new AvlNode( value.first, value.second );

			if ( _rootNode == NULL ) {
				_rootNode = _firstNode = _lastNode = newNode;
				_size++;
			} else {
				AvlNode* currentNode = _rootNode;

				while ( currentNode != NULL ) {
					bool compare = _comparer( currentNode->first(), newNode->first() );

					if ( compare ) {
						AvlNode* right = currentNode->getRight();
						if( right == NULL) {
							newNode->setParent( currentNode ); 
							currentNode->setRight( newNode );
							_size++;

							if ( _comparer( newNode->first(), _firstNode->first() ) ) {
								_firstNode = newNode;
							} else if ( !_comparer( newNode->first(), _lastNode->first() ) ) {
								_lastNode = newNode;
							}

							insertBalance( currentNode, -1 );

							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = right;
						}
					} else {
						AvlNode* left = currentNode->getLeft();
						if ( left == NULL ) {
							newNode->setParent( currentNode );
							currentNode->setLeft( newNode );
							_size++;

							if ( _comparer( newNode->first() , _firstNode->first() ) ) {
								_firstNode = currentNode;
							} else if ( !_comparer(  newNode->first(), _lastNode->first() ) ) {
								_lastNode = newNode;
							}

							insertBalance( currentNode, +1 );

							return std::pair<iterator,bool>( iterator( newNode ), true );
						} else {
							currentNode = left;
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

		iterator find ( const Key& key ) {
			AvlNode* currentNode = _rootNode;

			while ( currentNode != NULL ) {
				if ( key == currentNode->first() ) {
					return iterator( currentNode );
				}

				bool compare = _comparer( currentNode->first(), key );
				if ( compare ) {
					AvlNode* right = currentNode->getRight();
					if ( right == NULL ) {
						return iterator( NULL );
					} else {
						currentNode = right;
					}
				} else {
					AvlNode* left = currentNode->getLeft();
					if ( left == NULL ) {
						return iterator( NULL );
					} else {
						currentNode = left;
					}
				}
			}
			return iterator( NULL );
		}

		const_iterator find ( const Key& key ) const {
			AvlNode* currentNode = _rootNode;

			while ( currentNode != NULL ) {
				if ( key == currentNode->first() ) {
					return iterator( currentNode );
				}
			}

			bool compare = _comparer( currentNode->first(), key );
			if ( compare ) {
				AvlNode* right = currentNode->getRight();
				if ( right == NULL ) {
					return iterator( NULL );
				} else {
					currentNode = right;
				} 
			} else {
				AvlNode* left = currentNode->getLeft();
				if( left == NULL ) {
					return iterator( NULL );
				} else {
					currentNode = left;
				}
			}
			return iterator( NULL );
		}
		/*----------------------Clear------------------------*/
		//! Clears all the nodes of the AvlTree.
		/*!
		\return void
		*/
		void clear() {
			enum choice { Begin, End, Right, Parent };
			choice _action = Begin;
			AvlNode* node = _firstNode;
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
		void insertBalance( AvlNode* node, int balance ) {
			while ( node != NULL ) {
				node->setBalance( node->getBalance() + balance );
				balance = node->getBalance();

				if ( balance == 0 ) {
					return;
				} else if ( balance == 2 ) {
					if ( node->getLeft()->getBalance() == 1 ) {
						rotateRight( node );
					} else {
						rotateLeftRight( node );
					}

					return;
				} else if ( balance == -2 ) {
					if ( node->getRight()->getBalance() == -1 ) {
						rotateLeft( node );
					} else {
						rotateRightLeft( node );
					}

					return;
				}

				AvlNode* parentNode = node->getParent();

				if ( parentNode != NULL ) {
					balance = parentNode->getLeft() == node ? 1 : -1;
				}

				node = parentNode;
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
		AvlNode* rotateLeft( AvlNode* node ) {
			AvlNode* right = node->getRight();
			AvlNode* rightLeft = right->getLeft();
			AvlNode* parent = node->getParent();

			right->setParent( parent );
			right->setLeft( node );
			node->setRight( rightLeft );
			node->setParent( right );

			if ( rightLeft != NULL ) {
				rightLeft->setParent( node );
			} 

			if ( node == _rootNode ) {
				_rootNode = right;
			} else if ( parent->getRight() == node ) {
				parent->setRight( right );
			} else {
				parent->setLeft( right );
			}

			right->setBalance( right->getBalance() + 1 );
			node->setBalance( -( right->getBalance() ) );

			return right;
		}

		//For rotating the tree right to balance
		AvlNode* rotateRight( AvlNode* node ) {
			AvlNode* left = node->getLeft();
			AvlNode* leftRight = left->getRight();
			AvlNode* parent = node->getParent();

			left->setParent( parent );
			left->setRight( node );
			node->setLeft( leftRight );
			node->setParent( left );

			if ( leftRight != NULL ) {
				leftRight->setParent( node );
			}

			if ( node == _rootNode ) {
				_rootNode = left;
			} else if ( parent->getLeft() == node ) {
				parent->setLeft( left );
			} else {
				parent->setRight( left );
			}

			left->setBalance( left->getBalance() - 1 );
			node->setBalance( -( left->getBalance() ) );

			return left;
		}

		//For rotating the tree left then right to balance
		AvlNode* rotateLeftRight( AvlNode* node ) {
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

			if ( leftRightRight != NULL ) {
				leftRightRight->setParent( node );
			}

			if ( leftRightLeft != NULL ) {
				leftRightLeft->setParent( left );
			}

			if ( node == _rootNode ) {
				_rootNode = leftRight;
			} else if ( parent->getLeft() == node ) {
				parent->setLeft( leftRight );
			} else {
				parent->setRight( leftRight );
			}

			if ( leftRight->getBalance() == -1 ) {
				node->setBalance( 0 );
				left->setBalance( 1 );
			} else if ( leftRight->getBalance() == 0 ) {
				node->setBalance( 0 );
				left->setBalance( 0 );
			} else {
				node->setBalance( -1 );
				left->setBalance( 0 );
			}

			leftRight->setBalance( 0 );

			return leftRight;
		}

		//For rotating the tree right then left to balance
		AvlNode* rotateRightLeft( AvlNode* node ) {
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

			if ( rightLeftLeft != NULL ) {
				rightLeftLeft->setParent( node );
			}

			if ( rightLeftRight != NULL ) {
				rightLeftRight->setParent( right );
			}

			if ( node == _rootNode ) {
				_rootNode = rightLeft;
			} else if ( parent->getRight() == node ) {
				parent->setRight( rightLeft );
			} else {
				parent->setLeft( rightLeft );
			}

			if( rightLeft->getBalance() == 1 ) {
				node->setBalance( 0 );
				right->setBalance( -1 );
			} else if ( rightLeft->getBalance() == 0 ) {
				node->setBalance( 0 );
				right->setBalance( 0 );
			} else {
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