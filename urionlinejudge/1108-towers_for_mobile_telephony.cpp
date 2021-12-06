#include <bits/stdc++.h>

using namespace std;

typedef complex<double> Point;
typedef long long ll;

#define MAX 40

double dis[MAX][MAX];
Point points[MAX];
int N;

inline bool cmp(tuple<double, bool, int>& A, tuple<double, bool, int>& B) {
  if (get<0>(A) < get<0>(B))
    return true;
  else if (get<0>(A) > get<0>(B))
    return false;
  else
    return get<1>(A);
}

void points_inside(int i, double r, unordered_set<ll>& out) {
  ll covered = 1LL << i;
  out.insert(covered);

  vector<tuple<double, bool, int>> angles;

  for (int j = 0; j < N; j++) {
    if (i != j && dis[i][j] <= 2 * r) {
      double B = acos(dis[i][j] / (2 * r));
      double A = arg(points[j] - points[i]);
      double alpha = A - B;
      double beta = A + B;
      angles.push_back(make_tuple(alpha, true, j));
      angles.push_back(make_tuple(beta, false, j));
    }
  }

  sort(angles.begin(), angles.end(), cmp);

  bool enter;
  int point_idx;

  for (tuple<double, bool, int>& a : angles) {
    enter = get<1>(a);
    point_idx = get<2>(a);

    if (enter)
      covered |= (1LL << point_idx);
    else
      covered &= ~(1LL << point_idx);

    out.emplace(covered);
  }
}

unordered_set<ll> all_subsets;

bool covers_all_points(double r) {
  int subsets_size;
  all_subsets.clear();

  ll all_bits = (1LL << N) - 1;

  for (int i = 0; i < N; i++) points_inside(i, r, all_subsets);

  vector<ll> subsets(all_subsets.begin(), all_subsets.end());

  subsets_size = (int)subsets.size();

  for (int i = 0; i < subsets_size; i++)
    for (int j = i + 1; j < subsets_size; j++)
      if ((subsets[i] | subsets[j]) == all_bits) return true;

  return false;
}

void solve() {
  int x, y;
  double left = 0;
  double right = 5500;
  double mid;

  for (int i = 0; i < N; i++) {
    scanf("%d %d", &x, &y);
    points[i] = Point(x, y);
  }

  for (int i = 0; i < N; i++)
    for (int j = i + 1; j < N; j++)
      dis[i][j] = dis[j][i] = fabs(points[i] - points[j]);

  while (right - left > 0.0003) {
    mid = (right + left) / 2;

    if (covers_all_points(mid))
      right = mid;
    else
      left = mid;
  }

  printf("%.2f\n", left);
}

int main() {
  while (scanf("%d", &N) == 1 && N > 0) solve();
}
