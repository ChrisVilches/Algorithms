package main

func isBadVersion(version int) bool

func firstBadVersion(n int) int {
	lo := 0
	hi := n

	for lo < hi {
		mid := (lo + hi) / 2

		if isBadVersion(mid) {
			hi = mid
		} else {
			lo = mid + 1
		}
	}

	return lo
}
