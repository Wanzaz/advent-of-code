import os

class InputLoader:
    def __init__(self, input_dir: str = "inputs"):
        self.input_dir = input_dir

    def load(self, day_number: int, test: bool = False) -> str:
        """
        Načte vstupní data pro daný den.
        Pokud test=True, hledá testovací soubor (např. day01_test.txt).
        """
        suffix = "_test" if test else ""
        filename = f"day{day_number:02}{suffix}.txt"
        filepath = os.path.join(self.input_dir, filename)
        
        if not os.path.isfile(filepath):
            raise FileNotFoundError(f"Input file not found: {filepath}")
        
        with open(filepath, "r") as f:
            return f.read()

