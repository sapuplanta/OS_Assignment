#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //posix standard functions
#include <sys/mman.h> //memory management declarations
#include <sys/wait.h> //wait functions
#include <time.h> //time functions
#include "logger.h" //logger header

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
    char log_msg[100];
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
    sprintf(log_msg, "Player %d wins the game!", player_id + 1);
    log_event(log_msg);
    save_score(player_id + 1);
    exit(0);
}   //check win condition

char choice;
printf("Player %d at step %d (L/R): ", player_id + 1, step);
scanf(" %c", &choice); 

int selected = (choice == 'L' || choice == 'l') ? 0 : 1; //0 for left, 1 for right

if (game -> tileds [step] == selected) {
    game -> player_positions [player_id]++;
    printf("Player %d moves to step %d\n", player_id + 1, game -> player_positions [player_id]);
    sprintf(log_msg, "Player %d moves to step %d", player_id + 1, game -> player_positions [player_id]);
    log_event(log_msg);
} else {
    game -> alive [player_id] = 0;
    printf("Player %d eliminated at step %d\n", player_id + 1, step);
    sprintf(log_msg, "Player %d eliminated at step %d", player_id + 1, step);
    log_event(log_msg);
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

int main() {

    //Shared Memory Setup
    game = mmap(NULL, sizeof(Game), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (game == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    srand(time(NULL)); //seed random number generator

    init_logger(); //initialize logger
    log_event("Server Started"); //log game start event

    //Game Initialization
    for (int i = 0; i < PATH_LEN; i++) {
        game -> tileds [i] = rand() % 2; //randomly assign tiles
    }
    for (int i = 0; i < PLAYERS; i++) {
        game -> player_positions [i] = 0; //initialize player positions
        game -> alive [i] = 1; //set all players as alive
    }
    game -> turn = 0; //set first turn

    printf("Glass Bridge Game Start!\n");

    //Fork Player Processes
    for (int i = 0; i < PLAYERS; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            player_process(i); //child process runs player function
        }
    }

    //Wait for Player Processes to Finish
    for (int i = 0; i < PLAYERS; i++) {
        wait(NULL); //wait for all child processes
    }

    log_event("Game Over"); //log game over event
    close_logger(); //close logger
    munmap(game, sizeof(Game)); //unmap shared memory
    return 0;

    
}

