#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

#define x first
#define y second

vector<pii> producers, consumers;

ll area(const pii& producer, const pii& consumer) {
  if (!(producer.x < consumer.x && producer.y < consumer.y)) return 0;
  return (consumer.y - producer.y) * (consumer.x - producer.x);
}

ll divide(const int prod_l, const int prod_r, const int cons_l, const int cons_r) {
  if (prod_l == prod_r) return 0;

  const int prod_m = (prod_l + prod_r) / 2;

  ll max_area = 0;
  int cons_m = -1;

  for (int i = cons_l; i < cons_r && i < (int)consumers.size(); i++) {
    const ll rect = area(producers[prod_m], consumers[i]);

    if (rect > max_area || (cons_m == -1 && producers[prod_m].x <= consumers[i].x)) {
      max_area = rect;
      cons_m = i;
    }
  }

  if (cons_m == -1) return 0;
  return max({max_area, divide(prod_l, prod_m, cons_l, cons_m + 1),
              divide(prod_m + 1, prod_r, cons_m, cons_r)});
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;

  while (cin >> N >> M) {
    producers.resize(N);
    consumers.resize(M);

    for (pii& p : producers) cin >> p.x >> p.y;
    for (pii& c : consumers) cin >> c.x >> c.y;

    sort(producers.begin(), producers.end());
    sort(consumers.rbegin(), consumers.rend());

    int i = 0;
    for (auto p : producers)
      if (i == 0 || p.y < producers[i - 1].y) producers[i++] = p;
    producers.resize(i);

    i = 0;
    for (auto c : consumers)
      if (i == 0 || consumers[i - 1].y < c.y) consumers[i++] = c;
    consumers.resize(i);

    reverse(consumers.begin(), consumers.end());

    cout << divide(0, producers.size(), 0, consumers.size()) << endl;
  }
}
