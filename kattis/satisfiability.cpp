#include <bits/stdc++.h>
using namespace std;

string line;
stringstream ss;

bool satisfies(const vector<pair<int, bool>>& clause, const int solution) {
  return any_of(clause.begin(), clause.end(), [solution](const auto& item) {
    const auto [x, neg] = item;
    return ((solution & (1 << x)) != 0) ^ neg;
  });
}

bool solve(const vector<vector<pair<int, bool>>>& clauses, const int n) {
  for (int subset = 0; subset < (1 << n); subset++) {
    const bool ok = all_of(clauses.begin(), clauses.end(), [subset](const auto clause) {
      return satisfies(clause, subset);
    });

    if (ok) return true;
  }

  return false;
}

int main() {
  getline(cin, line);
  ss = stringstream(line);

  int t;
  ss >> t;

  while (t--) {
    getline(cin, line);
    ss = stringstream(line);
    int n, m;
    ss >> n >> m;

    vector<vector<pair<int, bool>>> clauses;

    while (m--) {
      getline(cin, line);
      vector<pair<int, bool>> clause;

      for (int i = 0; i < (int)line.size(); i++) {
        const char c = line[i];
        if (c != 'X') continue;

        if (i == 0 || line[i - 1] != '~') {
          clause.emplace_back(-1, false);
        } else {
          clause.emplace_back(-1, true);
        }
      }

      for (char& c : line) {
        if (c < '0' || c > '9') c = ' ';
      }

      ss = stringstream(line);
      for (auto& [x, _] : clause) ss >> x;
      for (auto& [x, _] : clause) x--;

      clauses.emplace_back(clause);
    }

    if (solve(clauses, n)) {
      cout << "satisfiable" << endl;
    } else {
      cout << "unsatisfiable" << endl;
    }
  }
}
