#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
//#include<conio.h>

using namespace std;
//원판돌리기
//bfs
int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int N, M, T,maxValue, rlwns;
int map[52][52];
bool visit[52][52];
typedef struct node {
	int y;
	int x;
}node;
queue<node> q;

void rotate(int x,int d, int k) {  // x의 배수 원판 회 ,d==0시계,1은 반시계, d방향 k번 실행
	k = k % M;
	for (int rX = x; rX <= N; rX =rX +x) {
		for (int rK = 0; rK < k; rK++) {
			int temp = 0;
			if (d == 0) {  //시계
				temp = map[rX][M];
				for (int i = M; i > 1; i--) {
					map[rX][i] = map[rX][i - 1];
				}
				map[rX][1] = temp;
			}
			else { 
				temp = map[rX][1];
				for (int i = 1; i < M; i++) {
					map[rX][i] = map[rX][i + 1];
				}
				map[rX][M] = temp;
			}
		}
	}
}
void bfs(int stand) {
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (nextY  < 1 || nextY >N ) continue;
			if (nextX == 0) {
				nextY = M;
			}
			if (nextX == M + 1) {
				nextX = 1;
			}
			if (map[nextY][nextX] == 0) continue;
			if (map[nextY][nextX] == stand) {
				map[cur.y][cur.x] = 0;
				map[nextY][nextX] = 0;
				rlwns = 1;
				q.push({ nextY, nextX });
			}

		}

	}
}
void noZero() {
	int stand = 0;
	int count = 0;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != 0) {
				stand = stand + map[i][j];
				count++;
			}
		}
	}
	if (count == 0) return;
	double vudrbs = (double)stand / count;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] != 0) {
				if (map[i][j] > vudrbs) {
					map[i][j] = map[i][j] - 1;
				}
				else if (map[i][j] < vudrbs) {
					map[i][j] = map[i][j] + 1;
				}
			}
		}
	}
}
void cal() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			maxValue = maxValue + map[i][j];
		}
	}
}
void init() {
	for (int i = 1; i < N; i++) {
		for (int j = 1; j < M; j++) {
			visit[i][j] = 0;
		}
	}
}
void input() {
	scanf("%d %d %d", &N, &M, &T);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int main() {
	input();
	int x, d, k;
	for (int i = 0; i < T; i++) {
		scanf("%d %d %d",&x,&d,&k);
		rotate(x,d,k);
		init();
		for (int y = 1; y <= N; y++) {
			for (int x = 1; x <= M; x++) {
				if (map[y][x] != 0) {
					q.push({ y,x });
					bfs(map[y][x]);
				}
			}
		}
		if (rlwns == 0) {
			noZero();
		}
		rlwns = 0;
	}
	cal();
	printf("%d", maxValue);

	return 0;
}
