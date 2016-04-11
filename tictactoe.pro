mak#  We need the qt libraries, we want compiler warnings on, and this is a release version of the program  
CONFIG += qt
CONFIG += warn_on
CONFIG += release

#  Widgets needed for QT5, 
QT += widgets
QT += core
QT += dbus
QT += network

TARGET = tictactoe
TEMPLATE = app
target.path = /usr/bin/
INSTALLS += target


#	header files
HEADERS		+= ./code/resource.h
HEADERS 	+= ./code/gameboard/gameboard.h

#	forms
FORMS		+= ./code/gameboard/ui/gameboard.ui

#	sources
SOURCES	+= ./code/main.cpp
SOURCES	+= ./code/gameboard/gameboard.cpp


##  Place all object files in their own directory and moc files in their own directory
##  This is not necessary but keeps things cleaner.
OBJECTS_DIR = ./object_files
MOC_DIR = ./moc_files

sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS *.pro

