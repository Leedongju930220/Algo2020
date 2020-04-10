//어려웠음
//디버깅오래걸렸음
// 문제 잘 읽기
// 큐 초기화 해야하는 경우 있는지 보고 꼭 초기화
// bool visit 상황봐가면서 쓰기 이번에는 visit을 bool로 해놓고 99를 넣어버려서 자꾸 1로 초기화 됨
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>
#include<conio.h>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[51][51];
int cMap[51][51];
int visit[51][51];
int cVisit[51][51];
int N, M, binCount,minValue = 987654321, notAct;

typedef struct node {
	int y;
	int x;
}node;
queue<node> q;
int vMap[10];
vector<node> v;


void virus() {  // 맵에 virus 뿌리기
	while (!q.empty()) {
		q.pop();
	}
	for (int i = 0; i < v.size(); i++) {
		if (vMap[i] == 1) {
			map[v[i].y][v[i].x] = -1; // 활성 바이러스
			visit[v[i].y][v[i].x] = 1;
			q.push({ v[i].y, v[i].x });
		}
		else {
			map[v[i].y][v[i].x] = 0;
			visit[v[i].y][v[i].x] = -2; // 비활성 바이러스
		}
	}
}
void copyMap() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			map[i][j] = cMap[i][j];
			visit[i][j] = cVisit[i][j];
		}
	}
}
void swap(int n2) {
	if (minValue > n2) {
		minValue = n2;
	}
	return;
}
void bfs() {
	node cur;
	int lTime = 0;
	int time = 0;
	int binCount1 = binCount;

	while (!q.empty()) {
		int qSize = q.size();
		time++;
		
		if (time > minValue) {
			while (!q.empty()) {
				q.pop();
			}
			return;
		}
		for (int i = 0; i < qSize; i++) {
			cur = q.front();
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int nextY = cur.y + dy[dir];
				int nextX = cur.x + dx[dir];
				if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= N || visit[nextY][nextX] == 1 || map[nextY][nextX] == -1 )continue;
				map[nextY][nextX] = time;
				if(visit[nextY][nextX] == 0)binCount1--;
				visit[nextY][nextX] = 1;
				q.push({ nextY,nextX });
			}
		}
		lTime = time;
		if (binCount1 == 0) {
			swap(lTime);
			return;
		}
	}
	if (binCount1 == 0) {
		swap(lTime);
	}
	return;
}
void dfs(int depth,int cur) {
	if (depth >= M) {
		virus();
		bfs();
		copyMap();

		return;
	}
	for (int i = cur; i < v.size(); i++) {
		if (vMap[i] == 0) {
			vMap[i] = 1;
			dfs(depth + 1, i + 1);
			vMap[i] = 0;
		}
	}
	notAct = v.size() - M;
}
void input() {
	scanf("%d %d ", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				map[i][j] = -1;
				visit[i][j] = 99;
			}
			if (map[i][j] == 2) {
				v.push_back({ i,j });
			}
			if (map[i][j] == 0) {
				binCount++;
			}
			cMap[i][j] = map[i][j];
			cVisit[i][j] = visit[i][j];
		}
	}
}
int main() {
	input();

	if (binCount != 0) dfs(0, 0);
	else minValue = 0;

	if (minValue == 987654321) {
		printf("-1");
	}
	else printf("%d", minValue);


	return 0;
}
