race.o: race.c
	gcc -Wall -c race.c
race: race.o
	gcc -Wall -pthread -o race race.o
clean: race
	rm race.o
