package main

import "fmt"

func main() {
	var n, m, money int
	fmt.Scan(&n)

	teaPrices := make([]int, n)

	for i := 0; i < n; i++ {
		fmt.Scan(&teaPrices[i])
	}

	fmt.Scan(&m)
	toppingPrices := make([]int, m)

	for i := 0; i < m; i++ {
		fmt.Scan(&toppingPrices[i])
	}

	cheapest := int(1e9)

	for i := 0; i < n; i++ {
		var k, idx int
		fmt.Scan(&k)

		for t := 0; t < k; t++ {
			fmt.Scan(&idx)
			price := teaPrices[i] + toppingPrices[idx-1]
			if price < cheapest {
				cheapest = price
			}
		}
	}

	fmt.Scan(&money)

	result := int(money/cheapest) - 1

	if result < 0 {
		result = 0
	}

	fmt.Println(result)
}
