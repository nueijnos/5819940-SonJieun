#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100   
#define INF 1000L   /* 무한대 값 (연결이 없는 경우) */

typedef struct GraphNode {
    int vertex, weight; //정점, 가중치
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType { 
    int n;	// 간선의 개수
    struct GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef struct { //힙 노드 구조체
    int vertex, distance; //정점, 그에 대한 거리
} HeapNode;

typedef struct { //최소 힙 구조체
    HeapNode heap[MAX_VERTICES]; //힙 배열
    int heap_size; 
} MinHeap;

int distance[MAX_VERTICES]; /* 시작 정점으로부터의 최단 경로 거리 */
int found[MAX_VERTICES];    /* 방문한 정점 표시 */
int found_index = 0;
int found_order[MAX_VERTICES];

void graph_init(GraphType* g) { //그래프 초기화 함수
    g->n = 10;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

void insert_edge(GraphType* g, int start, int end, int w) { //간선 삽입 연산
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->vertex = end;
    newNode->weight = w;
    newNode->next = g->adj_list[start];
    g->adj_list[start] = newNode;
}

void init_minheap(MinHeap* h) { //minheap 초기화
    h->heap_size = 0;
}

void swap(HeapNode* a, HeapNode* b) { //교환 함수
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* h, int index) { //최소 힙 heapify(재정렬) 함수
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->heap_size && h->heap[left].distance < h->heap[smallest].distance) //왼쪽 자식 값이 더 작다면
        smallest = left;
    if (right < h->heap_size && h->heap[right].distance < h->heap[smallest].distance) //오른쪽 자식 값이 더 작다면
        smallest = right;

    if (smallest != index) { //부모 노드 값과 자식 노드 값이 다르면
        swap(&h->heap[index], &h->heap[smallest]); //교환 후
        min_heapify(h, smallest); //힙 재정렬
    }
}

void insert_minheap(MinHeap* h, int vertex, int distance) { //minheap 간선 삽입 함수
    int i = h->heap_size++;
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;

    while (i && h->heap[i].distance < h->heap[(i - 1) / 2].distance) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode delete_minheap(MinHeap* h) { //minheap 최소 간선 제거 함수
    HeapNode min_edge = h->heap[0];
    h->heap[0] = h->heap[--h->heap_size];
    min_heapify(h, 0); //최소 힙 구조 유지
    return min_edge;
}

void print_dijkstra(int n) {  //다익스트라 알고리즘의 현재까지의 distance 정보와 found를 출력하는 함수
    printf("Distance: ");
    for (int j = 1; j <= n; j++) {
        if (distance[j] == INF)
            printf("* ");
        else
            printf("%d ", distance[j]); //현재까지의 distance 정보 출력
    }
    printf("\nFound:    ");
    for (int j = 1; j <= n; j++) { 
        printf("%d ", found[j]); //found 출력
    }
    printf("\n\n");
}

/* Dijkstra 알고리즘 함수 */
void dijkstra(GraphType* g, int start) {
    MinHeap h;
    init_minheap(&h);

    for (int i = 0; i < MAX_VERTICES; i++) { //초기화
        distance[i] = INF;
        found[i] = 0;
    }
    distance[start] = 0;
    insert_minheap(&h, start, 0);

    while (h.heap_size > 0) { //힙이 비어있지 않는 동안 계속 반복
        HeapNode u = delete_minheap(&h); //최소 거리 정점 제거

        if (found[u.vertex]) continue; //이미 방문했던 정점이면 건너 뛰고
        found[u.vertex] = 1; //정점을 방문 처리
        found_order[found_index++] = u.vertex;

        print_dijkstra(g->n); //현재 상태 출력

        for (GraphNode* v = g->adj_list[u.vertex]; v != NULL; v = v->next) { //인접 정점 탐색
            if (!found[v->vertex] && distance[u.vertex] + v->weight < distance[v->vertex]) { //방문하지 않거나 새로운 경로가 더 짧으면 거리 업데이트
                distance[v->vertex] = distance[u.vertex] + v->weight; //새로운 거리를 업데이트 하고 
                insert_minheap(&h, v->vertex, distance[v->vertex]); //힙에 삽입
            }
        }
    }

    printf("found order: "); //방문한 순서 출력
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

/* 그래프를 생성하는 함수 */
GraphType* GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);

    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 7, 8);

    insert_edge(g, 3, 8, 5);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 4, 2);

    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 4, 8, 14);

    insert_edge(g, 5, 10, 17);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);

    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);

    return g;
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    dijkstra(g, 1);

    free(g);
    return 0;
}
