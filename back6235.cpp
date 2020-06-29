#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

int N, K,M;
int map[11][11], dead[11][11], m[11][11];
vector<int> tree[11][11];
int dy[8] = {-1,-1,-1,0,0,1,1,1};
int dx[8] = { -1,0,1,-1,1,-1,0,1 };
int totalR = 0;

void spring() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			sort(tree[i][j].begin(), tree[i][j].end());
		}
	}
	
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			int temp = 0;
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (map[i][j] >= tree[i][j][k]) {
					map[i][j] -= tree[i][j][k];
					tree[i][j][k]++;
				}
				else {
					temp = k+1;
					break;
				}
			}
			if (temp != 0) {
				for (int k = tree[i][j].size() -1; k >= temp-1; k--) {
					map[i][j] += tree[i][j][k] / 2;
					tree[i][j].pop_back();
					totalR--;
				}
			}
		}
	}
}
void summer() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (dead[i][j] != 0) {
				map[i][j] += dead[i][j] / 2;
			}
		}
	}
}
void fall() {
	int nextY, nextX;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 0; k < tree[i][j].size(); k++) {
				if (tree[i][j][k] % 5 == 0) {
					for (int dir = 0; dir < 8; dir++) {
						nextY = i + dy[dir];
						nextX = j + dx[dir];
						if (nextY < 1 || nextX < 1 || nextY >N || nextX >N)continue;
						totalR++;
						tree[nextY][nextX].push_back(1);
					}
				}
			}
		}
	}
}
void winter() {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			map[i][j] += m[i][j];
		}
	}
}
void input() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &m[i][j]);
			map[i][j] = 5;
		}
	}
	int a, b,c;
	for (int i = 0; i < M; i++) {
		scanf("%d %d %d", &a, &b,&c);
		totalR++;
		tree[a][b].push_back(c);
	}
}
int main() {
	input();
	int time = K;
	while (K > 0) {
		spring();
		//summer();
		fall();
		winter();
		K--;
	}
	printf("%d", totalR);

	return 0;
}
