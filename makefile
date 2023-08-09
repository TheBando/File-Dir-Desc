CC = gcc
CFLAGS = -c -g
DEPS = main.c
BIN = a6

all: $(BIN)

$(BIN): $(DEPS)
	$(CC) -o $(BIN) $(DEPS)

clean:
	rm -f $BIN) *.o
