all: greetings

greetings: main.c
	gcc -o greetings main.c seeder.c service.c -lsqlite3

clear: 
	rm -r greetings
