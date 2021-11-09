#include <bits/stdc++.h>

using namespace std;
typedef pair<string, string> pss;

int main() {
  vector<pss> people;
  unordered_map<string, int> first_names;
  while (!cin.eof()) {
    string first, last;
    cin >> first >> last;
    if (first.empty()) break;

    if (first_names.find(first) == first_names.end())
      first_names[first] = 1;
    else
      first_names[first]++;

    people.push_back(make_pair(first, last));
  }

  sort(people.begin(), people.end(), [](const pss& p1, const pss& p2) {
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second < p2.second;
  });

  for (pss p : people) {
    auto [first, last] = p;

    cout << first;
    if (first_names[first] > 1) cout << ' ' << last << endl;
    cout << endl;
  }
}
