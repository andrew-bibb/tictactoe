/**************************** playerctl.cpp ****************************
Main window which also handles all the controls.

Copyright (C) 2014-2016
by: Andrew J. Bibb
License: MIT \

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
  this->initializeBoard();

	return;
}

/////////////////////////////// Private SLOTS ///////////////////////////////////
//
// Slot to process button clicks
void GameBoard::buttonClicked(int but)
{
  qDebug() << "button " << but << "pressed";
  bg01->button(but)->setText(QString("B %1").arg(but));

  return;
}

//
// Slot to initialize the board
void GameBoard::initializeBoard()
{
  QList<QAbstractButton*> blist = bg01->buttons();

  for (int i = 0; i < blist.count(); ++i) {
    blist.at(i)->setText("");
  }

  return;
}
