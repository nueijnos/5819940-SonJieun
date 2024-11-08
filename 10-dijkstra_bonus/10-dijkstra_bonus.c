#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100   
#define INF 1000L   /* ���Ѵ� �� (������ ���� ���) */

typedef struct GraphNode {
    int vertex, weight; //����, ����ġ
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType { 
    int n;	// ������ ����
    struct GraphNode* adj_list[MAX_VERTICES];
} GraphType;

typedef struct { //�� ��� ����ü
    int vertex, distance; //����, �׿� ���� �Ÿ�
} HeapNode;

typedef struct { //�ּ� �� ����ü
    HeapNode heap[MAX_VERTICES]; //�� �迭
    int heap_size; 
} MinHeap;

int distance[MAX_VERTICES]; /* ���� �������κ����� �ִ� ��� �Ÿ� */
int found[MAX_VERTICES];    /* �湮�� ���� ǥ�� */
int found_index = 0;
int found_order[MAX_VERTICES];

void graph_init(GraphType* g) { //�׷��� �ʱ�ȭ �Լ�
    g->n = 10;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

void insert_edge(GraphType* g, int start, int end, int w) { //���� ���� ����
    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->vertex = end;
    newNode->weight = w;
    newNode->next = g->adj_list[start];
    g->adj_list[start] = newNode;
}

void init_minheap(MinHeap* h) { //minheap �ʱ�ȭ
    h->heap_size = 0;
}

void swap(HeapNode* a, HeapNode* b) { //��ȯ �Լ�
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* h, int index) { //�ּ� �� heapify(������) �Լ�
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->heap_size && h->heap[left].distance < h->heap[smallest].distance) //���� �ڽ� ���� �� �۴ٸ�
        smallest = left;
    if (right < h->heap_size && h->heap[right].distance < h->heap[smallest].distance) //������ �ڽ� ���� �� �۴ٸ�
        smallest = right;

    if (smallest != index) { //�θ� ��� ���� �ڽ� ��� ���� �ٸ���
        swap(&h->heap[index], &h->heap[smallest]); //��ȯ ��
        min_heapify(h, smallest); //�� ������
    }
}

void insert_minheap(MinHeap* h, int vertex, int distance) { //minheap ���� ���� �Լ�
    int i = h->heap_size++;
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;

    while (i && h->heap[i].distance < h->heap[(i - 1) / 2].distance) {
        swap(&h->heap[i], &h->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode delete_minheap(MinHeap* h) { //minheap �ּ� ���� ���� �Լ�
    HeapNode min_edge = h->heap[0];
    h->heap[0] = h->heap[--h->heap_size];
    min_heapify(h, 0); //�ּ� �� ���� ����
    return min_edge;
}

void print_dijkstra(int n) {  //���ͽ�Ʈ�� �˰����� ��������� distance ������ found�� ����ϴ� �Լ�
    printf("Distance: ");
    for (int j = 1; j <= n; j++) {
        if (distance[j] == INF)
            printf("* ");
        else
            printf("%d ", distance[j]); //��������� distance ���� ���
    }
    printf("\nFound:    ");
    for (int j = 1; j <= n; j++) { 
        printf("%d ", found[j]); //found ���
    }
    printf("\n\n");
}

/* Dijkstra �˰��� �Լ� */
void dijkstra(GraphType* g, int start) {
    MinHeap h;
    init_minheap(&h);

    for (int i = 0; i < MAX_VERTICES; i++) { //�ʱ�ȭ
        distance[i] = INF;
        found[i] = 0;
    }
    distance[start] = 0;
    insert_minheap(&h, start, 0);

    while (h.heap_size > 0) { //���� ������� �ʴ� ���� ��� �ݺ�
        HeapNode u = delete_minheap(&h); //�ּ� �Ÿ� ���� ����

        if (found[u.vertex]) continue; //�̹� �湮�ߴ� �����̸� �ǳ� �ٰ�
        found[u.vertex] = 1; //������ �湮 ó��
        found_order[found_index++] = u.vertex;

        print_dijkstra(g->n); //���� ���� ���

        for (GraphNode* v = g->adj_list[u.vertex]; v != NULL; v = v->next) { //���� ���� Ž��
            if (!found[v->vertex] && distance[u.vertex] + v->weight < distance[v->vertex]) { //�湮���� �ʰų� ���ο� ��ΰ� �� ª���� �Ÿ� ������Ʈ
                distance[v->vertex] = distance[u.vertex] + v->weight; //���ο� �Ÿ��� ������Ʈ �ϰ� 
                insert_minheap(&h, v->vertex, distance[v->vertex]); //���� ����
            }
        }
    }

    printf("found order: "); //�湮�� ���� ���
    for (int i = 0; i < found_index; i++) {
        printf("%d ", found_order[i]);
    }
    printf("\n");
}

/* �׷����� �����ϴ� �Լ� */
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
