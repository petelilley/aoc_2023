CC = clang++
CFLAGS = -std=c++2a -w -O3

EXEC = $(shell basename $(CURDIR)).out
INPUT = input.txt

SRC = main.cpp
INC = -I../common/cpp -I/opt/homebrew/opt/fmt/include/
LIB = -L../common/cpp -laoc2023 -L/opt/homebrew/opt/fmt/lib/ -lfmt

default: build 1 2

build:
	$(CC) $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(EXEC)

1: build
	@echo ""
	./$(EXEC) $(INPUT) 1

2: build
	@echo ""
	./$(EXEC) $(INPUT) 2
