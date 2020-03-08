// 14500 테크노미노/
//dfs함수 넣을때 y,x 순서 잘 넣기
//2번만에 성공 순서바뀐거 때문에 시간 다 먹음
//로직은 한번에 잘 구현
// 푼시간 1시간30분
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[502][502];
int visit[502][502];
int N, M, maxValue = -1;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;

void print(int depth, int y, int x,int value) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			printf("%2d", visit[i][j]);
		}printf("\n");
	}
	printf("@@@@@@@@@@ [[[  %d ]]] y[%d]  x[%d]  value[%d]@@@@@@@@\n",depth,y,x,value);
}
void dfs(int depth, int y, int x ,int value) {
	if (depth == 4) {
		if (value > maxValue) {
			maxValue = value;
		}
		//print(depth,y,x,value);
		return;
	}
	visit[y][x] = 1;
	//print(depth, y, x, value + map[y][x]);
	for (int i = 0; i < 4; i++) {
		int nextX = x + dx[i];
		int nextY = y + dy[i];
		if (nextX < 1 || nextY < 1 || nextX > M || nextY > N || visit[nextY][nextX] == 1) continue;
		//print(depth,nextY,nextX,value + map[nextY][nextX]);
		visit[nextY][nextX] = 1;
		dfs(depth + 1, nextY, nextX, value + map[nextY][nextX]);
		visit[nextY][nextX] = 0;
	}
	visit[y][x] = 0;
}
void input() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int main() {
	input();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			visit[i][j] = 1;
			dfs(1, i, j, map[i][j]);
			visit[i][j] = 0;
		}
	}
	// ㅗ모양계싼
	
	for (int i = 1; i <= N ; i++) {
		for (int j =1; j <= M ; j++) {
			int temp = map[i][j];
			for (int dir = 0; dir < 4; dir++) {
				temp = temp + map[i + dy[dir]][j + dx[dir]];
			}
			//printf("확인 i[%d][ j[%d][ temp[%d]\n", i, j, temp);
			for (int dir = 0; dir < 4; dir++) {
				if ((temp - map[i + dy[dir]][j + dx[dir]]) > maxValue) {
					maxValue = (temp - map[i + dy[dir]][j + dx[dir]]);
				}
			}
		}
	}
	printf("%d", maxValue);

	return 0;
}
