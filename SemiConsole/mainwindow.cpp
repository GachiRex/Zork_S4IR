#include <iostream>
using namespace std;

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Command.h"
#include "CommandWords.h"
#include "ZorkUL.h"

ZorkUL game;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    redirect = new QDebugStream(cout, ui ->textEdit);
    ZorkUL game;
    game.printWelcome();

}

MainWindow::~MainWindow()
{
    delete redirect;
    delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{
    string input = ui->lineEdit->text().toStdString();
    cout << input << endl;                                      //
    ui->lineEdit->clear();                                      // Clear text from lineEdit and display it on textEdit

}

void MainWindow::on_pushButton_6_clicked()
{
    game.printHelp();
}

