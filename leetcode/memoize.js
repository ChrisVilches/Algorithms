function memoize(fn) {
  const memo = {}

  return function(...args) {
    const key = args.join('_')

    if (key in memo) return memo[key]

    return memo[key] = fn(...args)
  }
}

