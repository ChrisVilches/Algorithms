#include <bits/stdc++.h>
using namespace std;

int main() {
  int N;

  cin >> N;

  while (N--) {
    string word;
    cin >> word;

    if (word.size() <= 10) {
      cout << word << endl;
      continue;
    }

    cout << word.front() << word.size() - 2 << word.back() << endl;
  }
}
