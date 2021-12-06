#include <bits/stdc++.h>

using namespace std;

// https://dmoj.ca/problem/ioi09p3

struct Contestant {
  int id, solved, score;

  bool operator<(const Contestant& c) const {
    if (score == c.score) {
      if (solved == c.solved) return id < c.id;

      return solved > c.solved;
    }

    return score > c.score;
  }
};

int task_scores[2001];
short solutions[2001][2001];
Contestant contestants[2001];

int main() {
  int N, T, P;
  scanf("%d %d %d", &N, &T, &P);

  for (int i = 0; i < N; i++) {
    contestants[i].id = i + 1;
    for (int t = 0; t < T; t++) scanf("%hd", &solutions[i][t]);
  }

  for (int i = 0; i < N; i++)
    for (int t = 0; t < T; t++) task_scores[t] += !solutions[i][t];

  for (int i = 0; i < N; i++)
    for (int t = 0; t < T; t++)
      if (solutions[i][t]) {
        contestants[i].score += task_scores[t];
        contestants[i].solved++;
      }

  sort(contestants, contestants + N);

  for (int i = 0; i < N; i++)
    if (contestants[i].id == P) {
      printf("%d %d\n", contestants[i].score, i + 1);
      break;
    }
}
