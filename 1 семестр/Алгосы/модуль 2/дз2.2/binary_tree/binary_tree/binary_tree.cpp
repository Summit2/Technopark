/*
Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N. 
Требуется построить бинарное дерево, заданное наивным порядком вставки. 
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. 
Выведите элементы в порядке pre-order (сверху вниз).

Рекурсия запрещена.
*/
#include<cassert>
#include<iostream>
#include <stack>

template<class T, class Compare>
class BinaryTree {
public:
	BinaryTree( const Compare& _cmp ) : root( nullptr ), Size(0), cmp( _cmp ) {}
	~BinaryTree();

	void Add( const T& key );
	bool Has( const T& key ) const;

	void DfsPreOrder( void (*visit)(const T& key) ) const;

private:
	struct Node {
		T Key;
		Node* Left;
		Node* Right;

		Node(const T& key) : Key(key), Left(nullptr), Right(nullptr) {};
	};
	Node* root;
	Compare cmp;
	unsigned int Size;
	
};

template<class T, class Compare>
BinaryTree<T, Compare>::~BinaryTree()
{
	if (root == nullptr) {
		return;
	}


	Node* nodeToLookAt = root; //временная нода для обхода поддерева
	std::stack<Node*> saveNodes; //стек для хранения промежуточных нод

	std::stack<Node*> toDestroyNodes; //стек для добавления адресов нод в порядке post-order
	for (int i = Size-1; i > 0; --i)
	{


		if (nodeToLookAt->Right != nullptr) {
			if (nodeToLookAt->Left != nullptr) {
				saveNodes.push(nodeToLookAt);
			}
			nodeToLookAt = nodeToLookAt->Right;
			toDestroyNodes.push(nodeToLookAt);
		}
		else if (nodeToLookAt->Left != nullptr) {

			nodeToLookAt = nodeToLookAt->Left;
			toDestroyNodes.push(nodeToLookAt);
		}
		else {
			if (saveNodes.empty() == false) {
				nodeToLookAt = saveNodes.top()->Left;
				toDestroyNodes.push(nodeToLookAt);

				saveNodes.pop();

			}
		};

	}

	while (!toDestroyNodes.empty()) {

		delete toDestroyNodes.top();
		toDestroyNodes.pop();
	}
	delete root; //после всего удаляем root
}



template<class T, class Compare>
void BinaryTree<T, Compare>::Add( const T& key )
{

	if (root == nullptr) {
		root = new Node(key);
		++Size;
		return;
	};

	Node* currentNode = root;
	Node* parentNode = nullptr;

	while (true) {
		if (currentNode == nullptr) { //значит мы пришли в лист
			Node* tempNode = new Node(key); 
			if (cmp(parentNode->Key , key)) {
				parentNode->Right = tempNode;
			}
			else {
				parentNode->Left = tempNode;
			}
			++Size;
			return;
		}

		parentNode = currentNode; //запомнили текущую ноду, чтобы потом писать в ее потомка
		if (cmp(currentNode->Key, key)) {
			//идем в правый узел
			currentNode = currentNode->Right;
		}
		else {
			//идем в левый узел
			currentNode = currentNode->Left;
		}
	}
}



template<class T, class Compare>
bool BinaryTree<T, Compare>::Has( const T& key ) const
{
	if (root==nullptr) {
		return false;
	}
	Node* currentNode = root;


	while (true)
	{
		if (currentNode->Key == key) {
			return true;
		};
		if (cmp(currentNode->Key, key))  {
			//значит ключ справа
			if (currentNode->Right != nullptr) {
				currentNode = currentNode->Right;
			}
			else {
				return false;
			}
		}
		else {
			//значит ключ слева
			if (currentNode->Left != nullptr) {
				currentNode = currentNode->Left;
			}
			else {
				return false;
			}
		}
	}
	

}


template<class T, class Compare>
void BinaryTree<T, Compare>::DfsPreOrder( void (*visit)(const T& key) ) const 
{
	if (root == nullptr) {
		return;
	};

	visit(root->Key); 
	
	
	//обход циклом
	Node* nodeToLookAt = root; //временная нода для обхода поддерева
	std::stack<Node*> saveNodes; //стек для хранения промежуточных нод

	for (int i = 0; i < Size-1; i++)
	{
		


		if (nodeToLookAt->Left != nullptr) {
			
			if (nodeToLookAt->Right != nullptr) { 
				saveNodes.push(nodeToLookAt);
			}
			nodeToLookAt = nodeToLookAt->Left;

			

			visit(nodeToLookAt->Key);
		}
		else if (nodeToLookAt->Right != nullptr) {
			nodeToLookAt = nodeToLookAt->Right;
			visit(nodeToLookAt->Key);
		}
		else {
			

				
			
			if (saveNodes.empty() == false) {
				nodeToLookAt = saveNodes.top()->Right;
				saveNodes.pop();
				visit(nodeToLookAt->Key);
			}
			
		};
	}
}


struct IntCmp {
	bool operator()( int l, int r ) const { return l < r; }
};

int main()
{
	IntCmp cmp;
	BinaryTree<int, IntCmp> tree( cmp );

	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		int temp;
		std::cin >> temp;
		tree.Add(temp);
	};


	std::cout << std::endl;
	tree.DfsPreOrder( []( const int& key ) { std::cout << key << " "; } );

	return 0;
}