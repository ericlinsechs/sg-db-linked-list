SHELL = /bin/bash

EXEC = main 

all: $(EXEC)

CC = gcc
CFLAGS = -Wall -g 

# List of source files 
SRC = $(wildcard *.c)

# Generate a list of object files by replacing .c with .o
OBJS = $(SRC:%.c=%.o)

all: $(EXEC)

$(EXEC): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(EXEC) $(OBJS)
