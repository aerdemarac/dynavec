CC = gcc
SRC = main.c vector.c
CFLAGS = -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -std=c99 -Wall -Wextra -Wconversion -pedantic 
app: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o test
clean: 
	rm -r test

