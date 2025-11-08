#ifndef SERVICE_H
#define SERVICE_H
#include <sqlite3.h>
void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err);
char *allocate_message(char *s);
#endif 
