/* C220A6 Q1
   Luke Paddock (10157251)
   2016-12-5
*/

#include<stdio.h>
#include<stdlib.h> /* system () */
#include<pthread.h>
#include<unistd.h> /* usleep() */

void *compt_racer(void *pos);
void *redraw(void *args);
void drawlane(int racer_pos);

/* Racer_One is human, the rest are bots */
int *racer_one, *racer_two, *racer_three, *racer_four, *racer_five;
int *gameon; /* used as boolean, =1 when game is running, 0 when finished */

int main(int argc, char *argv[]) {
	pthread_t two, three, four, five;
	pthread_t graphics;

	gameon = malloc(sizeof(int));
	*gameon = 1; /* the games afoot */
	
	srand(time(NULL)); /* change rand number seed */

	racer_one = malloc(sizeof(int));
	racer_two = malloc(sizeof(int));
	racer_three = malloc(sizeof(int));
	racer_four = malloc(sizeof(int));
	racer_five = malloc(sizeof(int));

	*racer_one = 0;
	*racer_two = 0;
	*racer_three = 0;
	*racer_four = 0;
	*racer_five = 0;
	
	/* start graphics thread */
	pthread_create(&graphics, NULL, redraw, (void *) NULL);

	getchar(); /* wait for user to press enter */

	/* start bot threads */
	pthread_create(&five, NULL, compt_racer, (void *) racer_five);
	pthread_create(&two, NULL, compt_racer, (void *) racer_two);
	pthread_create(&three, NULL, compt_racer, (void *) racer_three);
	pthread_create(&four, NULL, compt_racer, (void *) racer_four);
	
	/* Keyboard racer control */
	while (*gameon) {
		char c = getchar();
		if ( c == '\n' && *racer_one < 40) { (*racer_one)++; }
	}

	/* wait for all the threads to terminate */
	pthread_join(five, NULL);
	pthread_join(two, NULL);
	pthread_join(three, NULL);
	pthread_join(four, NULL);
	pthread_join(graphics, NULL);

	/* free malloc'd variables */
	free(racer_one);
	free(racer_two);
	free(racer_three);
	free(racer_four);
	free(racer_five);
	free(gameon);
	return 0; /* program finished! */
}


/* Thread for computer racer (using rand numbers and stuff) */
void *compt_racer(void *pos) {
	int *x = (int*) pos;
	/* while everyone is below a winning score */
	while (*racer_one < 40 && *racer_two < 40 && *racer_three < 40 && *racer_four < 40 && *racer_five < 40) {
		int sleeptime = rand() % 100 + 1;
		usleep(sleeptime*1000);
		(*x)++;
	}
	*gameon = 0; /* the game is over set to 0 (false) */
	return 0;
}

/* thread that clears then draws the board */
void *redraw(void *args) {
	int lastdraw = 1; /* this variable is used to ensure that when the game is finished
			     the loop draws the screen one last time to show the last positions */
	while(lastdraw) {
		system("clear");
		printf("Welcome to CISC220 Racing Arena\nHit Enter to move forward\n");
		drawlane(*racer_one);
		printf("# Lane 1 \n");
		drawlane(*racer_two);
		printf("# Lane 2 \n");
		drawlane(*racer_three);
		printf("# Lane 3 \n");
		drawlane(*racer_four);
		printf("# Lane 4 \n");
		drawlane(*racer_five);
		printf("# Lane 5 \n");
		if (*gameon == 0) { lastdraw--; }
		usleep(1000000/5);
	}

	/* print the 'winner' banner */
	printf("\n\tThe Winner Is: "); /* multiple winners possible (tie) */
	if (*racer_one >= 40) { printf(" Racer One!"); }
	if (*racer_two >= 40) { printf(" Racer Two!"); }
	if (*racer_three >= 40) { printf(" Racer Three!"); }
	if (*racer_four >= 40) { printf(" Racer Four!"); }
	if (*racer_five >= 40) { printf(" Racer Five!"); }
	printf("\n");
	return 0;
}

/* draws racer, ~'s and spaces for one lane */
void drawlane(int race_pos) {
	for (int x = 0; x < race_pos; x++) {
		printf("~");
	}
	printf("|->");
	for (int x = 40; x > race_pos; x--) {
		printf(" ");
	} 
}
