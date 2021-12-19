package main

import (
	"fmt"
	"math"
)

var (
	N    int
	Q    int
	A    [100001]int
	tree [400001]int
)

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func query(p, L, R, i, j int) int {
	if i > R || j < L {
		return math.MaxInt32
	}
	if i <= L && R <= j {
		return tree[p]
	}

	m := (L + R) / 2
	return min(query(2*p, L, m, i, j), query(2*p+1, m+1, R, i, j))
}

func build_tree(p, L, R int) {
	if L == R {
		tree[p] = A[L]
	} else {
		build_tree(2*p, L, (L+R)/2)
		build_tree(2*p+1, (L+R)/2+1, R)
		tree[p] = min(tree[2*p], tree[2*p+1])
	}
}

func main() {
	fmt.Scan(&N)

	for i := 0; i < N; i++ {
		fmt.Scan(&A[i])
	}

	build_tree(1, 0, N-1)

	fmt.Scan(&Q)

	for q := 0; q < Q; q++ {
		var i, j int
		fmt.Scan(&i, &j)
		fmt.Println(query(1, 0, N-1, i, j))
	}
}
