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

int T, R;
bitset<21> running_tasks;
array<int, 21> ans, priority_ceilings, resource_own;
vector<Task> tasks;
map<int, set<int>> blocks;

void read_tasks() {
  tasks.clear();

  for (int i = 0; i < T; i++) {
    int s, b, a;
    scanf("%d%d%d", &s, &b, &a);

    tasks.emplace_back(s, b, a);

    for (pii& ins : tasks[i].instructions) {
      char c;
      scanf(" %c%d", &c, &ins.arg);
      ins.type = c == 'C' ? C : (c == 'L' ? L : U);
    }
  }
}

bool all_tasks_finished() {
  for (const Task& t : tasks) {
    if (!t.finished()) return false;
  }
  return true;
}

void update_priorities(const int i) {
  tasks[i].current_priority = tasks[i].base_priority;

  for (const int b : blocks[i])
    tasks[i].current_priority = max(tasks[i].current_priority, tasks[b].current_priority);
}

void set_blocked_tasks(const int clock) {
  running_tasks = 0;
  blocks.clear();

  for (int i = 0; i < T; i++) {
    Task& t = tasks[i];

    if (!t.running(clock)) continue;
    running_tasks.set(i);

    const auto [type, k] = t.current_instruction();
    if (type != L) continue;

    for (int r = 0; r <= R; r++) {
      const int idx = resource_own[r];
      if (idx == -1 || idx == i) continue;

      if (k == r || priority_ceilings[r] >= t.current_priority) {
        running_tasks.set(i, false);
        blocks[idx].insert(i);
      }
    }
  }
}

int highest_current_priority_task_idx() {
  int highest = -1;
  int idx = -1;
  for (int i = 0; i < T; i++) {
    if (!running_tasks[i]) continue;

    if (highest < tasks[i].current_priority) {
      highest = tasks[i].current_priority;
      idx = i;
    }
  }

  return idx;
}

void initialize_resources() {
  fill(resource_own.begin(), resource_own.end(), -1);
  fill(priority_ceilings.begin(), priority_ceilings.end(), 0);

  for (const Task& t : tasks) {
    for (const auto& [type, r] : t.instructions) {
      if (type != L) continue;

      priority_ceilings[r] = max(priority_ceilings[r], t.base_priority);
    }
  }
}

int main() {
  while (scanf("%d%d", &T, &R) == 2) {
    read_tasks();
    initialize_resources();

    int clock = 0;

    while (!all_tasks_finished()) {
      set_blocked_tasks(clock);

      for (int i = 0; i < T; i++) {
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
          resource_own[ins.arg] = -1;
          break;
      }

      task.curr_ins += (ins.type == C && ins.arg == 0) || ins.type != C;

      if (task.finished()) {
        ans[idx] = clock;
      }
    }

    for (int i = 0; i < T; i++) {
      printf("%d\n", ans[i]);
    }
  }
}
