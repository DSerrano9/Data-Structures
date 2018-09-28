#ifndef queueClass
#define queueClass
#include "DoubleLinkedList.h"


namespace Dennis_Serrano
{
	template <class T>
	class Queue : private DoubleLinkedList<T>
	{
	public:
		void clear();
		void enqueue(T element);
		T dequeue();
		T peek();
		T get(int index);
		T& at(int index);
		int size();
	private:
	};

	/*
	Description: Removes all elements from the the queue.
	*/
	template <class T>
	void Queue<T>::clear()
	{
		DoubleLinkedList<T>::clear();
		return;
	}

	/*
	Description: Adds a element to the end of the queue.
	*/
	template <class T>
	void Queue<T>::enqueue(T element)
	{
		this->addToEnd(element);
		return;
	}

	/*
	Description: Returns and removes the element at the front of the queue.
	*/
	template <class T>
	T Queue<T>::dequeue()
	{
		T t = this->get(0);
		this->remove(0);
		return t;
	}

	/*
	Description: Returns the element at the front of the queue.
	*/
	template <class T>
	T Queue<T>::peek()
	{
		return this->get(0);
	}

	/*
	Description: Returns a copy of the element's value at
	the specified index.
	*/
	template <class T>
	T Queue<T>::get(int index)
	{
		return DoubleLinkedList<T>::get(index);
	}

	/*
	Description: Returns a reference to the element's value
	at the specified index.
	*/
	template <class T>
	T& Queue<T>::at(int index)
	{
		return DoubleLinkedList<T>::at(index);
	}

	/*
	Description: Returns the size of the queue.
	*/
	template <class T>
	int Queue<T>::size()
	{
		return DoubleLinkedList<T>::size();
	}
}
#endif // ! queueClass
