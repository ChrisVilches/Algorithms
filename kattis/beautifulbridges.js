const fs = require('fs')
const lines = fs.readFileSync('/dev/stdin').toString().split('\n')

const [N, H, alpha, beta] = lines[0].split(' ').map(Number)
const ground = []

for (let i = 0; i < N; i++) {
  const [x, y] = lines[i + 1].split(' ').map(Number)
  ground.push({ x, y })
}

const sqrt = Math.sqrt
const pow = Math.pow
const min = Math.min
const abs = Math.abs

const arcLeftMax = new Array(N)
const arcRightMax = new Array(N)
const memo = new Array(N)

const dist = (i, j) => abs(ground[i].x - ground[j].x)
const pillarHeight = i => H - ground[i].y
const costPillar = i => alpha * pillarHeight(i)
const costArc = (i, j) => beta * pow(dist(i, j), 2)

const arcPossible = (i, j) => {
  const arcRadius = dist(i, j) / 2
  return arcRightMax[i] >= arcRadius && arcLeftMax[j] >= arcRadius
}

const precomputeArcBoundsRight = point => {
  let r = pillarHeight(point)
  for (let i = point + 1; i < N; i++) {
    const centerX = ground[point].x + r
    const centerY = H - r
    if (centerX < ground[i].x) break
    const circleY = sqrt(pow(r, 2) - pow(ground[i].x - centerX, 2)) + centerY
    if (circleY > ground[i].y) continue
    const [L, X, Y] = [ground[point].x, ground[i].x, ground[i].y]
    r = H - L + X - Y + sqrt(2) * sqrt(-H * L + H * X + L * Y - X * Y)
  }

  arcRightMax[point] = r
}

const precomputeArcBoundsLeft = point => {
  let r = pillarHeight(point)
  for (let i = point - 1; i >= 0; i--) {
    const centerX = ground[point].x - r
    const centerY = H - r
    if (ground[i].x < centerX) break
    const circleY = sqrt(pow(r, 2) - pow(ground[i].x - centerX, 2)) + centerY
    if (circleY > ground[i].y) continue
    const [R, X, Y] = [ground[point].x, ground[i].x, ground[i].y]
    r = H + R - X - Y + sqrt(2) * sqrt(H * R - H * X - R * Y + X * Y)
  }

  arcLeftMax[point] = r
}

const dp = n => {
  if (n === N - 1) return costPillar(n)
  if (memo[n] !== -1) return memo[n]

  let minCost = Infinity

  for (let i = n + 1; i < N; i++) {
    if (arcPossible(n, i)) {
      minCost = min(minCost, costPillar(n) + costArc(n, i) + dp(i))
    }
  }

  memo[n] = minCost
  return minCost
}

for (let i = 1; i < N; i++) precomputeArcBoundsLeft(i)
for (let i = 0; i < N - 1; i++) precomputeArcBoundsRight(i)
for (let i = 0; i < N; i++) {
  memo[i] = -1
}

// Avoid stack overflow error.
for (let i = N - 1; i >= 0; i--) {
  dp(i)
}

const result = dp(0)

if (result === Infinity) {
  console.log('impossible')
} else {
  console.log(result)
}
