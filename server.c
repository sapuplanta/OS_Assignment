#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //posix standard functions
#include <sys/mman.h> //memory management declarations
#include <time.h> //time functions

#define PLAYERS 3   //number of players
#define PATH_LEN 6  //length of the path

// Shared Game Structure
typedef struct {
    int tileds[PATH_LEN]; //tiles on the path
    int player_positions[PLAYERS]; //positions of players
    int alive [PLAYERS]; //alive status of players
    int turn; //current turn
} Game; 
Game *game; //pointer to shared game structure

// Player Process Function
void player_process(int player_id) {
    while (game -> alive [player_id]) {
        // Wait for turn
        if (game -> turn != player_id) {
            usleep(100000); //sleep for 100ms
            continue;
        }
    }

// Core Game Logic 
int step = game -> player_positions [player_id];
if (step >= PATH_LEN) {
    printf("Player %d wins!\n", player_id + 1);
    exit(0);
}   //check win condition

char choice;
printf("Player %d at step %d (L/R): ", player_id + 1, step);
scanf(" %c", &choice); 

int selected = (choice == 'L' || choice == 'l') ? 0 : 1; //0 for left, 1 for right

if (game -> tileds [step] == selected) {
    game -> player_positions [player_id]++;
    printf("Player %d moves to step %d\n", player_id + 1, game -> player_positions [player_id]);
} else {
    game -> alive [player_id] = 0;
    printf("Player %d eliminated at step %d\n", player_id + 1, step);
} //check tile and update position or alive status

//Turn Advancement
int next = (player_id + 1) % PLAYERS;
while (!game -> alive [next]) {
    next = (next + 1) % PLAYERS;
}
game -> turn = next;
    }
    exit(0);
}



