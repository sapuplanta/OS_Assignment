#include "logger.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t log_mutex; // Mutex for thread-safe logging
static FILE *log_file = NULL; // Log file pointer

// function to log messages with thread safety
void init_logger(){
    pthread_mutex_init(&log_mutex, NULL);

    log_file = fopen("game_log.txt", "a");
    if (log_file == NULL) {
        fprintf(log_file, "=== Game Session Started ===\n");
        fflush(log_file);

}
}

// log an event to the log file
void log_event(const char *event) {
    pthread_mutex_lock(&log_mutex);
    if (log_file != NULL) {
        fprintf(log_file, "%s\n", event);
        fflush(log_file);
    }
    pthread_mutex_unlock(&log_mutex);
}

// save the score to a file
void save_score(int winner_id){
    pthread_mutex_lock(&log_mutex);
    FILE *score_file = fopen("game_scores.txt", "a");
    if (score_file != NULL) {
        fprintf(score_file, "Player %d won the game!\n", winner_id + 1);
        fclose(score_file);
    }
    pthread_mutex_unlock(&log_mutex);
}

// close the logger and clean up resources
void close_logger(){
    pthread_mutex_lock(&log_mutex);
    if (log_file != NULL) {
        fprintf(log_file, "=== Game Session Ended ===\n");
        fclose(log_file);
        log_file = NULL;
    }
    pthread_mutex_unlock(&log_mutex);
    pthread_mutex_destroy(&log_mutex);
}