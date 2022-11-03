#pragma once
#include "MaxHeap.h"

template<typename T>
class HeapSort
{

public:

	void ascOrder(T* arr, int size)
	{
		MaxHeap<T> heap = MaxHeap<T>(arr, size);
		for (size_t i = size; i > 0; i--)
		{
			T val = heap.removeMax();
		}
	}
};