#include <bits/stdc++.h>
using namespace std;

int parse_time(string t) {
  t[2] = ' ';
  stringstream ss(t);
  int h, m;
  ss >> h >> m;
  return (h * 60) + m;
}

int main() {
  int l, k, s;
  cin >> l >> k >> s;

  unordered_map<int, int> completed;
  unordered_map<int, int> sum;

  for (int i = 0; i < l; i++) {
    int id;
    string time;
    cin >> id >> time;
    completed[id]++;
    sum[id] += parse_time(time);
  }

  vector<pair<int, int>> ranking;

  for (const auto& [id, time] : sum) {
    if (completed[id] != k) continue;

    ranking.emplace_back(time, id);
  }

  sort(ranking.begin(), ranking.end());

  for (const auto& [_, id] : ranking) {
    cout << id << endl;
  }
}
