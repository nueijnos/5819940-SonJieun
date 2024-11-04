#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100   
#define INF 1000L   /* 무한대 값 (연결이 없는 경우) */

typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; /* 시작 정점으로부터의 최단 경로 거리 */
int found[MAX_VERTICES];    /* 방문한 정점 표시 */
int found_index = 0; //방문 순서 인덱스
int found_order[MAX_VERTICES]; //방문 순서 기록

void graph_init(GraphType* g) {
    g->n = 10;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = (i == j) ? 0 : INF;
        }
    }
}

/* 엣지 추가 함수 */
void insert_edge(GraphType* g, int u, int v, int weight) {
    g->weight[u][v] = weight;
    g->weight[v][u] = weight; // 양방향 그래프일 경우
}

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n)
{
    int v = -1;
    for (int i = 1; i <= n; i++) {
        if (!found[i] && (v == -1 || distance[i] < distance[v])) { //선택되지 않거나 현재 거리보다 짧은 거리가 있는 정점 선택
            v = i;
        }
    }
    return v;
}

void print_dijkstra(int n) { //다익스트라 알고리즘의 현재까지의 distance 정보와 found를 출력하는 함수
    printf("Distance: ");
    for (int j = 1; j <= n; j++) {
        if (distance[j] == INF)
            printf("* ");
        else
            printf("%d ", distance[j]); //현재가지의 distance 정보 출력
    }
    printf("\nFound:    ");
    for (int j = 1; j <= n; j++) {
        printf("%d ", found[j]); //found 출력
    }
    printf("\n\n");
}

/* Dijkstra 알고리즘 함수 */
void dijkstra(GraphType* g, int start) {
    // 초기화
    for (int i = 1; i <= g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }
    distance[start] = 0;

    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n); //가장 짧은 거리의 방문하지 않은 정점을 선택
        found[u] = TRUE; //정점을 방문 처리
        found_order[found_index++] = u; //방문 순서 기록

        print_dijkstra(g->n); //현재 상태 출력

        for (int v = 1; v <= g->n; v++) {
            if (g->weight[u][v] != INF && !found[v]) { //연결된 방문하지 않은 정점이면
                if (distance[u] + g->weight[u][v] < distance[v]) {
                    distance[v] = distance[u] + g->weight[u][v]; //새로운 거리로 업데이트
                }
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
