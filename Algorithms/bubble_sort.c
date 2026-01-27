#include <stdio.h>
#include <stdlib.h>

void sort(int *arr, int size){

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (*(arr + j) > *(arr + j + 1))
            {
                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
            
        }
        
    }
    


}


int main() {
    int dizi[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(dizi) / sizeof(dizi[0]); // Dizinin eleman sayısını bulma

    printf("Before: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", dizi[i]);
    }

    sort(dizi, n);

    printf("\n\nAfter (Bubble Sort): \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", dizi[i]);
    }
    printf("\n");
    
    return 0;
}