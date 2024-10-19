#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100 //요소 최대 크기 정의

typedef struct Node { //각 빈도수와 트리 구조를 저장하는 구조체
    int frequency;
    char character;
    struct Node* left, * right;
} Node;

typedef struct { //힙에 들어갈 트리와 빈도수
    Node* ptree;
    int key;
} element;

typedef struct { //최소 힙 구조체
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

Node* create_heap(char character, int frequency) { //새로운 노드 생성 함수 
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) exit(1);
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int is_leaf(Node* node) { //리프 노드 함수
    return !(node->left) && !(node->right); // 왼쪽, 오른쪽 자식이 모두 없는 경우
}

void swap(element* a, element* b) { //교환 함수
    element temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(HeapType* h, int index) { //최소 힙 구조 함수
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->heap_size && h->heap[left].key < h->heap[smallest].key)
        smallest = left;
    if (right < h->heap_size && h->heap[right].key < h->heap[smallest].key)
        smallest = right;

    if (smallest != index) {
        swap(&h->heap[smallest], &h->heap[index]);
        min_heapify(h, smallest);
    }
}

Node* extract_min_heap(HeapType* h) { //힙에서 가장 작은 빈도수를 가진 노드를 뽑아주는 함수
    Node* temp = h->heap[0].ptree;
    h->heap[0] = h->heap[h->heap_size - 1];
    h->heap_size--;
    min_heapify(h, 0);
    return temp;
}

void print_heap(HeapType* h) { //힙 출력 함수
    for (int i = 0; i < h->heap_size; i++) {
        printf("%d ", h->heap[i].key);
    }
    printf("\n");
}

void insert_min_heap(HeapType* h, Node* item) { //새로운 노드 추가 함수
    h->heap[h->heap_size].ptree = item;
    h->heap[h->heap_size].key = item->frequency;
    h->heap_size++;

    int i = h->heap_size - 1;
    while (i && h->heap[i].key < h->heap[(i - 1) / 2].key) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    print_heap(h);
}

HeapType* create_min_heap() { //최소 힙 생성 함수
    HeapType* h = (HeapType*)malloc(sizeof(HeapType));
    if (h == NULL) exit(1);
    h->heap_size = 0;
    return h;
}

HeapType* build_min_heap(char characters[], int frequencies[], int size) { //최소 힙 빌드 함수
    HeapType* h = create_min_heap();
    for (int i = 0; i < size; i++) {
        insert_min_heap(h, create_heap(characters[i], frequencies[i]));
    }
    return h;
}

Node* buildHuffmanTree(char characters[], int frequencies[], int size) { //허프만 트리 함수
    Node* left, * right, * top;
    HeapType* h = build_min_heap(characters, frequencies, size);

    while (h->heap_size > 1) { //힙에 하나만 남을 때까지 계속 반복
        left = extract_min_heap(h);
        right = extract_min_heap(h);
        top = create_heap('$', left->frequency + right->frequency); //두 노드의 빈도수를 합친 새로운 노드 만듦
        top->left = left;
        top->right = right;

        printf("///%d + %d -> %d\n", left->frequency, right->frequency, top->frequency); //두 노드를 병합한 빈도수 결과 출력
        insert_min_heap(h, top); //새 노드를 힙에 삽입
    }

    return extract_min_heap(h);
}

void printCodes(Node* root, int codes[], int top) { //허프만 코드 출력 함수
    if (root->left) { //왼쪽 자식 노드 1 할당 
        codes[top] = 1;
        printCodes(root->left, codes, top + 1);
    }
    if (root->right) { //오른쪽 자식 노드 0 할당
        codes[top] = 0;
        printCodes(root->right, codes, top + 1);
    }
    if (is_leaf(root)) { //리프 노드에 도달할 시, 허프만 코드 출력
        printf("%c: ", root->character);
        for (int i = 0; i < top; i++)
            printf("%d", codes[i]);
        printf("\n");
    }
}

void GenerateHuffmanCodes(char characters[], int frequencies[], int size) { //허프만 트리 생성 함수(주어진 문자와 빈도수로)
    Node* root = buildHuffmanTree(characters, frequencies, size);
    int arr[MAX_ELEMENT];
    int top = 0;
    printCodes(root, arr, top);
}

int main() {
    char characters[] = { 'a', 'e', 'i', 'o', 'u', 's', 't' };
    int frequencies[] = { 10, 15, 12, 3, 4, 13, 1 };
    int size = sizeof(characters) / sizeof(characters[0]);
    GenerateHuffmanCodes(characters, frequencies, size);
    return 0;
}