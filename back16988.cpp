//굉장히 어렵게 돌아온 문제..아직 못품 마지막만 구현하면 될듯
//괜히 시간줄여보겠다고 별 쇼를 다하다 구현이 헬로감
//검은돌을 군집화해서 주위에 빈칸이 3개이상인 군집은 처음부터 계산에 안들어가도록 처리함
//흰돌을 놓을수있는 공간들을 dfs로 구현했고, 이제 최대 죽일수있는 돌이 몇개인지만 bfs구현하면 끝

#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[22][22];
int blackStoneDfs[400];
int N, M, maxValue = -1,blackC;
vector<int> zeroCount;  // 군집별로 몇개의 0이 둘러쌓였는지
typedef struct node {
	int y;
	int x;
}node;
vector<node> blackCountV[400];  // 각 군집별 좌표들어있는 벡터
vector<node> stoneYX;  // 0의 좌표가 들어있는 벡터
queue<node> q;

void blackCluster() {
	int zeroC=0;
	while (!q.empty()) {
		node cur = q.front();
		q.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (map[nextY][nextX] == 1) continue;
			else if (map[nextY][nextX] == 0) {
				map[nextY][nextX] = 4; // 0인칸은 잠시 4로 판별
				zeroC++;
				int size = stoneYX.size();
				//printf("사이즈 1 :%d  blackC: %d\n", size, blackC);
				blackStoneDfs[size] = blackC;
				stoneYX.push_back({ nextY,nextX });  //모든 0좌표 넣기
			}
			else if (map[nextY][nextX] == 2) {
				map[nextY][nextX] = 3;
				blackCountV[blackC].push_back({ nextY,nextX });  // 군집에 해당 노드 좌표들 넣기
				q.push({ nextY,nextX });
			}
		}
	}
	zeroCount.push_back(zeroC);  // 각 군집별로 0이 몇개인지
}

void print() {
	for (int i = 1; i <= N ; i++) {
		for (int j = 1; j <= M ; j++) {
			printf("%d", map[i][j]);
		}printf("\n");
	}
}
void blackCount() {
	print();
	printf("\n\n\n");

}
void blackStoneDfsCheck() {
	int size = zeroCount.size();
	int size2 = stoneYX.size();
	int count = 1;
	for (int i = 0; i < size2; i++) {
		if (zeroCount[blackStoneDfs[i]] > 2) {
			blackStoneDfs[i] = 0;
		}
		else {
			blackStoneDfs[i] = 1;
		}
	}
}
void stoneSelect(int depth,int count) {
	if (depth == 2) {
		blackCount();
		return;
	}
	int size = stoneYX.size();
	for (int dir = count; dir < size; dir++) {
		if (blackStoneDfs[dir] == 1) {
			blackStoneDfs[dir] = 2;
			map[stoneYX[dir].y][stoneYX[dir].x] = 1;  // 1로 바꾸는 칸은 흰돌을 놓은 자리
			stoneSelect(depth + 1, dir);
			blackStoneDfs[dir] = 1;
			map[stoneYX[dir].y][stoneYX[dir].x] = 4;
		}
	}
}
void input() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i <= N+1; i++) {
		for (int j = 0; j <= M + 1; j++) {
			map[i][j] = 1;
		}
	}
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int main() {
	input();
	//맵전체를 뒤지며 군집찾기
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			if (map[i][j] == 2) {
				q.push({ i,j });
				map[i][j] = 3;
				blackCluster();
				blackC++;
			}
		}
	}
	print();
	printf("\n\n");
	blackStoneDfsCheck();
	stoneSelect(0, 0);

	return 0;
}
