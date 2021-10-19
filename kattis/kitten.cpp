#include <bits/stdc++.h>

using namespace std;

vector<int> find_path(int curr_node, int target, map<int, vector<int>>& links) {
  vector<int> path;
  vector<int> adj = links[curr_node];
  path.push_back(curr_node);

  if (curr_node == target) return path;

  vector<int> subpath;
  for (int branch : adj) {
    subpath = find_path(branch, target, links);
    if (!subpath.empty()) break;
  }

  for (int b : subpath) path.push_back(b);

  return path;
}

int main() {
  int K;

  stringstream ss;
  string line;

  // Helpers to find which node is the root.
  unordered_set<int> all_nodes, nodes_with_parent;
  getline(cin, line);
  ss = stringstream(line);
  ss >> K;
  map<int, vector<int>> links;
  while (true) {
    int a, b;
    getline(cin, line);
    ss = stringstream(line);
    ss >> a;
    if (a == -1) break;
    all_nodes.emplace(a);
    while (!ss.eof()) {
      ss >> b;
      all_nodes.emplace(b);
      nodes_with_parent.emplace(b);
      if (links.find(b) == links.end()) {
        links[b] = vector<int>{};
      }
      links[b].push_back(a);
    }
  }

  int target;
  for (auto it = all_nodes.begin(); it != all_nodes.end(); it++) {
    if (nodes_with_parent.find(*it) == nodes_with_parent.end()) {
      target = *it;
      break;
    }
  }

  vector<int> path = find_path(K, target, links);
  for (int branch : path) {
    cout << branch << " ";
  }
  cout << endl;
}
