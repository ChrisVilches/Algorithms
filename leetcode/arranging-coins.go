package main

func arrangeCoins(n int) int {
	rows := 0

	for n > rows {
		n -= rows + 1
		rows++
	}

	return rows
}
