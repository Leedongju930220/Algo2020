//굉장히 어렵게 돌아온 문제..아직 못품 마지막만 구현하면 될듯
//괜히 시간줄여보겠다고 별 쇼를 다하다 구현이 헬로감
//검은돌을 군집화해서 주위에 빈칸이 3개이상인 군집은 처음부터 계산에 안들어가도록 처리함
//흰돌을 놓을수있는 공간들을 dfs로 구현했고, 이제 최대 죽일수있는 돌이 몇개인지만 bfs구현하면 끝


// 틀림 //반례를 못찾겠음 테케는 다 나옴
// 첫번째 생각 : 그냥 모든 바둑판에서 2개 흰돌 고르고 bfs돌기기
// 두번째 생각 : 첫번째는 계산안해도 되는 것들도 너무 많이 계산해서 생각을 바꿔봄
//               검은돌 주위 0만 벡터에 저장후 거기서 2개를 골라 bfs계싼
// 세번째 생각 : 두번때 생각도 계산 안해도 되는 부분이 많음, 예를들어 검은돌 군집 주변에 빈칸이 3개면 애초에 2개로 죽일수없는 돌들
//              그래서 검은돌 군집 주변에 빈칸이 2개 이하인 군집들만 계산해서 bfs돌리기
//  하지만 50%쯤에서 테케가 틀렸나봄
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<queue>
#include<vector>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[22][22];
int blackStoneDfs[400];
bool visit[22][22];
int copyMap[22][22];
int N, M, maxValue = -1,blackC,total,blackCheck,blackZeroC;
vector<int> zeroCount;  // 군집별로 몇개의 0이 둘러쌓였는지
typedef struct node {
	int y;
	int x;
}node;
vector<node> blackCountV[400];  // 각 군집별 좌표들어있는 벡터
vector<node> stoneYX;  // 0의 좌표가 들어있는 벡터
queue<node> q;
queue<node> q1;

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
			printf("%d ", visit[i][j]);
		}printf("\n");
	}
}
void blackCount() {
	blackZeroC = 0;
	while (!q1.empty()) {
		node cur=q1.front();
		q1.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (nextY < 1 || nextX < 1 || nextY > N || nextX > M || visit[nextY][nextX] == 1) continue;
			if (map[nextY][nextX] == 4) {
				blackZeroC++;
				continue;
			}
			if (map[nextY][nextX] == 3) {
				blackCheck++;
				visit[nextY][nextX] = 1;
				q1.push({ nextY,nextX });
			}
		}
	}
	if(blackZeroC == 0)total += blackCheck;
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
		blackCheck = 0;
		for (int i = 0; i <= N + 1; i++) {
			for (int j = 0; j <= M + 1; j++) {
				visit[i][j] = 0;
				if (map[i][j] == 1) {
					visit[i][j] = 1;
				}
			}
		}
		//print();
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				if (map[i][j] == 3 && visit[i][j] == 0) {
					q1.push({ i,j });
					visit[i][j] = 1;
					blackCheck++;
					blackCount();
					blackCheck = 0;
					int q1size = q1.size();
					for (int qq = 0; qq < q1size; qq++) {
						q1.pop();
					}
				}
			}
		}
		if (total > maxValue) {
			maxValue = total;
			
		}
		total = 0;
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
	blackStoneDfsCheck();
	stoneSelect(0, 0);
	if (maxValue == -1) {
		printf("0");
	}
	else printf("%d", maxValue);

	return 0;
}
