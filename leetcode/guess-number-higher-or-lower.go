package main

func guess(num int) int

func guessNumber(n int) int {
	lo := 0
	hi := n

	for lo < hi {
		mid := (lo + hi) / 2

		if guess(mid) >= 1 {
			lo = mid + 1
		} else {
			hi = mid
		}
	}

	return lo
}
