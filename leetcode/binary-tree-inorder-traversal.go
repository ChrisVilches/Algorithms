package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

func dfs(u *TreeNode, result *[]int) {
	if u == nil {
		return
	}

	dfs(u.Left, result)
	*result = append(*result, u.Val)
	dfs(u.Right, result)
}

func inorderTraversal(root *TreeNode) []int {
	var result []int

	dfs(root, &result)

	return result

}
