/**************************** playerctl.cpp ****************************
Main window which also handles all the controls.

Copyright (C) 2014-2016
by: Andrew J. Bibb
License: MIT 

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"),to deal 
in the Software without restriction, including without limitation the rights 
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions: 

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.
***********************************************************************/ 
# include <QtCore/QDebug>
# include <QList>
# include <QString>
# include <QMessageBox>
# include <QTimer>

# include "./code/gameboard/gameboard.h"	
# include "./code/resource.h"

GameBoard::GameBoard(QWidget* parent) : QDialog(parent)
{
	// Set the Locale (probably not necessary since the default is the system one anyway)
  QLocale::setDefault(QLocale::system() );	
	
	// Set the window title
	this->setWindowTitle(LONG_NAME);
	
	// Setup the user interface
  ui.setupUi(this);	

  // Setup the button group
  bg01 = new QButtonGroup(this);
  bg01->addButton(ui.pushButton_01, 1);
  bg01->addButton(ui.pushButton_02, 2);
  bg01->addButton(ui.pushButton_03, 3);
  bg01->addButton(ui.pushButton_04, 4);
  bg01->addButton(ui.pushButton_05, 5);
  bg01->addButton(ui.pushButton_06, 6);
  bg01->addButton(ui.pushButton_07, 7);
  bg01->addButton(ui.pushButton_08, 8);
  bg01->addButton(ui.pushButton_09, 9);

  // Add Actions - necessary for shortcuts to work
  this->addAction(ui.actionButton01);
  this->addAction(ui.actionButton02);
  this->addAction(ui.actionButton03);
  this->addAction(ui.actionButton04);
  this->addAction(ui.actionButton05);
  this->addAction(ui.actionButton06);
  this->addAction(ui.actionButton07);
  this->addAction(ui.actionButton08);
  this->addAction(ui.actionButton09);
  
  // Connect signals and slots
  connect (bg01, SIGNAL(buttonClicked(int)), this, SLOT(buttonClicked(int)));
  connect (ui.pushButton_new, SIGNAL(clicked()), this, SLOT(initializeBoard()));

  // Initialize board
  QTimer::singleShot(5, this, SLOT(initializeBoard()) );

	return;
}

/////////////////////////////// Private SLOTS ///////////////////////////////////
//
// Slot to process button clicks
void GameBoard::buttonClicked(int but)
{
  bg01->button(but)->setText(QString(cur_player.toUpper()) );
  game[but - 1] = cur_player; 

  
  qDebug() << "game over = " << gameOver(cur_player);
  cur_player = (cur_player == QChar('x') ? QChar('o') : QChar('x') );
  
  return;
}

//
// Slot to initialize the board
void GameBoard::initializeBoard()
{
  
  // initialize variables
  cur_player = QChar('x');
  for (uint i = 0; i < sizeof(game)/sizeof(QChar); ++i) { 
    game[i] = QChar();
  }
  
  // initialize the board 
  QList<QAbstractButton*> blist = bg01->buttons();

  for (int i = 0; i < blist.count(); ++i) {
    blist.at(i)->setText("");
  }

  // decide who goes first
  if (QMessageBox::question(this, LONG_NAME,
          tr("Would you like to make the first move?"),
          QMessageBox::Yes | QMessageBox::No,
          QMessageBox::Yes) == QMessageBox::No) {
    int move = qrand() % 9;
    game[move] = cur_player;
    bg01->button(move + 1)->click();
  }

  return;
}

/////////////////////////////// Private Functions ///////////////////////////////////
//
// Function to determine if the game is over
bool GameBoard::gameOver(const QChar& player)
{
  // check rows
  for (int i = 0; i < 9; i = i + 3) {
    if (game[i] == player && game[i + 1] == player && game[i + 2] == player)
      return true;
  } // rows

  // check columns
  for (int i = 0; i < 3; ++i) {
    if (game[i] == player && game[i + 3] == player && game[i + 6] == player)
      return true;
  } // columns
    
  // check diagonals
  if (game[0] == player && game[4] == player && game[8]  == player)
    return true;
  if (game[2] == player && game[4] == player && game[6] == player)
    return true;

  return false;
}
