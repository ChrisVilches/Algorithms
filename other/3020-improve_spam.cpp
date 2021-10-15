#include <bits/stdc++.h>

// https://www.urionlinejudge.com.br/judge/en/problems/view/3020

using namespace std;
typedef long long ll;
const ll MOD = 1e9 + 7;

int N, L;

ll memo[1008];
bool visited[1008];
vector<vector<int>> lists;

bool is_client(int i){
  return i >= L;
}

ll count(int address){
  if(memo[address] != -1) return memo[address];
  if(is_client(address)) return 1;
  ll total = 0;
  vector<int> adjacencies = lists[address];
  for(int adj : adjacencies){
    total += (count(adj) % MOD);
  }
  total = total % MOD;
  return memo[address] = total;
}

int non_repeated_clients(int address){
  if(visited[address]) return 0;
  visited[address] = true;
  if(is_client(address)) return 1;

  ll total = 0;
  for(int adj : lists[address]){
    total += non_repeated_clients(adj);
  }

  return total;
}

void solve(){
  memset(memo, -1, sizeof memo);
  fill(visited, visited+1000, false);
  lists.clear();

  for(int i=0; i<L; i++){
    int k, m;
    cin >> k;
    vector<int> list;
    while(k--){
      cin >> m;
      m--;
      list.push_back(m);
    }
    lists.push_back(list);
  }

  cout << count(0) << " " << non_repeated_clients(0) << endl;
}

int main(){
  while(scanf("%d %d", &N,&L) == 2) solve();
}
