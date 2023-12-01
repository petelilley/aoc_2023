CC = clang++
CFLAGS = -static -std=c++2a -w -O3

EXEC = libaoc2023.a
OBJ = libaoc2023.o
SRC = common.cpp
INC = -I. -I/opt/homebrew/opt/fmt/include/
LIB = -L/opt/homebrew/opt/fmt/lib/ -lfmt

default: build

build:
	$(CC) -c $(CFLAGS) $(SRC) $(INC) $(LIB) -o $(OBJ)
	ar rcs $(EXEC) $(OBJ)
	rm $(OBJ)
