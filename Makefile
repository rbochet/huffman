CC=gcc
CFLAGS=-W -Wall 
LDFLAGS=
EXEC=huffman
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)

huffman: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC)  -c $< $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
			
