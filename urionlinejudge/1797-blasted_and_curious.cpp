#include <bits/stdc++.h>

using namespace std;

#define MAX 1000003

int N, HAR;

double X[MAX], Y[MAX], S[MAX];

bool squares_aligned_x_aux(int i, int j) {
  double a = X[i] - S[i] / 2.0;
  double b = X[i] + S[i] / 2.0;
  double c = X[j] - S[j] / 2.0;
  double d = X[j] + S[j] / 2.0;
  return (c <= a && a <= d) || (c <= b && b <= d);
}

bool squares_aligned_y_aux(int i, int j) {
  double a = Y[i] - S[i] / 2.0;
  double b = Y[i] + S[i] / 2.0;
  double c = Y[j] - S[j] / 2.0;
  double d = Y[j] + S[j] / 2.0;
  return (c <= a && a <= d) || (c <= b && b <= d);
}

bool squares_aligned_x(int i, int j) {
  return squares_aligned_x_aux(i, j) || squares_aligned_x_aux(j, i);
}

bool squares_aligned_y(int i, int j) {
  return squares_aligned_y_aux(i, j) || squares_aligned_y_aux(j, i);
}

double point_dist(double x1, double y1, double x2, double y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void set_vertices(double (&vertices)[4][2], int i) {
  double half_side = S[i] / 2.0;

  double vert[][2] = {{X[i] - half_side, Y[i] - half_side},
                      {X[i] - half_side, Y[i] + half_side},
                      {X[i] + half_side, Y[i] - half_side},
                      {X[i] + half_side, Y[i] + half_side}};

  memcpy(vertices, vert, sizeof vert);
}

double square_dist(int i, int j) {
  double dist = DBL_MAX;

  if (squares_aligned_x(i, j))
    return fabs(Y[j] - Y[i]) - (S[i] / 2.0) - S[j] / 2.0;
  else if (squares_aligned_y(i, j))
    return fabs(X[j] - X[i]) - (S[i] / 2.0) - S[j] / 2.0;

  double vi[4][2], vj[4][2];
  set_vertices(vi, i);
  set_vertices(vj, j);

  for (int x = 0; x < 4; x++)
    for (int y = 0; y < 4; y++)
      dist = min(dist, point_dist(vi[x][0], vi[x][1], vj[y][0], vj[y][1]));

  return dist;
}

bool can_jump(int i, int j) {
  if (squares_aligned_y(i, j) && squares_aligned_x(i, j)) return true;

  if (square_dist(i, j) <= HAR) return true;

  return false;
}

bool possible() {
  for (int i = 0; i < N; i++) scanf("%lf %lf %lf", &X[i], &Y[i], &S[i]);

  for (int i = 0; i < N - 1; i++)
    if (!can_jump(i, i + 1)) return false;

  return true;
}

int main() {
  while (scanf("%d %d", &N, &HAR) == 2)
    cout << (possible() ? "YEAH" : "OUCH") << endl;
}
