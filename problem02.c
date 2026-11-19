
#include <stdio.h>
#include <stdlib.h>

void printArray(int array[], int size) {
    for (int index = 0; index < size; ++index) {
        printf("%d", array[index]);
        if (index + 1 == size) printf("\n");
        else printf(" ");
    }
}

void merge(int array[], int temp[], int left, int middle, int right, long long *comparisons) {
    int leftPartitionIndex = left;
    int rightPartitionIndex = middle + 1;
    int tempIndex = left;

    while (leftPartitionIndex <= middle && rightPartitionIndex <= right) {
        ++(*comparisons);

        if (array[leftPartitionIndex] <= array[rightPartitionIndex]) {
            temp[tempIndex++] = array[leftPartitionIndex++];
        } else {
            temp[tempIndex++] = array[rightPartitionIndex++];
        }
    }

    while (leftPartitionIndex <= middle) temp[tempIndex++] = array[leftPartitionIndex++];

    while (rightPartitionIndex <= right) temp[tempIndex++] = array[rightPartitionIndex++];

    for (int index = left; index <= right; ++index) {
        array[index] = temp[index];
    }
}

void MergeSort(int array[], int temp[], int left, int right, long long *comparisons) {
    if (left >= right) return;

    int middle = left + (right - left) / 2;

    MergeSort(array, temp, left, middle, comparisons);
    MergeSort(array, temp, middle + 1, right, comparisons);
    merge(array, temp, left, middle, right, comparisons);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int array[], int left, int right, long long *comparisons) {
    int pivot = array[right];
    int smallerIndex = left - 1;

    for (int scanIndex = left; scanIndex < right; ++scanIndex) {
        ++(*comparisons);

        if (array[scanIndex] < pivot) {
            ++smallerIndex;
            swap(&array[smallerIndex], &array[scanIndex]);
        }
    }

    swap(&array[smallerIndex + 1], &array[right]);

    return smallerIndex + 1;
}

void QuickSort(int array[], int left, int right, long long *comparisons) {
    if (left >= right) return;

    int pivotIndex = partition(array, left, right, comparisons);

    QuickSort(array, left, pivotIndex - 1, comparisons);
    QuickSort(array, pivotIndex + 1, right, comparisons);
}

void mergeSortedArrays(int array[], int newArray[], int updated[], int n, int m) {
    int firstIndex = 0;
    int secondIndex = 0;
    int updatedIndex = 0;

    while (firstIndex < n && secondIndex < m) {
        if (array[firstIndex] <= newArray[secondIndex]) {
            updated[updatedIndex++] = array[firstIndex++];
        } else {
            updated[updatedIndex++] = newArray[secondIndex++];
        }
    }

    while (firstIndex < n)  updated[updatedIndex++] = array[firstIndex++];

    while (secondIndex < m) updated[updatedIndex++] = newArray[secondIndex++];
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) return 1;

    int n, m;

    if (fscanf(file, "%d %d", &n, &m) != 2 || n < 0 || m < 0) {
        fclose(file);
        return 1;
    }

    int *mergeArray = malloc((n > 0 ? n : 1) * sizeof(int));
    int *quickArray = malloc((n > 0 ? n : 1) * sizeof(int));
    int *temp = malloc((n > 0 ? n : 1) * sizeof(int));
    int *newArray = malloc((m > 0 ? m : 1) * sizeof(int));
    int *updated = malloc(((size_t)n + m > 0 ? (size_t)n + m : 1) * sizeof(int));

    if (mergeArray == NULL || quickArray == NULL || temp == NULL ||
        newArray == NULL || updated == NULL) {
        fclose(file);
        free(mergeArray);
        free(quickArray);
        free(temp);
        free(newArray);
        free(updated);
        return 1;
    }

    for (int index = 0; index < n; ++index) {
        if (fscanf(file, "%d", &mergeArray[index]) != 1) {
            fclose(file);
            return 1;
        }
        quickArray[index] = mergeArray[index];
    }

    for (int index = 0; index < m; ++index) {
        if (fscanf(file, "%d", &newArray[index]) != 1) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);

    long long mergeComparisons = 0;
    long long quickComparisons = 0;

    MergeSort(mergeArray, temp, 0, n - 1, &mergeComparisons);
    QuickSort(quickArray, 0, n - 1, &quickComparisons);

    printf("Merge Sort: ");
    printArray(mergeArray, n);

    printf("Quick Sort: ");
    printArray(quickArray, n);

    printf("Merge Comparisons: %lld\n", mergeComparisons);
    printf("Quick Comparisons: %lld\n", quickComparisons);

    mergeSortedArrays(mergeArray, newArray, updated, n, m);

    printf("Updated Array: ");
    printArray(updated, n + m);

    free(mergeArray);
    free(quickArray);
    free(temp);
    free(newArray);
    free(updated);

    return 0;
}
