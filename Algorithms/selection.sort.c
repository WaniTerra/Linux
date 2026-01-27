#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int size)
{
    int min_idx;

    for (int i = 0; i < size - 1; i++)
    {

        min_idx = i;

        for (int j = i + 1; j < size; j++)
        {
            if (*(arr + j) < *(arr + min_idx))
            {
                min_idx = j;
            }
        }

        if (min_idx != i)
        {
            int temp = *(arr + i);
            *(arr + i) = *(arr + min_idx);
            *(arr + min_idx) = temp;
        }
    }
}

int main()
{

    int dizi[] = {64, 25, 12, 22, 11, 1, 99, 34};

    int n = sizeof(dizi) / sizeof(dizi[0]);

    printf("Before: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dizi[i]);
    }
    printf("\n");

    selectionSort(dizi, n);

    printf("Sorted:    ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", dizi[i]);
    }

    return 0;
}