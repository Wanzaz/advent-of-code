import re

# from collections import deque # would be also possible but own implementation is better

from core.base import AdventDay

"""
My first thought aboaut this task was do it with cycling buffer and then I thought about Regex in the first part at least

Even for the part 2 wasn't the cycling buffer really needed but it would be also option
"""

# class RingBuffer:
#     def __init__(self, size):
#         self.size = size
#         self.data = [None] * size
#         self.index = 0

#     def append(self, value):
#         self.data[self.index] = value
#         self.index = (self.index + 1) % self.size

#     def get(self):
#         return self.data[self.index:] + self.data[:self.index]


class Day03(AdventDay):
    def __init__(self, input_data):
        self.input_data = input_data

    def parse_input(self):
        return self.input_data

    def solve_part1(self):
        matches = re.findall(r"mul\((\d+),(\d+)\)", self.input_data)
        
        multiplications = sum([int(n1) * int(n2) for n1, n2 in matches])

        return multiplications


    def solve_part2(self):
        total = 0
        enabled = True  # by default, multiplications are enabled
        i = 0
        text = self.input_data

        while i < len(text):
            # Check for "do()" or "don't()" at current position
            if text.startswith("do()", i):
                enabled = True
                i += 4
                continue
            elif text.startswith("don't()", i):
                enabled = False
                i += 7
                continue

            # Try to match mul(n1,n2) at the current position
            mul_match = re.match(r"mul\((\d+),(\d+)\)", text[i:])
            if mul_match:
                if enabled:
                    n1, n2 = mul_match.groups()
                    total += int(n1) * int(n2)
                i += mul_match.end()  # move forward past the matched mul
            else:
                i += 1  # advance character by character

        return total




