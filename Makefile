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

all: check_updates

check_updates:
		gcc -o update_checker update_checker.c
		./update_checker

update:
	git pull origin main
	echo "1.0.0" > current_version.txt
