#include<cstdio>
#include<queue>
#include<vector>

// 5
using namespace std;

int map[3][3];
int ans[3];
vector<int> v;

void print(){
	for (int i = 0; i < 3; i++){
		printf("%d ", ans[i]);
	}printf("\n");
}
void dfs(int d,int index , int size){
	printf("들어옴\n");
	if (d == 3){
		print();
		return;
	}
	for (int i = index; i < size; i++){
		ans[d] = i;
		dfs(d + 1, i + 1, size);
		ans[d] = 0;
	}
}
int main(){
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			scanf("%d", &map[i][j]);
			if (map[i][j] == 0){
				v.push_back(i * 3 + j);
			}
		}
	}
	int size = v.size();
	
	dfs(0,0, size);


	return 0;
}
