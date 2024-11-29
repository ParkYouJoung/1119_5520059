#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100
int sorted[SIZE];
int comparisonCount = 0;
int moveCount = 0;

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int array[], int size, int rounds, int isFirst) {
    if (rounds % 10 == 0 && isFirst == 0) { // 10번에 한번만 출력
        for (int i = 0; i < 10; i++) // 0 ~ 9 값
            printf("%3d ", array[i]);
        printf("| ");
        for (int i = size / 2 - 1; i < size / 2 + 10; i++) // 중앙-1 ~ 중앙+10
            printf("%3d ", array[i]);
        printf("\n");
    }
}

void merge(int list[], int left, int mid, int right, int rounds) {
    int i = left, j = mid + 1, k = left;

    // 분할 정렬 리스트 합병
    while (i <= mid && j <= right) {
        comparisonCount++;
        if (list[i] <= list[j]) {
            sorted[k++] = list[i++];
        }
        else {
            sorted[k++] = list[j++];
        }
        moveCount++;  // 이동
    }

    // 남은 데이터 복사
    while (i <= mid) {
        sorted[k++] = list[i++];
        moveCount++;  // 이동 
    }
    while (j <= right) {
        sorted[k++] = list[j++];
        moveCount++;  // 이동 
    }

    // 정렬 데이터 원본 배열로 복사
    for (i = left; i <= right; i++) {
        list[i] = sorted[i];
        moveCount++;  // 이동 발생
    }

    // 배열 상태 출력
    printArray(list, SIZE, rounds, 0);
}

void doMergeSort(int list[], int left, int right, int rounds) {
    if (left < right) {
        int mid = (left + right) / 2;
        doMergeSort(list, left, mid, rounds + 1);
        doMergeSort(list, mid + 1, right, rounds + 1);
        merge(list, left, mid, right, rounds + 1);
    }
}

int main() {
    int array[SIZE];
    int totalComparisons = 0, totalMoves = 0;

    srand(time(0));

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;  // 비교 횟수 초기화
        moveCount = 0;        // 이동 횟수 초기화

        if (i == 0) {
            printf("Merge Sort Run\n");
            doMergeSort(array, 0, SIZE - 1, 0);

            printf("\nResult: ");
            for (int j = 0; j < SIZE; j++) {
                printf("%3d ", array[j]);
            }
            printf("\n\n");
        }
        else {
            doMergeSort(array, 0, SIZE - 1, -1);  // 출력 없이 실행
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}
