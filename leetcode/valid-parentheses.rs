use std::collections::HashMap;

impl Solution {
  pub fn is_valid(s: String) -> bool {
    let mut right_to_left = HashMap::new();

    right_to_left.insert('}', '{');
    right_to_left.insert(']', '[');
    right_to_left.insert(')', '(');

    let mut stack = vec![];

    for c in s.chars() {
      if c == '(' || c == '{' || c == '[' {
        stack.push(c);
        continue;
      }

      if stack.is_empty() {
        return false;
      }

      if *stack.last().unwrap() != right_to_left[&c] {
        return false;
      }

      stack.pop();
    }

    stack.is_empty()
  }
}
