race.o: race.c
	gcc -Wall -c race.c
race: race.o
	gcc -Wall -o race race.o
clean: race
	rm race.o
