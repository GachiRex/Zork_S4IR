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

//Help display button
void MainWindow::on_pushButton_6_clicked()
{
    game.printHelp();
}

//Wordle button
void MainWindow::on_pushButton_8_clicked()
{
    game.wordle();
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

//Go North button
void MainWindow::on_pushButton_5_clicked()
{
    Room* nextRoom = game.currentRoom->nextRoom("north");
    if (nextRoom == NULL) {
        cout << "[Impossible] You cannot go North anymore! Check the room's exits..." << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    cout << endl << game.currentRoom->longDescription() << endl;
}

//Go West Button
void MainWindow::on_pushButton_4_clicked()
{
    Room* nextRoom = game.currentRoom->nextRoom("west");
    if (nextRoom == NULL) {
        cout << "[Impossible] You cannot go West anymore! Check the room's exits..." << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    cout << endl << game.currentRoom->longDescription() << endl;
}

//Go East button
void MainWindow::on_pushButton_clicked()
{
    Room* nextRoom = game.currentRoom->nextRoom("east");
    if (nextRoom == NULL) {
        cout << "[Impossible] You cannot go East anymore!Check the room's exits..." << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    cout << endl << game.currentRoom->longDescription() << endl;
}

//Go South button
void MainWindow::on_pushButton_3_clicked()
{
    Room* nextRoom = game.currentRoom->nextRoom("south");
    if (nextRoom == NULL) {
        cout << "[Impossible] You cannot go South anymore! Check the room's exits..." << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    cout << endl << game.currentRoom->longDescription() << endl;
}

//Map display button
void MainWindow::on_pushButton_9_clicked()
{
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
}

