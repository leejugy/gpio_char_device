OBJ=gpio
FILE=main.c gpio.c timer.c
OPT=-lpthread
all:
	$(CC) -o $(OBJ) $(FILE) $(OPT)