#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;
vector<int> edge[1001];
queue<int> q;
bool check[1001];

void dfs(int node){
	
	check[node] = true;
	printf("%d ", node);
	for (int i = 0; i < edge[node].size(); i++){
		int next = edge[node][i];
		if (check[next] == false){
			dfs(next);
		}
	}
}
void bfs(int node){
	q.push(node);
	check[node] = true;
	while (!q.empty()){
		int start = q.front();
		printf("%d ", start);
		q.pop();
		for (int i = 0; i < edge[start].size(); i++){
			int next = edge[start][i];
			if (check[next] == false){
				check[next] = true;
				q.push(next);
			}
		}
	}
}


int main(){
	int n, m, start;
	scanf("%d %d %d", &n, &m, &start);
	while (m--){
		int u, v;
		scanf("%d %d", &u, &v);
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	for (int i = 0; i < n; i++){
		sort(edge[i].begin(), edge[i].end());
	}
	dfs(start);
	puts("");
	memset(check, false, sizeof(check));
	bfs(start);
	puts("");

	return 0;
}
