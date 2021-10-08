#include<bits/stdc++.h>
using namespace std;
  
typedef pair<int, int> pii;

struct DisjointSets{
  int *parent, *rnk;
  int n;

  DisjointSets(int n){
    this->n = n;
    parent = new int[n+1];
    rnk = new int[n+1];
    for (int i = 0; i <= n; i++){
      rnk[i] = 0;
      parent[i] = i;
    }
  }

  int find(int u){
    if (u != parent[u])
      parent[u] = find(parent[u]);
    return parent[u];
  }

  void merge(int x, int y){
    x = find(x), y = find(y);
    if (rnk[x] > rnk[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rnk[x] == rnk[y])
      rnk[y]++;
  }
};

struct Graph{
  int V, E;
  vector<pair<int, pii>> edges;

  Graph(int V, int E) : V(V), E(E){}

  void add_edge(int u, int v, int w){
    edges.push_back({w, {u, v}});
  }

  int kruskal_mst(){
    int mst_wt = 0;
    sort(edges.begin(), edges.end());

    DisjointSets ds(V);

    vector< pair<int, pii> >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++){
      int u = it->second.first;
      int v = it->second.second;

      int set_u = ds.find(u);
      int set_v = ds.find(v);

      if (set_u != set_v){
        mst_wt += it->first;
        ds.merge(set_u, set_v);
      }
    }

    return mst_wt;
  }
};

void solve(){
  int milk, cats;
  cin >> milk >> cats;

  int edges = (cats * (cats - 1))/2;
  Graph g(cats, edges);

  for(int i=0; i<edges; i++){
    int u, v, w;
    cin >> u >> v >> w;
    g.add_edge(u, v, w);
  }

  int mst_wt = g.kruskal_mst();

  int total_needed = cats + mst_wt;

  cout << (milk >= total_needed ? "yes" : "no") << endl;
}

int main(){
  int t;
  cin >> t;
  while(t--) solve();
}
