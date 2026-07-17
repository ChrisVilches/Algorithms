#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int scheduleCourse(const vector<vector<int>>& input) {
    vector<pair<int, int>> courses;

    for (const auto& course : input) {
      courses.emplace_back(course.back(), course.front());
    }

    priority_queue<int> pq;
    int total_time = 0;

    sort(courses.begin(), courses.end());

    for (const auto& [last, duration] : courses) {
      if (total_time + duration > last) {
        if (!pq.empty() && duration < pq.top()) {
          const int removed = pq.top();
          pq.pop();
          pq.emplace(duration);
          total_time += duration - removed;
        }
      } else {
        total_time += duration;
        pq.emplace(duration);
      }
    }

    return pq.size();
  }
};
