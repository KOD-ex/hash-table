all: hash_table

hash_table: main.o hash_table.o
	gcc main.o hash_table.o -o my_binary

main.o: main.c
	gcc -c main.c

hash_table.o: hash_table.c
	gcc -c hash_table.c

clean:
	rm -rf *.o hash_table