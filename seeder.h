#ifndef SEEDER_H
#define SEEDER_H
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>
  void seeder(sqlite3 *db, char * your_name, char *err);
#endif
