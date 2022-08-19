package main

func mySqrt(x int) int {
	lo := 0.0
	hi := 2147483647.0

	for it := 0; it < 150; it++ {
		mid := (lo + hi) / 2

		if int(mid*mid) > x {
			hi = mid
		} else {
			lo = mid
		}

	}

	return int(lo)
}
