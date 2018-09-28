#ifndef doubleLinkedListClass
#define doubleLinkedListClass
#include <string>


namespace Dennis_Serrano
{
	template <class T>
	struct Node
	{
		T data;
		Node<T>* next;
		Node<T>* prev;

		Node() {}
		Node(T data, Node<T>* next, Node<T>* prev) : data(data), next(next), prev(prev) {}
	};

	template <class T>
	class DoubleLinkedList
	{
	public:
		DoubleLinkedList();
		~DoubleLinkedList();
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
	Description: Allocate DoubleLinkedList object.
	*/
	template <class T>
	DoubleLinkedList<T>::DoubleLinkedList()
	{
		this->listSize = 0;
		this->head = nullptr;
	}

	/*
	Description: Deallocate DoubleLinkedList object.
	*/
	template <class T>
	DoubleLinkedList<T>::~DoubleLinkedList()
	{
		Node<T>* deleteThis;
		Node<T>* p = this->head;
		while (p != nullptr)
		{
			deleteThis = p;
			p = p->next;
			delete deleteThis;
		}
		return;
	}

	/*
	Description: Adds a element to the front of the list.
	*/
	template <class T>
	void DoubleLinkedList<T>::addToFront(T element)
	{
		Node<T>* n = nullptr;
		if (this->head == nullptr)
		{
			n = new Node<T>(element, this->head, this->head);
		}
		else
		{
			n = new Node<T>(element, this->head, nullptr);
			this->head->prev = n;
		}
		this->head = n;
		this->listSize++;
		return;
	}

	/*
	Description: Adds a element to the end of the list.
	*/
	template <class T>
	void DoubleLinkedList<T>::addToEnd(T element)
	{
		if (this->head == nullptr) { this->addToFront(element); }
		else
		{
			Node<T>* p = this->head;
			while (p->next != nullptr) { p = p->next; }
			Node<T>* n = new Node<T>(element, p->next, p);
			p->next = n;
			this->listSize++;
		}
		return;
	}

	/*
	Description: Removes all elements from the list.
	*/
	template <class T>
	void DoubleLinkedList<T>::clear()
	{
		if (this->listSize > 0)
		{
			this->~DoubleLinkedList();
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
	T DoubleLinkedList<T>::get(int index)
	{
		if ((index >= 0) && (index < this->listSize))
		{
			int i = 0;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (i == index) { return p->data; }
				else
				{
					i++;
					p = p->next;
				}
			}
		}
		throw std::out_of_range("Out of Range Index");
	}

	/*
	Description: Returns a reference to the element's value 
	at the specified index.
	*/
	template <class T>
	T& DoubleLinkedList<T>::at(int index)
	{
		if ((index >= 0) && (index < this->listSize))
		{
			int i = 0;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (i == index)
				{
					T& ref = p->data;
					return ref;
				}
				else
				{
					i++;
					p = p->next;
				}
			}
		}
		throw std::out_of_range("Out of Range Index");
	}

	/*
	Description: Returns the size of the List.
	*/
	template <class T>
	int DoubleLinkedList<T>::size()
	{
		return this->listSize;
	}

	/*
	Description: Returns the index of a specified element of a specified occurrence;
	otherwise, -1.
	*/
	template <class T>
	int DoubleLinkedList<T>::find(T element, int occurrence)
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
	bool DoubleLinkedList<T>::remove(int index)
	{
		int i = 0;
		Node<T>* p = this->head;
		while (p != nullptr)
		{
			if (i == index)
			{
				if (p->prev == nullptr)
				{
					this->head = p->next;
					if (this->head != nullptr) { this->head->prev = nullptr; }
				}
				else
				{
					p->prev->next = p->next;
					if (p->next != nullptr) { p->next->prev = p->prev; }
				}
				delete p;
				this->listSize--;
				return true;
			}
			p = p->next;
			i++;
		}
		return false;
	}

	/*
	Description: Removes a specified element of a specified
	occurrence and returns true; otherwise, false.
	*/
	template <class T>
	bool DoubleLinkedList<T>::remove(T element, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int occurrenceCount = 1;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (p->data == element)
				{
					if (occurrenceCount == occurrence)
					{
						if (p->prev == nullptr)
						{
							this->head = p->next;
							if (this->head != nullptr) { this->head->prev = nullptr; }
						}
						else
						{
							p->prev->next = p->next;
							if (p->next != nullptr) { p->next->prev = p->prev; }
						}
						delete p;
						this->listSize--;
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
	Description: Inserts a element after a specified element of a specified
	occurrence and returns true; otherwise, false.
	*/
	template <class T>
	bool DoubleLinkedList<T>::insertAfter(T element, T afterElement, int occurrence)
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
						Node<T>* n = new Node<T>(element, p->next, p);
						if (p->next == nullptr) { p->next = n; }
						else
						{
							p->next->prev = n;
							p->next = n;
						}
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
	Description: Inserts a element before a specified element of a specified
	occurrence and returns true; otherwise, false.
	*/
	template <class T>
	bool DoubleLinkedList<T>::insertBefore(T element, T beforeElement, int occurrence)
	{
		if ((occurrence > 0) &&
			(occurrence <= this->size()))
		{
			int occurrenceCount = 1;
			Node<T>* p = this->head;
			while (p != nullptr)
			{
				if (p->data == beforeElement)
				{
					if (occurrenceCount == occurrence)
					{
						Node<T>* n = new Node<T>(element, p, p->prev);
						if (p->prev == nullptr) { this->head = n; }
						else { p->prev->next = n; }
						p->prev = n;
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
}
#endif // ! doubleLinkedListClass
