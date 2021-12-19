@arr = nil
@tree = Array.new(4 * 100001)

def query(p, l, r, i, j)
  return 1e9.to_i if i > r || j < l
  return @tree[p] if i <= l && r <= j
  m = (l + r) / 2
  [query(2 * p, l, m, i, j), query(2 * p + 1, m + 1, r, i, j)].min
end

def build_tree(p, l, r)
  if l == r
    @tree[p] = @arr[l]
  else
    build_tree(2 * p, l, (l + r) / 2)
    build_tree(2 * p + 1, (l + r) / 2 + 1, r)
    @tree[p] = [@tree[2 * p], @tree[2 * p + 1]].min
  end
end

n = STDIN.gets.to_i

@arr = gets.scan(/\d+/).map(&:to_i)

build_tree 1, 0, n - 1

gets.to_i.times do
  i, j = gets.scan(/\d+/).map(&:to_i)
  puts query 1, 0, n - 1, i, j
end
