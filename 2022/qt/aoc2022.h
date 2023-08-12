#ifndef AOC2022_H
#define AOC2022_H

#include <iostream>
#include <vector>

#include <QString>
#include <QTextStream>


using namespace std;

class AoC2022
{
public:
    AoC2022();
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

    int day_10_1(QString user_input);
    string day_10_2(QString user_input);

    int day_11_1(QString user_input);
    long long int day_11_2(QString user_input);

private:
};

#endif // AOC2022_H
