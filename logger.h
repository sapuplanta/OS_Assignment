#ifndef LOGGER_H
#define LOGGER_H

void init_logger();
void log_event(const char *event);
void save_score(int winner_id);
void close_logger();

#endif // LOGGER_H