#include "utilities.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>

#include <QTextStream>
#include <QString>

namespace Utilities {

    vector<string> splitString(const string& str, char splitter)
    {
        vector<string> tokens;
        stringstream ss(str);
        string temp;
        // split into new "lines" based on character
        while (getline(ss, temp, splitter)) {
            tokens.push_back(temp);
        }
        return tokens;
    }

    vector<string> readAllLinesInFile(const filesystem::path& path)
    {
        auto lines = vector<string>{};
        if (!filesystem::exists(path))
        {
            return lines;
        }

        auto fileStream = ifstream{ path };
        auto currentLine = string{};
        while (getline(fileStream, currentLine))
        {
            lines.emplace_back(currentLine);
        }

        return lines;
    }

    vector<string> splitQStringByNewline(const QString& inputString) {
        vector<string> result;
        istringstream iss(inputString.toStdString());
        string line;

        while (std::getline(iss, line, '\n')) {
            result.push_back(line);
        }

        return result;
    }

    void verifyElseCrash(bool bAssert)
    {
        assert(bAssert);
        if (!bAssert)
        {
            terminate();
        }
    }

    void addStartEnd(vector<int> &array, string item1, string item2)
    {
        array.insert(array.begin(), stoi(item1));
        array.insert(array.begin() + 1, stoi(item2));

    }

    fstream& goToLine(fstream& file, unsigned int num){
        file.seekg(ios::beg);
        for(int i=0; i < num - 1; ++i){
            file.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        return file;
    }

    bool isInteger(const string& str) {
        try {
            stoi(str);
            return true;
        } catch (...) {
            return false;
        }
    }

}
