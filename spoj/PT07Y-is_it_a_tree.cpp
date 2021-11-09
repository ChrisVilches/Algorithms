#include <bits/stdc++.h>

using namespace std;
int n, m;
vector<int> nodes[10000];
set<int> visited;

void dfs(int u){
  visited.insert(u);
  for(auto v : nodes[u]){
    if(visited.find(v) != visited.end()) continue;
    dfs(v);
  }
}

int main(){
  scanf("%d %d", &n, &m);
  for(int i=0; i<m; i++){
    int u, v;
    scanf("%d %d", &u, &v);
    nodes[u - 1].push_back(v - 1);
  }

  if(n != m+1){
    cout << "NO" << endl;
    return 0;
  }

  dfs(0);
  cout << ((visited.size() != n) ? "NO" : "YES") << endl;
}
