package main

func reverseBits(num uint32) uint32 {
	var res uint32 = 0

	var bit uint32 = 1 << 31

	for num > 0 {

		if num&1 == 1 {
			res += bit
		}

		bit >>= 1
		num >>= 1
	}

	return res
}
