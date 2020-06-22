#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

int dy[4] = { 0,1,0,-1 };
int dx[4] = { 1,0,-1,0 };
int map[100][100];
int visit[100][100];
typedef struct node {
	int y;
	int x;
}node;
int totalTime,t,r,landCnt=0, landtemp;
queue<node> q;
queue<node> v;
vector<int> land;

void input() {
	scanf("%d %d",&t, &r);
	for (int i = 0; i < t; i++) {
		for (int j = 0; j < r; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) {
				landCnt++;
			}
		}
	}

}
void bfs(int localTime) {
	v.push({ 0,0 });
	visit[0][0] = 1;
	node cur;
	while (!v.empty()) {
		cur = v.front();
		v.pop();
		for (int dir = 0; dir < 4; dir++) {
			int nextY = cur.y + dy[dir];
			int nextX = cur.x + dx[dir];
			if (nextY < 0 || nextX < 0 || nextY >= t || nextX >= r)continue;
			if (visit[nextY][nextX] == localTime)continue;
			if (map[nextY][nextX] == 1) {
				map[nextY][nextX] = 0;
				visit[nextY][nextX] = localTime;
				landCnt--;
			}
			else {
				visit[nextY][nextX] = localTime;
				v.push({ nextY,nextX });
			}
		}
	}
}
int main() {
	input();
	int localTime = 0;
	
	while (1) {
		localTime++;
		landtemp = landCnt;
		bfs(localTime);
		if (landCnt == 0) {
			break;
		}
	}
	printf("%d\n%d", localTime, landtemp);

	return 0;
}
