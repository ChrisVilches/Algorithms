func numJewelsInStones(jewels string, stones string) int {
	set := map[rune]bool{}

	for _, c := range jewels {
		set[c] = true
	}

	result := 0

	for _, c := range stones {
		if set[c] {
			result++
		}
	}

	return result
}
