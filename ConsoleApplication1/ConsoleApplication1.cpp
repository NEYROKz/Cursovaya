#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace std;

const int N = 10000;

void best_case(int* array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = i + 1;
    }
}
void worst_case(int* array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = n - i;
    }

}
void average_case(int* array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = rand() % (n * 10);
    }
}
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
unsigned long long bubble_sort_opimized(int* a, int n)
{
    unsigned long long op_counter = 0;
    bool swapped = false;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            op_counter++;
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
        {
            break;
        }
    }
    return op_counter;
}
unsigned long long comb_sort(int* a, int n)
{
    unsigned long long op_counter = 0;
    int gap = n;
    bool swapped = true;

    while (gap > 1 || swapped)
    {
        gap = (gap * 10) / 13;
        if (gap < 1)
        {
            gap = 1;
        }
        swapped = false;
        for (int i = 0; i < n - gap; i++)
        {
            op_counter++;
            if (a[i] > a[i + gap])
            {
                swap(a[i], a[i + gap]);
                swapped = true;
            }
        }
    }
    return op_counter;
}
void copy_array(int* arr1, int* arr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        arr1[i] = arr2[i];
    }
}

void is_sorted(int* arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
            throw runtime_error("Array is not sorted!");
    }
}

void add_to_file(unsigned long long* sums, int n, string type, ofstream&
    file)
{
    file << type << ";" << n << ";";
    for (int k = 0; k < 3; k++)
        file << sums[k] << ";";
    file << "\n";
}
int main()
{
    ofstream file("results.csv");
    file << "type;size;bubble;optimized_bubble;comb\n";
    int array_lengths[] = { 4, 8, 16, 32, 64, 128, 256, 512, 1024 };
    for (int i = 0; i < 9; i++) 
    {
        int n = array_lengths[i];
        int* arr = new int[n]; 
        int* arr2 = new int[n]; 
        int* arr3 = new int[n];

        unsigned long long sums[3] = { 0 }; 

        for (int j = 0; j < N; j++)
        {
            average_case(arr, n);
            copy_array(arr2, arr, n);
            copy_array(arr3, arr, n);

            sums[0] += (double)bubble_sort(arr, n);
            sums[1] += (double)bubble_sort_opimized(arr2, n);
            sums[2] += (double)comb_sort(arr3, n);

            is_sorted(arr, n);
            is_sorted(arr2, n);
            is_sorted(arr3, n);
        }
        sums[0] /= N;
        sums[1] /= N;
        sums[2] /= N;
        add_to_file(sums, n, "average", file); 

        best_case(arr, n);
        copy_array(arr2, arr, n);
        copy_array(arr3, arr, n);
        sums[0] = (double)bubble_sort(arr, n);
        sums[1] = (double)bubble_sort_opimized(arr2, n);
        sums[2] = (double)comb_sort(arr3, n);
        is_sorted(arr, n);
        is_sorted(arr2, n);
        is_sorted(arr3, n);
        add_to_file(sums, n, "best", file); 

        worst_case(arr, n);
        copy_array(arr2, arr, n);
        copy_array(arr3, arr, n);
        sums[0] = (double)bubble_sort(arr, n);
        sums[1] = (double)bubble_sort_opimized(arr2, n);
        sums[2] = (double)comb_sort(arr3, n);
        is_sorted(arr, n);
        is_sorted(arr2, n);
        is_sorted(arr3, n);
        add_to_file(sums, n, "worst", file); 

        delete[] arr;
        delete[] arr2;
        delete[] arr3;
    }
    file.close();

    cout << "File was created";
    return 0;
}