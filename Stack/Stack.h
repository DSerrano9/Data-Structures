#ifndef stackClass
#define stackClass
#include "DoubleLinkedList.h"


namespace Dennis_Serrano
{
	template <class T>
	class Stack : private DoubleLinkedList<T>
	{
	public:
		void clear();
		void push(T element);
		T pop();
		T peek();
		T get(int index);
		T& at(int index);
		int size();
	private:
	};

	/*
	Description: Removes all elements from the the stack.
	*/
	template <class T>
	void Stack<T>::clear()
	{
		DoubleLinkedList<T>::clear();
		return;
	}

	/*
	Description: Adds a element to the end of the stack.
	*/
	template <class T>
	void Stack<T>::push(T element)
	{
		this->addToEnd(element);
		return;
	}

	/*
	Description: Returns and removes the element at the end of the stack.
	*/
	template <class T>
	T Stack<T>::pop()
	{
		T t = this->get(this->size() - 1);
		this->remove(this->size() - 1);
		return t;
	}

	/*
	Description: Returns the element at the end of the stack.
	*/
	template <class T>
	T Stack<T>::peek()
	{
		return this->get(this->size() - 1);
	}

	/*
	Description: Returns a copy of the element's value at
	the specified index.
	*/
	template <class T>
	T Stack<T>::get(int index)
	{
		return DoubleLinkedList<T>::get(index);
	}

	/*
	Description: Returns a reference to the element's value 
	at the specified index.
	*/
	template <class T>
	T& Stack<T>::at(int index)
	{
		return DoubleLinkedList<T>::at(index);
	}

	/*
	Description: Returns the size of the stack.
	*/
	template <class T>
	int Stack<T>::size()
	{
		return DoubleLinkedList<T>::size();
	}
}
#endif // ! stackClass
