// 아직 다 못품...dfs,bfs,MST까지 혼합문제
//  MST만구현하면 끝
// 현재 1시간30분걸림
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<queue>
#include<conio.h>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[11][11];
bool visit[11][11];
int mapDis[7][7];  // 맵탐색은 1부터
int N, M, minDis = 987654321,mapCount=1;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
void bfs(int y, int x) {
	q.push({ y,x });
	visit[y][x] = 1;
	map[y][x] = mapCount;
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= M) continue;
			if (visit[nextY][nextX] == 0 && map[nextY][nextX] != 0) {
				map[nextY][nextX] = mapCount;
				visit[nextY][nextX] = 1;
				q.push({ nextY,nextX });
			}
		}
	}
}
void dfs() {

}
void sortDist(int y, int x) {
	int stand = map[y][x];
	printf("들어옴 y[%d] x[%d] stand [%d]\n", y, x,stand);
	for (int dir = 0; dir < 4; dir++) {
		int mulCount = 1;
		while (1) {
			int nextY = y + dy[dir] * mulCount;
			int nextX = x + dx[dir] * mulCount;
			if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= M) break;
			printf(" mul [%d] y[%d] x[%d] dir[%d] \n", mulCount,nextY, nextX, dir);
			if (map[nextY][nextX] != 0 && map[nextY][nextX] != stand && mulCount-1 >= 2) {
				if (mapDis[map[nextY][nextX]][stand] == 0) {
					mapDis[map[nextY][nextX]][stand] = mulCount-1;
					mapDis[stand][map[nextY][nextX]] = mulCount-1;
					printf("%d 넣음 1번  \n", mulCount - 1);
					break;
				}
				else if (mapDis[map[nextY][nextX]][stand] > mulCount-1) {
					mapDis[map[nextY][nextX]][stand] = mulCount-1;
					mapDis[stand][map[nextY][nextX]] = mulCount-1;
					printf("%d 넣음 2번 \n", mulCount-1);
					break;
				}
				break;
			}
			if (map[nextY][nextX] == stand)break;
			if (map[nextY][nextX] != 0 && map[nextY][nextX] != stand && mulCount-1 < 2) break;

			mulCount++;
			printf("mul 업[%d]  y[%d] x[%d] dir[%d] \n", mulCount, nextY, nextX, dir);
		}
	}
}
void print() {
	for (int i = 1; i <= mapCount-1; i++) {
		for (int j = 1; j <= mapCount-1; j++) {
			printf("%d", mapDis[i][j]);
		}printf("\n");
	}
}
int main() {
	input();
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 1 && visit[i][j] == 0) {
				bfs(i, j);
				mapCount++;
			}
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] != 0) {
				sortDist(i, j);
			}
		}
	}
	print();


	return 0;
}
