CC = gcc
APP_SRC = main.c 
TEST_SRC = unit_test.c 
CFLAGS = -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -std=c99 -Wall -Wextra -Wconversion -pedantic 

test: $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o test
app: $(APP_SRC)
	$(CC) $(CFLAGS) $(APP_SRC) -o app
app32: $(APP_SRC)
	$(CC) $(CFLAGS) $(APP_SRC) -m32 -o app
clean: 
	rm -r test

