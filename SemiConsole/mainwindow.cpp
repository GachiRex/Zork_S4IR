#include <iostream>
#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QTextStream>
#include <unistd.h>

#include <QLabel>
#include <QHBoxLayout>
#include <QWidget>

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

    ui->hpBar->setMinimum(0);
    ui->hpBar->setMaximum(game.zorkPlayer->getHP());
    ui->hpBar->setValue(game.zorkPlayer->getHP());
    ui->hpBar->setFormat("%v");
    ui->mpBar->setMinimum(0);
    ui->mpBar->setMaximum(game.zorkPlayer->getMP());
    ui->mpBar->setValue(game.zorkPlayer->getMP());
    ui->mpBar->setFormat("%v");

    ui->pushButton_12->setEnabled(true);    //FirstRoom has an NPC
    ui->bullyButton->setEnabled(false);     //First Room has no enemies
    ui->interactButton->setEnabled(true);   //First Room has no items, but is northLocked

    redirect = new QDebugStream(cout, ui ->textEdit);
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

/** Wordle function **/

void MainWindow::Wordle() {
    string wordList[15] = {"pearl", "sewed", "moist", "croze","crane",
                          "bread", "short", "blunt", "flock", "sneed",
                          "candy", "worry", "towel", "short", "stock"
                         };

    string display = "_____";
    string remLetters = " a b c d e f g h i j k l m n o p q r s t u v w x y z";
    string ranWord = wordList[rand() % 15];
    int solved = 0, remAttempts = 6;
    string guess;

    //cout << "[debug] ranWord is: "<< ranWord << endl;
    cout << "Your guess must contain ONLY lowercase letters" << endl;

    while (remAttempts > 0 && solved < 5) {
        cout << endl << "Remaining attempts: " <<  remAttempts << endl << remLetters << endl << display << endl << "Your guess: ";

        //--connect signal, function should wait for user input (in ui->lineedit)
        cin >> guess;

        string incorrectLetters = "";
        if (guess.length() < 6) {
            solved = 0;
            int i = 0;
            while (i < 5 && solved < 5) {
                string correctLetter = "";
                if (ranWord.find(guess[i]) != string::npos) {             //'string::npos' represents a non-position
                    correctLetter += guess[i];
                    if (guess[i] == ranWord[i]) {
                        remLetters.at((guess[i] - 96) * 2 - 1) = '_';    //'-96' because 'a'=97, '*2' because letters are separated by a space
                        unsigned long j = 0;
                        while (j < guess.length()) {
                            if (guess[i]==ranWord[j]) { display[j] = guess[i]; }
                            j++;
                        }
                        solved++;
                    }
                    else { cout << "The letter " << correctLetter << " is correct, but in the wrong spot" << endl; }
                }
                else {
                    if ( (guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z')) {
                        incorrectLetters += ' ';
                        incorrectLetters += guess[i];
                        incorrectLetters += ' ';
                        remLetters.at((guess[i] - 96) * 2 - 1) = '_';
                    }
                }
                i++;
            }
            if (incorrectLetters != "") { cout << "Incorrect letters:" << incorrectLetters << " " << endl; }
            remAttempts--;
        }
        else { cout << "Your guess must be a word of 5 letters" << endl; }
    }
    if (solved == 5) { cout << endl << "You found the correct word!" << endl<<endl; }
    else { cout << endl << "You ran out of attempts!" << endl << "The word was: " << ranWord << endl<<endl; }
}

/** Button functions **/

inline void MainWindow::Go(string dst) {
    Room* nextRoom = game.currentRoom->nextRoom(dst);
    if (nextRoom == NULL) {
        cout << endl
             << "Impossible! You cannot go " << dst << "...";
        cout << endl;
    }
    else {
        game.currentRoom = nextRoom;
     }
    (game.currentRoom->getMobPresence()) ? ui->bullyButton->setEnabled(true) : ui->bullyButton->setEnabled(false);
    (game.currentRoom->getNPCpresence()) ? ui->pushButton_12->setEnabled(true) : ui->pushButton_12->setEnabled(false);
    (game.currentRoom->numberOfItems() || game.currentRoom->get_isNorthLocked()) ? ui->interactButton->setEnabled(true) : ui->interactButton->setEnabled(false);
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
    finScreen();//Go("west");
}

//Go North button
void MainWindow::on_pushButton_5_clicked()
{
    if (game.currentRoom->get_isNorthLocked() == 1) {
        cout << endl
             << "The door is locked. You should find something to open it with"
             << endl;
    }
    else {
        Go("north");
    }
}

//Help display button
void MainWindow::on_pushButton_6_clicked()
{
    game.printHelp();
}

//Random Teleportation button
void MainWindow::on_pushButton_7_clicked()
{
    string strRoomList[13] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m"};
    string ranDst = strRoomList[rand()%13];

    cout << endl << "[Teleportation] Teleported to a random room: room  "<< ranDst << endl;
    game.currentRoom = game.roomList[ranDst];
    cout << game.currentRoom->longDescription() << endl;
}

//Wordle button
void MainWindow::on_pushButton_8_clicked() {
    game.wordle();
}

//Map display button
void MainWindow::on_pushButton_9_clicked()
{
        cout << "           [m]        " << endl;
        cout << "             |         " << endl;
        cout << "[h] --- [f] --- [g]" << endl;
        cout << "             |         " << endl;
        cout << "             |         " << endl;
        cout << "[c] --- [a] --- [b]" << endl;
        cout << "             |         " << endl;
        cout << "             |         " << endl;
        cout << "[i] --- [d] --- [e]" << endl;
        cout << " |                       |" << endl;
        cout << " |                       |" << endl;
        cout << "[j] --- [k] --- [l]" << endl;
}

//Check Player's Stats button
void MainWindow::on_pushButton_10_clicked(){
    game.zorkPlayer->CheckStats();
}

//Check Player's Inventory button
void MainWindow::on_pushButton_11_clicked()
{
    game.zorkPlayer->checkInventory();
}


void MainWindow::on_pushButton_12_clicked()
{
    if (game.currentRoom->getNPCpresence()) {
        int dNb = game.currentRoom->getNPC()->getDialogNb();
        if (dNb >= 0) {
            game.currentRoom->getNPC()->coutDialog(dNb);
            dNb--; game.currentRoom->getNPC()->setDialogNb(dNb);
        }
        else {
            if (game.currentRoom->getNPC()->getLionel()) {
                finScreen();
                //ender();
            }
            game.currentRoom->getNPC()->coutDialog(0);
            cout << endl
                 << game.currentRoom->getNPC()->GetName()
                 << " has nothing else to say to you..."
                 << endl;
            ui->pushButton_12->setEnabled(false);
        }
    }
    else {
        cout << endl
             << "There's no one there to talk to..." << endl
             << endl;
    }
}


void MainWindow::on_bullyButton_clicked()
{
    if(game.currentRoom->getMobPresence()) {
            game.currentRoom->Bully(game.zorkPlayer, game.currentRoom);
            ui->bullyButton->setEnabled(false);
    }
    else {
        cout << endl
             << "You can only bully dumb-looking people..." << endl
             << endl;
    }
}


void MainWindow::on_interactButton_clicked()
{
    game.currentRoom->Interact(game.zorkPlayer, game.currentRoom);

    ui->hpBar->setMaximum(game.zorkPlayer->getHP());
    ui->mpBar->setMaximum(game.zorkPlayer->getMP());
    ui->hpBar->setValue(game.zorkPlayer->getHP());
    ui->mpBar->setValue(game.zorkPlayer->getMP());

    if (game.currentRoom->numberOfItems() == 0) {
        ui->interactButton->setEnabled(false);
    }
}

void MainWindow::finScreen() {
    QLabel *label = new QLabel();
    QHBoxLayout *hbox = new QHBoxLayout();
    QWidget *widg = new QWidget();

    this->hide();

    label->setStyleSheet("QLabel {color: white;background: blue;}");
    label->setText("Prosious fired you from the campus.\n You have lost 40K€.");

    label->setAlignment(Qt::AlignCenter);
    label->setWindowTitle("AÏE");
    hbox->addWidget(label);
    widg->setLayout(hbox);

    widg->setFixedSize(900,400);
    widg->show();
}

void MainWindow::ender() {
    this->hide();
    //exit(1);
}


