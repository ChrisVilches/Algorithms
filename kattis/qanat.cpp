#include <bits/stdc++.h>
using namespace std;

double cost(const double x) { return x * x / 2; }

int main() {
  cout << fixed << setprecision(6);
  double W, H;
  int N;

  while (cin >> W >> H >> N) {
    vector<double> shafts{0, 1};

    const double factor = pow(H / W, 2);
    double total_cost = 0;

    while (N--) {
      double shaft_x = 2 * shafts.back();
      shaft_x /= (1 - factor);
      shaft_x -= shafts[shafts.size() - 2];
      shafts.push_back(shaft_x);
    }

    for (double& s : shafts) s *= W / shafts.back();

    for (int i = 1; i < (int)shafts.size(); i++) {
      const double prev_shaft_height = shafts[i - 1] * (H / W);
      const double curr_shaft_height = shafts[i] * (H / W);
      const double ground = shafts[i] - shafts[i - 1];

      const double length = prev_shaft_height + ground + curr_shaft_height;
      const double half_length = length / 2;

      total_cost += cost(half_length) * 2;
      total_cost -= cost(prev_shaft_height);
    }

    cout << total_cost << '\n';

    for (int i = 1; i < (int)shafts.size() - 1 && i <= 10; i++) {
      cout << shafts[i] << '\n';
    }
  }
}
