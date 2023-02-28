defmodule Solve do
  def read_ints do
    IO.gets("") |> String.split() |> Enum.map(&String.to_integer/1)
  end

  defp max([h | t]) do
    List.foldr(t, h, &Kernel.max(&1, &2))
  end

  def solve(list) do
    IO.puts("#{max(list)} eh o maior")
  end
end

Solve.solve(Solve.read_ints())
