package main

import "fmt"

func main() {
	var target int64

	fmt.Scan(&target)

	fib := []int64{0, 1}

	for i := 2; ; i++ {
		val := fib[i-1] + fib[i-2]
		if val < 0 {
			break
		}

		fib = append(fib, val)
	}

	sol := []int64{}

	for i := len(fib) - 1; target > 0 && i >= 0; i-- {
		num := fib[i]

		for num <= target {
			sol = append(sol, num)
			target -= num
		}
	}

	for i := len(sol) - 1; i >= 0; i-- {
		fmt.Print(sol[i], " ")
	}

	fmt.Println()
}
