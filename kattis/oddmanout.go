package main

import "fmt"

func main() {
	var T, n int
	fmt.Scan(&T)

	for t := 0; t < T; t++ {
		fmt.Scan(&n)
		freqs := make(map[int]int)

		for i := 0; i < n; i++ {
			var x int
			fmt.Scan(&x)
			freqs[x]++
		}

		ans := 0

		for value, freq := range freqs {
			if freq == 1 {
				ans = value
			}
		}

		fmt.Printf("Case #%d: %d\n", t+1, ans)
	}
}
