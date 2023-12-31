#include "aoc2022.h"
#include "Utilities/utilities.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <sstream>
#include <limits>
#include <unordered_set>
#include <set>
#include <unordered_map>
#include <numeric>
#include <stack>
#include <map>

#include <QTextStream>
#include <QString>

using namespace std;


AoC2022::AoC2022()
{
    int day_01_1(QString input);
    int day_01_2(QString input);

    int day_02_1(QString input);
    int day_02_2(QString input);

    int day_03_1(QString input);
    int day_03_2(QString input);

    int day_04_1(QString input);
    int day_04_2(QString input);

    string day_05_1(QString user_input);
    string day_05_2(QString user_input);

    int day_06_1(QString input);
    int day_06_2(QString input);

    int day_07_1(QString input);
    int day_07_2(QString input);

    int day_08_1(QString user_input);
    int day_08_2(QString user_input);

    int day_09_1(QString user_input);
    int day_09_2(QString user_input);

    int day_10_1(QString user_input);
    string day_10_2(QString user_input);

    int day_11_1(QString user_input);
    long long int day_11_2(QString user_input);

}

// Find the Elf carrying the most Calories. How many total Calories is that Elf carrying?
int AoC2022::day_01_1(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line;
    int max = 0;
    int sum = 0;

    for (const auto& line : data) {
        if (line.empty()) {
            if (max < sum) {
                max = sum;
            }
            sum = 0;
            continue;
        }

        sum += stoi(line);
    }

    return max;
}

// Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?
int AoC2022::day_01_2(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line;
    int sum = 0;

    int max1 = 0;
    int max2 = 0;
    int max3 = 0;

    for (const auto& line : data) {
       if (line.empty()) {
           if (sum > max1) {
                max3 = max2;
                max2 = max1;
                max1 = sum;
           } else if (sum > max2) {
               max3 = max2;
               max2 = sum;
           } else if (sum > max3) {
               max3 = sum;
           }
           sum = 0;
        } else {
            sum += stoi(line);
        }
    }

    return (max1 + max2 + max3);
}


// What would your total score be if everything goes exactly according to your strategy guide?
int AoC2022::day_02_1(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line, elf_choice, elf_suggestion;
    int score = 0;

    for (const auto& line : data) {
        elf_choice = line.substr(0, 1); // strtok_r(line, " , "); --- didn't work out
        elf_suggestion = line.substr(2, 1);

        // Getting points for shape you selected - 1, 2, 3
        if (!elf_suggestion.compare("X")) {
            score += 1;
        } else if (!elf_suggestion.compare("Y")) {
            score += 2;
        } else if (!elf_suggestion.compare("Z")) {
            score += 3;
        }

        // Getting points for outcome of the round - 0, 3, 6
        if (!elf_suggestion.compare("X") && !elf_choice.compare("A")) { // draw
            score += 3;
        } else if (!elf_suggestion.compare("X") && !elf_choice.compare("B")) {
            continue;
        } else if (!elf_suggestion.compare("X") && !elf_choice.compare("C")) {
            score += 6;
        } else if (!elf_suggestion.compare("Y") && !elf_choice.compare("A")) {
            score += 6;
        } else if (!elf_suggestion.compare("Y") && !elf_choice.compare("B")) { // draw
            score += 3;
        } else if (!elf_suggestion.compare("Y") && !elf_choice.compare("C")) {
            continue;
        } else if (!elf_suggestion.compare("Z") && !elf_choice.compare("A")) {
            continue;
        } else if (!elf_suggestion.compare("Z") && !elf_choice.compare("B")) {
            score += 6;
        } else if (!elf_suggestion.compare("Z") && !elf_choice.compare("C")) { // draw
            score += 3;
        }
    }

    return score;
}

// Following the Elf's instructions for the second column,
//      what would your total score be if everything goes exactly according to your strategy guide?
int AoC2022::day_02_2(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line, elf_choice, round_end;
    int score = 0;

    for (const auto& line : data) {
        elf_choice = line.substr(0, 1);
        round_end = line.substr(2, 1);

        // X - need to lose
        // Y - need to end up in draw
        // Z - need to win

        // Getting points for shape + points for outcome of the round - 1, 2, 3 + 0, 3, 6
        if (!elf_choice.compare("A") && !round_end.compare("X")) {
            score += 3;
        } else if (!elf_choice.compare("A") && !round_end.compare("Y")) { // draw
            score += 1 + 3;
        } else if (!elf_choice.compare("A") && !round_end.compare("Z")) {
            score += 2 + 6;
        } else if (!elf_choice.compare("B") && !round_end.compare("X")) {
            score += 1;
        } else if (!elf_choice.compare("B") && !round_end.compare("Y")) { // draw
            score += 2 + 3;
        } else if (!elf_choice.compare("B") && !round_end.compare("Z")) {
            score += 3 + 6;
        } else if (!elf_choice.compare("C") && !round_end.compare("X")) {
            score += 2;
        } else if (!elf_choice.compare("C") && !round_end.compare("Y")) { // draw
            score += 3 + 3;
        } else if (!elf_choice.compare("C") && !round_end.compare("Z")) {
            score += 1 + 6;
        }
    }

    return score;
}

// Find the item type that appears in both compartments of each rucksack.
    // What is the sum of the priorities of those item types?
int AoC2022::day_03_1(QString input) {
    auto data = Utilities::splitQStringByNewline(input);

    int priority_sum = 0;

    for (const auto& line : data) {
        bool foundMatch = false;

        while (!foundMatch) {
            int length = line.length();
            string first_compartment = line.substr(0, length / 2);
            string second_compartment = line.substr(length / 2, length);

            for (int i = 0; i < first_compartment.length(); i++) {
               for (int j = 0; j < first_compartment.length(); j++) {
                   if (first_compartment[i] == second_compartment[j]) {
                       if (islower(first_compartment[i])) {
                           priority_sum += first_compartment[i] - 'a' + 1;
                       } else {
                           priority_sum += first_compartment[i] - 'A' + 27;
                       }
                       foundMatch = true;
                       break; // No need to continue inner loop after finding match
                   }
               }
               if (foundMatch) {
                   break; // No need to continue outer loop after finding match
               }
            }
        }
    }

    return priority_sum;
}

// // Find the item type that corresponds to the badges of each three-Elf group.
    // // What is the sum of the priorities of those item types?
int AoC2022::day_03_2(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    int priority_sum = 0;

    string line1, line2, line3;

    for (int idx = 0; idx + 2 < data.size(); idx += 3) {
        line1 = data[idx];
        line2 = data[idx + 1];
        line3 = data[idx + 2];

        bool matchFound = false;

        for (int i = 0; i < line1.length(); i++) {
            for (int j = 0; j < line2.length(); j++) {
               if (line1[i] == line2[j]) {
                   for (int k = 0; k < line3.length(); k++) {
                       if (line1[i] == line3[k]) {
                           if (islower(line1[i])) {
                               priority_sum += line1[i] - 96;
                           } else {
                               priority_sum += line1[i] - 38;
                           }
                           matchFound = true;
                           break; // No need to continue innermost loop after finding match
                       }
                   }
                   if (matchFound) {
                       break; // No need to continue middle loop after finding match
                   }
               }
            }
            if (matchFound) {
               break; // No need to continue outermost loop after finding match
            }
        }
    }

    return priority_sum;
}


// In how many assignment pairs does one range fully contain the other?
int AoC2022::day_04_1(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line;
    int result = 0, check = 1;
    vector<int> part1, part2;

    for (const auto& line : data) {
        vector<string> tokens = Utilities::splitString(line, ',');

        for (vector<string>::const_iterator it = tokens.begin(), end_it = tokens.end(); it != end_it; ++it) {
            const string& token = *it;
            vector<string> range = Utilities::splitString(token, '-');
            if (check == 1) {
                Utilities::addStartEnd(part1, range[0], range[1]);
                check++;
                continue;
            }
            Utilities::addStartEnd(part2, range[0], range[1]);
            check = 1;
        }

        if ((part1[0] <= part2[0] && part1[1] >= part2[1]) || (part2[0] <= part1[0] && part2[1] >= part1[1])) {
            result++;
        }
    }

    return result;
}

// In how many assignment pairs do the ranges overlap?
int AoC2022::day_04_2(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line;
    int result = 0, check = 1;
    vector<int> part1, part2;

    for (const auto& line : data) {
        vector<string> tokens = Utilities::splitString(line, ',');

        for (vector<string>::const_iterator it = tokens.begin(), end_it = tokens.end(); it != end_it; ++it) {
            const string& token = *it;
            vector<string> range = Utilities::splitString(token, '-');
            if (check == 1) {
                Utilities::addStartEnd(part1, range[0], range[1]);
                check++;
                continue;
            }
            Utilities::addStartEnd(part2, range[0], range[1]);
            check = 1;
        }

        if ((part1[0] <= part2[1] && part2[0] <= part1[1])) {
            result++;
        }
    }

    return result;
}


// After the rearrangement procedure completes, what crate ends up on top of each stack?
string AoC2022::day_05_1(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    // Find the empty line in out input.
    auto blankIndex = -1;
    for (auto i = 0; i < input.size(); ++i) {
        if (input[i].size() == 0) { // blank line
            blankIndex = i;
            break;
        }
    }

    // Setup initial state.
    auto stacks = vector<stack<char>>{};
    const auto& stackLabels = input[blankIndex - 1];
    for (auto i = 0; i < stackLabels.size(); ++i) {
        if (stackLabels[i] == ' ') {
            continue;
        }

        auto currentStack = stack<char>{};
        for (auto lineIndex = blankIndex - 2; lineIndex >= 0; --lineIndex) {
            const auto& line = input[lineIndex];
            const auto& crate = line[i];
            if (crate == ' ') {
                break;
            }

            currentStack.push(crate);
        }
        stacks.emplace_back(currentStack);
    }

    // Process moves.
    for (auto i = blankIndex + 1; i < input.size(); ++i) {
        auto tokens = Utilities::splitString(input[i], ' ');
        auto amount = stoi(tokens[1]);
        auto from = stoi(tokens[3]) - 1;
        auto to = stoi(tokens[5]) - 1;

        for (int i = 1; i <= amount; ++i) {
            auto crate = stacks[from].top();
            stacks[from].pop();
            stacks[to].push(crate);
        }
    }

    // Access the top elements.
    string result = "";
    for (const auto& currentStack : stacks) {
        result += currentStack.top();
    }

    return result;
}

// After the rearrangement procedure completes, what crate ends up on top of each stack?
string AoC2022::day_05_2(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    // Find the empty line in out input.
    auto blankIndex = -1;
    for (auto i = 0; i < input.size(); ++i) {
        if (input[i].size() == 0) { // blank line
            blankIndex = i;
            break;
        }
    }

    // Setup initial state.
    auto stacks = vector<stack<char>>{};
    const auto& stackLabels = input[blankIndex - 1];
    for (auto i = 0; i < stackLabels.size(); ++i) {
        if (stackLabels[i] == ' ') {
            continue;
        }

        auto currentStack = stack<char>{};
        for (auto lineIndex = blankIndex - 2; lineIndex >= 0; --lineIndex) {
            const auto& line = input[lineIndex];
            const auto& crate = line[i];
            if (crate == ' ') {
                break;
            }

            currentStack.push(crate);
        }
        stacks.emplace_back(currentStack);
    }

    // Process moves.
    for (auto i = blankIndex + 1; i < input.size(); ++i) {
        auto tokens = Utilities::splitString(input[i], ' ');
        auto amount = stoi(tokens[1]);
        auto from = stoi(tokens[3]) - 1;
        auto to = stoi(tokens[5]) - 1;

        auto crates = vector<char>{};
        while (amount-- > 0) {
            auto crate = stacks[from].top();
            stacks[from].pop();
            crates.emplace_back(crate);
        }

        reverse(crates.begin(), crates.end());

        for (const auto& crate : crates) {
            stacks[to].push(crate);
        }
    }

    // Access the top elements.
    string result = "";
    for (const auto& currentStack : stacks) {
        result += currentStack.top();
    }

    return result;


}


// How many characters need to be processed before the first start-of-packet marker is detected?
int AoC2022::day_06_1(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line, part;
    line = data[0];

    int i = 0, check = 0;

    LOOP:while (i + 4 < line.length()) {
        part = line.substr(i, 4);

        for (int j = 0; j < part.length(); j++) {
            for (int k = 0; k < part.length(); k++) {
                if (part[j] == part[k] && j != k) {
                    i++;
                    check = 0;
                    goto LOOP;
                }
                check++;
                if (check == 16) {
                    return i + 4;
                }
            }
        }
        i++;
        check = 0;
    }

    return 0;
}

// How many characters need to be processed before the first start-of-message marker is detected?
int AoC2022::day_06_2(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    string line, part;
    line = data[0];

    int i = 0, check = 0;

    LOOP:while (i + 14 < line.length()) {
        part = line.substr(i, 14);

        for (int j = 0; j < part.length(); j++) {
            for (int k = 0; k < part.length(); k++) {
                if (part[j] == part[k] && j != k) {
                    i++;
                    check = 0;
                    goto LOOP;
                }
                check++;
                if (check == 196) {
                    return i + 14;
                }
            }
        }
        i++;
        check = 0;
    }

    return 0;
}


// DAY 7
// Find all of the directories with a total size of at most 100000.
    // What is the sum of the total sizes of those directories?
struct ElfFile
{
    string path;
    int size = 0;
};

struct ElfDirectory
{
    string path;
    int size = -1;
    unordered_set<string> child_directories;
    unordered_set<string> child_files;

};

auto all_directories = unordered_map<string, ElfDirectory>{};
auto all_files = unordered_map<string, ElfFile>{};

void readInput7(QString input)
{
    auto data = Utilities::splitQStringByNewline(input);

    all_directories["/"] = ElfDirectory{"/"};

    auto pwd = vector<string>{{"/"}};

    for (const auto& line : data) {
        auto tokens = Utilities::splitString(line, ' ');
        if (tokens[0] == "$") {
            if (tokens[1] == "ls") {
                continue;
            } else {
                Utilities::verifyElseCrash(tokens[1] == "cd");
                const auto& target = tokens[2];
                if (target == "/") {
                    pwd.clear();
                    pwd.emplace_back("/");
                } else if (target == "..") {
                    pwd.pop_back();
                } else {
                    pwd.emplace_back(pwd.back() + target + "/");
                }
            }
        } else {
            auto& parent = all_directories.at(pwd.back());
            if (tokens[0] == "dir") {
                auto path = pwd.back() + tokens[1] + "/";
                if (all_directories.find(path) == all_directories.end()) {
                    all_directories[path] = ElfDirectory{ path };
                }

                parent.child_directories.insert(path);
            } else {
                auto path = pwd.back() + tokens[1];
                if (all_files.find(path) == all_files.end()) {
                    all_files[path] = ElfFile{ path, stoi(tokens[0]) };
                }

                parent.child_files.insert(path);
            }
        }
    }

}

int CalculateDirectorySize(ElfDirectory& directory)
{
    if (directory.size >= 0) {
        return directory.size;
    }

    int totalSizeOfFiles = accumulate(directory.child_files.begin(), directory.child_files.end(), 0,
                                           [](int sum, const string& path) { return sum + all_files.at(path).size; });

    int totalSizeOfDirectories = 0;
    for (const string& path : directory.child_directories) {
        totalSizeOfDirectories += CalculateDirectorySize(all_directories.at(path));
    }

    directory.size = totalSizeOfFiles + totalSizeOfDirectories;
    return directory.size;
}

int AoC2022::day_07_1(QString input)
{
    readInput7(input);
    CalculateDirectorySize(all_directories.at("/"));

    auto total_dir_size = accumulate(all_directories.begin(), all_directories.end(), 0,
                                        [](int sum, const pair<std::string, ElfDirectory>& directoryPair) {
                                            const ElfDirectory& directory = directoryPair.second;
                                            return sum + (directory.size <= 100000 ? directory.size : 0);
                                        });

    return total_dir_size;
}

int AoC2022::day_07_2(QString input)
{
    // Read the input and calculate the size of directories
    readInput7(input);
    CalculateDirectorySize(all_directories.at("/"));

    constexpr auto totalSpace = 70000000;
    constexpr auto desiredSpace = 30000000;

    // Calculate unused space in the root directory
    const auto unusedSpace = totalSpace - all_directories.at("/").size;

    // Calculate the size to delete from the directories to meet the desired space
    const auto sizeToDelete = desiredSpace - unusedSpace;

    // Get a vector of directories sorted by size
    vector<ElfDirectory> directoriesSortedBySize;
    for (const auto& entry : all_directories) {
        directoriesSortedBySize.push_back(entry.second);
    }
    sort(directoriesSortedBySize.begin(), directoriesSortedBySize.end(),
              [](const ElfDirectory& a, const ElfDirectory& b) { return a.size < b.size; });

    // Find the directory to delete based on the sizeToDelete
    auto deleted_directory_size = 0;
    for (const auto& directory : directoriesSortedBySize) {
        if (directory.size >= sizeToDelete) {
            deleted_directory_size = directory.size;
            break;
        }
    }

    return deleted_directory_size;
}


// Consider your map; how many trees are visible from outside the grid?
int AoC2022::day_08_1(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    auto treeMap = vector<vector<int>>{};
    auto visibleTreesSum = 0;

    // Putting input data into treeMap
    for (int i = 0; i < input.size(); ++i) {
        auto row = vector<int>{};
        for (int j = 0; j < input[i].length(); ++j) {
            row.push_back(stoi(input[i].substr(j, 1))); //treeMap[i][j] =
        }
        treeMap.push_back(row);
    }

    // Writting out treeMap
    // QTextStream qout(stdout);
    // for (int i = 0; i < treeMap.size(); ++i) {
        // for (int j = 0; j < treeMap[i].size(); ++j) {
            // qout << treeMap[i][j];
            // qout << " ";
        // }
        // qout << " \n";
    // }

    // Algorithm for checking if some tree is visible
    auto columnSize = treeMap.size() - 1;
    for (int i = 0; i <= columnSize; i++) {
        auto rowSize = treeMap[i].size() - 1;
        for (int j = 0; j <= rowSize; j++) {
            if (i == 0 || j == 0 || i == columnSize || j == rowSize) {
                visibleTreesSum++;
                continue;
            }

            // Checking the if the tree is visible from the LEFT side
            auto leftSideTrees = j;
            auto treeCounter = 0;
            for (int k = 0; k < leftSideTrees; ++k) {
                if (treeMap[i][j] > treeMap[i][k]) {
                    treeCounter++;
                }
            }

            if (treeCounter == leftSideTrees) {
                visibleTreesSum++;
                continue;
            }

            // Checking the if the tree is visible from the RIGHT side
            auto rightSideTrees = j + 1;
            treeCounter = 0;
            for (int k = rightSideTrees; k <= rowSize; ++k) {
                if (treeMap[i][j] > treeMap[i][k]) {
                    treeCounter++;
                }
            }

            if (treeCounter == rowSize - rightSideTrees + 1) {
                visibleTreesSum++;
                continue;
            }

            // Checking the if the tree is visible from the TOP side
            auto topTrees = i;
            treeCounter = 0;
            for (int k = 0; k < topTrees; ++k) {
                if (treeMap[i][j] > treeMap[k][j]) {
                    treeCounter++;
                }
            }

            if (treeCounter == topTrees) {
                visibleTreesSum++;
                continue;
            }

            // Checking the if the tree is visible from the BOTTOM side
            auto bottomTree = i;
            treeCounter = 0;
            for (int k = bottomTree + 1; k <= columnSize; ++k) {
                if (treeMap[i][j] > treeMap[k][j]) {
                    treeCounter++;
                }
            }

            if (treeCounter ==  columnSize - bottomTree) {
                visibleTreesSum++;
                continue;
            }
        }
    }


    return visibleTreesSum;
}

// Consider each tree on your map.
    // What is the highest scenic score possible for any tree?
int AoC2022::day_08_2(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    auto treeMap = vector<vector<int>>{};
    auto highestScenicScore = 1;
    auto scenicScore = 1;

    // Putting input data into treeMap
    for (int i = 0; i < input.size(); ++i) {
        auto row = vector<int>{};
        for (int j = 0; j < input[i].length(); ++j) {
            row.push_back(stoi(input[i].substr(j, 1))); //treeMap[i][j] =
        }
        treeMap.push_back(row);
    }

    // Writting out treeMap
    // QTextStream qout(stdout);
    // for (int i = 0; i < treeMap.size(); ++i) {
        // for (int j = 0; j < treeMap[i].size(); ++j) {
            // qout << treeMap[i][j];
            // qout << " ";
        // }
        // qout << " \n";
    // }

    // Algorithm for checking for the highest scenic score
    auto columnSize = treeMap.size() - 1;
    for (int i = 0; i <= columnSize; i++) {
        auto rowSize = treeMap[i].size() - 1;
        for (int j = 0; j <= rowSize; j++) {
            if (i == 0 || j == 0 || i == columnSize || j == rowSize) {
                continue;
            }

            auto current = treeMap[i][j];

            // Checking the what is the scenic score from LEFT
            auto visibleLeft = 0;
            for (auto k = j - 1; k >= 0 ; --k) {
                ++visibleLeft;
                if (treeMap[i][k] >= current) { break; }
            }

            // Checking the what is the scenic score from RIGHT
            auto visibleRight = 0;
            for (auto k = j + 1; k <= rowSize ; ++k) {
                ++visibleRight;
                if (treeMap[i][k] >= current) { break; }
            }

            // Checking the what is the scenic score from TOP
            auto visibleTop = 0;
            for (auto k = i - 1; k >= 0 ; --k) {
                ++visibleTop;
                if (treeMap[k][j] >= current) { break; }
            }

            // Checking the what is the scenic score from BOTTOM
            auto visibleBottom = 0;
            for (auto k = i + 1; k <= columnSize ; ++k) {
                ++visibleBottom;
                if (treeMap[k][j] >= current) { break; }
            }

            scenicScore *= visibleLeft * visibleRight * visibleTop * visibleBottom;

            if (scenicScore > highestScenicScore) {
                    highestScenicScore = scenicScore;
            }

            scenicScore = 1;
        }
    }


    return highestScenicScore;
}


// Simulate your complete hypothetical series of motions.
    // How many positions does the tail of the rope visit at least once?
struct Position {
    int x, y;

    // Custom comparison operator for set
    bool operator<(const Position& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

template<class T, class U>
QTextStream& operator<<(QTextStream& out, const QPair<T, U>& pair) {
    QTextStream qout(stdout);
    qout << QString("QPair<%1, %2> ")
               .arg(QString::fromStdString(pair.first))
               .arg(QString::number(pair.second));
    return out;
}

Position getNextTailPosition(Position *head, Position *tail) {
    // Update tail's position if head is not adjacent to tail
    int rowDist = abs(head->x - tail->x);
    int colDist = abs(head->y - tail->y);

    if (rowDist > 1 || colDist > 1) {
        // Move tail diagonally towards head
        // The tail->x += 0 or tail->y += 0 cannot happen because of the if statement above
        // But I wanted to use the ternary operator so I had to include the else case...
        tail->x += (head->x > tail->x) ? 1 : (head->x < tail->x) ? -1 : 0;
        tail->y += (head->y > tail->y) ? 1 : (head->y < tail->y) ? -1 : 0;
    } else if (rowDist == 2) {
        tail->x += (head->x > tail->x) ? 1 : -1;
    } else if (colDist == 2) {
        tail->y += (head->y > tail->y) ? 1 : -1;
    }

    return *tail;
}

// Simulate your complete hypothetical series of motions.
    // How many positions does the tail of the rope visit at least once?
int AoC2022::day_09_1(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);
    vector<pair<string, int>> moves;

    // Parse the input
    for (const auto& line : input) {
        auto tokens =  Utilities::splitString(line, ' ');
        moves.push_back({tokens[0], stoi(tokens[1])});
    }

    // Print the input
    for (const auto& move : moves) {
        QTextStream qout(stdout);
        qout << move;
        qout << "\n";
    }

    Position head = {0, 0};  // Initial head position
    Position tail = {0, 0};  // Initial tail position
    set<Position> visitedPositions;  // Set to store visited positions

    visitedPositions.insert(tail);  // Mark the initial position as visited

    for (const auto& move : moves) {
        string direction = move.first;
        int steps = move.second;

        // Update head's position based on the movement
        for (auto i = 0; i < steps; ++i) {
            if (direction == "R") head.x++;
            else if (direction == "L") head.x--;
            else if (direction == "U") head.y++;
            else if (direction == "D") head.y--;

            getNextTailPosition(&head, &tail);

            // Mark the new tail position as visited
            visitedPositions.insert(tail);
        }
    }

    return visitedPositions.size();
}

// Simulate your complete series of motions on a larger rope with ten knots.
    // How many positions does the tail of the rope visit at least once?
int AoC2022::day_09_2(QString user_input)
{
    // auto input = Utilities::splitQStringByNewline(user_input);
    auto input = Utilities::readAllLinesInFile("/Users/ondrejpazourek/dev/cpp/advent-of-code/2022/qt/data/day_09.txt");
    vector<pair<string, int>> moves;

    // Parse the input
    for (const auto& line : input) {
        auto tokens =  Utilities::splitString(line, ' ');
        moves.push_back({tokens[0], stoi(tokens[1])});
    }

    Position head = {0, 0};  // Initial head position
    vector<Position> tails(10, {0, 0});  // Initial tails position

    set<Position> visitedPositions;  // Set to store visited positions

    visitedPositions.insert(tails[0]);  // Mark the initial position as visited

    for (const auto& move : moves) {
        string direction = move.first;
        int steps = move.second;

        // Update head's position based on the movement
        for (auto i = 0; i < steps; ++i) {
            if (direction == "R") head.x++;
            else if (direction == "L") head.x--;
            else if (direction == "U") head.y++;
            else if (direction == "D") head.y--;

            // Update tail positions based on the previous positions
            Position prevTail = tails[0];
            getNextTailPosition(&head, &tails[0]);

            for (auto j = 1; j < tails.size(); ++j) {
                    Position temp = tails[j];
                    getNextTailPosition(&prevTail, &tails[j]);
                    prevTail = temp;
            }

            // Mark the new tail positions as visited
            for (const auto& tail : tails) {
                visitedPositions.insert(tail);
            }
        }
    }

    return visitedPositions.size();
}


// Find the signal strength during the 20th, 60th, 100th, 140th, 180th, and 220th cycles.
    // What is the sum of these six signal strengths?
int AoC2022::day_10_1(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    auto x = 1;
    auto signalStrength = 0;

    auto values = vector<int>{};

    for (auto i = 0; i < input.size() - 1; ++i) {
        auto tokens = Utilities::splitString(input[i], ' ');

        if (tokens.size() == 1) {
            values.emplace_back(x);
            continue;
        }

        values.emplace_back(x);
        values.emplace_back(x);
        auto num = stoi(tokens[1]);
        x += num;
    }

    for (int index = 20; index <= 220; index += 40) {
        signalStrength += index * values[index - 1];
    }

    return signalStrength;
}

// Render the image given by your program.
    // What eight capital letters appear on your CRT?
string AoC2022::day_10_2(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);

    vector<vector<string>> crtScreen(7, vector<string>(41, " "));

    auto x = 1;
    auto signalStrength = 0;

    auto values = vector<int>{};

    for (auto i = 0; i < input.size() - 1; ++i) {
        auto tokens = Utilities::splitString(input[i], ' ');

        if (tokens.size() == 1) {
            values.emplace_back(x);
            continue;
        }

        values.emplace_back(x);
        values.emplace_back(x);
        auto num = stoi(tokens[1]);
        x += num;
    }

    auto crtPosition = 0;
    auto k = 0;
    for (auto i = 0; i < crtScreen.size() - 1; ++i) {
        for (auto j = 0; j < crtScreen[i].size() - 1; ++j) {
            auto sprite = values[k];
            if (crtPosition == sprite - 1 || crtPosition == sprite
                || crtPosition == sprite + 1) {
                crtScreen[i].at(j) = "#";
            } else {
                crtScreen[i].at(j) = ".";
            }

            crtPosition++;
            k++;
        }
        crtPosition -= 40;
    }

    // Printing the result to Terminal
        // TODO: print it in the output of the application
    QTextStream qout(stdout);
    for (int i = 0; i < crtScreen.size(); ++i) {
        for (int j = 0; j < crtScreen[i].size(); ++j) {
            qout << QString::fromStdString(crtScreen[i][j]);
            // qout << " ";
        }
        qout << " \n";
    }

    return "PCPBKAPJ";
}


typedef struct _monkey
{
    int id;
    vector<int> items;
    vector<string> operation;
    int testNum;
    int trueCase;
    int falseCase;
    int inspectNum = 0;
} Monkey;

void printMonkeys(vector<Monkey> monkeys) {
    QTextStream qout(stdout);
    for (auto i = 0; i < monkeys.size(); ++i) {
        qout << i << ": ";
        for (auto j = 0; j <monkeys[i].items.size(); ++j) {
            qout << monkeys[i].items[j] << ", ";
        }
        qout << "\n";
    }
    qout << "-------------------------\n";
}

// Figure out which monkeys to chase by counting how many items they inspect over 20 rounds.
    // What is the level of monkey business after 20 rounds of stuff-slinging simian shenanigans?
int AoC2022::day_11_1(QString user_input)
{
    auto input = Utilities::splitQStringByNewline(user_input);
    vector<Monkey> monkeys;

    // Parsing input
    for (auto i = 0; i < input.size() - 1; i += 7) {
        Monkey monkey;

        auto idLine = Utilities::splitString(input[i], ' ');
        monkey.id = stoi(idLine[1].substr(0, 1));

        auto items = Utilities::splitString(input[i + 1], ' ');
        for (auto j = 4; j < items.size(); ++j) {
            monkey.items.push_back(stoi(items[j].substr(0, 2)));
        }

        auto operation = Utilities::splitString(input[i + 2], ' ');
        for (auto j = 5; j < operation.size(); ++j) {
            monkey.operation.push_back(operation[j]);
        }

        auto test = Utilities::splitString(input[i + 3], ' ');
        monkey.testNum = stoi(test[5]);

        auto trueCaseLine = Utilities::splitString(input[i + 4], ' ');
        monkey.trueCase = stoi(trueCaseLine[9]);

        auto falseCaseLine = Utilities::splitString(input[i + 5], ' ');
        monkey.falseCase = stoi(falseCaseLine[9]);

        monkeys.push_back(monkey);
    }

    for (auto k = 0; k < 20; ++k) {
        // Round
        float worryLevel = 0;
        for (auto i = 0; i < monkeys.size(); ++i) {
            // Turn
            for (auto j = 0; j <monkeys[i].items.size(); ++j) {

                // Figure out its worry level
                if (monkeys[i].operation[1] == "*" && monkeys[i].operation[2] == "old") {
                    worryLevel = monkeys[i].items[j] * monkeys[i].items[j];
                } else if (monkeys[i].operation[1] == "+" && monkeys[i].operation[2] == "old") {
                    worryLevel = monkeys[i].items[j] + monkeys[i].items[j];
                } else if (monkeys[i].operation[1] == "*" && Utilities::isInteger(monkeys[i].operation[2])) {
                    worryLevel = monkeys[i].items[j] * stoi(monkeys[i].operation[2]);
                } else if (monkeys[i].operation[1] == "+" && Utilities::isInteger(monkeys[i].operation[2])) {
                    worryLevel = monkeys[i].items[j] + stoi(monkeys[i].operation[2]);
                }

                // Divide worry level by 3
                auto finalWorryLevel = static_cast<int>(floor(worryLevel / 3));

                // Deciding by the result of the test where the bag will be thrown
                int destination = finalWorryLevel % monkeys[i].testNum == 0 ? monkeys[i].trueCase : monkeys[i].falseCase;
                monkeys[destination].items.push_back(finalWorryLevel);

                // Adding 1 to the inspectNum so we can count the business level afterwards
                monkeys[i].inspectNum++;
            }

            // Remove the bags that were thrown
            monkeys[i].items.clear();
        }
        // printMonkeys(monkeys);
    }

    auto max1 = 0;
    auto max2 = 0;
    for (auto i = 0; i < monkeys.size(); ++i) {
       if (monkeys[i].inspectNum > max1) {
            max2 = max1;
            max1 = monkeys[i].inspectNum;
       } else if (monkeys[i].inspectNum > max2) {
           max2 = monkeys[i].inspectNum;
       }
    }

    return max1 * max2;
}

// Worry levels are no longer divided by three after each item is inspected;
// you'll need to find another way to keep your worry levels manageable.
// Starting again from the initial state in your puzzle input,
    // what is the level of monkey business after 10000 rounds?
// Resources:
    // Chinese Remainder Theorem: https://www.youtube.com/watch?v=zIFehsBHB8o
long long int AoC2022::day_11_2(QString user_input)
{
    // auto input = Utilities::splitQStringByNewline(user_input);
    auto input = Utilities::readAllLinesInFile("/Users/ondrejpazourek/dev/cpp/advent-of-code/2022/qt/data/day_11.txt");
    vector<Monkey> monkeys;

    // Parsing input
    for (auto i = 0; i < input.size() - 1; i += 7) {
        Monkey monkey;

        auto idLine = Utilities::splitString(input[i], ' ');
        monkey.id = stoi(idLine[1].substr(0, 1));

        auto items = Utilities::splitString(input[i + 1], ' ');
        for (auto j = 4; j < items.size(); ++j) {
            monkey.items.push_back(stoi(items[j].substr(0, 2)));
        }

        auto operation = Utilities::splitString(input[i + 2], ' ');
        for (auto j = 5; j < operation.size(); ++j) {
            monkey.operation.push_back(operation[j]);
        }

        auto test = Utilities::splitString(input[i + 3], ' ');
        monkey.testNum = stoi(test[5]);

        auto trueCaseLine = Utilities::splitString(input[i + 4], ' ');
        monkey.trueCase = stoi(trueCaseLine[9]);

        auto falseCaseLine = Utilities::splitString(input[i + 5], ' ');
        monkey.falseCase = stoi(falseCaseLine[9]);

        monkeys.push_back(monkey);
    }

    auto N = 1;
    for (const auto& monkey : monkeys) {
        N *= monkey.testNum;
    }

    for (auto k = 1; k <= 10000; ++k) {
        // Round
        for (auto i = 0; i < monkeys.size(); ++i) {
            // Turn
            long long int worryLevel = 0;
            for (auto j = 0; j < monkeys[i].items.size(); ++j) {

                // Figure out its worry level
                if (monkeys[i].operation[1] == "*" && monkeys[i].operation[2] == "old") {
                    worryLevel = monkeys[i].items[j] * monkeys[i].items[j];
                } else if (monkeys[i].operation[1] == "+" && monkeys[i].operation[2] == "old") {
                    worryLevel = monkeys[i].items[j] + monkeys[i].items[j];
                } else if (monkeys[i].operation[1] == "*" && Utilities::isInteger(monkeys[i].operation[2])) {
                    worryLevel = monkeys[i].items[j] * stoi(monkeys[i].operation[2]);
                } else if (monkeys[i].operation[1] == "+" && Utilities::isInteger(monkeys[i].operation[2])) {
                    worryLevel = monkeys[i].items[j] + stoi(monkeys[i].operation[2]);
                }

                // Instead of dividing finalWorryLevel by three we use module with the multiplied test numbers
                worryLevel = worryLevel % N;

                // Deciding by the result of the test where the bag will be thrown
                int destination = worryLevel % monkeys[i].testNum == 0 ? monkeys[i].trueCase : monkeys[i].falseCase;
                monkeys[destination].items.push_back(worryLevel);

                // Adding 1 to the inspectNum so we can count the business level afterwards
                monkeys[i].inspectNum++;
            }

            // Remove the bags that were thrown
            monkeys[i].items.clear();
        }

        // Test
        if (k % 1000 == 0) {
            QTextStream qout(stdout);
            for (const auto& monkey : monkeys) {
                qout << monkey.id;
                qout << " ";
                qout << monkey.inspectNum;
                qout << "\n";
            }
            qout << "\n";
        }
    }

    auto max1 = 0;
    auto max2 = 0;
    for (const auto& monkey : monkeys) {
       if (monkey.inspectNum > max1) {
            max2 = max1;
            max1 = monkey.inspectNum;
       } else if (monkey.inspectNum > max2) {
           max2 = monkey.inspectNum;
       }
    }

    return max1 * max2;
}




































