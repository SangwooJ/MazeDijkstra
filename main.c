#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define MAX 12
#define SIZE 4

typedef struct maze {
	int mazeType; //장애물종류
	int nodeNum; //노드번호
}Maze;

void dijkstra(int G[MAX][MAX], int n, int startnode);
void setMazeNode(Maze map[SIZE][SIZE]);
void setAdj(Maze map[SIZE][SIZE], int G[MAX][MAX]);
void initAdj(int G[MAX][MAX]);
int countNode(Maze map[SIZE][SIZE]);
void printAdj(int G[MAX][MAX]);

int main()
{
	int G[MAX][MAX], i, j, n, u; //G는 엣지들의 값 담고있음
	Maze map[SIZE][SIZE] = { // 초기 맵 생성
		{ { 1,0 },{ 1,0 },{ 3,0 },{ 4,0 } },
		{ { 0,0 },{ 3,0 },{ 0,0 },{ 2,0 } },
		{ { 0,0 },{ 5,0 },{ 0,0 },{ 1,0 } },
		{ { 0,0 },{ 5,0 },{ 6,0 },{ 1,0 } }
	};
	
	setMazeNode(map); //노드번호 할당
	initAdj(G); //엣지 초기화
	setAdj(map, G); //엣지에 값할당 
	printf("\n");
	printAdj(G);

	n = countNode(map);

	printf("\nEnter the starting node:");
	scanf("%d", &u);
	dijkstra(G, n, u);

	return 0;
}

void setMazeNode(Maze map[SIZE][SIZE]) { //노드번호할당
	int i,j;
	int k = 1;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (map[i][j].mazeType != 0) {
				map[i][j].nodeNum = k;
				k++;
			}
		}
	}
}

int countNode(Maze map[SIZE][SIZE]) { //노드갯수 반환
	int i, j;
	int k = 1;
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			if (map[i][j].mazeType != 0) {
				k++;
			}
		}
	}
	return k;
}
void initAdj(int G[MAX][MAX]) { //엣지 초기화
	int i, j;
	for (i = 0; i < MAX; i++) 
		for (j = 0; j < MAX; j++) 
			G[i][j] = 0;

}
void setAdj(Maze map[SIZE][SIZE], int G[MAX][MAX]) { //edge 에 값할당
	int i, j;
	int temp; //인접한노드 번호
	int temp2; //현재노드 번호
	G[0][1] = map[0][0].mazeType;
	G[1][0] = map[0][0].mazeType;
	for (i = 0; i < SIZE; i++) { 
		for (j = 0; j < SIZE; j++) {
			if (map[i][j].mazeType != 0) { //길일 경우

				if (i != 0) { //위 존재확인
					if (map[i - 1][j].nodeNum != 0) { //존재하면
						temp = map[i - 1][j].nodeNum;
						temp2 = map[i][j].nodeNum;
						if(temp>temp2) 
							G[temp][temp2] = map[i][j].mazeType;
						else
							G[temp][temp2] = map[i - 1][j].mazeType;
					}
				}
				if (i != 3) { //아래 존재확인
					if (map[i + 1][j].nodeNum != 0) {
						temp = map[i + 1][j].nodeNum;
						temp2 = map[i][j].nodeNum;
						if (temp>temp2)
							G[temp][temp2] = map[i][j].mazeType;
						else
							G[temp][temp2] = map[i + 1][j].mazeType;
					}
				}
				if (j != 0) { //왼쪽 존재확인
					if (map[i][j-1].nodeNum != 0) {
						temp = map[i][j-1].nodeNum;
						temp2 = map[i][j].nodeNum;
						if (temp>temp2)
							G[temp][temp2] = map[i][j].mazeType;
						else
							G[temp][temp2] = map[i][j - 1].mazeType;
					}
				}
				if (j != 3) { //아래 존재확인
					if (map[i][j+1].nodeNum != 0) {
						temp = map[i][j+1].nodeNum;
						temp2 = map[i][j].nodeNum;
						if (temp>temp2)
							G[temp][temp2] = map[i][j].mazeType;
						else
							G[temp][temp2] = map[i][j + 1].mazeType;
					}
				}

			}
		}
	}

}

void printAdj(int G[MAX][MAX]) { //엣지 출력
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf(" %d ", G[i][j]);
		}
		printf("\n");
	}
}

void dijkstra(int G[MAX][MAX], int n, int startnode)
{

	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix
	for (i = 0; i<n; i++)
		for (j = 0; j<n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];

	//initialize pred[],distance[] and visited[]
	for (i = 0; i<n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count<n - 1)
	{
		mindistance = INFINITY;

		//nextnode gives the node at minimum distance
		for (i = 0; i<n; i++)
			if (distance[i]<mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}

		//check if a better path exists through nextnode            
		visited[nextnode] = 1;
		for (i = 0; i<n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i]<distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}

	//print the path and distance of each node
	for (i = 0; i<n; i++)
		if (i != startnode)
		{
			printf("\nDistance of node%d=%d", i, distance[i]);
			printf("\nPath=%d", i);

			j = i;
			do
			{
				j = pred[j];
				printf("<-%d", j);
			} while (j != startnode);
		}
}
