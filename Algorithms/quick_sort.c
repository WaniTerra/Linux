#include <stdio.h>
#include <stdlib.h>

int partition(int *arr, int low, int high)
{
    int pivot = *(arr + high);
    int border = low;

    for (int i = low; i < high; i++)
    {
        if (pivot > *(arr + i))
        {

            int temp = *(arr + i);
            *(arr + i) = *(arr + border);
            *(arr + border) = temp;

            border++;
        }
    }

    int temp = *(arr + high);
    *(arr + high) = *(arr + border);
    *(arr + border) = temp;

    return border;
}

void sort(int *arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int pi = partition(arr, low, high);

    sort(arr, low, pi - 1);

    sort(arr, pi + 1, high);
}

void print_arr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", *(arr + i));
    }
    printf("\n");
}

int main()
{
    int arr[] = {7, 2, 1, 8, 6, 3, 5};
    
    int n = sizeof(arr) / sizeof(arr[0]); 

    print_arr(arr, n); 
    
    sort(arr, 0, n - 1);
    
    print_arr(arr, n);

    return 0;
}