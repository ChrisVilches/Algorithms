#include <bits/stdc++.h>
using namespace std;

class Solution {
  vector<int> tree;

  int first_gte(int v, int lv, int rv, int bound, int x, bool forward) {
    if ((forward && rv < bound) || (!forward && lv > bound)) return -1;
    if (tree[v] < x) return -1;
    if (lv == rv) return lv;

    const int mid = (lv + rv) / 2;

    if (forward) {
      if (bound <= mid && tree[v << 1] >= x) {
        const int res = first_gte(v << 1, lv, mid, bound, x, forward);
        if (res != -1) return res;
      }
      return first_gte((v << 1) + 1, mid + 1, rv, bound, x, forward);
    } else {
      if (bound >= mid + 1 && tree[(v << 1) + 1] >= x) {
        const int res = first_gte((v << 1) + 1, mid + 1, rv, bound, x, forward);
        if (res != -1) return res;
      }
      return first_gte(v << 1, lv, mid, bound, x, forward);
    }
  }

  void update(int v, int L, int R, int i, int x) {
    if (L == R) {
      tree[v] = x;
    } else {
      const int m = (L + R) / 2;
      if (i <= m)
        update(v << 1, L, m, i, x);
      else
        update((v << 1) + 1, m + 1, R, i, x);
      tree[v] = max(tree[v << 1], tree[(v << 1) + 1]);
    }
  }

 public:
  vector<int> closestRoom(vector<vector<int>>& rooms,
                          const vector<vector<int>>& queries) {
    unordered_set<int> room_ids;
    for (const auto& r : rooms) room_ids.emplace(r.front());

    for (const auto& q : queries) {
      const int room_id = q.front();
      if (!room_ids.count(room_id)) {
        rooms.push_back({room_id, 0});
        room_ids.emplace(room_id);
      }
    }

    sort(rooms.begin(), rooms.end());

    const int n = rooms.size();
    tree.resize(4 * n);

    for (size_t i = 0; i < rooms.size(); i++) {
      update(1, 0, n - 1, i, rooms[i].back());
    }

    unordered_map<int, int> id_map;

    for (const auto& r : rooms) {
      id_map[r.front()] = id_map.size();
    }

    vector<int> ans;

    for (const auto& q : queries) {
      const int preferred = q.front();
      const int min_size = q.back();

      const int idx = id_map[preferred];

      const int left = first_gte(1, 0, n - 1, idx, min_size, false);
      const int right = first_gte(1, 0, n - 1, idx, min_size, true);

      if (left == -1) {
        ans.emplace_back(right);
      } else if (right == -1) {
        ans.emplace_back(left);
      } else {
        const int leftd = abs(preferred - rooms[left].front());
        const int rightd = abs(preferred - rooms[right].front());
        if (leftd <= rightd) {
          ans.emplace_back(left);
        } else {
          ans.emplace_back(right);
        }
      }
    }

    for (auto& x : ans) x = x == -1 ? -1 : rooms[x].front();

    return ans;
  }
};
