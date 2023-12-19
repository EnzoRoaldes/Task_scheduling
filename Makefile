CC = gcc
CFLAGS = -Wall
SRC_MAIN = src/*.c
EXEC_MAIN = main


all: $(EXEC_MAIN)

$(EXEC_MAIN): $(SRC_MAIN)
	$(CC) -fopenmp $(CFLAGS) $(SRC_MAIN) -o $(EXEC_MAIN) -lm

clean:
	rm -f $(EXEC_MAIN)