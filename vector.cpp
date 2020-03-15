// 코테 합격이 목표라면 vector 알고리즘 사용하기
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

typedef struct node {
	int y;
	int x;
}node;
vector<node> v1;
vector<node> v2[10][10];
bool compare1(node a, node b) {
	return a.y > b.y;
}
bool compare2(node a, node b) {
	return a.y < b.y;
}
int main() {
	node cur;
	for (int i = 0; i < 10; i++) {
		scanf("%d %d", &cur.y, &cur.x);
		v1.push_back(cur);
	}
	sort(v1.begin(), v1.end(), compare1);
	printf("y기준 내림차순 정렬\n");
	for (int i = 0; i < 10; i++) {
		printf("%d %d\n", v1[i].y, v1[i].x);
	}

	sort(v1.begin(), v1.end(), compare2);
	printf("y기준 오름차순 정렬\n");
	for (int i = 0; i < 10; i++) {
		printf("%d %d\n", v1[i].y, v1[i].x);
	}

	printf("맨 앞 출력\n");
	printf("%d %d \n", v1.front().y, v1.front().x);

	printf("2번째 erase\n");
	vector<node>::iterator iter = v1.begin();
	iter += 1; // 0부터 시작
	v1.erase(iter);
	for (int i = 0; i < 9; i++) {
		printf("%d %d\n", v1[i].y, v1[i].x);
	}

	printf("1부터 3번째까지 삭제\n");
	iter = v1.begin();
	v1.erase(iter, iter + 3); // 0, 1, 2 개 지워짐 +a-1까지 지움
	for (int i = 0; i < 6; i++) {
		printf("%d %d\n", v1[i].y, v1[i].x);
	}

	return 0;
}
