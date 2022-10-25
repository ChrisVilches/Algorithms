const isBalanced = function (root) {
  const height = node => {
    if (!node) return 0
    if ('memo' in node) return node.memo

    node.memo = 1 + Math.max(height(node.left), height(node.right))
    return node.memo
  }

  let balanced = true

  const dfs = node => {
    if (!node) return
    if (!balanced) return

    const h1 = height(node.left)
    const h2 = height(node.right)

    if (Math.abs(h1 - h2) > 1) {
      balanced = false
    }

    dfs(node.left)
    dfs(node.right)
  }

  dfs(root)

  return balanced
}
