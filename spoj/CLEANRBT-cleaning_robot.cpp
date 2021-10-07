#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> pii;

int w, h, bfs[11][20][20], memo[2000][5000];

char grid[20][20];
pii robot_pos;
vector<pii> dirty_tiles;
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};

int dist(int a, int b){
  pii target = dirty_tiles[b - 1];
  return bfs[a][target.first][target.second];
}

int dp(int idx, int mask){
  if(memo[idx][mask] != -1) return memo[idx][mask];
  int min_value = 0;

  for(int i=0; i<=dirty_tiles.size(); i++){
    if((mask & (1 << i)) > 0) continue;
    int result = dp(i, mask | (1 << i)) + dist(idx, i);
    if(min_value == 0)
      min_value = result;
    else
      min_value = min(result, min_value);
  }
  memo[idx][mask] = min_value;
  return min_value;
}

void calculate_bfs(int bfs_idx, pii init_pos){
  queue<pair<pii, int>> q;
  q.push(make_pair(init_pos, 0));

  while(!q.empty()){
    pair<pii, int> top = q.front();
    q.pop();
    pii pos = top.first;
    int dist = top.second;
    bfs[bfs_idx][pos.first][pos.second] = dist;

    for(int i=0; i<4; i++){
      int new_i = pos.first + dy[i];
      int new_j = pos.second + dx[i];
      if(new_i >= h || new_j >= w || new_i < 0 || new_j < 0) continue;
      if(grid[new_i][new_j] == 'x' || bfs[bfs_idx][new_i][new_j] != INT_MAX) continue;
      bfs[bfs_idx][new_i][new_j] = -1; // Make it visited, but have not yet calculated its distance.
      q.push(make_pair(make_pair(new_i, new_j), dist+1));
    }
  }
}

void solve(){
  memset(memo, -1, sizeof(memo));
  fill_n(&bfs[0][0][0], 11 * 20 * 20, INT_MAX);
  dirty_tiles.clear();

  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      char c;
      while(scanf("%c", &c) && !(c == '.' || c == '*' || c == 'x' || c == 'o'));
      grid[i][j] = c;

      if(c == 'o') robot_pos = make_pair(i, j);
      if(c == '*') dirty_tiles.push_back(make_pair(i, j));
    }
  }

  calculate_bfs(0, robot_pos);

  for(int i=0; i<dirty_tiles.size(); i++){
    pii pos = dirty_tiles[i];
    if(bfs[0][pos.first][pos.second] == INT_MAX){
      cout << -1 << endl;
      return;
    }
    calculate_bfs(i + 1, dirty_tiles[i]);
  }

  cout << dp(0, 1) << endl;
}

int main(){
  while(scanf("%d %d", &w, &h) == 2){
    if(w == 0 || h == 0) break;
    solve();
  }
}
