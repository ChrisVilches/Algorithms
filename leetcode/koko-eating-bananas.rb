def hours_needed(pile_size, eating_speed)
  (pile_size / eating_speed.to_f).ceil
end

def possible(piles, hours, eating_speed)
  piles.sum { |p| hours_needed(p, eating_speed) } <= hours
end

def min_eating_speed(piles, hours)
  left = 1
  right = 1 << 33

  while left < right
    mid = (left + right) / 2

    if possible(piles, hours, mid)
      right = mid
    else
      left = mid + 1
    end
  end

  right
end
