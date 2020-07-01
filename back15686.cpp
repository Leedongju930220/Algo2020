#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[51][51];
int visit[51][51];
int N, M, minV = 987654321, lminV, cCnt=0;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;
vector<node> v;
bool cHouse[15];

void input() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 2) {
				v.push_back({ i,j });
			}
		}
	}
	cCnt = v.size();
}
void bfs() {
	int time = 0;
	int size = 0;
	while (!q.empty()) {
		time++;
		size = q.size();
		for (int i = 0; i < size; i++) {
			node cur;
			cur = q.front();
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int nextY = cur.y + dy[dir];
				int nextX = cur.x + dx[dir];
				if (nextY <= 0 || nextX <= 0 || nextY > N || nextX > N || visit[nextY][nextX] >= 1 )continue;
				if (visit[nextY][nextX] == 0 && map[nextY][nextX] == 1) {
					lminV += time;
				}
				visit[nextY][nextX] = 1;
				q.push({ nextY,nextX });
			}
		}
	}
}
void minCal() {
	if (lminV < minV) {
		minV = lminV;
	}
}
void queueP() {
	for (int i = 0; i < cCnt; i++) {
		if (cHouse[i] == 1) {
			q.push({ v[i].y, v[i].x });
			visit[v[i].y][v[i].x] = 2;
		}
	}
}
void initVisit() {
	lminV = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			visit[i][j] = 0;
		}
	}
}
void dfs(int depth,int cur) {
	if (depth >= M) {
		queueP();
		bfs();
		minCal();
		initVisit();
		return;
	}
	for (int i = cur; i < cCnt; i++) {
		if (cHouse[i] == 0) {
			cHouse[i] = 1;
			dfs(depth + 1, i + 1);
			cHouse[i] = 0;
		}
	}
}
int main() {
	input();
	dfs(0,0);
	printf("%d", minV);

	return 0;
}
