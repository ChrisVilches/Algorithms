class Node {
  constructor(value, result) {
    this.value = value
    this.result = result
    this.children = new Map()
    this.hasValue = false
  }

  addChild(key) {
    const result = new Node(key)
    this.children.set(key, result)
    return result
  }

  findChild(key) {
    return this.children.get(key)
  }
}

class Memo {
  constructor() {
    this.root = new Node()
  }

  insert(args, result) {
    let curr = this.root

    for (const arg of args) {
      const child = curr.findChild(arg)
      if (child) {
        curr = child
      } else {
        curr = curr.addChild(arg)
      }
    }

    curr.hasValue = true
    return curr.result = result
  }

  find(args) {
    let curr = this.root

    for (const arg of args) {
      const child = curr.findChild(arg)
      if (!child) return { found: false, value: null }
      curr = child
    }

    return { found: curr.hasValue, value: curr.result }
  }
}

function memoize(fn) {
  const memo = new Memo()

  return function(...args) {
    const { found, value } = memo.find(args)

    if (found) return value

    return memo.insert(args, fn(...args))
  }
}

