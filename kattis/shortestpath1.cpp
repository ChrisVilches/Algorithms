#include <bits/stdc++.h>

using namespace std;

const int INF = 10e8;

// Simple Dijkstra.

int nodes, edges, init_node, queries;
int dist[10000];
int previous[10000];
auto comp = []( pair<int, int> a, pair<int, int> b ) { return a.second > b.second; };

void dijkstra(map<int, vector<pair<int, int>>> &graph){
  fill(dist, dist + nodes, INF);
  fill(previous, previous + nodes, -1);

  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> q(comp);

  q.push(make_pair(init_node, 0));
  dist[init_node] = 0;

  while(!q.empty()){
    pair<int, int> u = q.top();
    q.pop();
    auto neighbors = graph[u.first];
    for(pair<int, int> neighbor : neighbors){
      int v = neighbor.first;
      int alt = dist[u.first] + neighbor.second;
      if(alt < dist[v]){
        dist[v] = alt;
        previous[v] = u.first;
        q.push(make_pair(v, alt));
      }
    }
  }
}

void solve(){
  int query;
  map<int, vector<pair<int, int>>> graph;

  for(int i=0; i<edges; i++){
    int u, v, w;
    cin >> u >> v >> w;

    graph[u].push_back(make_pair(v, w));
  }

  dijkstra(graph);

  for(int i=0; i<queries; i++){
    cin >> query;
    if(dist[query] == INF){
      cout << "Impossible" << endl;
    } else {
      cout << dist[query] << endl;
    }
  }
}

int main(){
  while(scanf("%d %d %d %d", &nodes, &edges, &queries, &init_node) == 4){
    if(nodes == 0 && edges == 0 && init_node == 0 && queries == 0) return 0;
    solve();
  }
}
