package main

import (
	"fmt"
)

func solve() bool {
	var h, w, n int

	fmt.Scan(&h, &w, &n)

	curr := 0

	for i := 0; i < n && h > 0; i++ {
		var x int
		fmt.Scan(&x)

		curr += x

		if curr > w {
			return false
		} else if curr == w {
			h--
			curr = 0
		}
	}

	return h == 0
}

func main() {
	if solve() {
		fmt.Println("YES")
	} else {
		fmt.Println("NO")
	}
}
