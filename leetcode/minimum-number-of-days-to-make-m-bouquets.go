package main

func possible(bloomDay []int, m, k, day int) bool {
	count := 0

	adj := 0

	for _, d := range bloomDay {
		if d > day {
			adj = 0
			continue
		}

		adj++
		if adj == k {
			adj = 0
			count++
		}
	}

	return count >= m
}

func minDays(bloomDay []int, m int, k int) int {
	const inf = int(1e9 + 7)

	lo := 0
	hi := inf

	for lo < hi {
		mid := (lo + hi) / 2

		if possible(bloomDay, m, k, mid) {
			hi = mid
		} else {
			lo = mid + 1
		}
	}

	if lo == inf {
		return -1
	} else {
		return lo
	}
}
