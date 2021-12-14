#include <bits/stdc++.h>
using namespace std;

void solve() {
  string all_sounds;
  string pregathered;
  set<string> known_sounds;

  getline(cin, all_sounds);

  while (getline(cin, pregathered) && pregathered != "what does the fox say?") {
    string sound;
    stringstream ss(pregathered);

    ss >> sound >> sound >> sound;  // Skip two.
    known_sounds.emplace(sound);
  }

  stringstream ss(all_sounds);

  while (!ss.eof()) {
    string sound;
    ss >> sound;
    if (!known_sounds.count(sound)) cout << sound << ' ';
  }

  cout << endl;
}

int main() {
  string test_int;
  getline(cin, test_int);
  stringstream ss(test_int);
  int T;
  ss >> T;
  while (T--) solve();
}
