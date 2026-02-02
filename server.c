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
