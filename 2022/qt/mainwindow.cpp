#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aoc2022.h"


using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->comboBox->addItems({"1", "2", "3", "4", "5", "6", "7", "8", "9", "10",
                            "11"});
    ui->textEdit->setText("Always provide right input for the right day\n"
                          "If not there is a possibility that program will crash without any warning!\n");
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::execute);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::execute()
{
    AoC2022 AoC;
    QString input = ui->lineEdit->text();

    QString output_text = "The result is %1 \n";
    int choice = ui->comboBox->currentIndex() + 1;
    int part = ui->radioButtonp1->isChecked() ? 1 : 2;


    try {
        switch (choice) {
        case 1:
            output_text = part == 1 ? output_text.arg(AoC.day_01_1(input)) : output_text.arg(AoC.day_01_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 2:
            output_text = part == 1 ? output_text.arg(AoC.day_02_1(input)) : output_text.arg(AoC.day_02_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 3:
            output_text = part == 1 ? output_text.arg(AoC.day_03_1(input)) : output_text.arg(AoC.day_03_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 4:
            output_text = part == 1 ? output_text.arg(AoC.day_04_1(input)) : output_text.arg(AoC.day_04_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 5:
            output_text = part == 1 ? output_text.arg(QString::fromStdString(AoC.day_05_1(input))) :
                                      output_text.arg(QString::fromStdString(AoC.day_05_2(input)));
            ui->textEdit->setText(output_text);
            break;
        case 6:
            output_text = part == 1 ? output_text.arg(AoC.day_06_1(input)) : output_text.arg(AoC.day_06_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 7:
            output_text = part == 1 ? output_text.arg(AoC.day_07_1(input)) : output_text.arg(AoC.day_07_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 8:
            output_text = part == 1 ? output_text.arg(AoC.day_08_1(input)) : output_text.arg(AoC.day_08_2(input));
            ui->textEdit->setText(output_text);
            break;
        case 9:
            ui->textEdit->setText("NOT SOLVED YET");
            break;
        case 10:
            output_text = part == 1 ? output_text.arg(AoC.day_10_1(input)) : output_text.arg(QString::fromStdString(AoC.day_10_2(input)));
            ui->textEdit->setText(output_text);
            break;
        case 11:
            output_text = part == 1 ? output_text.arg(AoC.day_11_1(input)) : output_text.arg(AoC.day_11_2(input));
            ui->textEdit->setText(output_text);
            break;
        default:
            break;
        }
    } catch (...) {
        ui->textEdit->setText("Invalid input! \n"
                              "Please put valid input into the input line above.");
    }

    // It over-writes the "The result is 0" statement because of an empty input line
    if (input.isEmpty()) {
        ui->textEdit->setText("Invalid input! \n"
                              "Please put valid input into the input line above.");
    }

}













