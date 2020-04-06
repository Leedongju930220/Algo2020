// 위가 dfs로 구현한 콤비네이션
// 아래가 비트마스크로 구현한 콤비네이션
// 15콤비네이션 5일때 위가 1.5초 아래가 3.0초 나옴, 일반적인 상황에선 dfs로 

#define _CRT_SECURE_NO_WARNINGS
#include<queue>
#include<time.h>

using namespace std;

clock_t start, endt;
int map[15];
int countv = 0;

void dfs(int depth, int count, int cur) {
	if (count >= 5) {
		for (int i = 0; i < depth; i++) {
			if (map[i] == 1) printf("%d ", i);
		}printf("\n");
		countv++;
		return;
	}
	for (int i = cur; i < depth; i++) {
		if (map[i] == 0) {
			map[i] = 1;
			dfs(depth, count+1, i + 1);
			
			map[i] = 0;
			
		}
	}

}
int main() {
	start = clock();

	dfs(15, 0,0);

	endt = clock();
	double result = (double)(endt - start);
	printf("시간측정 : %f  및 총 개수 %d", result, countv);


	return 0;
}

////////////////////////////////////////////////////////////////
#include <algorithm>
#include <iostream>
#include <string>
#include<time.h>

using namespace std; 

int countV = 0, countv;
clock_t start, endt;

void comb(int N, int K)
{
	string bitmask(K, 1); // K leading 1's
	bitmask.resize(N, 0); // N-K trailing 0's

	// print integers and permute bitmask
	do {
		for (int i = 0; i < N; ++i) // [0..N-1] integers
		{
			if (bitmask[i]) {
				cout << " " << i;
				//countv++;
			}

		}
		countv++;
		std::cout << std::endl;
	} while (std::prev_permutation(bitmask.begin(), bitmask.end()));
}

int main()
{
	start = clock();
	comb(15, 5);
	//printf("%d\n", countV);
	endt = clock();
	double result = (double)(endt - start);
	printf("시간측정 : %f 총 개수 %d", result,countv);
}
