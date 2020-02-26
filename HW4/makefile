# Name: Forrest Lang
# Course: COP 3330-0005
# Assignment: Assignment 4
# Due Date: 7 MAR 2020

CC=g++				# Use the c++ compiler
OFILE=main			# Set the executable name to main
DIR=.
CFLAGS=-c -g			# -c compile only, -g debugger
LFLAGS=-I $(DIR) -g -o $(OFILE)	# -i. include current directory
				# -g use debugger
				# -o rename executable

main: menu.o playlist.o song.o
	$(CC) $(LFLAGS) menu.o playlist.o song.o
menu.o: menu.cpp
	$(CC) $(CFLAGS) menu.cpp
playlist.o: playlist.cpp
	$(CC) $(CFLAGS) playlist.cpp
song.o: song.cpp
	$(CC) $(CFLAGS) song.cpp
clean:				# "make clean" is used
	rm -rf *.o
