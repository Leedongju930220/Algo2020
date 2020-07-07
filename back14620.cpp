#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

int N, G;
int map[10][10];
bool visit[10][10];
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int totalMin = 987654321,lMin =0;
typedef struct node {
	int y;
	int x;
}node;
node fMap[90];

void comp() {
	if (totalMin > lMin) {
		totalMin = lMin;
	}
}
void uncheck(int y , int x) {
	for (int i = 0; i < 4; i++) {
		if (visit[y + dy[i]][x + dx[i]] == 1) {
			lMin -= map[y + dy[i]][x + dx[i]];
		
		}
		visit[y + dy[i]][x + dx[i]] = 0;
	}
	visit[y][x] = 0;
	lMin -= map[y][x];
	
}
void draw(int y,int x) {
	visit[y][x] = 1;
	lMin += map[y][x];
	for (int i = 0; i < 4; i++) {
		visit[y + dy[i]][x + dx[i]] = 1;
		lMin += map[y + dy[i]][x + dx[i]];
	}
}
bool check(int y,int x) {
	for (int i = 0; i < 4; i++) {
		if (visit[y + dy[i]][x + dx[i]] == 1)return false;
	}
	if (visit[y][x] == 1) return false;

	return true;
}
void dfs(int depth, int cur) {
	if (depth >= 3) {
		comp();
		return;
		return;
	}
	for (int i = cur; i <= (N - 2) * (N - 2)-1; i++) {
		node temp = fMap[i];
		if (visit[temp.y][temp.x] == 1) {
			continue;
		}
		if (check(temp.y, temp.x) == true) {
			draw(temp.y, temp.x);
			dfs(depth + 1, i + 1);
			uncheck(temp.y, temp.x);
		}
	}
}
void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int cnt = 0;
	node temp;
	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			temp = { i,j };
			fMap[cnt] = temp;
			cnt++;
		}
	}
}
int main() {
	input();
	dfs(0,0);
	printf("%d", totalMin);
	return 0;
}
