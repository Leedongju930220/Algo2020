#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int dy[4] = { 1,0,0,-1 };
int dx[4] = { 0,1,-1,0 };
int map[21][21];
bool visit[21][21];
int N, fTime, fSize=2, upCnt = 0;
typedef struct node {
	int y;
	int x;
}node;
node start;

vector<node> v;
vector<node> v1;
queue<node> q;


void input() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 9) {
				q.push({ i,j });
				start.y = i;
				start.x = j;
			}
		}
	}
}
bool compareX(node a, node b) {
	return a.x > b.x;
}
bool compareY(node a, node b) {
	return a.y < b.y;
}
void cal() {
	map[start.y][start.x] = 0;
	if (v.size() > 1) {
		sort(v.begin(), v.end(), compareY);
		if (v[0].y == v[1].y) {
			if (v[0].x > v[1].x) {
				start.y = v[1].y;
				start.x = v[1].x;
			}
			else {
				start.y = v[0].y;
				start.x = v[0].x;
			}
		}
		else {
			
			start.y = v[0].y;
			start.x = v[0].x;

		}
	}
	else {
		start.y = v[0].y;
		start.x = v[0].x;
	}
	while (!q.empty()) {
		q.pop();
	}
	upCnt++;
	if (upCnt == fSize) {
		fSize++;
		upCnt = 0;
	}
	v.clear();
	map[start.y][start.x] = 9;
	q.push(start);
}
void bfs() {
	node cur;
	int time = 0;
	bool flag = true;
	while (!q.empty()) {
		int size = q.size();
		time++;
		for (int i = 0; i < size; i++) {
			cur = q.front();
			q.pop();
			for (int dir = 0; dir < 4; dir++) {
				int nextY = cur.y + dy[dir];
				int nextX = cur.x + dx[dir];
				if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= N)continue;
				if (visit[nextY][nextX] == 1 || map[nextY][nextX] > fSize) continue;
				if (map[nextY][nextX] < fSize && map[nextY][nextX] >0 ) {
					visit[nextY][nextX] = 1;
					v.push_back({ nextY,nextX });
					flag = false;
				}
				visit[nextY][nextX] = 1;
				q.push({ nextY,nextX });
			}
		}
		if (flag == false) {
			//printf("cal들어가기전 %d\n",v.size());
			
			cal();
			//printf("cal나옴\n");
			fTime += time;
			time = 0;
			flag = true;
			for (int ii = 0; ii < N; ii++) {
				for (int jj = 0; jj < N; jj++) {
					visit[ii][jj] = 0;
				}
			}
			visit[start.y][start.x] = 1;
		}
	}
}
int main() {
	input();
	bfs();
	printf("%d", fTime);

	return 0;
}
