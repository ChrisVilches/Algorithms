#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;

  while (cin >> s) {
    map<int, int> freq;

    for (const char c : s) {
      freq[c]++;
    }

    vector<int> a;

    for (const auto& [_, v] : freq) {
      a.emplace_back(v);
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < 2 && !a.empty(); i++) a.pop_back();

    cout << accumulate(a.begin(), a.end(), 0) << endl;
  }
}
