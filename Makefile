OBJ=gpio
FILE=main.c gpio.c
OPT=-lpthread
all:
	$(CC) -o $(OBJ) $(FILE) $(OPT)