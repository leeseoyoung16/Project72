#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 200
#define INF 1000000

//(2) 연결 리스트를 이용하여 구현

typedef struct Node {
	int vertex;
	int weight;
	struct Node* next;
}Node;

typedef struct GraphType {
	int n; //정점의 갯수
	Node* adj_list[MAX_VERTICES]; //인접 리스트 배열
}GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) { //아직 방문하지 않았고, min가 거리보다 적을때
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

// 현재 상태 출력 함수
void print_status(GraphType* g) {
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");

	printf("Found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

// 간선 추가 함수
void add_edge(GraphType* g, int start, int end, int weight) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->vertex = start;
	new_node->weight = weight;
	new_node->next = g->adj_list[end];
	g->adj_list[end] = new_node;
}

// 최단 경로 찾기 함수
void shortest_path(GraphType* g, int start) {
	int i, u, w;
	Node* temp;

	for (i = 0; i < g->n; i++) {
		distance[i] = INF;
		found[i] = FALSE;
	}

	distance[start] = 0;

	for (i = 0; i < g->n-1 ; i++) {
		
		u = choose(distance, g->n, found);
		found[u] = TRUE;

		temp = g->adj_list[u];

		while (temp != NULL) {
			w = temp->vertex;
			if (!found[w] && distance[u] + temp->weight < distance[w])
				distance[w] = distance[u] + temp->weight;

			temp = temp->next;
		}
		print_status(g);
	}

	int sorted_vertices[MAX_VERTICES];

	for (i = 0; i < g->n; i++) {
		sorted_vertices[i] = i;
	}

	for(i=0; i<g->n-1; i++){
		for (int j = 0; j < g->n - i - 1; j++) {
			if (distance[sorted_vertices[j]] > distance[sorted_vertices[j + 1]]) {
				int temp = sorted_vertices[j];
				sorted_vertices[j] = sorted_vertices[j + 1];
				sorted_vertices[j + 1] = temp;
			}
		}
	}
	// 정렬된 결과 출력
	for (i = 0; i < g->n; i++) {
		printf("%d ", sorted_vertices[i]+1);
	}
}

int main(void) {
	GraphType g;
	g.n = 10;

	for (int i = 0; i < MAX_VERTICES; i++) {
		g.adj_list[i] = NULL;
	}

	// 그래프 초기화 (인접 리스트에 간선 추가)
	add_edge(&g, 0, 1, 3);
	add_edge(&g, 0, 5, 11);
	add_edge(&g, 0, 6, 12);

	add_edge(&g, 1, 0, 3);
	add_edge(&g, 1, 2, 5);
	add_edge(&g, 1, 3, 4);
	add_edge(&g, 1, 4, 1);
	add_edge(&g, 1, 5, 7);
	add_edge(&g, 1, 6, 8);

	add_edge(&g, 2, 1, 5);
	add_edge(&g, 2, 3, 2);
	add_edge(&g, 2, 6, 6);
	add_edge(&g, 2, 7, 5);

	add_edge(&g, 3, 1, 4);
	add_edge(&g, 3, 2, 2);
	add_edge(&g, 3, 4, 13);
	add_edge(&g, 3, 7, 14);
	add_edge(&g, 3, 9, 16);

	add_edge(&g, 4, 1, 1);
	add_edge(&g, 4, 3, 13);
	add_edge(&g, 4, 5, 9);
	add_edge(&g, 4, 8, 18);
	add_edge(&g, 4, 9, 17);

	add_edge(&g, 5, 0, 11);
	add_edge(&g, 5, 1, 7);
	add_edge(&g, 5, 4, 9);

	add_edge(&g, 6, 1, 8);
	add_edge(&g, 6, 2, 6);
	add_edge(&g, 6, 7, 13);


	add_edge(&g, 7, 2, 5);
	add_edge(&g, 7, 3, 14);
	add_edge(&g, 7, 6, 13);
	add_edge(&g, 7, 9, 15);

	add_edge(&g, 8, 4, 18);
	add_edge(&g, 8, 9, 10);

	add_edge(&g, 9, 3, 16);
	add_edge(&g, 9, 4, 17);
	add_edge(&g, 9, 7, 15);
	add_edge(&g, 9, 8, 10);

	printf("Dijkstra Algorithm (2)\n");
	shortest_path(&g, 0);

	return 0;
}