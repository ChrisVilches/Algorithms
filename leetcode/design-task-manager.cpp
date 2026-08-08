#include <bits/stdc++.h>
using namespace std;

class TaskManager {
  using tiii = tuple<int, int, int>;
  unordered_map<int, tiii> task_map;
  set<tiii> s;

 public:
  TaskManager(const vector<vector<int>>& tasks) {
    for (const vector<int>& task : tasks) {
      add(task[0], task[1], task[2]);
    }
  }

  void add(const int user_id, const int task_id, const int priority) {
    const auto [it, ok] = s.emplace(priority, task_id, user_id);
    assert(ok);
    task_map[task_id] = *it;
  }

  void edit(const int task_id, const int new_priority) {
    const int user_id = get<2>(task_map[task_id]);
    rmv(task_id);
    add(user_id, task_id, new_priority);
  }

  void rmv(const int task_id) { s.erase(task_map[task_id]); }

  int execTop() {
    if (s.empty()) return -1;

    const int user_id = get<2>(*s.rbegin());
    s.erase(prev(s.end()));
    return user_id;
  }
};
