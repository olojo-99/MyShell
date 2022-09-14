# Benjamin Olojo, 19500599 - CA216 Assignment 1
# ca216/myshell

PROGRAM = myshell # name of executable

# Destination and source paths
DEST = ../bin
SOURCE = .

# Compiler name and flags
COMPILER = gcc
FLAGS = -Wall

# Find C files
FILE = $(shell find $(SOURCE) -name '*.c')
OBJ = $(FILE: = $(DEST))

# Build step
$(DEST)/$(PROGRAM): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $@

# "make clean" to remove executable
.PHONY: clean
clean:
	rm -f $(DEST)/*


# Makefile tutorial - https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# I certify that this assignment is my own work carried out in a manner pursuant to the DCU Academic Integrity Policy,
# based on my personal study and/or research and that I have acknowledged all material and sources used in its preparation.
# Benjamin Olojo - 19500599