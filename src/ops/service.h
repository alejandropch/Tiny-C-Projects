#ifndef SERVICE_H
#define SERVICE_H

#include <stdbool.h>
#include <sqlite3.h>

#define DAYTIME_LIST \
  X(EARLY_MORNING) \
  X(MORNING) \
  X(AFTERNOON) \
  X(EVENING)

enum Daytime {
#define X(key) key,
    DAYTIME_LIST
#undef X
  DAYTIME_LENGTH 
};

void print_random_message(sqlite3 *db);
void insert_wise_message(char *s, int day_time, sqlite3 *db);
bool exploded(int *rc, sqlite3 *db);
char *allocate_message(char *s);

#endif 
