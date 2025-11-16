#include "service.h"
#include <sqlite3.h>
#include <stdio.h>
#include <time.h>


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
bool exploded(int *rc, sqlite3 *db){
  if(*rc != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n return code: %d\n", sqlite3_errmsg(db), *rc);
    sqlite3_close(db);
    return true;
  }
  return false;
}
enum Daytime getDaytime (int hour) {
  if( hour < 6 ){
    return EARLY_MORNING;
  }
  if( hour < 12 ){
    return MORNING;
  }
  if( hour < 18 ){
    return AFTERNOON;
  }
  if( hour < 24 ){
    return EVENING;
  }
  fprintf(stderr, "Error bro: getDaytime shouldn't be returning this enum 'EVENING'\n");
  return EVENING;
}
void print_random_message(sqlite3 *db)
{
  int rc, nmessages, dt, idt;
  const unsigned char *selected_message;
  time_t now;
  sqlite3_stmt *stm;
  struct tm *clock;
  const char *sql_select;

  time(&now);
  clock = localtime(&now);
  dt = getDaytime(clock->tm_hour);
  sql_select = "SELECT text FROM messages WHERE daytime=:dt ORDER BY RANDOM() LIMIT 1";

  rc = sqlite3_prepare_v2(db, sql_select, -1, &stm, NULL);
  if(exploded(&rc, db)) return;
  idt = sqlite3_bind_parameter_index(stm, ":dt");
  rc = sqlite3_bind_int(stm, idt, dt);
  if(exploded(&rc, db)) return;

  while(rc = sqlite3_step(stm), rc == SQLITE_ROW ){ 
    selected_message = sqlite3_column_text(stm, 0);
    fprintf(stdout, "%s\n", selected_message);
  }
  if( rc != SQLITE_DONE){
    fprintf(stderr, "get wise message given an id failed bro");
    return;
  }
}
void insert_wise_message(char *s, int day_time, sqlite3 *db)
{
  int m, dt, rc;
  sqlite3_stmt *stm;
  const char sql_create[] = "INSERT INTO messages (text, daytime) VALUES (:message, :daytime)";
  rc = sqlite3_prepare_v2(db, sql_create, -1, &stm, 0);
  if(exploded(&rc, db)) return;
  // getting the index of my paramters (This is unnecessary but i want to learn more about the SQLite3 interface)
  m = sqlite3_bind_parameter_index(stm, ":message");
  dt = sqlite3_bind_parameter_index(stm, ":daytime");

  rc = sqlite3_bind_text(stm, m, s, -1, SQLITE_STATIC);
  if(exploded(&rc, db)) return;
  rc = sqlite3_bind_int(stm, dt, day_time);
  if(exploded(&rc, db)) return;
  rc = sqlite3_step(stm);
  if(rc == SQLITE_DONE){
    fprintf(stdout, "%s\n", s);
    sqlite3_finalize(stm);
  }else{
    fprintf(stderr, "insert wise message failed bro");
    return;
  }
}
