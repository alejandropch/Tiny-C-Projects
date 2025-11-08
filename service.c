#include "service.h"
#include <stdio.h> 
#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>

char *allocate_message(char *s)
{
  char *buffer = malloc(strlen(s) + 1);
  if(buffer == NULL){
    fprintf(stderr, "Unable to allocate memory to buffer");
    exit(EXIT_FAILURE);
  }
  return buffer;
}
void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err)
{
  sqlite3_stmt *smt;
  const char sql_create[] = "INSERT INTO messages (text) VALUES ('?')";
  sqlite3_prepare_v2(db, sql_create, -1, &smt, 0);  
  sqlite3_bind_text(smt, 1, s, -1, SQLITE_STATIC);
  int rc = sqlite3_step(smt);
  if(rc == SQLITE_DONE){
    sqlite3_finalize(smt);
    printf("message: %s\n", s);
  }else{
    fprintf(stderr, "insert wise message failed bro");
    return;
  }
}
