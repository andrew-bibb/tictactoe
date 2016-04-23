/**************************** gameboard.cpp ****************************
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
# include <QMap>

# include "./code/gameboard/gameboard.h"	
# include "./code/resource.h"

GameBoard::GameBoard(QWidget* parent) : QDialog(parent)
{
	// Set the Locale (probably not necessary since the default is the system one anyway)
  QLocale::setDefault(QLocale::system() );	

	// Setup the user interface
  ui.setupUi(this);	

  // Set the window title
	this->setWindowTitle(LONG_NAME);
  
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
  // Return now if not the human turn
  if (! b_humanturn) return;

  // Return if invalid button picked
  if (! game[but - 1].isNull() ) return;

  // process the move
  bg01->button(but)->setText(QString(human.toUpper()) );
  game[but - 1] = human; 
  
  processEndOfGame();
  b_humanturn = false;
  computerMove();
  return;
}

//
// Slot to initialize the board
// Called from constructor and whenever a new game is started.
void GameBoard::initializeBoard()
{
  
  // initialize variables
  b_humanturn = false;
  choice = -1;
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
          QMessageBox::Yes) == QMessageBox::Yes) {
    human = QChar('x');
    computer = QChar('o');
    b_humanturn = true;
  }
  else {
    computer = QChar('x');
    human = QChar('o');
    int move = qrand() % 9;
    bg01->button(move + 1)->setText(computer.toUpper() );
    game[move] = computer; 
    b_humanturn = true;

  } // else

  ui.label_human_playing->setText(tr("You are playing: <b>%1</b>").arg(human.toUpper()));
  return;
}

/////////////////////////////// Private Functions ///////////////////////////////////
//
// Function for the computer to calculate a move
void GameBoard::computerMove()
{

  miniMax(game, -1);
  bg01->button(choice + 1)->setText(computer.toUpper() );
  game[choice] = computer;

  processEndOfGame();
  b_humanturn = true;
  return;
}

//
// Minimax function
int GameBoard::miniMax(const QChar cgame[], int depth)
{ 
  // Return score if this branch is done
  if (gameWin(cgame, computer) ) return 10 - depth;
  if (gameWin(cgame, human) ) return depth - 10;
  if (gameDraw(cgame) ) return 0;

  // Initialize variables
  ++depth;
  QMap<int, int> map_result;
  QChar cur_player = ((depth + 2) % 2 == 1 ?  human:  computer); 
  // Find and score all possible moves, recurse as needed
  for (int i = 0; i < 9; ++i) {
    if (cgame[i].isNull() ) {
      QChar pgame[9];
      for (int j = 0; j < 9; ++j) {
        pgame[j] = cgame[j];
      } // j for
      pgame[i] = cur_player;
      map_result[i] = miniMax(pgame, depth);
    } // if move is valid
  } // i for

  // Find the move out of the min or max values
  int score = (cur_player == computer ? -20 : 20);
  QMapIterator<int, int> itr(map_result);
  while (itr.hasNext()) {
    itr.next();
    if (cur_player == computer) { 
      if (itr.value() >= score) {
        score = itr.value();
        choice = itr.key();
      } // if
    } // if computer
    else {
      if (itr.value() <= score) {
        score = itr.value();
        choice = itr.key();
      } // if
    } // else
  } // while
  return score;
}

//
// Function to determine if the game was won by player
bool GameBoard::gameWin(const QChar cgame[], const QChar& player)
{
  // check rows
  for (int i = 0; i < 9; i = i + 3) {
    if (cgame[i] == player && cgame[i + 1] == player && cgame[i + 2] == player)
      return true;
  } // rows

  // check columns
  for (int i = 0; i < 3; ++i) {
    if (cgame[i] == player && cgame[i + 3] == player && cgame[i + 6] == player)
      return true;
  } // columns
    
  // check diagonals
  if (cgame[0] == player && cgame[4] == player && cgame[8]  == player)
    return true;
  if (cgame[2] == player && cgame[4] == player && cgame[6] == player)
    return true;

  return false;
}

//
// Function to see if the game is a draw
bool GameBoard::gameDraw(const QChar cgame[])
{
  for (int i = 0; i < 9; ++i) {
    if (cgame[i].isNull() ) return false;
  }
  
  return true;
}

//
// Function to check if the game is over
void GameBoard::processEndOfGame()
{
  
  if (gameWin(game, human)) {
    qDebug() << "This cannot happen, the human won";
   // initializeBoard();
  }

  if (gameWin(game, computer) ) {
    qDebug() << "Yea - I won!";
    //initializeBoard();
  }

  if (gameDraw(game) ) {
    qDebug() << "We have a draw";
  //initializeBoard();
}
  return;
  
}
