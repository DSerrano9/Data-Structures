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
		T get(std::string key);
		T& at(std::string key);
		bool add(std::string key, T value);
		bool remove(std::string key);
	private:
		std::vector<HashNode<T>>* table;
		int hashFunction(std::string key, int tablesize);
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
		for (unsigned int i = 0; i < this->table->size(); i++)
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
	Description: Returns a copy of the specified key's
	value.
	*/
	template <class T>
	T HashTable<T>::get(std::string key)
	{
		int index = this->hashFunction(key, this->table->size());
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
		int index = this->hashFunction(key, this->table->size());
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
	Description: Adds the specified key and value
	to the table if and only if the key hasn't 
	already been added with a different value.
	If added, the function returns true; otherwise,
	false.
	*/
	template <class T>
	bool HashTable<T>::add(std::string key, T value)
	{
		int index = this->hashFunction(key, this->table->size());
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
					if (this->table->at(index).values->at(i).value == value)
					{
						this->table->at(index).values->at(i).count++;
						return true;
					}
					return false;
				}
			}
		}
		this->table->at(index).values->addToFront(HashState<T>(1, key, value));
		return true;
	}

	/*
	Description: Removes the value with the specified key
	from the table and returns true; otherwise, false.
	*/
	template <class T>
	bool HashTable<T>::remove(std::string key)
	{
		int index = this->hashFunction(key, this->table->size());
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

						if (this->table->at(index).values->size() == 0)
						{
							delete this->table->at(index).values;
							this->table->at(index).values = nullptr;
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	/*
	Credit to: 
	Weiss, Mark. Allen. Data Structures
	and Algorithm Analysis in C++ Third Edition.
	*/
	template <class T>
	int HashTable<T>::hashFunction(std::string key, int tablesize)
	{
		int hashVal = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hashVal = 37 * hashVal + key[i];
		}
		hashVal %= tablesize;
		if (hashVal < 0)
		{
			hashVal += tablesize;
		}
		return hashVal;
	}
}
#endif // ! hashTableClass
