#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드

// 초기화
void set_init(int n)
{
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType { //그래프 구조체
	int n;	// 간선의 개수
	int vertex; //정점의 수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화(시작하는 정점과 끝나는 정점, 그리고 가중치를 초기화)
void graph_init(GraphType* g) 
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

// qsort()에 사용되는 함수(간선 비교 함수)
int compare(const void* a, const void* b) 
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

typedef struct MinHeap { //최소 힙 구조체
	struct Edge edges[2 * MAX_VERTICES];
	int heap_size;
} MinHeap;


void init_minheap(MinHeap* h) { //minheap 초기화
	h->heap_size = 0;
}


void swap(struct Edge* a, struct Edge* b) { //교환 함수
	struct Edge temp = *a;
	*a = *b;
	*b = temp;
}

void min_heapify(MinHeap* h, int index) { //최소 힙 heapify 함수
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < h->heap_size && h->edges[left].weight < h->edges[smallest].weight)
		smallest = left;
	if (right < h->heap_size && h->edges[right].weight < h->edges[smallest].weight)
		smallest = right;

	if (smallest != index) {
		swap(&h->edges[index], &h->edges[smallest]);
		min_heapify(h, smallest);
	}
}

void insert_minheap(MinHeap* h, struct Edge e) { //minheap 간선 삽입 함수
	int i = h->heap_size++;
	while (i > 0 && e.weight < h->edges[(i - 1) / 2].weight) {
		h->edges[i] = h->edges[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	h->edges[i] = e;  //새 간선 삽입
}

struct Edge delete_minheap(MinHeap* h) { //minheap 최소 간선 제거 함수
	struct Edge min_edge = h->edges[0];
	h->edges[0] = h->edges[--h->heap_size];
	min_heapify(h, 0); //최소 힙 구조 유지
	return min_edge;
}

void QuickKruskal(GraphType* g) { // kruskal의 최소 비용 신장 트리 프로그램(qsort 기반)
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Quick Based Kruskal \n");
	int i = 0;
	while (edge_accepted < (g->vertex - 1))	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
}


void MinHeapKruskal(GraphType* g) { //minheap 기반 kruskal
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;
	MinHeap heap;

	set_init(g->vertex);				// 집합 초기화
	init_minheap(&heap); 

	//모든 간선을 최소 힙에 삽입
	for (int i = 0; i < g->n; i++) {
		insert_minheap(&heap, g->edges[i]);
	}

	printf("\nMinheap Based Kruskal \n");
	while (edge_accepted < (g->vertex - 1) && heap.heap_size > 0)	// 간선의 수 < (n-1)
	{
		e = delete_minheap(&heap); //힙에서 최소 간선 제거
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) select %d \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
	}
}

GraphType* GenerateGraph(GraphType *g) {
	g->vertex = 10; //정점 수 설정
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

	GenerateGraph(g); //그래프 생성 함수

	QuickKruskal(g); 
	MinHeapKruskal(g);

	free(g);
	return 0;
}