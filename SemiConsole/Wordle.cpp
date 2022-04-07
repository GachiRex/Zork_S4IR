#include "Wordle.h"
#include <QTimer>

Wordle::Wordle(QString inWord)
   : lineEdit_(new QLineEdit)
{
    this->word = inWord;
    connect(lineEdit_, SIGNAL(textEdited(const QString&)),
           this, SLOT(handleUserInput(const QString&)));
}

Wordle::~Wordle()
{
   delete lineEdit_;
}

void Wordle::handleUserInput(const QString& text)
{
   if(text != "desiredText")
      return;

   // do stuff here when it matches
}

void Wordle::setWord(QString inWord){
    this->word = inWord;
}

QString Wordle::getWord() {
    return word;
}
