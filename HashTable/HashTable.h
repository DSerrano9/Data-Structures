#ifndef hashTableClass
#define hashTableClass
#include <string>
#include <vector>
#include "LinkedList.h"


namespace Dennis_Serrano
{
	template <class T>
	struct HashState
	{
		T value;
		unsigned int count;
		const std::string key;

		HashState(int count, std::string key, T value)
			: count(count), key(key), value(value)
		{

		}
		bool operator ==(HashState& state)
		{
			return this->key == state.key;
		}		
	};

	template <class T>
	struct HashNode
	{
		LinkedList<HashState<T>>* values;
		HashNode() : values(nullptr)
		{

		}
	};

	template <class T>
	class HashTable
	{
	public:
		HashTable();
		HashTable(int size);
		~HashTable();
		void clear();
		void add(std::string key, T value);
		void remove(std::string key);
		T get(std::string key);
		T& at(std::string key);
	private:
		std::vector<HashNode<T>>* table;
		int bernsteinHashFunction(char* c);
		char* to_CharArray(std::string str);
	};

	/*
	Description: Allocates the HashTable object with 
	a table size of fifty.
	*/
	template <class T>
	HashTable<T>::HashTable()
	{
		this->table = new std::vector<HashNode<T>>(50);
	} 

	/*
	Description: Allocates the HashTable object with
	a specified table size.
	*/
	template <class T>
	HashTable<T>::HashTable(int size)
	{
		this->table = new std::vector<HashNode<T>>(size);
	}

	/*
	Description: Deallocates the HashTable object.
	*/
	template <class T>
	HashTable<T>::~HashTable()
	{
		for (int i = 0; i < this->table->size(); i++)
		{
			if (this->table->at(i).values != nullptr)
			{
				delete this->table->at(i).values;
			}
		}
		delete this->table;
		return;
	}

	/*
	Description: Removes all values from the table.
	*/
	template <class T>
	void HashTable<T>::clear()
	{
		int size = this->table->size();
		this->~HashTable();
		this->table = new std::vector<HashNode<T>>(size);
		return;
	}

	/*
	Description: Adds the specified key and value
	to the table.
	*/
	template <class T>
	void HashTable<T>::add(std::string key, T value)
	{
		char* charArray = this->to_CharArray(key);
		int index = this->bernsteinHashFunction(charArray);
		delete charArray;

		if (this->table->at(index).values == nullptr)
		{
			this->table->at(index).values = new LinkedList<HashState<T>>();
		}
		else
		{
			int size = this->table->at(index).values->size();
			for (int i = 0; i < size; i++)
			{
				if (this->table->at(index).values->at(i).key == key)
				{
					this->table->at(index).values->at(i).count++;
					return;
				}
			}
		}
		this->table->at(index).values->addToFront(HashState<T>(1, key, value));
		return;
	}

	/*
	Description: Removes the value with the specified key
	from the table.
	*/
	template <class T>
	void HashTable<T>::remove(std::string key)
	{
		char* charArray = this->to_CharArray(key);
		int index = this->bernsteinHashFunction(charArray);
		delete charArray;

		if (this->table->at(index).values != nullptr)
		{
			int size = this->table->at(index).values->size();
			for (int i = 0; i < size; i++)
			{
				if (this->table->at(index).values->at(i).key == key)
				{
					this->table->at(index).values->at(i).count--;
					if (this->table->at(index).values->at(i).count == 0)
					{
						this->table->at(index).values->remove(
							this->table->at(index).values->at(i), 1);
					}
					if (this->table->at(index).values->size() == 0)
					{
						delete this->table->at(index).values;
						this->table->at(index).values = nullptr;
					}
					return;
				}
			}
		}
		return;
	}

	/*
	Description: Returns a copy of the specified key's
	value.
	*/
	template <class T>
	T HashTable<T>::get(std::string key) 
	{
		char* charArray = this->to_CharArray(key);
		int index = this->bernsteinHashFunction(charArray);
		delete charArray;

		if (this->table->at(index).values != nullptr)
		{
			int size = this->table->at(index).values->size();
			for (int i = 0; i < size; i++)
			{
				if (this->table->at(index).values->at(i).key == key)
				{
					return this->table->at(index).values->get(i).value;
				}
			}
		}
		throw std::exception("Nonexistent Key");
	}

	/*
	Description: Returns a reference to the specified 
	key's value.
	*/
	template <class T>
	T& HashTable<T>::at(std::string key)
	{
		char* charArray = this->to_CharArray(key);
		int index = this->bernsteinHashFunction(charArray);
		delete charArray;

		if (this->table->at(index).values != nullptr)
		{
			int size = this->table->at(index).values->size();
			for (int i = 0; i < size; i++)
			{
				if (this->table->at(index).values->at(i).key == key)
				{
					return this->table->at(index).values->at(i).value;
				}
			}
		}
		throw std::exception("Nonexistent Key");
	}

	/*
	Description: An algorithm produced by Professor
	Daniel J. Bernstein.
	*/
	template <class T>
	int HashTable<T>::bernsteinHashFunction(char* c)
	{
		char *p = c;
		int hashVal = 5381;
		while (*p)
		{
			hashVal *= 33;
			hashVal += static_cast<int>(*p++);
		}
		hashVal %= strlen(c);
		return hashVal;
	}

	/*
	Description: Returns the parameter-supplied string as a
	char*.
	*/
	template <class T>
	char* HashTable<T>::to_CharArray(std::string str)
	{
		char* c = new char[str.length() + 1];
		for (int i = 0; i < str.length(); i++)
		{
			c[i] = str[i];
		}
		c[str.length()] = '\0';
		return c;
	}
}
#endif // ! hashTableClass
