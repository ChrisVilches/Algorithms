const fs = require('fs')
const { generateIndex } = require('./indexgen')
const spawn = require('child_process').spawn

const README_FILE = './README.md'
const START_TAG = '<!-- auto-generated-index-start -->'
const END_TAG = '<!-- auto-generated-index-end -->'

const throwIncorrectReadmeTagsError = () => { throw new Error('Readme tags are incorrect') }

const updateReadmeFile = text => { fs.writeFileSync(README_FILE, text) }

const showGitDiff = () => { spawn('git diff', [README_FILE], { shell: true, stdio: 'inherit' }) }

const insertIndex = readmeLines => {
  const filteredLines = []

  let insideTag = false

  for (let i = 0; i < readmeLines.length; i++) {
    const line = readmeLines[i]

    switch (insideTag) {
      case true:
        if (line.trim() === START_TAG) throwIncorrectReadmeTagsError()

        if (line.trim() === END_TAG) {
          filteredLines.push(line)
          insideTag = false
        }
        break

      case false:
        if (line.trim() === END_TAG) throwIncorrectReadmeTagsError()

        filteredLines.push(line)

        if (line.trim() === START_TAG) {
          filteredLines.push(generateIndex())
          insideTag = true
        }
        break
    }
  }

  if (insideTag) throwIncorrectReadmeTagsError()

  return filteredLines
}

(function () {
  const readmeLines = fs.readFileSync(README_FILE, { encoding: 'utf8', flag: 'r' }).split('\n')

  const readmeLinesWithIndex = insertIndex(readmeLines)

  const resultText = readmeLinesWithIndex.join('\n').trim() + '\n'

  updateReadmeFile(resultText)

  showGitDiff()
})()
