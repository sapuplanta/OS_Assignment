#include "logger.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t log_mutex; // Mutex for thread-safe logging
static FILE *log_file = NULL; // Log file pointer

void init_logger(){
    pthread_mutex_init(&log_mutex, NULL);

    log_file = fopen("game_log.txt", "a");
    if (log_file == NULL) {
        fprintf(log_file, "=== Game Session Started ===\n");
        fflush(log_file);

}
}