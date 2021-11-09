#include <bits/stdc++.h>

using namespace std;

typedef pair<string, int> psi;

void solve() {
  int n;
  cin >> n;
  map<string, int> counts;

  while (n--) {
    string name;
    int count;
    cin >> name >> count;

    if (counts.find(name) == counts.end()) {
      counts[name] = count;
    } else {
      counts[name] += count;
    }
  }

  vector<psi> counts_list;

  for (auto it = counts.begin(); it != counts.end(); it++) {
    counts_list.push_back(make_pair(it->first, it->second));
  }

  sort(counts_list.begin(), counts_list.end(),
       [](const psi& toy1, const psi& toy2) {
         if (toy1.second == toy2.second) return toy1.first < toy2.first;
         return toy1.second > toy2.second;
       });

  cout << counts_list.size() << endl;

  for (psi toy : counts_list) {
    cout << toy.first << ' ' << toy.second << endl;
  }
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
