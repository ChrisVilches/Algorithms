#include <bits/stdc++.h>

using namespace std;
typedef pair<double, double> pdd;
int N, M;

double dijkstra(double t, vector<vector<pair<int, pdd>>> &adj){
  double dist[N];
	fill(dist, dist+N, 10e9);
  priority_queue<pair<double, int>> q;

  q.push(make_pair(0, 0));
  dist[0] = 0;

  while(!q.empty()){
    pair<double, int> u = q.top();
    q.pop();
    vector<pair<int, pdd>> neighbors = adj[u.second];
    if(u.first > dist[u.second]) continue;
    for(pair<int, pdd> neighbor : neighbors){
      int v = neighbor.first;
      double alt = dist[u.second] + (neighbor.second.first * t + neighbor.second.second);
      if(alt < dist[v]){
        dist[v] = alt;
        q.push(make_pair(alt, v));
      }
    }
  }

  return dist[adj.size() - 1];
}

void solve(){
  vector<vector<pair<int, pdd>>> adj;

  for(int i=0; i<N; i++){
    vector<pair<int, pdd>> list;
    adj.push_back(list);
  }

  for(int i=0; i<M; i++){
    int source, target;
    double a, b;
    cin >> source >> target >> a >> b;
    source--;
    target--;

    adj[source].push_back(make_pair(target, make_pair(a, b)));
    adj[target].push_back(make_pair(source, make_pair(a, b)));
  }
  double left = 0;
  double right = 60*24;
  int iters = 80;

  while(iters--){
    double third = (right-left)/3;
    double third1 = left + third;
    double third2 = right - third;
    double d1 = dijkstra(third1, adj);
    double d2 = dijkstra(third2, adj);

    if(d1 < d2)
      left = third1;
    else
      right = third2;
  }

  printf("%0.5f\n", dijkstra(left, adj));
}

int main(){
  while(scanf("%d %d", &N, &M) == 2)
    solve();
  return 0;
}
