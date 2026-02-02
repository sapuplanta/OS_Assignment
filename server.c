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
