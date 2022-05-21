#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void fillRandom(int* arr, int len, int border) { 
    for (int i = 0; i < len; ++i) {
        *(arr + i) = rand() % border;
    }
}

void printIntArray(int* array, int size, int offset) {
    char format[7];
    sprintf(format, "%%%dd", offset);
    for (int i = 0; i < size; ++i) {
        printf(format, array[i]);
        if (i != size - 1)
            printf(",");
    }
    printf("\n");
}

int qs(int* arr, int first, int last) {
    int i = first;
    int j = last;

    int x = arr[(first + last) / 2];

    do {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;
         if (i <= j) {
             swap(&arr[i], &arr[j]);
             i++;
             j--;
         }
    } while (i <= j);
    if (i < last) qs(arr, i, last);
    if (first < j) qs(arr, first, j);
}

void thickSplit(int* arr, int l, int r) {
    int x = arr[r];
    if (r <= l) return;

    int i = l;
    int j = r - 1;
    int p = l - 1;
    int q = r;

    while (i <= j) {
        while (arr[i] < x) i++;
        while (arr[j] > x) j--;

        if (i >= j) break;
        swap(&arr[i], &arr[j]);

        if (arr[i] == x) {
            p++;
            swap(&arr[i], &arr[j]);
            i++;
        }
        if (arr[j] == x) {
            swap(&arr[--q], &arr[j--]);
        }
    }
    swap(&arr[i], &arr[j]);
    j = i - 1;
    i++;
    for (int k = l; k <= p; ++k, --j) {
        swap(&arr[k], &arr[i]);
    }
    for (int k = r - 1; k >= q; ++k, ++i) {
        swap(&arr[k], &arr[i]);
    }
    thickSplit(arr, l, j);
    thickSplit(arr, i, r);

}

void bucketSort(int* arr, int len) {
    const int max = len;
    const int b = 10;

    int buckets[b][max + 1];
    for (int i = 0; i < b; ++i) {
        buckets[i][max] = 0;
    }
    for (int digit = 1; digit < 1000000000; digit*=10) {
        for (int i = 0; i < max; ++i) {
            int d = (arr[i] / digit) % b;
            buckets[d][buckets[d][max]++] = arr[i];
        }
        int idx = 0;
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < buckets[i][max]; ++j) {
                arr[idx++] = buckets[i][j];
            }
            buckets[i][max] = 0;
        }
    }
}

void sortShells(int* arr, int len) {
    int i;
    int j;
    int step;
    int temp;

    for (step = len / 2; step > 0; step /= 2) {
        for (i = step; i < len; ++i) {
        temp = arr[i];
        for (j = i; j >= step; j -= step) {
            if (temp < arr[j - step]) {
                arr[j] = arr[j - step];
            } else {
                break;
            }
        }
    }
}
}

int ultraqs(int* arr, int len) {
    if (len > 10) {
        sortShells(arr, len);
        return arr[len];
    } else {
    // Необходимо найти способ определения медианного значения
        qs(arr, 0, len);
        return arr[len];
    }
}

int main() {
    
    const int SIZE = 12;
    int arr[SIZE];
    fillRandom(arr, SIZE, 30);
    printIntArray(arr, SIZE, 3);
    printf("\n");
    ultraqs(arr, SIZE);
    printIntArray(arr, SIZE, 3);
    return 0;
}