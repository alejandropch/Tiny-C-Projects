all: greetings

greetings: main.c
	gcc -o greetings main.c seeder.c service.c -lsqlite3

.PHONY: recompile
recompile:
	gcc -o greetings main.c seeder.c service.c -lsqlite3

.PHONY: clear
clear: 
	rm -r greetings
