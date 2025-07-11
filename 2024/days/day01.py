from core.base import AdventDay

"""
3   4
4   3
2   5
1   3
3   9
3   3

Pair up the smallest number in the left list with the smallest number in the right list,
then the second-smallest left number with the second-smallest right number, and so on.

To find the total distance between the left list and the right list, add up the distances between all of the pairs you found.
In the example above, this is 2 + 1 + 0 + 1 + 2 + 5, a total distance of 11!
"""

class Day01(AdventDay):
    def __init__(self, input_data):
        self.input_data = input_data

    def parse_input(self):
        pairs = [tuple(map(int, line.split())) for line in self.input_data.strip().split('\n')]
        return pairs

    def solve_part1(self):
        pairs = self.parse_input()

        # Divide into separate lists
        left_numbers = [pair[0] for pair in pairs]
        right_numbers = [pair[1] for pair in pairs]

        # Sort both lists
        left_numbers.sort()
        right_numbers.sort()

        # Calculate absolute differences
        difference = [abs(l - r) for l, r in zip(left_numbers, right_numbers)]

        return sum(difference)

    def solve_part2(self):
        return "Not implemented yet"

