#include <bits/stdc++.h>

using namespace std;

int grid[500][500];
int dist[500][500];
int n, m;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void solve(){
  std::fill(*dist, *dist + (500 * 500), -1);
  queue<pair<pair<int, int>, int>> q;

  q.push(make_pair(make_pair(0, 0), 0));
  dist[0][0] = 0;

  while(!q.empty()){
    auto item = q.front();
    auto curr = item.first;
    auto curr_dist = item.second;
    q.pop();
    if(curr.first == n - 1 && curr.second == m - 1){
      cout << dist[curr.first][curr.second] << endl;
      return;
    }

    for(int i=0; i<4; i++){
      int speed = grid[curr.first][curr.second];
      int y = curr.first + (dy[i] * speed);
      int x = curr.second + (dx[i] * speed);

      if(x >= 0 && x < m && y >= 0 && y < n && dist[y][x] == -1){
        q.push(make_pair(make_pair(y, x), curr_dist + 1));
        dist[y][x] = curr_dist + 1;
      }
    }
  }

  cout << -1 << endl;
}

int main(){
  cin >> n >> m;
  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      char c;
      while(scanf("%c", &c) == 1){
        if(c >= '0' && c <= '9') break;
      }
      grid[i][j] =  c - '0';
    }
  }

  solve();
}
