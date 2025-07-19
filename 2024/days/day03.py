import re

from core.base import AdventDay

"""
"""

class Day03(AdventDay):
    def __init__(self, input_data):
        self.input_data = input_data

    def parse_input(self):
        return self.parse_input

    def solve_part1(self):
        matches = re.findall(r"mul\((\d+),(\d+)\)", self.input_data)
        
        multiplications = sum([int(n1) * int(n2) for n1, n2 in matches])

        return multiplications

    def solve_part2(self):
        return "Not implemented yet"

