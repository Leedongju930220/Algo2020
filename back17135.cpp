#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int dy[3] = { 0,-1,0 };
int dx[3] = { -1,0,1 };
int map[16][16];  // 0~15까지 쓰고 N+1은 궁수자리
int cMap[16][16];
int N, M, D, maxValue, finishValue, deleteCnt;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;

void bfs(int cnt) {
	int wCnt = 1;
	while (1) {
		if (wCnt > D) {
			break;
		}
		int size = q.size();
		for (int i = 0; i < size; i++) {
			node cur = q.front();
			q.pop();
			for (int dir = 0; dir < 3; dir++) {
				int nextY = cur.y + dy[dir];
				int nextX = cur.x + dx[dir];
				if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= M )continue;
				if (map[nextY][nextX] == -1 || map[nextY][nextX] == -3) {
					map[nextY][nextX] = -3;
					return;
				}
				map[nextY][nextX] = cnt;
				q.push({ nextY,nextX });
			}
		}
		wCnt++;
	}

}
void input() {
	scanf("%d %d %d", &N, &M, &D);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				map[i][j] = -1;
				finishValue++;
			}
		}
	}
}
void select() {
	int cnt = 1;
	for (int i = 0; i < M; i++) {
		if (map[N][i] == cnt || map[N][i] == -2) {
			q.push({ N,i });
			map[N][i] = cnt;
			bfs(cnt);
			while (!q.empty()) {
				q.pop();
			}
			map[N][i] = -2;
			cnt++;
		}
	}
}
void deleteA() {
	finishValue = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (map[i][j] == -3) {
				map[i][j] = 0;
				deleteCnt++;
			}
			if (map[i][j] == -1)finishValue++;
		}
	}
}
void down() {
	for (int j = 0; j < M; j++) {
		for (int i = N - 2; i >= 0; i--) {
			map[i + 1][j] = map[i][j];
		}
		map[0][j] = 0;
	}
}
void dfs(int depth, int cur) {
	if (depth >= 3) {
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= M; j++) {
				cMap[i][j] = map[i][j];
			}
		}
		int  cfinishValue = 0;
		cfinishValue = finishValue;
		deleteCnt = 0;
		while (1) {

			select();
			deleteA();
			if (finishValue == 0) break;
			down();
		}
		finishValue = cfinishValue;
		if (deleteCnt > maxValue) maxValue = deleteCnt;
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= M; j++) {
				map[i][j] = cMap[i][j];
			}
		}
		return;
	}

	for (int i = cur; i < M; i++) {
		if (map[N][i] == 0) {
			map[N][i] = -2; // -2 궁수
			dfs(depth + 1, i + 1);
			map[N][i] = 0;
		}
	}
}
int main() {
	input();

	dfs(0, 0);

	printf("%d", maxValue);

	return 0;
}
