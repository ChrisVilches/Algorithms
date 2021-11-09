def solve(n)
  op = ["+", "-", "/", "*"]

  4.times do |i|
    4.times do |j|
      4.times do |k|
        exp = "4 #{op[i]} 4 #{op[j]} 4 #{op[k]} 4"
        result = eval exp
        if result == n
          puts "#{exp} = #{n}"
          return
        end
      end
    end
  end

  puts "no solution"
end

t = STDIN.gets.to_i

t.times do
  n = STDIN.gets.to_i
  solve(n)
end
