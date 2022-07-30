#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
#define type first
#define arg second

enum { C, L, U };

struct Task {
  const int start_time;
  const int base_priority;
  int current_priority;
  int curr_ins = 0;

  vector<pii> instructions;

  Task(const int s, const int b, const int a)
      : start_time(s),
        base_priority(b),
        current_priority(b),
        instructions(vector<pii>(a)) {}

  pii& current_instruction() { return instructions[curr_ins]; }
  bool finished() const { return curr_ins == (int)instructions.size(); }
  bool running(const int clock) const { return start_time <= clock && !finished(); }
};

bitset<21> running_tasks;
array<int, 21> priority_ceilings;
vector<Task> tasks;
map<int, int> resource_own;
map<int, set<int>> blocks;

vector<Task> read_tasks(const int T) {
  vector<Task> tasks;

  for (int i = 0; i < T; i++) {
    int s, b, a;
    cin >> s >> b >> a;
    tasks.emplace_back(s, b, a);

    for (pii& instruction : tasks[i].instructions) {
      string ins;
      cin >> ins;
      const char type = ins.front();

      instruction.type = type == 'C' ? C : (type == 'L' ? L : U);

      ins[0] = ' ';

      stringstream ss(ins);
      ss >> instruction.arg;
    }
  }

  return tasks;
}

bool all_tasks_finished() {
  for (const Task& t : tasks) {
    if (!t.finished()) return false;
  }
  return true;
}

// TODO: Why does this work without recursion?
void update_priorities(const int i) {
  tasks[i].current_priority = tasks[i].base_priority;

  for (const int b : blocks[i])
    tasks[i].current_priority = max(tasks[i].current_priority, tasks[b].current_priority);
}

void set_blocked_tasks(const int clock) {
  bitset<21> res;

  blocks.clear();

  for (int i = 0; i < (int)tasks.size(); i++) {
    Task& t = tasks[i];

    if (!t.running(clock)) continue;
    res.set(i);

    const auto [type, k] = t.current_instruction();

    if (type == L) {
      for (const auto [r, idx] : resource_own) {
        if (idx == i) continue;

        if (k == r || priority_ceilings[r] >= t.current_priority) {
          res.set(i, false);
          blocks[idx].insert(i);
        }
      }
    }
  }

  running_tasks = res;
}

int highest_current_priority_task_idx() {
  int highest = -1;
  int idx = -1;
  for (int i = 0; i < (int)tasks.size(); i++) {
    if (!running_tasks[i]) continue;

    if (highest < tasks[i].current_priority) {
      highest = tasks[i].current_priority;
      idx = i;
    }
  }

  return idx;
}

void calculate_priority_ceilings() {
  fill(priority_ceilings.begin(), priority_ceilings.end(), 0);

  for (const Task& t : tasks) {
    for (const auto& [type, r] : t.instructions) {
      if (type != L) continue;

      priority_ceilings[r] = max(priority_ceilings[r], t.base_priority);
    }
  }
}

int main() {
  int T, R;

  while (cin >> T >> R) {
    tasks = read_tasks(T);
    vector<int> ans(T);

    calculate_priority_ceilings();

    int clock = 0;

    resource_own.clear();

    while (!all_tasks_finished()) {
      set_blocked_tasks(clock);

      for (int i = 0; i < (int)tasks.size(); i++) {
        update_priorities(i);
      }

      if (running_tasks.none()) {
        clock++;
        continue;
      }

      const int idx = highest_current_priority_task_idx();
      Task& task = tasks[idx];

      pii& ins = task.current_instruction();

      switch (ins.type) {
        case C:
          clock++;
          ins.arg--;
          break;
        case L:
          resource_own[ins.arg] = idx;
          break;
        case U:
          resource_own.erase(ins.arg);
          break;
      }

      task.curr_ins += (ins.type == C && ins.arg == 0) || ins.type != C;

      if (task.finished()) {
        ans[idx] = clock;
      }
    }

    for (const int a : ans) {
      cout << a << '\n';
    }
  }
}
