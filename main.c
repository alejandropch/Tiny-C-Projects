#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>

#include "seeder.h"
#include "service.h"

bool is_valid_daytime(char *s){
  int len = strlen(s);
  if(len > 2){
    fprintf(stderr, "your daytime is too big bro. (em, m, a, e)");
    return false;
  }
  char *valid_day_times[] =  { "em", "m", "a", "e"};
  len = sizeof(valid_day_times) / sizeof(valid_day_times[0]);
  for(int i = 0; i < len; i++)
    if(strcmp(valid_day_times[i], s) == 0)
      return true;

  return false;
}
bool exploded(int *rc, sqlite3 *db, char *err){
  if(*rc != SQLITE_OK) {
    fprintf(stderr, "Error: %s\n", err);
    sqlite3_free(err);
    sqlite3_close(db);
    return true;
  }
  return false;
}
int main(int argc, char *argv[]){

  sqlite3 *db;
  char *time, *message, *err;
  int rc = sqlite3_open("full_of_wisdom_this_db_is.db", &db);
  if(exploded(&rc, db, err))
  {
    fprintf(stderr, "error when opening a connection to SQLite3: %s\n", err);
    return 1;
  }
  const char sql_create[] = "CREATE TABLE IF NOT EXISTS messages (id INT AUTO_INCREMENT PRIMARY_KEY, text VARCHAR(255), daytime VARCHAR(2));";
  rc = sqlite3_exec(db, sql_create, 0 , 0, &err);
  if(exploded(&rc, db, err))
  {
    fprintf(stderr, "error when creating table: %s\n", err);
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--seed") == 0)
    {

      if(strcmp(argv[i + 1], "-n") == 0 || strcmp(argv[i + 1], "--name") == 0)
      {
        char *name = argv[i + 2];
        seeder(db, name, err);
        return 0;
      }
    }
    if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0)
    {
        if(strcmp(argv[i + 1], "-t") == 0 || strcmp(argv[i + 1], "--time") == 0)
        {
          time = argv[i + 2];
          if(is_valid_daytime(time) == false)
          {
            fprintf(stderr, "bad option, you forgot the day time bro. (em, m, a, e)");
            return 1;
          }
          message = argv[i + 3]; 
          insert_wise_message(message, time, db, err);
          return 0;
        }
      }
    }
  return 0; 
}
