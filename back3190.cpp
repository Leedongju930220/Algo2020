// 백준 3190 뱀
// 한번에 성공
// 문제 잘 읽기, 이동 후 방향전환이니깐 함수 순서 잘 지키기
// 푼시간 총 1시간 40분  // 설계 30분 구현 30분 테스트 40
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>

using namespace std;

int dx[4] = { 1,0,-1, 0 };
int dy[4] = { 0,1,0,-1 };  // 방향 꺾는거 조심
int movemap[10001];  // 1이면 좌측 2이면 우측  0이면 없음
int map[102][102];
int N, K, X, C, L, time;
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;

int moveCal(int dir, int leftOrRight) {
	int returnDir=0;
	if (dir == 0) {
		if (movemap[leftOrRight] == 1) {
			returnDir = 3;
		}
		if (movemap[leftOrRight] == 2) {
			returnDir = 1;
		}
	}
	if (dir == 1) {
		if (movemap[leftOrRight] == 1) {
			returnDir = 0;
		}
		if (movemap[leftOrRight] == 2) {
			returnDir = 2;
		}
	}
	if (dir == 2) {
		if (movemap[leftOrRight] == 1) {
			returnDir = 1;
		}
		if (movemap[leftOrRight] == 2) {
			returnDir = 3;
		}
	}
	if (dir == 3) {
		if (movemap[leftOrRight] == 1) {
			returnDir = 2;
		}
		if (movemap[leftOrRight] == 2) {
			returnDir = 0;
		}
	}
	return returnDir;
}
void moving() {
	q.push({ 1,1 });
	int dir = 0;
	time =0;
	int x = 1;
	int y = 1;
	map[1][1] = 1;
	while(1) {
		time++;
		int nextX = x + dx[dir];
		int nextY = y + dy[dir];
		if (nextX <1 || nextY < 1 || nextX >N || nextY > N) {  // 벽이면
			return;
		}
		else if (map[nextY][nextX] == 2) {  //다음이 사과면
			map[nextY][nextX] = 1;
			q.push({ nextY,nextX });
			x = nextX;
			y = nextY;
		}
		else if (map[nextY][nextX] == 0) {  // 갈수있는 공백이면
			map[nextY][nextX] = 1;
			q.push({ nextY,nextX });
			node deleteNode = q.front();
			q.pop();
			map[deleteNode.y][deleteNode.x] = 0;
			x = nextX;
			y = nextY;
		}
		else if (map[nextY][nextX] == 1) {  // 자기몸이면
			return;
		}
		if (movemap[time] != 0) {
			dir = moveCal(dir, time);
		}
	}
}
void input() {
	scanf("%d %d", &N, &K);
	int x, y;
	for (int i = 0; i < K; i++) {
		scanf("%d %d", &y, &x);
		map[y][x] = 2;  //2는 사과
	}
	char c;
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		scanf("%d", &x);
		scanf(" %c", &c);
		if (c == 'L') {
			movemap[x] = 1;
		}
		if (c == 'D') {
			movemap[x] = 2;
		}
	}
}

int main() {
	input();
	moving();
	printf("%d", time);

	return 0;
}
