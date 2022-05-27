#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 50'007;

template <typename T>
class SegmentTree2D {
  int H, W;
  vector<T> seg;
  const T neutral_value = 0;
  T f(const T a, const T b) const { return max(a, b); }

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
        seg[id(h, w)] = f(seg[id(2 * h + 0, w)], seg[id(2 * h + 1, w)]);

    for (int h = 0; h < 2 * H; h++)
      for (int w = W - 1; w; w--)
        seg[id(h, w)] = f(seg[id(h, 2 * w + 0)], seg[id(h, 2 * w + 1)]);
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
      seg[id(i, w)] = f(seg[id(2 * i + 0, w)], seg[id(2 * i + 1, w)]);

    for (; h; h >>= 1)
      for (int j = w >> 1; j; j >>= 1)
        seg[id(h, j)] = f(seg[id(h, 2 * j + 0)], seg[id(h, 2 * j + 1)]);
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

int X[MAX_N], Y[MAX_N];
bool has_parent[MAX_N];
SegmentTree2D<int> segtree(801, 801);
vector<vector<int>> tree;
int ans = 0;

void dfs(const int u) {
  const int new_value = 1 + segtree.query(0, 0, Y[u] - 1, X[u] - 1);

  ans = max(ans, new_value);

  if (tree[u].empty()) return;

  segtree.update(Y[u], X[u], new_value);

  for_each(tree[u].begin(), tree[u].end(), dfs);

  segtree.update(Y[u], X[u], 0);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  cin >> N >> M;

  for (int i = 0; i < N; i++) {
    cin >> X[i] >> Y[i];
    X[i] += 400;
    Y[i] += 400;
  }

  tree.resize(N);

  for (int i = 0; i < M; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    has_parent[u] = true;
    tree[v].push_back(u);
  }

  for (int i = 0; i < N; i++) {
    if (has_parent[i]) continue;
    dfs(i);
  }

  cout << ans << endl;
}
