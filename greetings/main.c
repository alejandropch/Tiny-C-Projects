#include <stdio.h>
#include <time.h>
#include <sqlite3.h>
#include <string.h>
int insertWiseMessage(char *s){
  printf("message: %s\n", s);
}
int main(int agrc, char *argv[]){
  
  sqlite3 *db;
  for(int i = 1; i < agrc; i++)
  {
    if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--create") == 0)
      insertWiseMessage(argv[i + 1]);
    return 0; 
  }
  char *err;
  int rc = sqlite3_open("full_of_wisdom_this_db_is.db", &db);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "error when opening a connection to SQLite3: %s\n", err);
    sqlite3_free(err);
    sqlite3_close(db);
    return 1;
  }
  const char sql_create[] = "CREATE TABLE IF NOT EXISTS Messages (id INT AUTO_INCREMENT PRIMARY_KEY, name VARCHAR(255));";
  rc = sqlite3_exec(db, sql_create, 0 , 0, &err);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "error when creating table: %s\n", err);
    sqlite3_free(err);
    sqlite3_close(db);
    printf("SQLite not initialized\n");
    return 1;
  }

  if(agrc < 2)
    printf("Heey, my boy\n");
  else {
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
  
  return 0;
}



