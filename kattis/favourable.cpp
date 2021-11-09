#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

struct Node{
  bool catastrophic = false;
  bool favourable = false;
  int a, b, c;
};

bool is_catastroph(string str){
  for(int i=0; i<str.size(); i++){
    if(str[i] == 'c') return true;
  }
  return false;
}

bool is_fav(string str){
  for(int i=0; i<str.size(); i++){
    if(str[i] == 'f') return true;
  }
  return false;
}

map<int, ll> memo;

ll recur(int page, map<int, Node> &graph){
  if(memo.count(page)) return memo[page];

  Node node = graph[page];
  if(node.catastrophic) return 0;
  if(node.favourable) return 1;

  ll paths = recur(node.a, graph) + recur(node.b, graph) + recur(node.c, graph);

  return (memo[page] = paths);
}

void solve(){
  int s, page;
  cin >> s;
  map<int, Node> graph;

  while(s--){
    memo.clear();
    cin >> page;

    string line;
    getline(cin, line);

    Node n;

    if(is_catastroph(line)) n.catastrophic = true;
    else if(is_fav(line)) n.favourable = true;
    else sscanf(line.c_str(), "%d %d %d", &n.a, &n.b, &n.c);

    graph[page] = n;
  }

  cout << recur(1, graph) << endl;
}

int main(){
  int t;
  cin >> t;
  while(t--) solve();
}
