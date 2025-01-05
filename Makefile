CC = gcc
CFLAGS = -Wall
SRC = cinnamon1/src/cinnamon_interpreter.c
OBJ = cinnamon_interpreter.o
EXEC = cinnamon

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

clean:
	rm -f $(OBJ) $(EXEC)
