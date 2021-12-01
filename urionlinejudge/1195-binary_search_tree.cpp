#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node() {}
  Node(int v) : value(v) {}
  ~Node() {
    if (left) delete (left);
    if (right) delete (right);
  }

  void insert(int v) {
    if (v < value) {
      if (left) {
        left->insert(v);
      } else {
        left = new Node(v);
      }
    } else {
      if (right) {
        right->insert(v);
      } else {
        right = new Node(v);
      }
    }
  }

  void pre(vector<int>& result) {
    result.push_back(value);
    if (left) left->pre(result);
    if (right) right->pre(result);
  }

  void in(vector<int>& result) {
    if (left) left->in(result);
    result.push_back(value);
    if (right) right->in(result);
  }

  void post(vector<int>& result) {
    if (left) left->post(result);
    if (right) right->post(result);
    result.push_back(value);
  }
};

void print_result(vector<int>& result) {
  for (int i = 0; i < (int)result.size(); i++) {
    if (i > 0) cout << ' ';
    cout << result[i];
  }
  cout << endl;
}

void solve() {
  int N;
  cin >> N;

  Node root;
  cin >> root.value;

  for (int i = 1; i < N; i++) {
    int v;
    cin >> v;
    root.insert(v);
  }

  vector<int> pre, in, post;
  root.pre(pre);
  root.in(in);
  root.post(post);

  printf("Pre.: ");
  print_result(pre);

  printf("In..: ");
  print_result(in);

  printf("Post: ");
  print_result(post);
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    printf("Case %d:\n", i + 1);
    solve();
    cout << endl;
  }
}
