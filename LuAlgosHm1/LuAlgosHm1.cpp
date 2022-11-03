// LuAlgosHm1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MaxHeap.h"
#include <vector>
#include <tuple>
#include <algorithm>
MaxHeap<int> findMinElements(int* arr, int arrSize, int k);
int findMostPopularElement(int* arr, int arrSize);


typedef std::tuple<int, int> interval;
int getPossiblePairs(std::vector<interval> dudes, std::vector<int> chicks);

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

	//int arr[] = { 7, 2, 3, 4, 9 };
	//std::tuple<int, int> arr33[3]{};
	std::vector<interval> dudes;

	interval t1 = std::make_tuple(1, 8);
	interval t2 = std::make_tuple(3, 5);
	interval t3 = std::make_tuple(7, 9);
	interval t4 = std::make_tuple(3, 7);
	interval t5 = std::make_tuple(5, 7);

	dudes.push_back(t1);
	dudes.push_back(t2);
	dudes.push_back(t3);
	dudes.push_back(t4);
	dudes.push_back(t5);

	std::vector<int> chicks;

	chicks.push_back(8);
	chicks.push_back(6);
	chicks.push_back(4);
	chicks.push_back(1);
	chicks.push_back(10);

	//std::cout << std::get<0>(dudes[0]);
	//std::cout << std::get<1>(dudes[0]);

	int pairs = getPossiblePairs(dudes, chicks);

	std::cout << pairs;
}

int getPossiblePairs(std::vector<interval> dudes, std::vector<int> chicks) {

	int counter = 0;
	// TODO. sort chicks
	std::sort(chicks.begin(), chicks.end());

	auto findBoundary = [](bool isLeftLimit, int limit, std::vector<int> chicks) {
		
		int midpoint = -1;
		int left = 0;
		int right = chicks.size() - 1;

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

	for (size_t i = 0; i < dudes.size(); i++)
	{		
		int midpoint = -1;
		int left = 0;
		int right = chicks.size() - 1;

		int chickLowestIndex = findBoundary(true, std::get<0>(dudes[i]), chicks);
		int chickHighestIndex = findBoundary(false, std::get<1>(dudes[i]), chicks);
		
		counter += chickHighestIndex - chickLowestIndex + 1;
		
		std::cout << "chickLowestIndex: " << chickLowestIndex << std::endl;
		std::cout << "chickHighestIndex: " << chickHighestIndex << std::endl;
		std::cout << "counter: " << counter << std::endl;
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
