package main

import "fmt"

func serie(n int) int {
	return (n + 1) * n / 2
}

func findSolution(d, r, t int) int {
	ritaAges := make(map[int]int)
	theoAges := make(map[int]int)

	for i := 0; i < 100; i++ {
		ritaAges[serie(i)-serie(3)] = i
		theoAges[serie(i)-serie(2)] = i
	}

	for i := 0; ; i++ {
		ritaAge := ritaAges[r-i]
		theoAge := theoAges[t+i]

		if ritaAge-theoAge == d {
			return i
		}
	}
}

func main() {
	var d, r, t int
	fmt.Scan(&d, &r, &t)
	fmt.Println(findSolution(d, r, t))
}
