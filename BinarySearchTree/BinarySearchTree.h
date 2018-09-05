#ifndef binarySearchTreeClass
#define binarySearchTreeClass
#include <iostream>


namespace Dennis_Serrano
{
	template <class T>
	struct Node
	{
		T data;
		Node<T>* left;
		Node<T>* right;

		Node() {}
		Node(T data, Node<T>* left, Node<T>* right)
			: data(data), left(left), right(right) {}
	};

	template <class T>
	class BinarySearchTree
	{
	public:
		BinarySearchTree();
		~BinarySearchTree();
		int size();
		bool isEmpty();
		bool contains(T element);
		bool insert(T element);
		bool remove(T element);
		T findMin();
		T findMax();
		void clear();
		void printTree();
	private:
		Node<T>* root;
		bool contains(Node<T>* tree, T& element);
		bool insert(Node<T>*& tree, T& element);
		bool remove(Node<T>* tree, Node<T>* parent, T& element);
		T findMin(Node<T>* tree);
		T findMax(Node<T>* tree);
		void size(Node<T>* tree, int& size);
		void printTree(Node<T>* tree);
		void destructor(Node<T>* tree);
	};

	/*
	Description: Allocates the BinarySearchTree object.
	*/
	template <class T>
	BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}

	/*
	Description: Deallocates the BinarySearchTree object.
	*/
	template <class T>
	void BinarySearchTree<T>::destructor(Node<T>* tree)
	{
		if (tree != nullptr)
		{
			this->destructor(tree->left);
			this->destructor(tree->right);
			delete tree;
		}
		return;
	}
	template <class T>
	BinarySearchTree<T>::~BinarySearchTree()
	{
		this->destructor(this->root);
		return;
	}

	/*
	Description: Returns the size of the tree.
	*/
	template <class T>
	void BinarySearchTree<T>::size(Node<T>* tree, int& size)
	{
		if (tree != nullptr)
		{
			size++;
			this->size(tree->left, size);
			this->size(tree->right, size);
		}
		return;
	}
	template <class T>
	int BinarySearchTree<T>::size()
	{
		int size = 0;
		this->size(this->root, size);
		return size;
	}

	/*
	Description: Returns true if the tree is empty; otherwise, false.
	*/
	template <class T>
	bool BinarySearchTree<T>::isEmpty()
	{
		return this->root == nullptr;
	}

	/*
	Description: Returns true if the tree contains the specified element;
	otherwise, false.
	*/
	template <class T>
	bool BinarySearchTree<T>::contains(Node<T>* tree, T& element)
	{
		if (tree == nullptr) { return false; }
		else if (element < tree->data) { this->contains(tree->left, element); }
		else if (element > tree->data) { this->contains(tree->right, element); }
		else { return true; }
	}
	template <class T>
	bool BinarySearchTree<T>::contains(T element)
	{
		return this->contains(this->root, element);
	}

	/*
	Description: Inserts the specified element into the tree, if not already inserted,
	and returns true; otherwise, false.
	*/
	template <class T>
	bool BinarySearchTree<T>::insert(Node<T>*& tree, T& element)
	{
		if (tree == nullptr) 
		{
			tree = new Node<T>(element, nullptr, nullptr);
			return true;
		}
		else if (element < tree->data) { this->insert(tree->left, element); }
		else if (element > tree->data) { this->insert(tree->right, element); }
		else { return false; }
	}
	template <class T>
	bool BinarySearchTree<T>::insert(T element)
	{
		return this->insert(this->root, element);
	}

	/*
	Description: Removes the specified element from the tree and returns true;
	otherwise, false.
	*/
	template <class T>
	bool BinarySearchTree<T>::remove(Node<T>* tree, Node<T>* parent, T& element)
	{
		if (tree == nullptr) { return false; }
		else if (element < tree->data) { this->remove(tree->left, tree, element); }
		else if (element > tree->data) { this->remove(tree->right, tree, element); }
		else
		{
			if ((tree->left != nullptr) &&
				(tree->right == nullptr)) 
			{
				if (element < parent->data) { parent->left = tree->left; }
				else if (element > parent->data) { parent->right = tree->left; }
				else { this->root = tree->left; }
				delete tree;
			}
			else if ((tree->left == nullptr) &&
				(tree->right != nullptr)) 
			{
				if (element < parent->data) { parent->left = tree->right; }
				else if (element > parent->data) { parent->right = tree->right; }
				else { this->root = tree->right; }
				delete tree;
			}
			else if ((tree->left != nullptr) &&
				(tree->right != nullptr)) 
			{
				T min = this->findMin(tree->right);
				this->remove(tree->right, tree, min);
				tree->data = min;
			}
			else 
			{
				if (element < parent->data) { parent->left = nullptr; }
				else if (element > parent->data) { parent->right = nullptr; }
				else { this->root = nullptr; }
				delete tree;
			}
			return true;
		}
	}
	template <class T>
	bool BinarySearchTree<T>::remove(T element)
	{
		return this->remove(this->root, this->root, element);
	}

	/*
	Description: Returns the minimum element from the tree.
	*/
	template <class T>
	T BinarySearchTree<T>::findMin(Node<T>* tree)
	{
		if (tree->left == nullptr) { return tree->data; }
		else { this->findMin(tree->left); }
	}
	template <class T>
	T BinarySearchTree<T>::findMin()
	{
		return (this->root == nullptr)
			? throw std::exception("BinarySearchTree is empty.")
			: this->findMin(this->root);
	}

	/*
	Description: Returns the maximum element from the tree.
	*/
	template <class T>
	T BinarySearchTree<T>::findMax(Node<T>* tree)
	{
		if (tree->right == nullptr) { return tree->data; }
		else { this->findMax(tree->right); }
	}
	template <class T>
	T BinarySearchTree<T>::findMax()
	{
		return (this->root == nullptr)
			? throw std::exception("BinarySearchTree is empty.")
			: this->findMax(this->root);
	}

	/*
	Description: Removes all elements from the tree.
	*/
	template <class T>
	void BinarySearchTree<T>::clear()
	{
		this->~BinarySearchTree();
		this->root = nullptr;
		return;
	}

	/*
	Description: Writes the tree to the standard output stream.
	*/
	template <class T>
	void BinarySearchTree<T>::printTree(Node<T>* tree)
	{
		if (tree != nullptr)
		{
			std::cout << tree->data << std::endl;
			this->printTree(tree->left);
			this->printTree(tree->right);
		}
		return;
	}
	template <class T>
	void BinarySearchTree<T>::printTree()
	{
		return this->printTree(this->root);
	}
}
#endif // ! binarySearchTreeClass
