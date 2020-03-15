//14503 로봇청소기 dfs/
// 푼시간 1시간 1번에 성공
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>

using namespace std;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int map[51][51];
int visit[51][51];
int N, M,r,c,d, clearCount;

void dfs() {
	for (int dir = 0; dir < 4; dir++) {
		int nextDir = (d + 3) % 4;
		int nextY = r + dy[nextDir];
		int nextX = c + dx[nextDir];
		if (map[nextY][nextX] == 0) {
			map[nextY][nextX] = 2;
			clearCount++;
			r = nextY;
			c = nextX;
			d = nextDir;
			//print(d);
			//_getch();
			dfs();
			return;
		}
		d = nextDir;
	}
	if (map[r - dy[d]][c - dx[d]] == 1) {
		return;
	}
	else {
		r = r - dy[d];
		c = c - dx[d];
		dfs();
		return;
	}
}
void input() {
	scanf("%d %d %d %d %d", &N, &M,&r,&c,&d);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			visit[i][j] = map[i][j];
		}
	}
}
int main() {
	input();
	map[r][c] = 2;
	clearCount++;
	dfs();
	printf("%d", clearCount);

	return 0;
}

