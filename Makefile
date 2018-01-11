CC=gcc

all: paren

paren: paren.c
	$(CC) -std=gnu99 -o paren paren.c

clean:
	rm paren
