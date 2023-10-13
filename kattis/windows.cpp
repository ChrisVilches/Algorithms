#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

struct Window {
  int top, left, bottom, right, idx;

  Window(const int x, const int y, const int w, const int h, const int idx)
      : top(y + h), left(x), bottom(y), right(x + w), idx(idx) {}

  bool operator<(const Window& w) const { return idx < w.idx; }

  bool vertical_overlap(const Window& w) const {
    return w.bottom < top && bottom < w.top;
  }

  bool horizontal_overlap(const Window& w) const {
    return w.left < right && left < w.right;
  }

  void set_left(const int x) {
    const int w = right - left;
    left = x;
    right = x + w;
  }

  bool point_inside(const int x0, const int y0) const {
    return left <= x0 && x0 < right && bottom <= y0 && y0 < top;
  }
};

int width, height, cmd_idx;
vector<Window> windows;

void rotate_windows() {
  for (auto& w : windows) {
    w = Window{-w.top + height, w.left, w.top - w.bottom, w.right - w.left, w.idx};
  }
}

vector<Window>::iterator search_window(const int x, const int y) {
  return find_if(windows.begin(), windows.end(),
                 [x, y](const Window& w) { return w.point_inside(x, y); });
}

bool window_fits(const Window& window) {
  for (const Window& w : windows) {
    if (w.horizontal_overlap(window) && w.vertical_overlap(window)) return false;
  }
  return window.right <= width && window.top <= height;
}

void log(const string msg) { cout << "Command " << cmd_idx << ": " << msg << endl; }

void open(const int x, const int y, const int w, const int h) {
  const Window new_window{x, y, w, h, cmd_idx};
  if (!window_fits(new_window)) {
    log("OPEN - window does not fit");
  } else {
    windows.push_back(new_window);
  }
}

void resize(const int x, const int y, const int w, const int h) {
  const auto it = search_window(x, y);
  if (it == windows.end()) {
    log("RESIZE - no window at given position");
    return;
  }
  const Window prev_window = *it;
  windows.erase(it);
  const Window new_window{prev_window.left, prev_window.bottom, w, h, prev_window.idx};
  if (!window_fits(new_window)) {
    log("RESIZE - window does not fit");
    windows.push_back(prev_window);
  } else {
    windows.push_back(new_window);
  }
}

void move(const int window_idx, const int shift) {
  if (window_idx == -1) {
    log("MOVE - no window at given position");
    return;
  }

  sort(windows.begin(), windows.end(),
       [](const Window& w1, const Window& w2) { return w1.left < w2.left; });

  const auto it = find_if(windows.begin(), windows.end(),
                          [&](const Window& w) { return w.idx == window_idx; });

  const auto x0 = it->left;

  unordered_map<int, int> prev_pos;

  int min_y = it->bottom;
  int max_y = it->top;

  for (int i = 0; i < (int)windows.size(); i++) {
    if (windows[i].left < it->left) continue;
    if (windows[i].top <= min_y || max_y <= windows[i].bottom) continue;

    prev_pos[i] = windows[i].left;

    int min_x = INT_MIN;

    for (int j = 0; j < i; j++) {
      if (!windows[i].vertical_overlap(windows[j])) continue;
      if (!prev_pos.count(j)) continue;

      min_x = max(min_x, windows[j].right);
    }

    if (min_x != INT_MIN) {
      windows[i].set_left(min_x);
      min_y = min(min_y, windows[i].bottom);
      max_y = max(max_y, windows[i].top);
    }
  }

  int overflow = 0;

  for (const auto& [i, _] : prev_pos) {
    windows[i].set_left(windows[i].left + shift);
    overflow = max(overflow, windows[i].right - width);
  }

  for (const auto& [i, p] : prev_pos) {
    windows[i].set_left(max(windows[i].left - overflow, p));
  }

  const int actual_shift = abs(it->left - x0);
  if (actual_shift != shift) {
    stringstream ss;
    ss << "MOVE - moved " << actual_shift << " instead of " << shift;
    log(ss.str());
  }
}

void close(const int x, const int y) {
  const auto it = search_window(x, y);
  if (it == windows.end()) {
    log("CLOSE - no window at given position");
  } else {
    windows.erase(it);
  }
}

int main() {
  while (cin >> width >> height) {
    cmd_idx = 0;
    windows.clear();
    string cmd;
    while (cin >> cmd) {
      cmd_idx++;
      int x, y, a, b;

      if (cmd == "CLOSE") {
        cin >> x >> y;
        close(x, y);
        continue;
      }

      cin >> x >> y >> a >> b;

      if (cmd == "OPEN") open(x, y, a, b);
      if (cmd == "RESIZE") resize(x, y, a, b);
      if (cmd == "MOVE") {
        const auto it = search_window(x, y);

        int rotate_times = 0;
        for (; a <= 0; rotate_times++) {
          swap(a, b);
          a *= -1;

          rotate_windows();
          swap(width, height);
        }

        move(it == windows.end() ? -1 : it->idx, a);

        for (int r = 0; r < 4 - rotate_times; r++) {
          rotate_windows();
          swap(width, height);
        }
      }
    }

    sort(windows.begin(), windows.end());
    cout << windows.size() << " window(s):" << endl;
    for (const Window& window : windows) {
      const int w = window.right - window.left;
      const int h = window.top - window.bottom;
      cout << window.left << " " << window.bottom << " " << w << " " << h << endl;
    }
  }
}
