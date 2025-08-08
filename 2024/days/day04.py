from core.base import AdventDay


class Day04(AdventDay):
    def __init__(self, input_data):
        self.input_data = input_data.strip()
        self.matrix = self.parse_input()
        self.rows = len(self.matrix)
        self.cols = len(self.matrix[0])
        self.pattern = "XMAS"
        self.pattern_length = len(self.pattern)

        # 8 směrů: →, ←, ↓, ↑, ↘, ↙, ↖, ↗
        self.directions = [
            (0, 1),    # →
            (0, -1),   # ←
            (1, 0),    # ↓
            (-1, 0),   # ↑
            (1, 1),    # ↘
            (1, -1),   # ↙
            (-1, -1),  # ↖
            (-1, 1),   # ↗
        ]

    def parse_input(self):
        matrix = [list(row) for row in self.input_data.split('\n')]
        expected_len = len(matrix[0])
        for idx, row in enumerate(matrix):
            if len(row) != expected_len:
                raise ValueError(f"Row {idx} length {len(row)} != expected {expected_len}")
        return matrix

    def is_in_bounds(self, row, col, dr, dc, length):
        for i in range(length):
            r = row + i * dr
            c = col + i * dc
            if r < 0 or r >= self.rows or c < 0 or c >= self.cols:
                return False
        return True

    def get_string(self, row, col, dr, dc, length):
        chars = []
        for i in range(length):
            r = row + i * dr
            c = col + i * dc
            if r < 0 or r >= self.rows or c < 0 or c >= self.cols:
                raise IndexError(f"Index out of range: row={r}, col={c}")
            chars.append(self.matrix[r][c])
        return ''.join(chars)

    def solve_part1(self):
        total = 0
        for row in range(self.rows):
            for col in range(self.cols):
                for dr, dc in self.directions:
                    if self.is_in_bounds(row, col, dr, dc, self.pattern_length):
                        word = self.get_string(row, col, dr, dc, self.pattern_length)
                        if word == self.pattern:
                            total += 1
        return total


    def is_A(self, element):
        return element == 'A'

    def solve_part2(self):
        total = 0

        for row in range(1, self.rows - 1):
            for col in range(1, self.cols - 1):
                if self.is_A(self.matrix[row][col]):
                    x = self.matrix[row + 1][col + 1] + 'A' + self.matrix[row - 1][col - 1] 
                    y = self.matrix[row + 1][col - 1] + 'A' + self.matrix[row - 1][col + 1]
                    if x in ('SAM', 'MAS') and y in ('SAM', 'MAS'):
                        total += 1

        return total

    # def solve_part2(self):
    #     total = 0 

    #     # don't start at the last line because it has to have diagonal element...
    #     for row in range(1, self.rows - 1):
    #         for col in range(1, self.cols - 1):
    #             if self.is_A(self.matrix[row][col]):
    #                 r_r = row
    #                 r_c = col

    #                 # 1️⃣ MAS ↖↘ a MAS ↗↙
    #                 if (
    #                     self.is_M(self.matrix[r_r - 1][r_c - 1]) and self.is_S(self.matrix[r_r + 1][r_c + 1]) and
    #                     self.is_M(self.matrix[r_r - 1][r_c + 1]) and self.is_S(self.matrix[r_r + 1][r_c - 1])
    #                 ):
    #                     total += 1

    #                 # 2️⃣ SAM ↖↘ a SAM ↗↙
    #                 elif (
    #                     self.is_S(self.matrix[r_r - 1][r_c - 1]) and self.is_M(self.matrix[r_r + 1][r_c + 1]) and
    #                     self.is_S(self.matrix[r_r - 1][r_c + 1]) and self.is_M(self.matrix[r_r + 1][r_c - 1])
    #                 ):
    #                     total += 1

    #                 # 3️⃣ MAS ↖↘ a SAM ↗↙
    #                 elif (
    #                     self.is_M(self.matrix[r_r - 1][r_c - 1]) and self.is_S(self.matrix[r_r + 1][r_c + 1]) and
    #                     self.is_S(self.matrix[r_r - 1][r_c + 1]) and self.is_M(self.matrix[r_r + 1][r_c - 1])
    #                 ):
    #                     total += 1

    #                 # 4️⃣ SAM ↖↘ a MAS ↗↙
    #                 elif (
    #                     self.is_S(self.matrix[r_r - 1][r_c - 1]) and self.is_M(self.matrix[r_r + 1][r_c + 1]) and
    #                     self.is_M(self.matrix[r_r - 1][r_c + 1]) and self.is_S(self.matrix[r_r + 1][r_c - 1])
    #                 ):
    #                     total += 1

    #     return total

