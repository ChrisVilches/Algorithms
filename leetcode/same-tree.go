package main

type TreeNode struct {
	Val   int
	Left  *TreeNode
	Right *TreeNode
}

const EMPTY int = 1 << 30

func dfs(u *TreeNode, pre, in, post *[]int) {
	if u == nil {
		*pre = append(*pre, EMPTY)
		*in = append(*in, EMPTY)
		*post = append(*post, EMPTY)
		return
	}

	*pre = append(*pre, u.Val)
	dfs(u.Left, pre, in, post)
	*in = append(*in, u.Val)
	dfs(u.Right, pre, in, post)
	*post = append(*post, u.Val)
}

func equal(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}

	for i := range a {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

func isSameTree(p *TreeNode, q *TreeNode) bool {
	var pre1, in1, post1 []int
	var pre2, in2, post2 []int

	dfs(p, &pre1, &in1, &post1)
	dfs(q, &pre2, &in2, &post2)

	return equal(pre1, pre2) && equal(in1, in2) && equal(post1, post2)
}
