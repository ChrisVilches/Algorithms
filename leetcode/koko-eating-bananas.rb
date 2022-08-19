def hours_needed(pile_size, eating_speed)
  (pile_size / eating_speed.to_f).ceil
end

def possible(piles, h, eating_speed)
  piles.map { |p| hours_needed(p, eating_speed) }.sum <= h
end

def min_eating_speed(piles, h)
  left = 1
  right = 1 << 33

  while left < right
    mid = (left + right) / 2

    if possible(piles, h, mid)
      right = mid
    else
      left = mid + 1
    end
  end

  right
end
