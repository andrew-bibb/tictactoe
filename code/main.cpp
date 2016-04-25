/**************************** main.cpp *******************************

Main program to parse command line arguments and start the event loop

Copyright (C) 2013-2016
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
# include <QApplication>
# include <QCommandLineOption>
# include <QCommandLineParser>
# include <QStringList>
# include <QTime>
# include <QLibraryInfo>

# include <signal.h> 

# include "./code/gameboard/gameboard.h"
# include "./code/resource.h"	


// Create a signal handler to catch ^C from console
void signalhandler(int sig) {
  if(sig == SIGINT || sig == SIGTERM) {
    qApp->quit();
  }
  
  return;
}

int main(int argc, char *argv[])
{
  QApplication::setApplicationName(LONG_NAME);
  QApplication::setApplicationVersion(VERSION);
  QApplication::setDesktopSettingsAware(true);
  QApplication app(argc, argv);

	// Create seed for the QT random number generator
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	// setup the command line parser
	QCommandLineParser parser;
  parser.addHelpOption();  	
  parser.addVersionOption();
 
  QCommandLineOption kobayashiMaru (QStringList() << "k" << "kobayashi-maru", QCoreApplication::translate("main.cpp", "Allow computer to make mistakes") );
	parser.addOption(kobayashiMaru);		  
    
  // Process comand line arguments
  parser.process(QCoreApplication::arguments() );   
  QStringList sl = parser.unknownOptionNames();
  if (sl.size() > 0 ) parser.showHelp(1);
  if (parser.isSet("help") ) parser.showHelp(1);	
  if (parser.isSet("version") ) parser.showVersion();
  
  // signal handler             
  signal(SIGINT, signalhandler); 
  
  GameBoard gbrd(NULL);
  gbrd.show();
   
  return app.exec();

}


