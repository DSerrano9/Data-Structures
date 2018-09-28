#ifndef linkedListClass
#define linkedListClass
#include <string>


namespace Dennis_Serrano
{
	template <class T>
	struct Node
	{
		T data;
		Node<T>* next;

		Node() {}
		Node(T data, Node<T>* next) : data(data), next(next) {}
	};

	template <class T>
	class LinkedList
	{
	public:
		LinkedList();
		~LinkedList();
		void addToFront(T element);
		void addToEnd(T element);
		void clear();
		T get(int index);
		T& at(int index);
		int size();
		int find(T element, int occurrence);
		bool remove(int index);
		bool remove(T element, int occurrence);
		bool insertAfter(T element, T afterElement, int occurrence);
		bool insertBefore(T element, T beforeElement, int occurrence);
	private:
		int listSize;
		Node<T>* head;
	};

	/*
	Description: Allocates the LinkedList object.
	*/
	template <class T>
	LinkedList<T>::LinkedList()
	{
		this->listSize = 0;
		this->head = nullptr;
	}

	/*
	Description: Deallocates the LinkedList object.
	*/
	template <class T>
	LinkedList<T>::~LinkedList()
	{
		Node<T>* p = this->head;
		Node<T>* p1 = nullptr;
		while (p != nullptr)
		{
			p1 = p->next;
			delete p;
			p = p1;
		}
		return;
	}

	/*
	Description: Adds a element to the front of the list.
	*/
	template <class T>
	void LinkedList<T>::addToFront(T element)
	{
		Node<T>* n = new Node<T>(element, this->head);
		this->head = n;
		this->listSize++;
		return;
	}

	/*
	Description: Adds a element to the end of the list.
	*/
	template <class T>
	void LinkedList<T>::addToEnd(T element)
	{
		if (this->head == nullptr) { this->addToFront(element); }
		else
		{
			Node<T>* p = this->head;
			while (p->next != nullptr) { p = p->next; }
			Node<T>* n = new Node<T>(element, p->next);
			p->next = n;
			this->listSize++;
		}
		return;
	}

	/*
	Description: Removes all elements from the list.
	*/
	template <class T>
	void LinkedList<T>::clear()
	{
		if (this->listSize > 0)
		{
			this->~LinkedList();
			this->head = nullptr;
			this->listSize = 0;
		}
		return;
	}

	/*
	Description: Returns a copy of the element's value at
	the specified index.
	*/
	template <class T>
	T LinkedList<T>::get(int index)
	{
		if ((index >= 0) && (index < this->listSize))
		{
			int i = 0;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (i++ == index)
				{
					return p->data;
				}
				else { p = p->next; }
			}
		}
		throw std::out_of_range("Out of Range Index");
	}

	/*
	Description: Returns a reference to the element's value 
	at the specified index.
	*/
	template <class T>
	T& LinkedList<T>::at(int index)
	{
		if ((index >= 0) && (index < this->listSize))
		{
			int i = 0;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (i++ == index)
				{
					T& ref = p->data;
					return ref;
				}
				else { p = p->next; }
			}
		}
		throw std::out_of_range("Out of Range Index");
	}

	/*
	Description: Returns the size of the List.
	*/
	template <class T>
	int LinkedList<T>::size()
	{
		return this->listSize;
	}

	/*
	Description: Returns the index of a specified element of a specified occurrence;
	otherwise, -1.
	*/
	template <class T>
	int LinkedList<T>::find(T element, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int i = 0, occurrenceCount = 1;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (p->data == element)
				{
					if (occurrenceCount == occurrence) { return i; }
					else { occurrenceCount++; }
				}
				p = p->next;
				i++;
			}
		}
		return -1;
	}

	/*
	Description: Removes the element at the specified index
	and returns true; otherwise, false.
	*/
	template <class T>
	bool LinkedList<T>::remove(int index)
	{
		int i = 0;
		Node<T>* p = this->head;
		Node<T>* p1 = nullptr;
		while (p != nullptr)
		{
			if (i == index)
			{
				if (p1 == nullptr) { this->head = p->next; }
				else { p1->next = p->next; }
				delete p;
				this->listSize--;
				return true;
			}
			i++;
			p1 = p;
			p = p->next;
		}
		return false;
	}

	/*
	Description: Removes a specified element of a specified occurrence and returns true;
	otherwise, false.
	*/
	template <class T>
	bool LinkedList<T>::remove(T element, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int occurrenceCount = 1;
			Node<T>* p = this->head;
			Node<T>* p1 = nullptr;
			while (p != nullptr)
			{
				if (p->data == element)
				{
					if (occurrenceCount == occurrence)
					{
						if (p1 == nullptr) { this->head = p->next; }
						else { p1->next = p->next; }
						delete p;
						this->listSize--;
						return true;
					}
					else { occurrenceCount++; }
				}
				p1 = p;
				p = p->next;
			}
		}
		return false;
	}

	/*
	Description: Inserts a element after a specified element of a specified occurrence
	and returns true; otherwise, false.
	*/
	template <class T>
	bool LinkedList<T>::insertAfter(T element, T afterElement, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int occurrenceCount = 1;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (p->data == afterElement)
				{
					if (occurrenceCount == occurrence)
					{
						Node<T>* n = new Node<T>(element, p->next);
						p->next = n;
						this->listSize++;
						return true;
					}
					else { occurrenceCount++; }
				}
				p = p->next;
			}
		}
		return false;
	}

	/*
	Description: Inserts a element before a specified element of a specified occurrence
	and returns true; otherwise, false.
	*/
	template <class T>
	bool LinkedList<T>::insertBefore(T element, T beforeElement, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int occurrenceCount = 1;
			Node<T>* p = this->head;
			Node<T>* p1 = nullptr;
			while (p != nullptr)
			{
				if (p->data == beforeElement)
				{
					if (occurrenceCount == occurrence)
					{
						Node<T>* n = new Node<T>(element, p);
						if (p1 == nullptr) { this->head = n; }
						else { p1->next = n; }
						this->listSize++;
						return true;
					}
					else { occurrenceCount++; }
				}
				p1 = p;
				p = p->next;
			}
		}
		return false;
	}
}
#endif // ! linkedListClass
