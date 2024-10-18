const path = require('path')
const fs = require('fs')
const { prettyCapitalize } = require('./pretty-capitalize')

const IGNORE_DIR_PATTERNS = [
  '.git/',
  '.vscode/',
  'node_modules',
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

function cleanIndexData (data) {
  const allFiles = getAllFiles('./')

  return data.map(({ header, items }) => ({
    header: prettyCapitalize(header),
    items: items.map(({ title, files }) => {
      const paths = files.map(f => findUniqueFilePath(f, allFiles))

      if (paths.length !== (new Set(files).size)) {
        throw new Error(`Files in "${header}" -> "${title}" are not unique`)
      }

      return {
        title: prettyCapitalize(title),
        files: paths.toSorted((a, b) => a.localeCompare(b))
      }
    })
  }
  ))
}

module.exports = {
  cleanIndexData
}
