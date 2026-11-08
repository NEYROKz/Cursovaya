#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <time.h>
#include <stdexcept>
#include <fstream>
#include <utility>
#include <ctime>
#include <cstdlib>

using namespace std;

//Пузырьковая сортировка
unsigned long long bubble_sort(int* a, int n)
{
	unsigned long long op_counter = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			op_counter++;
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
	return op_counter;
}



//Функция разделения массива (метод Хоара)
void quickSortHelper(int arr[], int left, int right) 
{
	int i = left;
	int j = right;

	// Выбор опорного элемента (середина массива)

	int pivot = arr[left + (right - left) / 2];

	// Разделение массива на две части
	while (i <= j)
	{
		while (arr[i] < pivot) i++;
		while (arr[j] > pivot) j--;
		if (i <= j) 
		{
			swap(arr[i], arr[j]);
			i++; j--;
		}
	}
	// Рекурсивные вызовы для левой и правой частей
	if (left < j) quickSortHelper(arr, left, j);
	if (i < right) quickSortHelper(arr, i, right);
}

//Главная функция быстрой сортировки
void quickSort(int arr[], int n)
{
	if (n > 1) quickSortHelper(arr, 0, n - 1);
}