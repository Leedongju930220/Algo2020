// 구슬탈출 2 // 어렵다....
// 시도 방법 : DFS
// 큰틀 :  1. 입력
//         2. DFS 호출
//         3. 10번보다 많으면 끝 , 최소이동한 횟수보다 많으면 끝
//         4. 먼저 굴려야하는 공 선택 ( ex. 좌로 굴릴때 더 좌측에 있는공 먼저 굴리기 )
//         5. 파란공은 안들어가고 빨간공만 들어가면 
//         푼시간 1시간 // 결과 : 실패

#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>
#include<conio.h>

using namespace std;

int map[10][10];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0 ,1,0,-1 };
int minValue=987654321, redHoll, blueHoll, N,M, redX ,redY ,blueX, blueY;

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			printf("%3d", map[i][j]);
		}printf("\n");
	}
	printf("---------------------\n");
	//printf("%d %d %d %d", redX, redY, blueX, blueY);
}

int swapCheck(int firstX, int firstY, int secondX, int secondY, int dir) {  //dir 우 하 좌 상 // 우일땐 우측공 먼저, 하일땐 아래공 먼저, 좌일땐 좌측공 먼저, 상일땐 위쪽 공 먼저, return 1이면 순서 스왑
	if (dir == 0 && (secondX > firstX) ) return 1;
	if (dir == 1 && (secondY > firstY) ) return 1;
	if (dir == 2 && (secondX < firstX) ) return 1;
	if (dir == 3 && (secondY < firstY) ) return 1;
	return 0;
}
int mapCheck(int X, int Y) {  // 다음 공 좌표가 1이면 못감, 2이면 구멍, 갈 수 있으면 0
	if (X < 0 || Y < 0 || X > M || Y > N || map[X][Y] == 1) return 1;
	if (map[X][Y] == 2) return 2;
	else return 0;
}
void dfs(int firstX, int firstY, int secondX, int secondY, int depth) {
	if (depth > 10  || depth > minValue )  {  // 종료조건
		return;
	}

	for (int dir = 0; dir < 4; dir++) {

		int swapCheckValue = swapCheck(firstX, firstY, secondX, secondY, dir);
		if (swapCheckValue == 1) {  // return 1이면 두번째공을 첫번째공으로 스왑 , 0이면 그대로 첫번째공 먼저 굴리기
			int tempX, tempY;
			tempX = firstX, tempY = firstY;
			firstX = secondX, firstY = secondY;
		}
		int count = 1;
		int nextFisrtX, nextFisrtY;
		while (1) {   // 첫번째 공 갈수있는 위치만큼 while
			nextFisrtX = firstX + dx[dir]*count;
			nextFisrtY = firstY + dy[dir]*count;
			int mapCheckValue = mapCheck(nextFisrtX, nextFisrtY);
			if (mapCheckValue == 1) {  // 다음 좌표 이동 불가면 이전 좌표로 저장해야해서 count -1 곱해서 더하기
				nextFisrtX = firstX + dx[dir] * (count - 1);
				nextFisrtY = firstY + dy[dir] * (count - 1);
				map[nextFisrtX][nextFisrtY] = map[firstX][firstY];
				map[firstX][firstY] = 0;
				break;
			}
			if (mapCheckValue == 2) {  // 구멍이면 무슨색 공인지 체크
				if (map[nextFisrtX][nextFisrtY] == 3) redHoll = 1;
				if (map[nextFisrtX][nextFisrtY] == 4) return;  // 파랑이 구멍이면 리턴
				break;
			}
			count++;
		}
		count = 1;
		int nextsecondX, nextsecondY;
		while (1) {  // 두번째 공 갈수있는 위치만큼 while
			nextsecondX = secondX + dx[dir] * count;
			nextsecondY = secondY + dy[dir] * count;
			int mapCheckValue = mapCheck(nextsecondX, nextsecondY);
			if (mapCheckValue == 1) {  // 다음 좌표 이동 불가면 이전 좌표로 저장해야해서 count -1 곱해서 더하기
				nextsecondX = secondX + dx[dir] * (count - 1);
				nextsecondY = secondY + dy[dir] * (count - 1);
				map[nextsecondX][nextsecondY] = map[secondX][secondY];
				map[secondX][secondY] = 0;
				break;
			}
			if (mapCheckValue == 2) {  // 구멍이면 무슨색 공인지 체크
				if (map[nextsecondX][nextsecondY] == 3) redHoll = 1;
				if (map[nextsecondX][nextsecondY] == 4) return;  // 파랑이 구멍이면 리턴
				break;
			}
			count++;
		}
		printf("redx : %d @@ redY : %d @@ blueX : %d @@ blueY : %d @@ depth : %d \n", firstX, firstY, secondX, secondY, depth);
		print();
		_getch();

		if (redHoll == 0 && blueHoll == 0) {  // 만약 둘 다 아직 안들어 갔으면 다음 dfs 호출
			dfs(nextFisrtX, nextFisrtY, nextsecondX, nextsecondY, depth + 1);
			redHoll = 0, blueHoll = 0;
		}
		else if(redHoll == 1 && blueHoll == 0) {   // 만약 빨간공만 들어갔으면 minValue에 depth넣고 끝
			minValue = depth;
			return;
		}
	}
}
void input() {
	char c;
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf(" %c", &c);
			if (c == '#') {
				map[i][j] = 1;
			}
			else if (c == 'O') {
				map[i][j] = 2;
			}
			else if (c == 'R') {
				map[i][j] = 3;
				redX = i;
				redY = j;
			}
			else if(c == 'B'){
				map[i][j] = 4;
				blueX = i;
				blueY = j;
			}
		}
	}
}

int main() {
	input();

	dfs(redX, redY, blueX, blueY, 1);

	if (minValue == 987654321) printf("-1");
	else printf("%d", minValue);


	return 0;

}
