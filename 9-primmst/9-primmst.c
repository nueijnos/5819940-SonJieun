#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType { //그래프 구조체
	int n;	// 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; //인접 행렬
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 11;  // 정점 개수 설정
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->weight[i][j] = INF;
		}
		selected[i] = FALSE;
		distance[i] = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int weight) { //간선 삽입 함수
	g->weight[start][end] = weight;
	g->weight[end][start] = weight; // 무방향 그래프
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
	int v = -1;
	for (int i = 1; i < n + 1; i++) {
		if (!selected[i] && (v == -1 || distance[i] < distance[v])) { //선택되지 않거나 현재 거리보다 짧은 거리가 있는 정점 선택
			v = i;
		}
	}
	return v;
}

//prim 알고리즘(MST 찾기)
void prim(GraphType* g, int s)
{
	int i, u, v;

	for (u = 0; u < g->n; u++)
		distance[u] = INF;
	distance[s] = 0;
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;
		if (distance[u] == INF) return;
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++)
			if (g->weight[u][v] != INF)
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
	}
}

void FindPrimMST(GraphType* g) { //prim mst를 찾는 함수
	printf("Prim MST Algorithm\n");
	for (int i = 0; i < MAX_VERTICES; i++) {
		selected[i] = FALSE;
	}
	prim(g, 1); //시작 정점을 1로 설정
}

GraphType* GenerateGraph(GraphType* g) { //그래프 생성 함수
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

	FindPrimMST(g);

	free(g);
	return 0;
}
