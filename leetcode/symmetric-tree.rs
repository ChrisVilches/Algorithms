use std::cell::RefCell;
use std::rc::Rc;

const DUMMY_VALUE: i32 = -1000000;

#[derive(PartialEq, Copy, Clone)]
pub enum Order {
  In,
  Pre,
  Post,
}

impl TreeNode {
  pub fn traversal(&self, order: Order, invert: bool) -> Vec<i32> {
    fn dfs(node: &TreeNode, ret: &mut Vec<i32>, order: Order, invert: bool) {
      if order == Order::Pre {
        ret.push(node.val);
      }

      if let Some(n) = if invert { &node.right } else { &node.left } {
        dfs(&n.borrow(), ret, order, invert);
      } else {
        ret.push(DUMMY_VALUE);
      }

      if order == Order::In {
        ret.push(node.val);
      }

      if let Some(n) = if invert { &node.left } else { &node.right } {
        dfs(&n.borrow(), ret, order, invert);
      } else {
        ret.push(DUMMY_VALUE);
      }

      if order == Order::Post {
        ret.push(node.val);
      }
    }

    let mut ret = vec![];
    dfs(self, &mut ret, order, invert);
    ret
  }
}

fn tree_eq(root1: &Option<Rc<RefCell<TreeNode>>>, root2: &Option<Rc<RefCell<TreeNode>>>) -> bool {
  let default1 = Rc::new(RefCell::new(TreeNode::new(DUMMY_VALUE)));
  let default2 = Rc::new(RefCell::new(TreeNode::new(DUMMY_VALUE)));

  let n1 = root1.as_ref().unwrap_or(&default1).borrow();
  let n2 = root2.as_ref().unwrap_or(&default2).borrow();

  n1.traversal(Order::Pre, false) == n2.traversal(Order::Pre, true)
    && n1.traversal(Order::In, false) == n2.traversal(Order::In, true)
    && n1.traversal(Order::Post, false) == n2.traversal(Order::Post, true)
}

impl Solution {
  pub fn is_symmetric(root: Option<Rc<RefCell<TreeNode>>>) -> bool {
    match root {
      None => true,
      Some(node) => {
        let n = node.borrow();

        tree_eq(&n.left, &n.right)
      }
    }
  }
}
