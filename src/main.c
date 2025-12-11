#include "seeder.h"
#include "ops/service.h"

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

char *get_valid_day_time_text (){
#define X(name) #name ","
  char *str_daytimes = DAYTIME_LIST "\0";
#undef X
  char *buffer = malloc(strlen(str_daytimes) + 1);
  strcpy(buffer, str_daytimes);
  buffer[strlen(buffer) - 1] = '\0'; // removing the trailing comma
  return str_daytimes;
}

int get_valid_daytime(char *day_time){
#define X(name) #name,
  char *valid_day_times[] =  { DAYTIME_LIST };
#undef X
  for(int i = 0; i < DAYTIME_LENGTH; i++)
    if(strcmp(valid_day_times[i], day_time) == 0)
    {
      return i;
    }
  return -1;
}

int main(int argc, char *argv[]){

  sqlite3 *db;
  char *time, *message, *err;
  char *db_full_filename = "/usr/local/share/greetings/full_of_wisdom_this_db_is.db";
  int rc = sqlite3_open(db_full_filename, &db);
  if(exploded(&rc, db))
  {
    fprintf(stderr, "error when opening a connection to SQLite3\n");
    return 1;
  }
  const char sql_create[] = "CREATE TABLE IF NOT EXISTS messages (id INT AUTO_INCREMENT PRIMARY_KEY, text VARCHAR(255), daytime INT);";
  rc = sqlite3_exec(db, sql_create, 0 , 0, &err);
  if(exploded(&rc, db))
  {
    fprintf(stderr, "error when creating table: %s\n", err);
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
    {

    }
    if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--seed") == 0)
    {

      if(strcmp(argv[i + 1], "-n") == 0 || strcmp(argv[i + 1], "--name") == 0)
      {
        char *name = argv[i + 2];
        seeder(db, name);
        return 0;
      }
    }
    if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0)
    {
        if(strcmp(argv[i + 1], "-t") == 0 || strcmp(argv[i + 1], "--time") == 0)
        {
          time = argv[i + 2];
          int daytime_code = get_valid_daytime(time);
          char *str_daytimes = get_valid_day_time_text();
          if(daytime_code == -1)
          {
            fprintf(stderr, "bad option, you forgot the day time bro. (%s)", str_daytimes);
            return 1;
          }
          message = argv[i + 3];
          insert_wise_message(message, daytime_code, db);
          return 0;
        }
      }
    }
  // no flag, just print out some saved message
  print_random_message(db);

  return 0; 
}
