const path = require('path')
const fs = require('fs')
const ejs = require('ejs')
const data = require('./indexdata.json')
const spawn = require('child_process').spawn
const { cleanIndexData } = require('./index-clean.js')

const README_FILE = './README.md'
const URL_PREFIX = 'github.com/ChrisVilches/Algorithms/blob/main/'

const updateReadmeFile = text => { fs.writeFileSync(README_FILE, text) }

const showGitDiff = () => { spawn('git diff', [README_FILE], { shell: true, stdio: 'inherit' }) }

const toLink = x => 'https://' + path.join(URL_PREFIX, x)

const readmeInput = fs.readFileSync('./README.md.ejs', 'utf8')
const template = ejs.compile(readmeInput, { rmWhitespace: true })

const renderedReadme = template({
  helpers: { toLink },
  data: cleanIndexData(data)
})

updateReadmeFile(renderedReadme)
showGitDiff()
