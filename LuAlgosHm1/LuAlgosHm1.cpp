// LuAlgosHm1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MaxHeap.h"
#include <vector>
#include <tuple>
#include <algorithm>
#include "HeapSort.h"

MaxHeap<int> findMinElements(int* arr, int arrSize, int k);
int findMostPopularElement(int* arr, int arrSize);

typedef std::tuple<int, int> interval;

int getPossiblePairs(interval* dudes, int* chicks, int n);

int main()
{
	//int arr[] = { 7, 2, 3, 4, 9 };
	//int arrSize = sizeof(arr) / sizeof(arr[0]);
	//int k = 3;

	//MaxHeap<int> maxHeap = findMinElements(arr, arrSize, k);

	//std::cout << maxHeap.toString();

	//int arr1[] = { 3, 3, 3, 2, 1 };
	//int arr2[] = { 2, 3, 1, 1, 1 };
	//int arr3[] = { 2, 2, 3, 2, 1 };

	//int arrSize = sizeof(arr1) / sizeof(arr1[0]);

	//int mostPopular = findMostPopularElement(arr2, arrSize);
	//std::cout << mostPopular;	

	std::tuple<int, int> dudes[] = {
		std::make_tuple(1, 8),
		std::make_tuple(3, 5),
		std::make_tuple(7, 9),
		std::make_tuple(3, 7),
		std::make_tuple(5, 7)
	};

	int chicks[] = { 8, 6, 4, 1, 10 };
	int n = sizeof(dudes) / sizeof(dudes[0]);
	int pairs = getPossiblePairs(dudes, chicks, n);

	std::cout << pairs;
}

int getPossiblePairs(interval* dudes, int* chicks, int n) {

	int counter = 0;
	HeapSort<int> sort;
	sort.ascOrder(chicks, n);

	auto findBoundary = [](bool isLeftLimit, int limit, int* chicks, int n) {

		int midpoint = -1;
		int left = 0;
		int right = n - 1;

		while (left <= right)
		{
			midpoint = (right + left) / 2;
			int valueAtMidPoint = chicks[midpoint];

			if (limit < valueAtMidPoint)
			{
				right = midpoint - 1;
			}
			else if (limit > valueAtMidPoint)
			{
				left = midpoint + 1;
			}
			else
			{
				return midpoint;
			}
		}

		return isLeftLimit ? left : right;
	};

	for (size_t i = 0; i < n; i++)
	{
		int chickLowestIndex = findBoundary(true, std::get<0>(dudes[i]), chicks, n);
		int chickHighestIndex = findBoundary(false, std::get<1>(dudes[i]), chicks, n);

		counter += chickHighestIndex - chickLowestIndex + 1;
	}

	return counter;
}

MaxHeap<int> findMinElements(int* arr, int arrSize, int k) {

	MaxHeap<int> maxHeap = MaxHeap<int>(k);

	for (size_t i = 0; i < k; i++)
	{
		maxHeap.insert(arr[i]);
	}

	for (size_t i = k; i < arrSize; i++)
	{
		if (maxHeap.getMax() > arr[i])
		{
			int popedMaxVal = maxHeap.removeMax();
			maxHeap.insert(arr[i]);
		}
	}

	return maxHeap;
}

int findMostPopularElement(int* arr, int arrSize) {

	int index = 0;
	int counter = 1;

	for (size_t i = 1; i < arrSize; i++)
	{
		counter += (arr[index] == arr[i]) ? 1 : -1;

		if (counter == 0)
		{
			index = i;
			counter = 1;
		}
	}

	return arr[index];
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
