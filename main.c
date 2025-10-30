#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>


void seeder(sqlite3 *db, char *err){
    time_t now;
    struct tm *clock;
    time(&now);
    clock = localtime(&now);
    if(clock->tm_hour < 6)
    {
      printf(" %s, my boy... why are you still awake? Hard programming night I see... I sense it..  \n", argv[1]);
    }
    else if(clock->tm_hour <= 12)
    {
      printf("%s!, Use your time wisely, you will. Trust in your judgement, I do\n", argv[1]); 
    }
    else if(clock->tm_hour <= 18)
    {
      printf("%s, the chosen one you are\n", argv[1]);
    }
    else if(clock->tm_hour <= 23)
    {
      printf("%s, remember this you will. The dark side of the force, only the weak embrace it\n", argv[1]);
    }
  }
bool is_valid_daytime(char *s){
  int len = strlen(s);
  if(len > 2){
    fprintf(stderr, "your daytime is too big bro. (em, m, a, e)");
    return false;
  }
  char *valid_day_times[] =  { "em", "m", "a", "e"};
  len = sizeof(valid_day_times) / sizeof(valid_day_times[0]);
  for(int i = 0; i < len; i++)
    if(strcmp(valid_day_times[i], s))
      return true;

  return false;
}
void insert_wise_message(char *s, char *day_time, sqlite3 *db, char *err){
  printf("message: %s\n", s);
  const char sql_create[] = "INSERT INTO Messages (text) VALUES %s";
  char buffer[strlen(sql_create) + 255];
  sprintf(buffer, sql_create, s);
  sqlite3_exec(db, sql_create, 0, 0, &err);
}
int main(int agrc, char *argv[]){
  
  sqlite3 *db;
  char *err;
  int rc = sqlite3_open("full_of_wisdom_this_db_is.db", &db);

  if(rc != SQLITE_OK) {
    fprintf(stderr, "error when opening a connection to SQLite3: %s\n", err);
    sqlite3_free(err);
    sqlite3_close(db);
    return 1;
  }
  const char sql_create[] = "CREATE TABLE IF NOT EXISTS Messages (id INT AUTO_INCREMENT PRIMARY_KEY, text VARCHAR(255), daytime VARCHAR(2));";
  rc = sqlite3_exec(db, sql_create, 0 , 0, &err);

  if(rc != SQLITE_OK) {
    fprintf(stderr, "error when creating table: %s\n", err);
    sqlite3_free(err);
    sqlite3_close(db);
    printf("SQLite not initialized\n");
    return 1;
  }
  for (int i = 1; i < argc; i++)
  {
    if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--seed") == 0)
      seeder(db, err);
    if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0)
      if( i + 2 < agrc || is_valid_daytime(argv[i]) == false)
        fprintf(stderr, "bad option, you forgot the day time bro. (em, m, a, e)");
        return 1;
  }
  insert_wise_message(argv[2], argv[3], db, err);
  return 0; 
}


  
  return 0;
}



