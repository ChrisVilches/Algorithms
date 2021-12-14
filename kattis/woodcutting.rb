def solve
  woods = []

  gets.to_i.times {
    woods << gets.scan(/\d+/).map(&:to_f)[1...].sum
  }

  sum = 0
  ans = 0

  woods.sort.each do |w|
    sum += w
    ans += sum
  end

  printf "%.10f\n", ans / woods.count
end

gets.to_i.times { solve }
