package main

import (
	"fmt"
)

func calculate(c, n int) bool {
	curr := 0

	for i := 0; i < n; i++ {
		var left, enter, wait int
		fmt.Scan(&left, &enter, &wait)

		curr -= left

		if curr < 0 {
			return false
		}

		curr += enter

		if curr > c {
			return false
		}

		if wait > 0 && curr < c {
			return false
		}
	}

	return curr == 0
}

func main() {
	var c, n int
	fmt.Scan(&c, &n)

	if calculate(c, n) {
		fmt.Println("possible")
	} else {
		fmt.Println("impossible")
	}
}
