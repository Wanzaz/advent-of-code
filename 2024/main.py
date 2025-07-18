import argparse
from utils.input_loader import InputLoader
from days import day01
from days import day02

DAYS = {
    1: day01.Day01,
    2: day02.Day02,
}

def main():
    parser = argparse.ArgumentParser(description="Run Advent of Code solution by day")
    parser.add_argument(
        "--day", type=int, required=True, help="Day number to run (e.g. 1, 2, ...)"
    )
    parser.add_argument(
        "--test", action="store_true", help="Use test input file (e.g. day01_test.txt)"
    )
    args = parser.parse_args()

    day_number = args.day
    if day_number not in DAYS:
        print(f"No solution implemented for day {day_number}")
        return

    loader = InputLoader()
    input_data = loader.load(day_number, test=args.test)
    day_class = DAYS[day_number]

    day = day_class(input_data)
    part1 = day.solve_part1()
    part2 = day.solve_part2()

    print(f"Day {day_number} results:")
    print(f"  Part 1: {part1}")
    print(f"  Part 2: {part2}")

if __name__ == "__main__":
    main()

