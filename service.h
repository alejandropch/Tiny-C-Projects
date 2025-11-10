#ifndef SERVICE_H
#define SERVICE_H
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
  void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err);
  bool exploded(int *rc, sqlite3 *db, char *err);
  char *allocate_message(char *s);
#endif 
