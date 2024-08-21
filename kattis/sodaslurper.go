package main

import "fmt"

func main() {
	var e, f, c int

	fmt.Scan(&e)
	fmt.Scan(&f)
	fmt.Scan(&c)

	result := 0
	f += e

	for f >= c {
		buy := f / c
		result += buy
		f = (f % c) + buy
	}

	fmt.Println(result)
}
