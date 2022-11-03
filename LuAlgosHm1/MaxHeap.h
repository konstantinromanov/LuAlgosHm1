#pragma once

#include <string>
#include <sstream>

template<typename T>
class MaxHeap
{

private:

	int m_capacity{};
	T* m_heap;
	int m_nextPosition{ 0 };

	int getLeftPosition(int position)
	{
		return 2 * position + 1;
	}

	int getRightPosition(int position)
	{
		return 2 * position + 2;
	}

	int getParentPosition(int position)
	{
		return (position - 1) / 2;
	}

	void moveUp(int position)
	{
		int parentPosition = getParentPosition(position);

		while (m_heap[parentPosition] < m_heap[position])
		{
			swapValues(parentPosition, position);
			position = parentPosition;
			parentPosition = getParentPosition(parentPosition);
		}
	}

	void swapValues(int a, int b)
	{
		T temp = m_heap[a];
		m_heap[a] = m_heap[b];
		m_heap[b] = temp;
	}

	bool positionOfMaxChild(int position, int& childPosition)
	{
		bool result = true;
		int leftChildPosition = getLeftPosition(position);
		int rightChildPosition = getRightPosition(position);

		bool leftIsPossible = leftChildPosition < size() && m_heap[leftChildPosition] > m_heap[position];
		bool rightIsPossible = rightChildPosition < size() && m_heap[rightChildPosition] > m_heap[position];

		if (leftIsPossible && rightIsPossible)
		{
			childPosition = m_heap[leftChildPosition] > m_heap[rightChildPosition] ? leftChildPosition : rightChildPosition;
		}
		else if (leftIsPossible)
		{
			childPosition = leftChildPosition;
		}
		else if (rightIsPossible)
		{
			childPosition = rightChildPosition;
		}
		else
		{
			result = false;
		}

		return result;
	}

	void moveDown(int position)
	{
		int childPosition;

		while (positionOfMaxChild(position, childPosition))
		{
			swapValues(childPosition, position);
			position = childPosition;
		}
	}

	void buildHeap(T* arr, int arrSize, bool inPlace = false)
	{
		if (inPlace)
		{
			for (size_t i = 0; i < arrSize; i++)
			{
				processNode(arr[i]);
			}
		}
		else
		{
			for (size_t i = 0; i < arrSize; i++)
			{
				insert(arr[i]);
			}
		}
	}

	void processNode(T data)
	{
		if (m_nextPosition > 0 && m_heap[getParentPosition(m_nextPosition)] < data)
		{
			moveUp(m_nextPosition);
		}

		m_nextPosition++;
	}

public:

	MaxHeap(T* arr, int arrSize)
	{
		m_capacity = arrSize;
		m_heap = arr;
		buildHeap(arr, arrSize, true);
	}

	MaxHeap(T* arr, int arrSize, int capacity)
	{
		if (capacity < arrSize)
		{
			throw std::invalid_argument("Capacity must be equal or more than Array Size.");
		}

		m_capacity = capacity;

		if (arrSize == capacity)
		{
			m_heap = arr;
			buildHeap(arr, arrSize, true);
		}
		else
		{
			m_heap = new T[m_capacity];
			buildHeap(arr, arrSize);
		}
	}

	MaxHeap(int capacity) {
		m_capacity = capacity;
		m_heap = new T[m_capacity];
	}

	T& operator[](int index) {

		if (index < 0 || index > size() - 1)
		{
			throw std::invalid_argument("Index is outside of range");
		}

		return m_heap[index];
	}

	void insert(T data)
	{
		if (m_nextPosition == m_capacity)
		{
			throw std::out_of_range("Heap is full");
		}

		m_heap[m_nextPosition] = data;
		processNode(data);
	}

	void remove(T data)
	{
		T lastData = m_heap[m_nextPosition - 1];
		int deletedPosition{};

		for (size_t i = 0; i < m_nextPosition; i++)
		{
			if (m_heap[i] == data)
			{
				m_heap[i] = lastData;
				deletedPosition = i;
				m_nextPosition--;

				break;
			}
		}

		if (deletedPosition < m_nextPosition / 2) // if not leaf nodes, then proceed with check.
		{
			int parentPosition = getParentPosition(deletedPosition);

			if (m_heap[parentPosition] < m_heap[deletedPosition])
			{
				moveUp(deletedPosition);
			}
			else
			{
				moveDown(deletedPosition);
			}
		}
	}

	T getMax()
	{
		if (size() == 0)
		{
			throw std::out_of_range("Heap is empty");
		}

		return m_heap[0];
	}

	T removeMax()
	{
		if (size() == 0)
		{
			throw std::out_of_range("Heap is empty");
		}

		T maxValue = m_heap[0];
		swapValues(0, size() - 1);
		m_nextPosition--;
		moveDown(0);

		return maxValue;
	}

	std::string toString()
	{
		std::stringstream ss("");
		std::string result;

		for (size_t i = 0; i < m_nextPosition; i++)
		{
			ss << m_heap[i] << ' ';
		}

		result = ss.str();

		if (result != "")
		{
			result.pop_back();
		}

		return result;
	};

	int size()
	{
		return m_nextPosition;
	}
};

