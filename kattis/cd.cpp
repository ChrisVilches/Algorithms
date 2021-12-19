#include <bits/stdc++.h>
using namespace std;

int main() {
  int N, M;

  while (scanf("%d %d", &N, &M) == 2 && N && M) {
    unordered_set<int> cds;

    while (N--) {
      int cd;
      cin >> cd;
      cds.insert(cd);
    }

    int total = 0;

    while (M--) {
      int cd;
      cin >> cd;
      if (cds.count(cd)) total++;
    }

    cout << total << endl;
  }
}
