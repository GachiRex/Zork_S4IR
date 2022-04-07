#ifndef WORDLE_H
#define WORDLE_H

#include <iostream>
#include <string>
#include <QTimer>
#include <QLineEdit>

using namespace std;

class Wordle : public QObject
{
Q_OBJECT
private slots:
   void handleUserInput(const QString& text);
private:
   QString word;
   QLineEdit* lineEdit_;
public:
   Wordle(QString inWord);
   ~Wordle();
   QString getWord();
   void setWord(QString inWord);
};



#endif // WORDLE_H
