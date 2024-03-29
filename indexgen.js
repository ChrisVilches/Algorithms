const data = require('./indexdata.json')
const path = require('path')
const fs = require('fs')
const { prettyCapitalize } = require('./pretty-capitalize')

const URL_PREFIX = 'github.com/ChrisVilches/Algorithms/blob/main/'

const IGNORE_DIR_PATTERNS = [
  '.git/',
  '.vscode/',
  /\.md/
]

function shouldIgnore (path) {
  for (let i = 0; i < IGNORE_DIR_PATTERNS.length; i++) {
    if (path.search(IGNORE_DIR_PATTERNS[i]) !== -1) return true
  }
  return false
}

function getAllFiles (directory) {
  const files = []

  const dfs = (directory) => {
    fs.readdirSync(directory).forEach(file => {
      const absolute = path.join(directory, file)

      if (shouldIgnore(absolute)) return

      if (fs.statSync(absolute).isDirectory()) {
        dfs(absolute)
      } else {
        files.push(absolute)
      }
    })
  }

  dfs(directory)

  return files
}

const normalizeString = x => x.replace(/[^a-zA-Z0-9\s]/g, ' ').replace(/\s+/g, ' ').toLowerCase()

function findUniqueFilePath (simplifiedFilename, allFiles) {
  let found = null
  simplifiedFilename = normalizeString(simplifiedFilename)

  for (let i = 0; i < allFiles.length; i++) {
    const file = allFiles[i]

    if (normalizeString(file).search(simplifiedFilename) !== -1) {
      if (found != null) throw new Error(`Multiple matches for "${simplifiedFilename}": "${found}" and "${file}"`)

      found = file
    }
  }

  if (found == null) throw new Error(`Not found: ${simplifiedFilename}`)

  return found
}

const toLink = x => 'https://' + path.join(URL_PREFIX, x)

function generateIndex () {
  const allFiles = getAllFiles('./')

  let printNewLine = false

  const lines = []

  data.forEach(category => {
    if (printNewLine) lines.push('')
    printNewLine = true

    lines.push(`### ${prettyCapitalize(category.header)}`)

    category.items.forEach(item => {
      lines.push(`\n${prettyCapitalize(item.title)}\n`)

      const files = item.files
        .map(f => findUniqueFilePath(f, allFiles))

      if (files.length !== (new Set(files).size)) {
        throw new Error(`Files in "${category.header}" -> "${item.title}" are not unique`)
      }

      files.sort((a, b) => a === b ? 0 : (a < b ? -1 : 1))
        .forEach(file => lines.push(`* [${file}](${toLink(file)})`))
    })
  })

  return lines.join('\n')
}

module.exports = {
  generateIndex
}
