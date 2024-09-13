package main

import (
	"bufio"
	"fmt"
	"os"
)

func max(a, b int) int {
	if a < b {
		return b
	}

	return a
}

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	fmt.Fscan(in, &n)

	nums := make([]int, n)

	for i, _ := range nums {
		fmt.Fscan(in, &nums[i])
	}

	sum := 0
	ans := 0
	squared := 0

	for _, x := range nums {
		sum += x
	}

	for _, x := range nums {
		sum -= x
		squared += x * x
		curr := squared * sum
		ans = max(ans, curr)
	}

	fmt.Println(ans)
}
