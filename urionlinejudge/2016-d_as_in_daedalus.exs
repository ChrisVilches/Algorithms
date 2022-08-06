defmodule Solve do
  defp highest_value([current_value | remaining], other_sum, budget) do
    if current_value + other_sum <= budget do
      Kernel.max(current_value, highest_value(remaining, other_sum, budget))
    else
      0
    end
  end

  defp highest_value([], _, _) do
    0
  end

  defp highest_value(other_sum, budget) do
    highest_value([1, 10, 100, 1000, 10000], other_sum, budget)
  end

  def round_possible_score([budget | [_ | other_cards]]) do
    highest_value(other_cards |> Enum.sum(), budget)
  end

  def received_round([budget | [daedalus | other_cards]]) do
    if daedalus + (other_cards |> Enum.sum()) <= budget do
      daedalus
    else
      0
    end
  end

  def read_ints do
    IO.gets("") |> String.split() |> Enum.map(&String.to_integer/1)
  end
end

[_, m] = Solve.read_ints()

rounds = for _ <- 0..(m - 1), do: Solve.read_ints()

received = rounds |> Enum.map(&Solve.received_round/1) |> Enum.sum()
optimal = rounds |> Enum.map(&Solve.round_possible_score/1) |> Enum.sum()

IO.puts(optimal - received)
