//This class will contain the implementation of different comparison sort algorithms

#pragma once
#include <vector>
class ComparisonSorts
{
public:
	ComparisonSorts();
	~ComparisonSorts();
	std::vector<int> bubbleSort(std::vector<int> A, int N);
	std::vector<int> insertionSort(std::vector<int> A, int N);
	std::vector<int> selectionSort(std::vector<int> A, int N);
	std::vector<int> quickSort(std::vector<int> A, int low, int high);
	std::vector<int> mergeSort(std::vector<int> A, int low, int high);

private:
	void swap(int& a, int& b);
	int posMin(std::vector<int> A, int i, int N);
	int partition(std::vector<int> &A, int low, int high);
	void merge(std::vector<int> &A, int low, int mid, int high);
};

