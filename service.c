#include <sqlite3.h>

void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err){
  printf("message: %s\n", s);
  const char sql_create[] = "INSERT INTO Messages (text) VALUES %s";
  char buffer[strlen(sql_create) + 255];
  sprintf(buffer, sql_create, s);
  sqlite3_exec(db, sql_create, 0, 0, &err);
}
