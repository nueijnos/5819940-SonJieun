#include <stdio.h>
#include <stdlib.h>
//#define MAX_ELEMENT 100
//이번 문제는 heap 구조체가 불필요할 것 같아 제외시켰습니다.
/*
typedef struct HeapType{
    int heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType* create_heap() {
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    h->heap_size = 0;
    return h;
}
*/

//교환 함수
void swap(int inputData[], int a, int b) {
    int temp = inputData[a];
    inputData[a] = inputData[b];
    inputData[b] = temp;
}

//최대 힙 정렬 함수(i를 기준으로 최대힙 정렬)
void resortHeap(int inputData[], int n, int i) {
    int largest = i; //i(현재 노드)
    int left = 2 * i + 1; //왼쪽 자식 인덱스
    int right = 2 * i + 2; //오른쪽 자식 인덱스

    if (left < n && inputData[left] > inputData[largest]) { //왼쪽 자식이 더 크다면
        largest = left;
    }
    if (right < n && inputData[right] > inputData[largest]) { //오른쪽 자식이 더 크다면
        largest = right;
    }
    if (largest != i) { //루트가 가장 큰 값이 아닌 경우
        swap(inputData, i, largest); //교환 후
        resortHeap(inputData, n, largest); //다시 힙 정렬
    }
}

//최대 힙으로 만드는 빌드 함수
void buildMaxHeap(int inputData[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        resortHeap(inputData, n, i); //각 노드에 최대 힙 정렬
    }
}

//힙 정렬 함수
void BuildMaxHeapAndSort(int inputData[], int n) {
    for (int i = 1; i <= n; i++) {
        buildMaxHeap(inputData, i);
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }

    // 하나씩 힙에서 루트(최대값)를 제거하고 정렬
    for (int i = n - 1; i > 0; i--) {
        swap(inputData, 0, i); //루트 노드와 마지막 노드를 교환
        resortHeap(inputData, i, 0); 

        // 힙 재정렬 후 상태 출력
        for (int j = 0; j < i; j++) {
            printf("%d ", inputData[j]);
        }
        printf("\n");
    }
}

int main(void) {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    //힙 정렬 실행
    printf("<Sort>\n");
    BuildMaxHeapAndSort(inputData, size);

    // 정렬된 결과 출력(최종으로 정렬된 결과)
    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
