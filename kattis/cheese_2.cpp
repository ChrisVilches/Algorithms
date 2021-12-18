#include <bits/stdc++.h>
using namespace std;
int N, S;

struct Sphere {
  double r, x, y, z;
  double volume() const { return 4 * M_PI * pow(r, 3) / 3; }

  double partial_volume(double z0) {
    if (z0 <= z) {
      double min_z = z - r;
      z0 = max(z0, min_z);
      return cap(z0 - min_z);
    } else {
      double max_z = z + r;
      z0 = min(z0, max_z);
      return volume() - cap(max_z - z0);
    }
  }

 private:
  // https://en.wikipedia.org/wiki/Spherical_cap
  double cap(double h) { return (M_PI * h * h / 3) * (3 * r - h); }
} holes[10'007];

double cheese_volume(double z) {
  double total = 1e15 * z / 100000;
  for (int i = 0; i < N; i++) total -= holes[i].partial_volume(z);
  return total;
}

int main() {
  scanf("%d %d", &N, &S);

  for (int i = 0; i < N; i++)
    scanf("%lf %lf %lf %lf", &holes[i].r, &holes[i].x, &holes[i].y, &holes[i].z);

  double full_volume = 1e15;

  for (int i = 0; i < N; i++) full_volume -= holes[i].volume();

  const double one_slice = full_volume / S;

  double prev_partition = 0;

  for (int i = 1; i <= S; i++) {
    double left = 0;
    double right = 100000;
    const double required = one_slice * i;

    while (right - left > 1e-7) {
      double mid = (right + left) / 2;
      if (cheese_volume(mid) < required)
        left = mid;
      else
        right = mid;
    }

    printf("%.9f\n", (left - prev_partition) / 1000);
    prev_partition += left - prev_partition;
  }
}
