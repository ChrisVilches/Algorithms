#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
  ll N, M, A;

  cin >> N >> M >> A;

  ll ans = ((N / A) + (N % A != 0)) * ((M / A) + (M % A != 0));

  cout << ans << endl;
}
