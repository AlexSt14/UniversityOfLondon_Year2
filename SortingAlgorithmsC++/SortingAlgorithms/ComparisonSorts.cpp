#include "ComparisonSorts.h"

ComparisonSorts::ComparisonSorts()
{
}
ComparisonSorts::~ComparisonSorts()
{
}
//Blubble sort implementation with a swap function
std::vector<int> ComparisonSorts::bubbleSort(std::vector<int> A, int N)
{
	bool swapped = true;
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < N - 1; ++i)
		{
			if (A[i] > A[i + 1])
			{
				swap(A[i], A[i + 1]);
				swapped = true;
			}
		}
		--N;
	}
	return A;
}
void ComparisonSorts::swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}
//Insertion sort implementation
std::vector<int> ComparisonSorts::insertionSort(std::vector<int> A, int N)
{
	for (int i = 1; i <= N - 1; ++i)
	{
		int provisory = A[i];
		int j = i - 1;
		while (j >= 0 && provisory < A[j])
		{
			A[j + 1] = A[j];
			--j;
		}
		A[j + 1] = provisory;
	}
	return A;
}
//Selection sort implementation
std::vector<int> ComparisonSorts::selectionSort(std::vector<int> A, int N)
{
	for (int i = 0; i < N - 1; ++i)
	{
		int min = posMin(A, i, N - 1);
		swap(A[i], A[min]);
	}
	return A;
}
int ComparisonSorts::posMin(std::vector<int> A, int j, int N)
{
	int min = j;
	for (int i = j; i <= N; ++i)
	{
		if (A[i] < A[min])
		{
			min = i;
		}
	}
	return min;
}
//Quick sort implementation
std::vector<int> ComparisonSorts::quickSort(std::vector<int> A, int low, int high)
{
	if (low < high)
	{
		int pivot = partition(A, low, high);
		A = quickSort(A, low, pivot - 1);
		A = quickSort(A, pivot + 1, high);
	}
	return A;
}
int ComparisonSorts::partition(std::vector<int> &A, int low, int high)
{
	int pivot = A[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; ++j)
	{
		if (A[j] < pivot)
		{
			++i;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[high]);
	return i + 1;
}
//Merge sort implementation
std::vector<int> ComparisonSorts::mergeSort(std::vector<int> A, int low, int high)
{
	if (low < high)
	{
		int mid = (low + high) / 2;
		A = mergeSort(A, low, mid);
		A = mergeSort(A, mid + 1, high);
		merge(A, low, mid, high);
	}
	return A;
}
void ComparisonSorts::merge(std::vector<int>& A, int low, int mid, int high)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;
	std::vector<int> L(n1 + 1);
	std::vector<int> R(n2 + 1);
	for (int i = 0; i < n1; ++i)
	{
		L[i] = A[low + i];
	}
	for (int j = 0; j < n2; ++j)
	{
		R[j] = A[mid + j + 1];
	}
	L[n1] = INT_MAX;
	R[n2] = INT_MAX;
	int i = 0;
	int j = 0;
	for (int k = low; k <= high; ++k)
	{
		if (L[i] <= R[j])
		{
			A[k] = L[i];
			++i;
		}
		else
		{
			A[k] = R[j];
			++j;
		}
	}
}