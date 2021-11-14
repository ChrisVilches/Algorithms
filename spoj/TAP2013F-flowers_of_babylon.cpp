#include <bits/stdc++.h>

using namespace std;

typedef complex<double> Point;

#define MAX_POINTS 501

double dis[MAX_POINTS][MAX_POINTS];

vector<Point> points;

bool cmp(pair<double, bool> A, pair<double, bool> B) {
  if (A.first < B.first)
    return true;
  else if (A.first > B.first)
    return false;
  else
    return (A.second == 1);
}

int points_inside(int i, double r) {
  vector<pair<double, bool>> angles;

  for (int j = 0; j < (int)points.size(); j++) {
    if (i != j && dis[i][j] <= 2 * r) {
      double B = acos(dis[i][j] / (2 * r));
      double A = arg(points[j] - points[i]);
      double alpha = A - B;
      double beta = A + B;
      angles.push_back(make_pair(alpha, true));
      angles.push_back(make_pair(beta, false));
    }
  }

  sort(angles.begin(), angles.end(), cmp);

  int count = 1, res = 1;

  vector<pair<double, bool>>::iterator it;
  for (it = angles.begin(); it != angles.end(); ++it) {
    if ((*it).second)
      count++;
    else
      count--;
    if (count > res) res = count;
  }

  return res;
}

int max_points(double r) {
  for (int i = 0; i < (int)points.size() - 1; i++)
    for (int j = i + 1; j < (int)points.size(); j++)
      dis[i][j] = dis[j][i] = abs(points[i] - points[j]);
  int ans = 0;
  for (int i = 0; i < (int)points.size(); i++)
    ans = max(ans, points_inside(i, r));
  return ans;
}

void solve() {
  int N, P;
  cin >> N >> P;

  points.clear();

  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    Point p(x, y);
    points.push_back(p);
  }

  int iters = 50;
  double left = 0;
  double right = 150000;

  while (iters--) {
    double mid = (left + right) / 2;

    if (max_points(mid) < P)
      left = mid;
    else
      right = mid;
  }
  printf("%.4f\n", left);
}

int main() {
  int T;
  cin >> T;
  while (T--) solve();
}
