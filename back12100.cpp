 // 2048(easy)
 // 최대값은 매번 계산해 줘야한다. 그리고 flag를 쓸 때 언제 flag를 초기화해야하는지 고민
 //2시간
 #define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <queue>
#include <cstdio>
#include <string>

using namespace std;

int map[21][21];
int N, maxValue = -1;
typedef struct node {
	int y;
	int x;
}node;
vector<int> v;


void maxValueCheck() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (maxValue < map[i][j]) {
				maxValue = map[i][j];
			}
		}
	}
}
void cal(int dir) {
	//int qSize = 0;
	int flag = 0; // 0이면 병합x, 1이면 병합o
	int jC = 0;
	int back = 0;
	int vSize = 0;

	if (dir == 0) { // 오른쪽 
		for (int i = 0; i <N ; i++) {
			flag = 0;
			for (int j = N-1; j >= 0 ; j--) {
				if (map[i][j] != 0) {
					if (v.size() == 0) {
						v.push_back(map[i][j]);
					}
					else {
						if (flag == 0) {
							back = v.back();
							if (back == map[i][j]) {
								back = 2 * back;
								v.pop_back();
								v.push_back(back);
								flag = 1;
							}
							else {
								v.push_back(map[i][j]);
							}
						}
						else {
							v.push_back(map[i][j]);
							flag = 0;
						}
					}
					map[i][j] = 0;
				}
			}
			int j = N - 1;
			vSize = v.size();
			for (int vs = 0; vs < vSize; vs++) {
				map[i][j - vs] = v[vs];
			}
			v.clear();
		}

	}
	else if (dir == 1) {  // 아래쪽 
		for (int j = 0; j < N; j++) {
			flag = 0;
			for (int i = N-1; i >= 0; i--) {
				if (map[i][j] != 0) {
					if (v.size() == 0) {
						v.push_back(map[i][j]);
					}
					else {
						if (flag == 0) {
							back = v.back();
							if (back == map[i][j]) {
								back = 2 * back;
								v.pop_back();
								v.push_back(back);
								flag = 1;
							}
							else {
								v.push_back(map[i][j]);
							}
						}
						else {
							v.push_back(map[i][j]);
							flag = 0;
						}
					}
					map[i][j] = 0;
				}
			}
			int i = N - 1;
			vSize = v.size();
			for (int vs = 0; vs < vSize; vs++) {
				map[i-vs][j] = v[vs];
			}
			v.clear();
		}

	}
	else if (dir == 2) {  // 왼쪽 
		for (int i = 0; i < N; i++) {
			flag = 0;
			for (int j = 0; j < N; j++) {
				if (map[i][j] != 0) {
					if (v.size() == 0) {
						v.push_back(map[i][j]);
					}
					else {
						if (flag == 0) {
							back = v.back();
							if (back == map[i][j]) {
								back = 2 * back;
								v.pop_back();
								v.push_back(back);
								flag = 1;
							}
							else {
								v.push_back(map[i][j]);
							}
						}
						else {
							v.push_back(map[i][j]);
							flag = 0;
						}
					}
					map[i][j] = 0;
				}
			}
			int j = 0;
			vSize = v.size();
			for (int vs = 0; vs < vSize; vs++) {
				map[i][j + vs] = v[vs];
			}
			v.clear();
		}

	}
	else if (dir == 3) { // 윗쪽
		for (int j = 0; j < N; j++) {
			flag = 0;
			for (int i = 0; i < N; i++) {
				if (map[i][j] != 0) {
					if (v.size() == 0) {
						v.push_back(map[i][j]);
					}
					else {
						if (flag == 0) {
							back = v.back();
							if (back == map[i][j]) {
								back = 2 * back;
								v.pop_back();
								v.push_back(back);
								flag = 1;
							}
							else {
								v.push_back(map[i][j]);
							}
						}
						else {
							v.push_back(map[i][j]);
							flag = 0;
						}
					}
					map[i][j] = 0;
				}
			}
			int i = 0;
			vSize = v.size();
			for (int vs = 0; vs < vSize; vs++) {
				map[i+vs][j] = v[vs];
			}
			v.clear();
		}

	}
}
void dfs(int depth) {
	if (depth == 5) {
		
		return;
	}
	for (int dir = 0; dir < 4; dir++) {

		int cMap[21][21];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cMap[i][j] = map[i][j];
			}
		}
		

		cal(dir);
		maxValueCheck();

		
		dfs(depth + 1);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				map[i][j] = cMap[i][j];
			}
		}
	}

}
void input() {
	scanf("%d", &N);
	for (int i =0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}
int main() {
	input();
	
	dfs(0);

	printf("%d", maxValue);

	return 0;
}

