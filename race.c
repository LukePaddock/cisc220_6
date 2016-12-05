/* C220A6 Q1
   Luke Paddock (10157251)
   2016-12-5
*/

#include<stdio.h>
#include<stdlib.h> /* system () */
#include<pthread.h>
#include<unistd.h> /* usleep() */

void *human_racer(int *pos);
void *compt_racer(int *pos);
void *redraw();
void drawlane(int racer_pos);

int racer_one, racer_two, racer_three, racer_four, racer_five;
int gameon;

int main(int argc, char *argv[]) {
	gameon = 1;
}

/* Thread for human racer (using keyboard) */
void *human_racer(int *pos) {

}

/* Thread for computer racer (using rand numbers and stuff) */
void *compt_racer(int *pos) {

}

/* Clear then draw the board */
void *redraw() {
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
