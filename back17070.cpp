#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
//#include<conio.h>

using namespace std;

typedef struct node {
	int y;
	int x;
}node;
int map[17][17];
int maxValue = 0;
int N;

void print() {
	printf("출력함수\n");
	for (int i = 1; i <= N; i++) {
		for (int j =1; j <= N; j++) {
			printf("%d ", map[i][j]);
		}printf("\n");
	}
}
void input() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
void dfs(int y, int x, int num) {
	if (y == N && x == N) {
		maxValue++;
		return;
	}
	if (maxValue > 1000000) {
		return;
	}
	//print();
	//_getch();
	if (num == 1) {
		if ( y>0 && x+1 > 0 && y <=N && x+1 <=N && map[y][x+1] ==0) {
			map[y][x + 1] = 1;
			dfs(y , x + 1, 1);
			map[y][x + 1] = 0;
		}
		if (y > 0 && x + 1 > 0 && y <= N && x + 1 <= N && map[y][x + 1] == 0 && y + 1 > 0 && x > 0 && y + 1 <= N && x <= N && map[y + 1][x] == 0 && y + 1 > 0 && x + 1 > 0 && y + 1 <= N && x + 1 <= N && map[y + 1][x + 1] == 0) {
			map[y + 1][x] = 1;
			map[y][x + 1] = 1;
			map[y + 1][x + 1] = 1;
			dfs(y + 1, x + 1, 3);
			map[y + 1][x] = 0;
			map[y][x + 1] = 0;
			map[y + 1][x + 1] = 0;
		}
	}
	else if (num == 2) {
		if (y + 1 > 0 && x > 0 && y + 1 <= N && x <= N && map[y + 1][x] == 0) {
			map[y + 1][x] = 1;
			dfs(y + 1, x, 2);
			map[y + 1][x] = 0;
		}
		if (y > 0 && x + 1 > 0 && y <= N && x + 1 <= N && map[y][x + 1] == 0 && y + 1 > 0 && x > 0 && y + 1 <= N && x <= N && map[y + 1][x] == 0 && y + 1 > 0 && x + 1 > 0 && y + 1 <= N && x + 1 <= N && map[y + 1][x + 1] == 0) {
			map[y + 1][x] = 1;
			map[y][x + 1] = 1;
			map[y + 1][x + 1] = 1;
			dfs(y + 1, x + 1, 3);
			map[y + 1][x] = 0;
			map[y][x + 1] = 0;
			map[y + 1][x + 1] = 0;
		}

	}
	else if (num == 3) {
		if (y > 0 && x + 1 > 0 && y <= N && x + 1 <= N && map[y][x + 1] == 0) {
			map[y][x + 1] = 1;
			dfs(y, x + 1, 1);
			map[y][x + 1] = 0;
		}
		if (y + 1 > 0 && x > 0 && y + 1 <= N && x <= N && map[y + 1][x] == 0) {
			map[y + 1][x] = 1;
			dfs(y + 1, x, 2);
			map[y + 1][x] = 0;
		}
		if (y > 0 && x + 1 > 0 && y <= N && x + 1 <= N && map[y][x + 1] == 0 && y + 1 > 0 && x > 0 && y + 1 <= N && x <= N && map[y + 1][x] == 0 && y + 1 > 0 && x + 1 > 0 && y + 1 <= N && x + 1 <= N && map[y + 1][x + 1] == 0) {
			map[y + 1][x] = 1;
			map[y][x + 1] = 1;
			map[y + 1][x + 1] = 1;
			dfs(y + 1, x + 1, 3);
			map[y + 1][x] = 0;
			map[y][x + 1] = 0;
			map[y + 1][x + 1] = 0;
		}
	}
}
int main() {
	input();
	map[1][1] = 1;
	map[1][2] = 1;
	dfs(1, 2, 1);
	if (maxValue == 1000001)printf("1000000\n");
	else printf("%d", maxValue);

	return 0;
}
