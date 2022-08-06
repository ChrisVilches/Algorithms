#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree2D {
  int H, W;
  vector<T> seg;
  const T neutral_value = 0;
  T f(const T a, const T b) const { return a + b; }

  int id(int h, int w) { return h * 2 * W + w; }

  void init(int h, int w) {
    H = W = 1;
    while (H < h) H <<= 1;
    while (W < w) W <<= 1;
    seg.assign(4 * H * W, neutral_value);
  }

  void set(int h, int w, const T& x) { seg[id(h + H, w + W)] = x; }

  void build() {
    for (int w = W; w < 2 * W; w++)
      for (int h = H - 1; h; h--)
        seg[id(h, w)] = f(seg[id(2 * h, w)], seg[id(2 * h + 1, w)]);

    for (int h = 0; h < 2 * H; h++)
      for (int w = W - 1; w; w--)
        seg[id(h, w)] = f(seg[id(h, 2 * w)], seg[id(h, 2 * w + 1)]);
  }

  T query(int h, int w1, int w2) {
    T res = neutral_value;
    for (; w1 < w2; w1 >>= 1, w2 >>= 1) {
      if (w1 & 1) res = f(res, seg[id(h, w1)]), w1++;
      if (w2 & 1) --w2, res = f(res, seg[id(h, w2)]);
    }
    return res;
  }

 public:
  SegmentTree2D(int h, int w) { init(h, w); }

  void update(int h, int w, const T& x) {
    h += H, w += W;
    seg[id(h, w)] = x;
    for (int i = h >> 1; i; i >>= 1)
      seg[id(i, w)] = f(seg[id(2 * i, w)], seg[id(2 * i + 1, w)]);

    for (; h; h >>= 1)
      for (int j = w >> 1; j; j >>= 1)
        seg[id(h, j)] = f(seg[id(h, 2 * j)], seg[id(h, 2 * j + 1)]);
  }

  T query(int h1, int w1, int h2, int w2) {
    h2++, w2++;
    if (h1 >= h2 || w1 >= w2) return neutral_value;
    T res = neutral_value;
    h1 += H, h2 += H, w1 += W, w2 += W;
    for (; h1 < h2; h1 >>= 1, h2 >>= 1) {
      if (h1 & 1) res = f(res, query(h1, w1, w2)), h1++;
      if (h2 & 1) --h2, res = f(res, query(h2, w1, w2));
    }
    return res;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, Q;
  cin >> N >> Q;

  SegmentTree2D<int> segtree(N, N);

  for (int i = 0; i < N; i++) {
    string line;
    cin >> line;

    for (int j = 0; j < N; j++)
      if (line[j] == '*') segtree.update(i, j, 1);
  }

  while (Q--) {
    int type, y, x;
    int y1, x1, y2, x2;

    cin >> type;

    switch (type) {
      case 1:
        cin >> y >> x;
        y--;
        x--;
        segtree.update(y, x, !segtree.query(y, x, y, x));
        break;
      case 2:
        cin >> y1 >> x1 >> y2 >> x2;
        y1--;
        x1--;
        y2--;
        x2--;

        cout << segtree.query(y1, x1, y2, x2) << '\n';
        break;
    }
  }
}
