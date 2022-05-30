#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

#define x first
#define y second

int N, M;

vector<pii> prod, cons;

ll area(const pii& producer, const pii& consumer) {
  if (!(producer.x < consumer.x && producer.y < consumer.y)) return 0;
  return (consumer.y - producer.y) * (consumer.x - producer.x);
}

ll divide(const int prod_l, const int prod_r, const int cons_l, const int cons_r) {
  if (prod_l == prod_r) return 0;

  const int mid_prod_idx = (prod_l + prod_r) / 2;

  ll best_area = 0;
  int best_idx = -1;

  for (int i = cons_l; i < cons_r && i < (int)cons.size(); i++) {
    // TODO: Why is this necessary?
    if (best_idx == -1 && prod[mid_prod_idx].x < cons[i].x) best_idx = i;

    const ll rect = area(prod[mid_prod_idx], cons[i]);
    if (rect > best_area) {
      best_area = rect;
      best_idx = i;
    }
  }

  return max({best_area, divide(prod_l, mid_prod_idx, cons_l, best_idx + 1),
              divide(mid_prod_idx + 1, prod_r, best_idx, cons_r)});
}

void solve() {
  vector<pii> producers(N), consumers(M);

  for (pii& p : producers) cin >> p.x >> p.y;
  for (pii& c : consumers) cin >> c.x >> c.y;

  sort(producers.begin(), producers.end());
  sort(consumers.rbegin(), consumers.rend());

  prod.clear();
  cons.clear();

  // TODO: Why does this work?
  // Is the lexicographic ordering correct?
  // Does the X coordinate mess it up?
  for (auto p : producers) {
    if (prod.empty() || p.y < prod.back().y) prod.push_back(p);
  }

  for (auto c : consumers) {
    if (cons.empty() || cons.back().y < c.y) cons.push_back(c);
  }

  reverse(cons.begin(), cons.end());

  cout << divide(0, prod.size(), 0, cons.size()) << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  while (cin >> N >> M) solve();
}
