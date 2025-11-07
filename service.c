#include <stdio.h> 
#include <sqlite3.h>

void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err)
{
  printf("message: %s\n", s);
  sqlite3_stmt *smt;
  const char sql_create[] = "INSERT INTO Messages (text) VALUES ('?')";
  sqlite3_prepare_v2(db, sql_create, -1, &smt, 0);  
  sqlite3_bind_text(smt, 1, s, -1, SQLITE_STATIC);
  int rc = sqlite3_step(smt);
  if(rc == SQLITE_DONE){
    sqlite3_finalize(smt);
  }else{
    fprintf(stderr, "insert wise message failed bro");
    return;
  }
}
