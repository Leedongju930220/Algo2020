// 연구소 문제 난이도음
// 푼 시간 1시간
//한번에 성공
//
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[8][8];
int copyM[8][8];
//int visit[8][8];
int N, M, maxValue = -1,noVirus,copyVirus;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;
queue<node> v;
vector<node> w;

void bInit() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			copyM[i][j] = map[i][j];
		}
	}
}
void go() {
	bInit();
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		map[cur.y][cur.x] = 1;
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (nextY < 0 || nextX < 0 || nextY >= N || nextX >= M || map[nextY][nextX] != 0 )continue;
			noVirus--;
			map[nextY][nextX] = 1;
			q.push({ nextY, nextX });
		}
	}
	if (noVirus > maxValue) {
		maxValue = noVirus;
	}
}
void aInit() {
	int size = v.size();
	for (int i = 0; i < size; i++) {
		node cur = v.front();
		v.pop();
		q.push(cur);
		v.push(cur);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			map[i][j] = copyM[i][j];
		}
	}
	noVirus = copyVirus;
}
void wall(int depth,int count) {
	if (depth == 3) {
		go();
		aInit();
		return;
	}
	for (int i = count; i < w.size(); i++) {
		if (map[w.at(i).y][w.at(i).x] == 0) {
			map[w.at(i).y][w.at(i).x] = 1;
			wall(depth + 1, count + 1);
			map[w.at(i).y][w.at(i).x] = 0;
		}
	}
}
void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0) {
				noVirus++;
				w.push_back({ i,j });
			}
			if (map[i][j] == 2) {
				v.push({ i,j });  // 원본용
				q.push({ i,j }); //계산용
			}
		
		}
	}
}
int main() {
	input();
	copyVirus = noVirus - 3;
	noVirus = noVirus - 3;
	wall(0,0);
	printf("%d", maxValue);
	return 0;
}
//
