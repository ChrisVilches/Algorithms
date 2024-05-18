import (
	"fmt"
	"strconv"
	"strings"
)

func toInt(a byte) int {
	if a == '1' {
		return 1
	} else {
		return 0
	}
}

func addBinary(a string, b string) string {
	size := max(len(a), len(b)) + 1
	a = strings.Repeat("0", size-len(a)) + a
	b = strings.Repeat("0", size-len(b)) + b
	sumResult := make([]rune, size)

	plusOne := 0
	for i := size - 1; i >= 0; i-- {
		sum := toInt(a[i]) + toInt(b[i]) + plusOne
		sumResult[i] = []rune(strconv.Itoa(sum % 2))[0]

		if sum > 1 {
			plusOne = 1
		} else {
			plusOne = 0
		}
	}

	result := string(sumResult)
	if result[0] == '0' {
		result = result[1:]
	}
	return result
}
