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

//Button functions ===================================

inline void MainWindow::Go(string dst) {
    Room* nextRoom = game.currentRoom->nextRoom(dst);
    if (nextRoom == NULL) {
        cout << "[Impossible!] You cannot go " << dst << " anymore! Check the room's exits..." << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    cout << endl << game.currentRoom->longDescription() << endl;
}

//quit button
void MainWindow::on_pushButton_2_clicked()
{
    qApp->closeAllWindows();
}

//Go East button
void MainWindow::on_pushButton_clicked()
{
    Go("east");
}

//Go South button
void MainWindow::on_pushButton_3_clicked()
{
    Go("south");
}

//Go West Button
void MainWindow::on_pushButton_4_clicked()
{
    Go("west");
}

//Go North button
void MainWindow::on_pushButton_5_clicked()
{
    Go("north");
}

//Help display button
void MainWindow::on_pushButton_6_clicked()
{
    game.printHelp();
}

//Random Teleportation button
void MainWindow::on_pushButton_7_clicked()
{
    string strRoomList[10] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};
    string ranDst = strRoomList[rand()%10];

    cout << endl << "[Teleportation] teleported to a random room: room  "<< ranDst << endl;
    game.currentRoom = game.roomList[ranDst];
    cout << game.currentRoom->longDescription() << endl;
    return;
}

//Wordle button
void MainWindow::on_pushButton_8_clicked()
{
    game.wordle();
}

//Map display button
void MainWindow::on_pushButton_9_clicked()
{
    cout << endl;
    cout << "[h] --- [f] --- [g]" << endl;
    cout << "         |         " << endl;
    cout << "         |         " << endl;
    cout << "[c] --- [a] --- [b]" << endl;
    cout << "         |         " << endl;
    cout << "         |         " << endl;
    cout << "[i] --- [d] --- [e]" << endl;
    cout << " |                 " << endl;
    cout << " |                 " << endl;
    cout << "[j]                " << endl;
    cout << endl;
}

