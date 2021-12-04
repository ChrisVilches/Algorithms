#include <bits/stdc++.h>

using namespace std;

/*
Micro-optimized.
*/

void print(uint32_t n) {
  if (n / 10) print(n / 10);
  putchar_unlocked(n % 10 + '0');
}

char r;
bool start = false;
uint32_t ret = 0;

uint32_t read_int() {
  start = false;
  ret = 0;
  while (true) {
    r = getchar_unlocked();
    if ((r - '0' < 0 || r - '0' > 9) && !start) {
      continue;
    }
    if ((r - '0' < 0 || r - '0' > 9) && start) {
      break;
    }
    if (start) ret *= 10;
    start = true;
    ret += r - '0';
  }
  return ret;
}

struct Point {
  int x, y;
  Point() {}

  inline bool operator<(const Point& p) const {
    return (y == p.y && x < p.x) || y < p.y;
  }
};

struct Segment {
  Point p, q;
  inline int from() const { return p.x < q.x ? p.x : q.x; }
  inline int to() const { return p.x < q.x ? q.x : p.x; }
  inline Point exit() const { return p.y > q.y ? p : q; }
};

const int MAX = 100001;
int N, Q;

Point queries[MAX];
Segment segments[MAX];
bool segment_visited[MAX];
pair<int, int> removed[MAX];
pair<Point, int> events[2 * MAX];
int parent[MAX];

set<pair<int, int>> queries_set;

void disjoint_set_initialize(int n) {
  for (int i = 0; i < n; i++) parent[i] = i;
}

int find(int u) {
  if (u != parent[u]) parent[u] = find(parent[u]);
  return parent[u];
}

void merge(int x, int y) { parent[find(x)] = find(y); }

void read_data() {
  for (int i = 0; i < N; i++) {
    segments[i].p.x = read_int();
    segments[i].p.y = read_int();
    segments[i].q.x = read_int();
    segments[i].q.y = read_int();
  }

  for (int i = 0; i < Q; i++) {
    queries[i].x = read_int();
    queries[i].y = -1;
    queries_set.emplace(make_pair(queries[i].x, i));
  }
}

void sweep_line() {
  int ev_n = 0, rem_n, segment_idx;
  pair<int, int> q, lower_bnd = make_pair(0, -1);

  for (int i = 0; i < N; i++) {
    events[ev_n++] = make_pair(segments[i].p, i);
    events[ev_n++] = make_pair(segments[i].q, i);
  }

  sort(events, events + ev_n);

  for (int i = 0; i < ev_n; i++) {
    segment_idx = events[i].second;

    if (!segment_visited[segment_idx]) {
      segment_visited[segment_idx] = true;
      continue;
    }

    Segment& segment = segments[segment_idx];

    rem_n = 0;
    lower_bnd.first = segment.from();

    while (!queries_set.empty()) {
      auto it = queries_set.lower_bound(lower_bnd);

      if (it == queries_set.end()) break;
      if (segment.to() < it->first) break;

      q = *it;

      if (segment.p.y != segment.q.y) {
        q.first = segment.exit().x;
        queries[q.second].x = segment.exit().x;
        removed[rem_n++] = q;
      } else {
        queries[q.second].y = segment.p.y;
      }
      queries_set.erase(it);
    }

    if (rem_n == 0) continue;

    for (int i = 1; i < rem_n; i++) merge(removed[i].second, removed[0].second);

    queries_set.emplace(removed[0]);
  }
}

void print_result() {
  Point q;

  for (int i = 0; i < Q; i++) {
    q = queries[find(i)];

    print(q.x);

    if (~q.y) {
      putchar_unlocked(' ');
      print(q.y);
    }

    putchar_unlocked('\n');
  }
}

int main() {
  while (scanf("%d %d", &N, &Q) == 2) {
    queries_set.clear();
    disjoint_set_initialize(Q);
    memset(segment_visited, 0, sizeof segment_visited);

    read_data();
    sweep_line();
    print_result();
  }
}
