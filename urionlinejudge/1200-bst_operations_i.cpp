#include <bits/stdc++.h>

using namespace std;

template <class T>
struct Node {
  T data;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;
  Node(T data) : data(data) {}
  ~Node() {
    if (left) delete left;
    if (right) delete right;
  }
};

void insert(Node<char>* tree, char c) {
  if (tree->data < c) {
    if (tree->right) {
      insert(tree->right, c);
    } else {
      tree->right = new Node<char>(c);
    }
  } else {
    if (tree->left) {
      insert(tree->left, c);
    } else {
      tree->left = new Node<char>(c);
    }
  }
}

vector<char> traversal;

bool search(Node<char>* tree, char c) {
  if (tree == nullptr) return false;
  if (tree->data == c) return true;
  bool search_left = search(tree->left, c);
  bool search_right = search(tree->right, c);
  return search_left || search_right;
}

void inorder(Node<char>* tree) {
  if (tree == nullptr) return;
  inorder(tree->left);
  traversal.push_back(tree->data);
  inorder(tree->right);
}

void preorder(Node<char>* tree) {
  if (tree == nullptr) return;
  traversal.push_back(tree->data);
  preorder(tree->left);
  preorder(tree->right);
}

void postorder(Node<char>* tree) {
  if (tree == nullptr) return;
  postorder(tree->left);
  postorder(tree->right);
  traversal.push_back(tree->data);
}

void print_traversal() {
  for (int i = 0; i < (int)traversal.size(); i++) {
    printf("%c%c", traversal[i], i < ((int)traversal.size() - 1) ? ' ' : '\n');
  }
}

int main() {
  Node<char> tree((char)0);

  string line;
  stringstream ss;

  while (getline(cin, line)) {
    ss = stringstream(line);

    while (!ss.eof()) {
      string first, second;
      ss >> first;

      if (first == "I") {
        ss >> second;
        if (tree.data == (char)0)
          tree.data = second[0];
        else
          insert(&tree, second[0]);
      } else if (first == "INFIXA") {
        traversal.clear();
        inorder(&tree);
        print_traversal();
      } else if (first == "PREFIXA") {
        traversal.clear();
        preorder(&tree);
        print_traversal();
      } else if (first == "POSFIXA") {
        traversal.clear();
        postorder(&tree);
        print_traversal();
      } else if (first == "P") {
        ss >> second;
        if (search(&tree, second[0]))
          printf("%c existe\n", second[0]);
        else
          printf("%c nao existe\n", second[0]);
      }
    }
  }
}
