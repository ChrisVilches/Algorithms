const ALPHABET = /[a-zA-Z]+/g

const MINOR_WORDS = [
  'of',
  'a',
  'an',
  'in',
  'the',
  'as',
  'and',
  'or',
  'of',
  'with',
  'by',
  'for',
  'to'
]

function isMinorWord (word) {
  return Boolean(MINOR_WORDS.indexOf(word) > -1)
}

function maybeIsAcronym (word) {
  return word.toUpperCase() === word
}

function capitalizeWord (word, force = false) {
  if (maybeIsAcronym(word)) return word
  if (!force && isMinorWord(word)) return word.toLowerCase()

  return word[0].toUpperCase() + word.substr(1).toLowerCase()
}

function prettyCapitalize (text) {
  const parts = text.match(ALPHABET)

  for (let i = 0; i < parts.length; i++) {
    parts[i] = capitalizeWord(parts[i], i === 0)
  }

  let result = ''

  for (let i = 0, j = 0; i < text.length;) {
    if (text[i].match(ALPHABET) !== null) {
      result += parts[j]
      i += parts[j].length
      j++
    } else {
      result += text[i]
      i++
    }
  }

  return result
}

console.assert(maybeIsAcronym('BFS'))
console.assert(maybeIsAcronym('DFS'))
console.assert(prettyCapitalize('  ford and Fulkerson ') === '  Ford and Fulkerson ')
console.assert(prettyCapitalize('  ford & Fulkerson ') === '  Ford & Fulkerson ')
console.assert(prettyCapitalize('  ford &   Fulkerson ') === '  Ford &   Fulkerson ')
console.assert(prettyCapitalize('  just use DFS or BFS ') === '  Just Use DFS or BFS ')
console.assert(prettyCapitalize('  and you??? ') === '  And You??? ')
console.assert(isMinorWord('of'))
console.assert(!isMinorWord('hello'))

module.exports = {
  prettyCapitalize
}
