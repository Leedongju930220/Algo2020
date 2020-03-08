//백준 주사위굴리기
// 시뮬레이션
//한번에 성공
//문제푼 시간 1시간
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int dx[5] = { 0,1,-1,0,0 };
int dy[5] = { 0,0,0,-1,1 };
int tpfh[4] = { 0,0,0,0 };
int rkfh[4] = { 0,0,0,0 };
int map[20][20];
int N, M, x, y, K;

void cal(int dir) {
	int temp;
	if (dir == 1) {
		temp = rkfh[3];
		rkfh[3] = rkfh[2];
		rkfh[2] = rkfh[1];
		rkfh[1] = rkfh[0];
		rkfh[0] = temp;
		tpfh[1] = rkfh[1], tpfh[3] = rkfh[3];
		
	}
	else if (dir == 2) {
		temp = rkfh[0];
		rkfh[0] = rkfh[1];
		rkfh[1] = rkfh[2];
		rkfh[2] = rkfh[3];
		rkfh[3] = temp;
		tpfh[1] = rkfh[1], tpfh[3] = rkfh[3];
		
	}
	else if (dir == 3) {
		
		temp = tpfh[3];
		tpfh[3] = tpfh[2];
		tpfh[2] = tpfh[1];
		tpfh[1] = tpfh[0];
		tpfh[0] = temp;
		rkfh[1] = tpfh[1], rkfh[3] = tpfh[3];
		
	}
	else {
		temp = tpfh[0];
		tpfh[0] = tpfh[1];
		tpfh[1] = tpfh[2];
		tpfh[2] = tpfh[3];
		tpfh[3] = temp;
		rkfh[1] = tpfh[1], rkfh[3] = tpfh[3];
	}
}
void move(int y ,int x) {
	if (map[y][x] == 0) {
		map[y][x] = rkfh[3];
	}
	else {
		rkfh[3] = map[y][x];
		tpfh[3] = map[y][x];
		map[y][x] = 0;
	}
}
int main() {
	scanf("%d %d %d %d %d", &N, &M, &y, &x, &K);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	int dir;
	for (int i = 0; i < K; i++) {
		scanf("%d", &dir);
		int nextX = x + dx[dir];
		int nextY = y + dy[dir];
		if (nextX < 0 || nextY < 0 || nextY >= N || nextX >= M) continue;
		
		cal(dir);
		move(nextY, nextX);
		x = nextX;
		y = nextY;
		printf("%d\n", rkfh[1]);
	}
	return 0;
}
