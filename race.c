/* C220A6 Q1
   Luke Paddock (10157251)
   2016-12-5
*/

#include<stdio.h>
#include<stdlib.h> /* system () */
#include<pthread.h>
#include<unistd.h> /* usleep() */

void *human_racer(void *pos);
void *compt_racer(void *pos);
void *redraw(void *args);
void drawlane(int racer_pos);

int *racer_one, *racer_two, *racer_three, *racer_four, *racer_five;
int *gameon;

int main(int argc, char *argv[]) {
	int x;
	pthread_t one, two, three, four;

	gameon = malloc(sizeof(int));
	*gameon = 1;

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
	

	x = pthread_create(&one, NULL, compt_racer, (void *) racer_one);
	x = pthread_create(&two, NULL, compt_racer, (void *) racer_two);
	x = pthread_create(&three, NULL, compt_racer, (void *) racer_three);
	x = pthread_create(&four, NULL, compt_racer, (void *) racer_four);

	pthread_join(one, NULL);
	pthread_join(two, NULL);
	pthread_join(three, NULL);
	pthread_join(four, NULL);
}

/* Thread for human racer (using keyboard) */
void *human_racer(void *pos) {

}

/* Thread for computer racer (using rand numbers and stuff) */
void *compt_racer(void *pos) {
	int *x = (int*) pos;
	printf("Hello: %d\n", *x);
}

/* Clear then draw the board */
void *redraw(void *args) {
	while(gameon) {
		system("clear");
		printf("Welcome to CISC220 Racing Arena\nHit Enter to move forward\n");
		drawlane(racer_one);
		printf("# Lane 1 \n");
		drawlane(racer_two);
		printf("# Lane 2 \n");
		drawlane(racer_three);
		printf("# Lane 3 \n");
		drawlane(racer_four);
		printf("# Lane 4 \n");
		drawlane(racer_five);
		printf("# Lane 5 \n");
	}
	
}

void drawlane(int race_pos) {
	for (int x = 0; x < race_pos; x++) {
		printf("~");
	}
	printf("|->");
	for (int x = 40; x > race_pos; x--) {
		printf(" ");
	} 
}
