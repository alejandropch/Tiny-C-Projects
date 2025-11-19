all: greetings 

greetings: *.c
	gcc -o greetings main.c seeder.c service.c -lsqlite3

.PHONY: clear
clear: 
	rm -r greetings

.PHONY: install
install: 
	gcc -o /usr/bin/greetings main.c seeder.c service.c -lsqlite3
	mkdir -p /usr/local/share/greetings
	
.PHONY: uninstall
uninstall:  
	rm -rf /usr/local/share/greetings
	rm -f /usr/bin/greetings
