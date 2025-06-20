#include <bits/stdc++.h>
using namespace std;

class Node {
 public:
  bool val;
  bool isLeaf;
  Node* topLeft;
  Node* topRight;
  Node* bottomLeft;
  Node* bottomRight;

  Node(bool _val, bool _isLeaf) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = NULL;
    topRight = NULL;
    bottomLeft = NULL;
    bottomRight = NULL;
  }

  Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft,
       Node* _bottomRight) {
    val = _val;
    isLeaf = _isLeaf;
    topLeft = _topLeft;
    topRight = _topRight;
    bottomLeft = _bottomLeft;
    bottomRight = _bottomRight;
  }
};

class Solution {
  vector<vector<int>> grid;
  int n;

  bool all_same(const int i1, const int j1, const int i2, const int j2) {
    const int val = grid[i1][j1];
    for (int i = i1; i < i2; i++) {
      for (int j = j1; j < j2; j++) {
        if (grid[i][j] != val) return false;
      }
    }
    return true;
  }

  Node* aux(const int i1, const int j1, const int i2, const int j2) {
    if (all_same(i1, j1, i2, j2)) return new Node(grid[i1][j1], true);

    const array<int, 3> i{i1, (i1 + i2) / 2, i2};
    const array<int, 3> j{j1, (j1 + j2) / 2, j2};

    Node* top_left = aux(i[0], j[0], i[1], j[1]);
    Node* top_right = aux(i[0], j[1], i[1], j[2]);
    Node* bottom_left = aux(i[1], j[0], i[2], j[1]);
    Node* bottom_right = aux(i[1], j[1], i[2], j[2]);
    return new Node(-1, false, top_left, top_right, bottom_left, bottom_right);
  }

 public:
  Node* construct(const vector<vector<int>>& input_grid) {
    this->grid = input_grid;
    this->n = grid.size();
    return aux(0, 0, n, n);
  }
};
