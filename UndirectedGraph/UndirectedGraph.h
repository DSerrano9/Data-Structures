#ifndef undirectedgraphClass
#define undirectedgraphClass
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
		UndirectedGraph(int size);
		~UndirectedGraph();
		void clear();
		void addVertex(T vertex);
		void removeVertex(T vertex);	
		void addEdge(T vertex1, T vertex2);	
		void removeEdge(T vertex1, T vertex2);
		void printDepthFirstTraversal(int index);
		void printGraph();		
	private:
		std::vector<AdjacencyNode<T>>* adjacencyList;
		void addVertex(int index, T vertex);
		void printDepthFirstTraversal(int index, std::vector<bool>& visited);		
		int indexOf(T vertex);
		int indexOfUnassignedElement();
	};

	/*
	Description: Allocates the Graph object and
	sets the adjacency list with a size of fifty.
	*/
	template <class T>
	UndirectedGraph<T>::UndirectedGraph()
	{
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(50);
	}

	/*
	Description: Allocates the Graph object and
	sets the adjacency list with a specified size.
	*/
	template <class T>
	UndirectedGraph<T>::UndirectedGraph(int size)
	{
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(size);
	}

	/*
	Description: Deallocates the Graph object.
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
	Description: Removes all vertexs from the
	adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::clear()
	{
		int size = this->adjacencyList->size();
		this->~Graph();
		this->adjacencyList = new std::vector<AdjacencyNode<T>>(size);
		return;
	}

	/*
	Description: Adds the specified vertex to the
	adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::addVertex(T vertex)
	{
		int index = this->indexOfUnassignedElement();
		if (index != -1)
		{
			this->addVertex(index, vertex);
			return;
		}
		throw std::exception("Adjacency List is full");
	}

	/*
	Description: Adds a vertex to the adjacency list
	at the specified index.
	*/
	template <class T>
	void UndirectedGraph<T>::addVertex(int index, T vertex)
	{
		this->adjacencyList->at(index).vertexs = new LinkedList<AdjacencyState<T>>();
		this->adjacencyList->at(index).vertexs->addToEnd(AdjacencyState<T>(index, vertex));
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
				this->adjacencyList->at(edgeIndex).vertexs->remove(removeThis, 1);
			}
			delete this->adjacencyList->at(index).vertexs;
			this->adjacencyList->at(index).vertexs = nullptr;
		}
		return;
	}

	/*
	Description: Adds a edge to the adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::addEdge(T vertex1, T vertex2)
	{
		for (unsigned int i = 0; i < this->adjacencyList->size(); i++)
		{
			if (this->adjacencyList->at(i).vertexs == nullptr)
			{
				this->addVertex(i, vertex1);
			}
			if (this->adjacencyList->at(i).vertexs->at(0).vertex == vertex1)
			{
				int index = this->indexOf(vertex2);
				if (index == -1)
				{
					index = this->indexOfUnassignedElement();
					if (index == -1)
					{
						break;
					}
					this->addVertex(index, vertex2);
				}
				this->adjacencyList->at(i).vertexs->addToEnd(
					this->adjacencyList->at(index).vertexs->get(0));
				this->adjacencyList->at(index).vertexs->addToEnd(
					this->adjacencyList->at(i).vertexs->get(0)); 
				return;
			}
		}
		throw std::exception("Adjacency List is full");
	}

	/*
	Description: Removes a edge from the adjacency list.
	*/
	template <class T>
	void UndirectedGraph<T>::removeEdge(T vertex1, T vertex2)
	{
		int v1Index = this->indexOf(vertex1);
		int v2Index = this->indexOf(vertex2);
		if (v1Index != -1 && v2Index != -1)
		{
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

	/*
	Description: Prints the adjacency list to the console
	using a depth first traversal algorithm.
	*/
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
	void UndirectedGraph<T>::printGraph()
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
	Description: Returns the next unassigned element's index
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
#endif // ! undirectedgraphClass
