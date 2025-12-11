#ifndef SEEDER_H
#define SEEDER_H

#include <stdbool.h>
#include <sqlite3.h>

void seeder(sqlite3 *db, char *your_name);

#endif
