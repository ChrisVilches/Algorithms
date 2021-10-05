#include <bits/stdc++.h>

using namespace std;

int cases;
int maze[20][20];
int n, m;
int edges_open;

int exits(int i, int j){
  if(i < 0 || j < 0 || i >= n || j >= m) return 0;
  if(maze[i][j] == 1) return 0;
  maze[i][j] = 1;

  return exits(i + 1, j) +
    exits(i - 1, j) +
    exits(i, j + 1) +
    exits(i, j - 1) +
    (i == 0 || j == 0 || i == n - 1 || j == m - 1);
}

void count_open_edge(int i, int j){
  if(maze[i][j] != 0) return;
  maze[i][j] = -1;
  edges_open++;
}

bool solve(){
  char c;
  cin >> n >> m;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      while(1){
        scanf("%c", &c);
        if(c == '#' || c == '.') break;
      }
      for(int x=0; x<m; x++)
        maze[i][j] = c == '#' ? 1 : 0;
    }
  }

  edges_open = 0;

  for(int i=0; i<n; i++){
    count_open_edge(i, 0);
    count_open_edge(i, m - 1);
  }

  for(int j=0; j<m; j++){
    count_open_edge(0, j);
    count_open_edge(n - 1, j);
  }

  if(edges_open != 2) return false;

  for(int i=0; i<n; i++){
    for(int j=0; j<m; j++){
      if(exits(i, j) == 2) return true;
    }
  }

  return false;
}

int main(){
  cin >> cases;
  while(cases--){
    cout << (solve() ? "valid" : "invalid") << endl;
  }
}
