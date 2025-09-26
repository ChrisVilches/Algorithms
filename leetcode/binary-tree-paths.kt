class TreeNode(
    var `val`: Int,
) {
    var left: TreeNode? = null
    var right: TreeNode? = null
}

class Solution {
    fun isLeaf(node: TreeNode?): Boolean = node != null && node.left == null && node.right == null

    fun binaryTreePaths(root: TreeNode?): List<String> {
        val res = mutableListOf<String>()
        val currPath = mutableListOf<Int>()

        fun dfs(node: TreeNode?) {
            if (node == null) return

            currPath.add(node.`val`)

            if (isLeaf(node)) {
                res.add(currPath.map { "$it" }.joinToString(separator = "->"))
            }

            dfs(node.left)
            dfs(node.right)

            currPath.removeLast()
        }

        dfs(root)

        return res
    }
}
