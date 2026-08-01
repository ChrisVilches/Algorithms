// Categories are separated by two blank lines, items by one. This reproduces
// the old EJS output exactly; a single blank line would read just as well.
const CATEGORY_SEPARATOR = '\n\n\n'
const ITEM_SEPARATOR = '\n\n'

const renderItem = (item, helpers) => [
  item.title,
  '',
  ...item.files.map(file => `* [${file}](${helpers.toLink(file)})`)
].join('\n')

const renderCategory = (category, helpers) => [
  `### ${category.header}`,
  '',
  category.items.map(item => renderItem(item, helpers)).join(ITEM_SEPARATOR)
].join('\n')

const renderReadme = (data, helpers) => [
  '# Algorithms',
  '## Index',
  '*Note: This index is not exhaustive.*',
  '',
  data.map(category => renderCategory(category, helpers)).join(CATEGORY_SEPARATOR)
].join('\n') + '\n\n'

module.exports = { renderReadme }
