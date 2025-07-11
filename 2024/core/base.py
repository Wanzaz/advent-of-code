from abc import ABC, abstractmethod

class AdventDay(ABC):
    def __init__(self, input_data: str) -> None:
        self.input_data = input_data
        super().__init__()
        self.parse_input()

    @abstractmethod
    def parse_input(self):
        """Parse and save the data to attributes"""
        pass

    @abstractmethod
    def solve_part1(self) -> any:
        """Returns the result of part 1"""
        pass

    @abstractmethod
    def solve_part2(self) -> any:
        """Returns the result of part 2"""
        pass

    def run(self) -> tuple:
        return self.solve_part1(), self.solve_part2()
