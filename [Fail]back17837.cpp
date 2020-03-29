// 시뮬레이션 구현문제
//틀림
//다시풀어보기
//마지막 테케 실패
/*#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>
#include<conio.h>

using namespace std;

typedef struct node {
	int y;
	int x;
	int dir;
}node;
int map[14][14];
int dy[5] = {0, 0,0,-1,1 };
int dx[5] = { 0, 1,-1,0,0 };
vector<int> vMap[14][14]; // 0이랑 마지막은 가면 파란색으로
vector<int> temp;
node kWhere[13];
int N, K,finish = -1;


void printV() {
	printf("벡터맵\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d", vMap[i][j].size());
		}printf("\n");
	}
	printf("말 위치\n");
	for (int i = 1; i <= K; i++) {
		printf("%d 번말 위치 y[%d]: x[%d]: dir[%d] \n", i, kWhere[i].y, kWhere[i].x, kWhere[i].dir);
	}
}
void input() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	node cur;
	for (int i = 1; i <= K;  i++) {
		scanf("%d %d %d", &cur.y, &cur.x, &cur.dir);
		kWhere[i] = cur;
		vMap[cur.y][cur.x].push_back(i);
	}
}
void check(node cur, int mSize, int turn) {  // 해당 턴에서 움직일 것들 temp벡터에 넣은 체크함수
	temp.clear();
	int forCount = 0;
	for (int i = 0; i < mSize; i++) {
		if (vMap[cur.y][cur.x].at(i) == turn) {
			forCount = i;
			break;
		}
	}
	for (int i = forCount; i < mSize; i++) {
		temp.push_back(vMap[cur.y][cur.x][i]);
	}
	for (int i = mSize - 1; i >= forCount; i--) {
		vMap[cur.y][cur.x].pop_back();
	}
}
void simul() {
	int count = 1;
	int turn = 0;
	int mSize = 0;
	node cur;

	while (1) {
		
		if (count == 1001) {
			return;
		}
		for (int i = 1; i <= K; i++) {
			turn = i;
			cur.y = kWhere[turn].y;
			cur.x = kWhere[turn].x;
			cur.dir = kWhere[turn].dir;
			mSize = vMap[cur.y][cur.x].size();

			int nextY = cur.y + dy[cur.dir];
			int nextX = cur.x + dx[cur.dir];
			printf("이번 count [%d]  y [%d] x [%d] 방향 [%d]\n", count, nextY, nextX, cur.dir);

			//check(cur,mSize,turn);
			//int tempSize = temp.size();
			if (map[nextY][nextX] == 0 && !(nextY == 0 || nextX == 0 || nextY > N || nextX > N)) {  // 흰색
				printf("1)))  현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
				check(cur, mSize, turn);
				int tempSize = temp.size();
				for (int i = 0; i < tempSize; i++) {
					vMap[nextY][nextX].push_back(temp.at(i));
					kWhere[temp.at(i)].y = nextY;
					kWhere[temp.at(i)].x = nextX;
				}
			}
			else if (map[nextY][nextX] == 1 && !(nextY == 0 || nextX == 0 || nextY > N || nextX > N)) {  // 빨강
				printf("2))) 현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
				check(cur, mSize, turn);
				int tempSize = temp.size();
				for (int i = tempSize - 1; i >= 0; i--) {
					vMap[nextY][nextX].push_back(temp.at(i));
					kWhere[temp.at(i)].y = nextY;
					kWhere[temp.at(i)].x = nextX;
				}
			}
			else if (map[nextY][nextX] == 2 || nextY == 0 || nextX == 0 || nextY > N || nextX > N ) {  // 파랑 & 맵 밖

				if (cur.dir == 1 || cur.dir == 3) {
					cur.dir = cur.dir + 1;
				}
				else cur.dir = cur.dir - 1;
				nextY = cur.y + dy[cur.dir];
				nextX = cur.x + dx[cur.dir];
				kWhere[turn].dir = cur.dir;
				printf("3-1))) 현재 turn [%d] 현재 y [%d] x [%d] 방향 [%d] \n", turn, nextY, nextX, cur.dir);
				if (map[nextY][nextX] == 2 || nextY == 0 || nextX == 0 || nextY > N  || nextX > N) {
					printf("또 파랑이거나 벽\n");
				}
				else {
					printf("이번에는 파랑이거나 벽이 아님\n");
					check(cur, mSize, turn);
					int tempSize = temp.size();
					for (int i = 0; i < tempSize; i++) {
						vMap[nextY][nextX].push_back(temp.at(i));
						kWhere[temp.at(i)].y = nextY;
						kWhere[temp.at(i)].x = nextX;
					}
				}
				printf("3-2))) 현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
			}
			if (vMap[nextY][nextX].size() >= 4) {
				finish = count;
				return;
			}
			printV();
			_getch();
			printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		}
		count++;
		//종료조건
	}
}
int main() {
	input();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d", vMap[i][j].size());
		}printf("\n");
	}
	printf("\n\n\n\n");
	for (int i = 1; i <= K; i++) {
		printf("%d %d %d\n", kWhere[i].y, kWhere[i].x, kWhere[i].dir);
	}
	simul();
	printV();
	printf("%d", finish);

	return 0;
}*/

#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

typedef struct node {
	int y;
	int x;
	int dir;
}node;
int map[14][14];
int dy[5] = { 0, 0,0,-1,1 };
int dx[5] = { 0, 1,-1,0,0 };
vector<int> vMap[14][14]; // 0이랑 마지막은 가면 파란색으로
vector<int> temp;
node kWhere[13];
int N, K, finish = -1;


void printV() {
	printf("벡터맵\n");
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			printf("%d", vMap[i][j].size());
		}printf("\n");
	}
	printf("말 위치\n");
	for (int i = 1; i <= K; i++) {
		printf("%d 번말 위치 y[%d]: x[%d]: dir[%d] \n", i, kWhere[i].y, kWhere[i].x, kWhere[i].dir);
	}
}
void input() {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	node cur;
	for (int i = 1; i <= K; i++) {
		scanf("%d %d %d", &cur.y, &cur.x, &cur.dir);
		kWhere[i] = cur;
		vMap[cur.y][cur.x].push_back(i);
	}
}
void check(node cur, int mSize, int turn) {  // 해당 턴에서 움직일 것들 temp벡터에 넣은 체크함수
	temp.clear();
	int forCount = 0;
	for (int i = 0; i < mSize; i++) {
		if (vMap[cur.y][cur.x].at(i) == turn) {
			forCount = i;
			break;
		}
	}
	for (int i = forCount; i < mSize; i++) {
		temp.push_back(vMap[cur.y][cur.x][i]);
	}
	for (int i = mSize - 1; i >= forCount; i--) {
		vMap[cur.y][cur.x].pop_back();
	}
}
void simul() {
	int count = 1;
	int turn = 0;
	int mSize = 0;
	node cur;

	while (1) {

		if (count == 1001) {
			return;
		}
		for (int i = 1; i <= K; i++) {
			turn = i;
			cur.y = kWhere[turn].y;
			cur.x = kWhere[turn].x;
			cur.dir = kWhere[turn].dir;
			mSize = vMap[cur.y][cur.x].size();

			int nextY = cur.y + dy[cur.dir];
			int nextX = cur.x + dx[cur.dir];
			//printf("이번 count [%d]  y [%d] x [%d] 방향 [%d]\n", count, nextY, nextX, cur.dir);

			//check(cur,mSize,turn);
			//int tempSize = temp.size();
			if (map[nextY][nextX] == 0 && !(nextY == 0 || nextX == 0 || nextY > N || nextX > N)) {  // 흰색
				//printf("1)))  현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
				check(cur, mSize, turn);
				int tempSize = temp.size();
				for (int i = 0; i < tempSize; i++) {
					vMap[nextY][nextX].push_back(temp.at(i));
					kWhere[temp.at(i)].y = nextY;
					kWhere[temp.at(i)].x = nextX;
				}
			}
			else if (map[nextY][nextX] == 1 && !(nextY == 0 || nextX == 0 || nextY > N || nextX > N)) {  // 빨강
				//printf("2))) 현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
				check(cur, mSize, turn);
				int tempSize = temp.size();
				for (int i = tempSize - 1; i >= 0; i--) {
					vMap[nextY][nextX].push_back(temp.at(i));
					kWhere[temp.at(i)].y = nextY;
					kWhere[temp.at(i)].x = nextX;
				}
			}
			else if (map[nextY][nextX] == 2 || nextY == 0 || nextX == 0 || nextY > N || nextX > N) {  // 파랑 & 맵 밖

				if (cur.dir == 1 || cur.dir == 3) {
					cur.dir = cur.dir + 1;
				}
				else cur.dir = cur.dir - 1;
				nextY = cur.y + dy[cur.dir];
				nextX = cur.x + dx[cur.dir];
				kWhere[turn].dir = cur.dir;
				//printf("3-1))) 현재 turn [%d] 현재 y [%d] x [%d] 방향 [%d] \n", turn, nextY, nextX, cur.dir);
				if (map[nextY][nextX] == 2 || nextY == 0 || nextX == 0 || nextY > N || nextX > N) {
					//printf("또 파랑이거나 벽\n");
				}
				else {
					//printf("이번에는 파랑이거나 벽이 아님\n");
					check(cur, mSize, turn);
					int tempSize = temp.size();
					for (int i = 0; i < tempSize; i++) {
						vMap[nextY][nextX].push_back(temp.at(i));
						kWhere[temp.at(i)].y = nextY;
						kWhere[temp.at(i)].x = nextX;
					}
				}
				//printf("3-2))) 현재 turn [%d] 현재 y [%d] 현재 x [%d] 현재 방향 dir [%d]  count [%d]\n", turn, nextY, nextX, cur.dir, count);
			}
			if (vMap[nextY][nextX].size() >= 4) {
				finish = count;
				return;
			}
			//printV();
			//_getch();
			//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		}
		count++;
		//종료조건
	}
}
int main() {
	input();
	
	simul();
	//printV();

	printf("%d", finish);

	return 0;
}
