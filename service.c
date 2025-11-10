#include "service.h"
#include <stdio.h>

char *allocate_message(char *s)
{
  char *buffer = malloc(strlen(s) + 1);
  if(buffer == NULL){
    fprintf(stderr, "Unable to allocate memory to buffer");
    exit(EXIT_FAILURE);
  }
  buffer = s;
  return buffer;
}
bool exploded(int *rc, sqlite3 *db, char *err){
  if(*rc != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n return code: %d\n", err, *rc);
    sqlite3_free(err);
    sqlite3_close(db);
    return true;
  }
  return false;
}
void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err)
{
  int m, dt, rc;
  sqlite3_stmt *smt;
  const char sql_create[] = "INSERT INTO messages (text, daytime) VALUES (:message, :daytime)";
  rc = sqlite3_prepare_v2(db, sql_create, -1, &smt, 0);
  if(exploded(&rc, db, err)) return;
  // getting the index of my paramters (This is unnecessary but i want to learn more about the SQLite3 interface)
  m = sqlite3_bind_parameter_index(smt, ":message");
  dt = sqlite3_bind_parameter_index(smt, ":daytime");

  rc = sqlite3_bind_text(smt, m, s, -1, SQLITE_STATIC);
  if(exploded(&rc, db, err)) return;
  rc = sqlite3_bind_text(smt, dt, s, -1, SQLITE_STATIC);
  if(exploded(&rc, db, err)) return;
  rc = sqlite3_step(smt);
  if(rc == SQLITE_DONE){
    sqlite3_finalize(smt);
    printf("message: %s\n", s);
  }else{
    fprintf(stderr, "insert wise message failed bro");
    return;
  }
}
