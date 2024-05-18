var simplifyPath = function (path) {
  const parts = path.split('/').filter(x => x.length > 0).filter(x => x !== '.')

  let result = []

  for (const part of parts) {
      if (part === '..') {
          result = result.slice(0, -1);
      } else {
          result.push(part)
      }
  }

  return `/${result.join('/')}`
};
