package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
)

func main() {
	var n int
	in := bufio.NewReader(os.Stdin)

	fmt.Fscan(in, &n)

	nums := make([]int, n)

	for i := 0; i < n; i++ {
		fmt.Fscan(in, &nums[i])
	}

	ans := 0

	sorted := make([]int, n)
	copy(sorted, nums)
	sort.Ints(sorted)

	for i := 0; i < n; i++ {
		if nums[i] != sorted[i] {
			ans++
		}
	}

	fmt.Println(ans)
}
