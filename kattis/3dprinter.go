package main

import (
	"fmt"
	"io"
)

var memo [10001]int

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func dp(n int) int {
	if n <= 1 {
		return n
	}

	if memo[n] != -1 {
		return memo[n]
	}

	printStatue := dp(n - 1)
	var printPrinter int

	if n%2 == 1 {
		printPrinter = dp((n / 2) + 1)
	} else {
		printPrinter = dp((n / 2))
	}

	memo[n] = 1 + min(printStatue, printPrinter)

	return memo[n]
}

func main() {
	for i := range memo {
		memo[i] = -1
	}

	var N int

	for {
		_, err := fmt.Scan(&N)
		if err == io.EOF {
			break
		}

		fmt.Println(dp(N))
	}
}
