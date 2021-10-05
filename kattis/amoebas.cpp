#include <bits/stdc++.h>

using namespace std;

int grid[100][100];
int n, m;
int total = 0;
int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

void visit(int i, int j){
  queue<pair<int, int>> q;
  q.push(make_pair(i, j));

  // ID for this amoeba.
  int id = 71 + total; // Make it different from 0 and 1, which mean something else.

  int iters=0;
  while(!q.empty()){
    iters++;
    auto curr = q.front();
    q.pop();

    grid[curr.first][curr.second] = id;

    for(int i=0; i<8; i++){
      int y = curr.first + dy[i];
      int x = curr.second + dx[i];

      if(y >= 0 && x >= 0 && y < n && x < m && grid[y][x] == 1){
        grid[y][x] = id;
        q.push(make_pair(y, x));
      }
    }
  }
}

void solve(){
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(grid[i][j] == 1){
        total++;
        visit(i, j);
      }
    }
  }
  cout << total << endl;
}

int main(){
  cin >> n >> m;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      char c;
      while(scanf("%c", &c) == 1){
        if(c == '#' || c == '.') break;
      }
      grid[i][j] =  c == '#' ? 1 : 0;
    }
  }
  solve();
}
