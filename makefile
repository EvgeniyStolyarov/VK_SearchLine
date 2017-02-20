CC=gcc
CFLAGS= -std=c99 -c
search_lines: main.o HashTable.o InputProcessing.o
	$(CC) -std=c99 main.c HashTable.c InputProcessing.c -o search_lines

main.o: main.c InputProcessing.h HashTable.h
	$(CC) $(CFLAGS) main.c
HashTable.o: HashTable.c HashTable.h
	$(CC) $(CFLAGS) HashTable.c
InputProcessing.o: InputProcessing.c InputProcessing.h
	$(CC) $(CFLAGS) InputProcessing.c

clean:
	rm -f search_lines *.o