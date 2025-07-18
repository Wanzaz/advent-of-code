from core.base import AdventDay

"""
    The engineers are trying to figure out which reports are safe.
    The Red-Nosed reactor safety systems can only tolerate levels that are either gradually increasing or gradually decreasing.
    So, a report only counts as safe if both of the following are true:

- The levels are either all increasing or all decreasing.
- Any two adjacent levels differ by at least one and at most three.
"""

class Day02(AdventDay):
    def __init__(self, input_data):
        self.input_data = input_data

    def parse_input(self):
        reports = [[int(level) for level in report.split()] for report in self.input_data.strip().split('\n')]
        return reports

    def solve_part1(self):
        reports = self.parse_input()
        safe_reports = 0

        for report in reports:
            differences = [b - a for a, b in zip(report, report[1:])]
            
            # Check if strictly increasing with step between 1 and 3
            is_increasing = all(1 <= diff <= 3 for diff in differences)
            
            # Check if strictly decreasing with step between 1 and 3
            is_decreasing = all(-3 <= diff <= -1 for diff in differences)

            if is_increasing or is_decreasing:
                safe_reports += 1

        return safe_reports

    def solve_part2(self):
        reports = self.parse_input()
        safe_reports = 0

        def is_valid(report):
            diffs = [b - a for a, b in zip(report, report[1:])]
            is_inc = all(1 <= d <= 3 for d in diffs)
            is_dec = all(-3 <= d <= -1 for d in diffs)
            return is_inc or is_dec

        for report in reports:
            if is_valid(report):
                safe_reports += 1
                print(report)
                continue

            # Try removing each single level to fix the report
            for i in range(len(report)):
                fixed = report[:i] + report[i+1:]
                if is_valid(fixed):
                    safe_reports += 1
                    print(report)
                    break  # only one fix allowed

        return safe_reports


    # My mistake was that I was removing always the current level and never the next level which could actually be the problem

    # def solve_part2(self):
    #     reports = self.parse_input()

    #     safe_reports = 0

    #     for report in reports:
    #         is_increasing = True
    #         is_decreasing = True
    #         for i in range(len(report)):
    #             current_level = report[i]
    #             next_level = report[i + 1] if i < len(report) - 1 else None

    #             if next_level != None:
    #                 if not (1 <= next_level - current_level <= 3):
    #                     report_copy = list(report)
    #                     report_copy.pop(i)
    #                     for j in range(len(report_copy)):
    #                         cp_current_level = report_copy[j]
    #                         cp_next_level = report_copy[j + 1] if j < len(report_copy) - 1 else None
    #                         if cp_next_level != None:
    #                             if not (1 <= cp_next_level - cp_current_level <= 3):
    #                                 is_increasing = False
    #             if next_level != None:
    #                 if not (1 <= current_level - next_level <= 3):
    #                     report_2copy = list(report)
    #                     report_2copy.pop(i)
    #                     for q in range(len(report_2copy)):
    #                         cp2_current_level = report_2copy[q]
    #                         cp2_next_level = report_2copy[q + 1] if q < len(report_2copy) - 1 else None
    #                         if cp2_next_level != None:
    #                             if not (1 <= cp2_current_level - cp2_next_level <= 3):
    #                                 is_decreasing = False
    #         if is_increasing  or is_decreasing:
    #             safe_reports += 1
    #             print(report)

    #     return safe_reports

    # def solve_part2(self):
    #     reports = self.parse_input()

    #     safe_reports = 0

    #     for report in reports:
    #         is_increasing = True
    #         is_decreasing = True
    #         for i in range(len(report)):
    #             current_level = report[i]
    #             next_level = report[i + 1] if i < len(report) - 1 else None

    #             if next_level != None:
    #                 if current_level >= next_level or current_level + 3 < next_level or current_level + 1 > next_level:
    #                     report_copy = list(report)
    #                     report_copy.pop(i)
    #                     for j in range(len(report_copy)):
    #                         cp_current_level = report_copy[j]
    #                         cp_next_level = report_copy[j + 1] if j < len(report_copy) - 1 else None
    #                         if cp_next_level != None:
    #                             if cp_current_level >= cp_next_level or cp_current_level + 3 < cp_next_level or cp_current_level + 1 > cp_next_level:
    #                                 is_increasing = False
    #             if next_level != None:
    #                 if current_level <= next_level or current_level - 3 > next_level or current_level - 1 < next_level:
    #                     report_2copy = list(report)
    #                     report_2copy.pop(i)
    #                     for q in range(len(report_2copy)):
    #                         cp2_current_level = report_2copy[q]
    #                         cp2_next_level = report_2copy[q + 1] if q < len(report_2copy) - 1 else None
    #                         if cp2_next_level != None:
    #                             if cp2_current_level <= cp2_next_level or cp2_current_level - 3 > cp2_next_level or cp2_current_level - 1 < cp2_next_level:
    #                                 is_decreasing = False
    #         if is_increasing  or is_decreasing:
    #             safe_reports += 1
    #             print(report)

    #     return safe_reports

    # def solve_part1(self):
    #     reports = self.parse_input()

    #     safe_reports = 0

    #     # trying if increasing
    #     for report in reports:
    #         whole_report_flag = True
    #         for i in range(len(report)):
    #             current_level = report[i]
    #             next_level = report[i + 1] if i < len(report) - 1 else None

    #             if next_level != None:
    #                 if current_level >= next_level or current_level + 3 < next_level or current_level + 1 > next_level:
    #                     whole_report_flag = False
    #         if whole_report_flag:
    #             safe_reports += 1


    #     # trying if decreasing
    #     for report in reports:
    #         whole_report_flag = True
    #         for i in range(len(report)):
    #             current_level = report[i]
    #             next_level = report[i + 1] if i < len(report) - 1 else None

    #             if next_level != None:
    #                 if current_level <= next_level or current_level - 3 > next_level or current_level - 1 < next_level:
    #                     whole_report_flag = False
    #         if whole_report_flag:
    #             safe_reports += 1

    #     return safe_reports







