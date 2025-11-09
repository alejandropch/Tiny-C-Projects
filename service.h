#include <sqlite3.h>
#ifndef SERVICE_H
#define SERVICE_H
void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err);
char *allocate_message(char *s);
#endif 
