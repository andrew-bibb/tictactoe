/**************************** gameboard.h ******************************
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
# ifndef GAME_BOARD
# define GAME_BOARD

# include <QDialog>
# include <QButtonGroup>
# include <QChar>

# include "ui_gameboard.h"

class GameBoard : public QDialog
{
	Q_OBJECT
	
	public:
    GameBoard(QWidget* parent = 0);
    
  private slots:
    void buttonClicked(int);
    void initializeBoard();

  private:
  // members 
    Ui::GameBoard ui;    
    QButtonGroup* bg01;    
    QChar cur_player;
    QChar game[9];
};

# endif
