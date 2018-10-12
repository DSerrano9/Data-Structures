#ifndef undirectedGraphClass
#define undirectedGraphClass
#include <vector>
#include <iostream>
#include "LinkedList.h"


namespace Dennis_Serrano
{
	template <class T>
	struct AdjacencyState
	{
		const int index;
		const T vertex;

		AdjacencyState(int index, T vertex)
			: index(index), vertex(vertex)
		{

		}
		bool operator ==(AdjacencyState& state)
		{
			return this->vertex == state.vertex;
		}
	};

	template <class T>
	struct AdjacencyNode
	{
		LinkedList<AdjacencyState<T>>* vertexs;
		AdjacencyNode() : vertexs(nullptr)
		{

		}
	};

	template <class T>
	class UndirectedGraph
	{
	public:
		UndirectedGraph();
		UndirectedGraph(int capacity);
		~UndirectedGraph();
		void clear();
		void addVertex(T vertex);
		void removeVertex(T vertex);	
		void addEdge(T vertex1, T vertex2);	
		void removeEdge(T vertex1, T vertex2);
		void printDepthFirstTraversal(int index);
		void printUndirectedGraph();	
		bool isConnected(T vertex1, T vertex2);
		bool contains(T vertex);
		int capacity();
		int count();
	private:
		int adjacencyListCount;
		std::vector<AdjacencyNode<T>>* adjacencyList;
		void printDepthFirstTraversal(int index, std::vector<bool>& visited);	
		int indexOf(T vertex);
		int indexOfUnassignedElement();
	};

	/*
	Description: Allocates the UndirectedGraph object and
	sets the adjacency list with a capacity of fifty.
	*/
	template <class T>
	UndirectedGraph<T>::UndirectedGraph()
	{
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(50);
		this->adjacencyListCount = 0;
	}

	/*
	Description: Allocates the UndirectedGraph object and
	sets the adjacency list with a specified capacity.
	*/
	template <class T>
	UndirectedGraph<T>::UndirectedGraph(int capacity)
	{
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(capacity);
		this->adjacencyListCount = 0;
	}

	/*
	Description: Deallocates the UndirectedGraph object.
	*/
	template <class T>
	UndirectedGraph<T>::~UndirectedGraph()
	{
		for (unsigned int i = 0; i < this->adjacencyList->size(); i++)
		{
			if (this->adjacencyList->at(i).vertexs != nullptr)
			{
				delete this->adjacencyList->at(i).vertexs;
			}
		}
		delete this->adjacencyList;
		return;
	}

	/*
	Description: Removes all vertices from the adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::clear()
	{
		int capacity = this->adjacencyList->size();
		this->~Graph();
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(capacity);
		this->adjacencyListCount = 0;
		return;
	}

	/*
	Description: Adds the specified vertex to the
	adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::addVertex(T vertex)
	{
		if (this->indexOf(vertex) == -1)
		{
			int index = this->indexOfUnassignedElement();
			if (index != -1)
			{
				this->adjacencyList->at(index).vertexs = new LinkedList<AdjacencyState<T>>();
				this->adjacencyList->at(index).vertexs->addToEnd(AdjacencyState<T>(index, vertex));
				this->adjacencyListCount++;
			}
		}
		return;
	}

	/*
	Description: Removes the specified vertex from the
	adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::removeVertex(T vertex)
	{
		int index = this->indexOf(vertex);
		if (index != -1)
		{
			AdjacencyState<T> removeThis = this->adjacencyList->at(index).vertexs->get(0);
			for (int i = 1; i < this->adjacencyList->at(index).vertexs->size(); i++)
			{
				int edgeIndex = this->adjacencyList->at(index).vertexs->at(i).index;
				if (removeThis.index != edgeIndex)
				{
					this->adjacencyList->at(edgeIndex).vertexs->remove(removeThis, 1);
				}			
			}
			delete this->adjacencyList->at(index).vertexs;
			this->adjacencyList->at(index).vertexs = nullptr;
			this->adjacencyListCount--;
		}
		return;
	}

	/*
	Description: Adds the specified vertices to the adjacency
	list, if not already added, and creates a edge between 
	them.
	*/
	template <class T>
	void UndirectedGraph<T>::addEdge(T vertex1, T vertex2)
	{	
		if (!this->isConnected(vertex1, vertex2))
		{
			int v1Index = this->indexOf(vertex1);		
			if (vertex1 == vertex2)
			{
				if ((this->capacity() - this->count()) >= 1 &&
					v1Index == -1)
				{
					this->addVertex(vertex1);
					v1Index = this->indexOf(vertex1);
				}
				if (v1Index != -1)
				{
					this->adjacencyList->at(v1Index).vertexs->addToEnd(
						this->adjacencyList->at(v1Index).vertexs->get(0));
				}
				return;
			}
			int v2Index = this->indexOf(vertex2);
			if (v1Index == -1 && v2Index == -1)
			{
				if ((this->capacity() - this->count()) >= 2)
				{
					this->addVertex(vertex1);
					this->addVertex(vertex2);
					v1Index = this->indexOf(vertex1);
					v2Index = this->indexOf(vertex2);
				}
			}
			else if (v1Index == -1 && v2Index != -1)
			{
				if ((this->capacity() - this->count()) >= 1)
				{
					this->addVertex(vertex1);
					v1Index = this->indexOf(vertex1);
				}
			}
			else if (v1Index != -1 && v2Index == -1)
			{
				if ((this->capacity() - this->count()) >= 1)
				{
					this->addVertex(vertex2);
					v2Index = this->indexOf(vertex2);
				}
			}
			if (v1Index != -1 && v2Index != -1)
			{
				this->adjacencyList->at(v1Index).vertexs->addToEnd(
					this->adjacencyList->at(v2Index).vertexs->get(0));
				this->adjacencyList->at(v2Index).vertexs->addToEnd(
					this->adjacencyList->at(v1Index).vertexs->get(0));
			}
		}
		return;
	}

	/*
	Description: Removes the edge between the specified vertices. 
	*/
	template <class T>
	void UndirectedGraph<T>::removeEdge(T vertex1, T vertex2)
	{
		if (this->isConnected(vertex1, vertex2))
		{
			int v1Index = this->indexOf(vertex1);
			if (vertex1 == vertex2)
			{
				this->adjacencyList->at(v1Index).vertexs->remove(
					this->adjacencyList->at(v1Index).vertexs->get(0), 2);
				return;
			}
			int v2Index = this->indexOf(vertex2);
			this->adjacencyList->at(v1Index).vertexs->remove(
				this->adjacencyList->at(v2Index).vertexs->get(0), 1);
			this->adjacencyList->at(v2Index).vertexs->remove(
				this->adjacencyList->at(v1Index).vertexs->get(0), 1);
		}		
		return;
	}

	/*
	Description: Prints the adjacency list to the console
	using a depth first traversal algorithm.
	*/
	template <class T>
	void UndirectedGraph<T>::printDepthFirstTraversal(int index)
	{
		std::vector<bool> visited = std::vector<bool>(this->adjacencyList->size());
		this->printDepthFirstTraversal(index, visited);
		return;
	}
	template <class T>
	void UndirectedGraph<T>::printDepthFirstTraversal(int index, std::vector<bool>& visited)
	{
		if (this->adjacencyList->at(index).vertexs != nullptr)
		{
			std::cout << this->adjacencyList->at(index).vertexs->at(0).vertex <<
				std::endl;

			visited[index] = true;
			for (int i = 1; i < this->adjacencyList->at(index).vertexs->size(); i++)
			{
				int j = this->adjacencyList->at(index).vertexs->at(i).index;
				if (!visited[j])
				{
					printDepthFirstTraversal(j, visited);
				}
			}
		}
		return;
	}

	/*
	Description: Prints the adjacency list to the console.
	*/
	template <class T>
	void UndirectedGraph<T>::printUndirectedGraph()
	{
		int adjacencyListSize = this->adjacencyList->size();
		for (int i = 0; i < adjacencyListSize; i++)
		{
			if (this->adjacencyList->at(i).vertexs != nullptr)
			{
				if (i != 0)
				{
					std::cout << std::endl;
				}
				std::cout << "Vertex: " << this->adjacencyList->at(i).vertexs->at(0).vertex <<
					std::endl;
			
				int edgeListSize = this->adjacencyList->at(i).vertexs->size();
				for (int j = 1; j < edgeListSize; j++)
				{
					std::cout << "Edge: " << this->adjacencyList->at(i).vertexs->at(j).vertex <<
						std::endl;
				}
			}
		}
		return;
	}	

	/*
	Description: Returns true if the specified vertices 
	are connected as a edge; otherwise, false.
	*/
	template <class T>
	bool UndirectedGraph<T>::isConnected(T vertex1, T vertex2)
	{
		int index = this->indexOf(vertex1);
		if (index != -1)
		{
			int size = this->adjacencyList->at(index).vertexs->size();
			for (int i = 1; i < size; i++)
			{
				if (this->adjacencyList->at(index).vertexs->at(i).vertex
					== vertex2)
				{
					return true;
				}
			}
		}
		return false;
	}

	/*
	Description: Returns true if the adjacency list
	contains the specified vertex; otherwise, false.
	*/
	template <class T>
	bool UndirectedGraph<T>::contains(T vertex)
	{
		return (indexOf(vertex) != -1);
	}

	/*
	Description: Returns the total number of vertices the 
	adjacency list can hold.
	*/
	template <class T>
	int UndirectedGraph<T>::capacity()
	{
		return this->adjacencyList->size();
	}

	/*
	Description: Returns the number of vertices 
	contained in the adjacency list.
	*/
	template <class T>
	int UndirectedGraph<T>::count()
	{
		return this->adjacencyListCount;
	}

	/*
	Description: Returns the specified vertex's index
	from the adjacency list; otherwise, -1.
	*/
	template <class T>
	int UndirectedGraph<T>::indexOf(T vertex)
	{
		for (unsigned int i = 0; i < this->adjacencyList->size(); i++)
		{
			if (this->adjacencyList->at(i).vertexs != nullptr &&
				this->adjacencyList->at(i).vertexs->at(0).vertex == vertex)
			{
				return i;
			}
		}
		return -1;
	}

	/*
	Description: Returns a unassigned element's index
	from the adjacency list; otherwise, -1.
	*/
	template <class T>
	int UndirectedGraph<T>::indexOfUnassignedElement()
	{
		for (unsigned int i = 0; i < this->adjacencyList->size(); i++)
		{
			if (this->adjacencyList->at(i).vertexs == nullptr)
			{
				return i;
			}
		}
		return -1;
	}
}
#endif // ! undirectedGraphClass
