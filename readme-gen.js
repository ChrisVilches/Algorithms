const path = require('path')
const fs = require('fs')
const data = require('./indexdata.json')
const spawn = require('child_process').spawn
const { cleanIndexData } = require('./index-clean.js')
const { renderReadme } = require('./readme-template.js')

const README_FILE = './README.md'
const URL_PREFIX = 'github.com/ChrisVilches/Algorithms/blob/main/'

const updateReadmeFile = text => { fs.writeFileSync(README_FILE, text) }

const showGitDiff = () => { spawn('git', ['diff', README_FILE], { stdio: 'inherit' }) }

const toLink = x => 'https://' + path.join(URL_PREFIX, x)

const renderedReadme = renderReadme(cleanIndexData(data), { toLink })

updateReadmeFile(renderedReadme)
showGitDiff()
