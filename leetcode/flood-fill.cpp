#include <bits/stdc++.h>
using namespace std;

class Solution {
  using vii = vector<vector<int>>;
  int n, m;
  const int di[4]{-1, 1, 0, 0};
  const int dj[4]{0, 0, -1, 1};

  void dfs(vii& image, const int i, const int j, const int from, const int to) {
    if (from == to) return;
    if (image[i][j] != from) return;

    image[i][j] = to;

    for (int d = 0; d < 4; d++) {
      const int i2 = i + di[d];
      const int j2 = j + dj[d];
      if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;

      dfs(image, i2, j2, from, to);
    }
  }

 public:
  vii floodFill(vii& image, int sr, int sc, int color) {
    n = image.size();
    m = image.front().size();
    dfs(image, sr, sc, image[sr][sc], color);
    return image;
  }
};
