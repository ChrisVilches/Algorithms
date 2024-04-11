var current string
var answer []string

func removeLastChar() {
	current = current[:len(current)-1]
}

func dfs(n, m int) {
	if n == 0 && m == 0 {
		answer = append(answer, current)
		return
	}

	if n > 0 {
		current += "("
		dfs(n-1, m+1)
		removeLastChar()
	}

	if m > 0 {
		current += ")"
		dfs(n, m-1)
		removeLastChar()
	}

}

func generateParenthesis(n int) []string {
	answer = []string{}
	current = ""
	dfs(n, 0)

	return answer
}
