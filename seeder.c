
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
  char *text;
  char daytime[2];
} Messages;

void seeder(sqlite3 *db, char * your_name, char *err){
  time_t now;
  struct tm *clock;
  time(&now);
  char *str, *buffer;
  int namelen = strlen(your_name);
  clock = localtime(&now);
  Messages messages[] = {
    ", my boy... why are you still awake? Hard programming night I see... I sense it..\n",
    "!, Use your time wisely, you will. Trust in your judgement, I do\n",
    ", the chosen one you are\n",
    ", remember this you will. The dark side of the force, only the weak embrace it\n"
  };
  buffer = (char *) malloc(namelen + strlen(messages[0]) + 1);
  for (int i = 1; i < sizeof(messages) / sizeof(messages[0]); i++){
    sprintf(buffer, "%s%s", your_name, str);
    insert_wise_message(buffer, "em", db, err);
  }
  str = ;
  buffer = realloc(buffer, namelen + sizeof(str) + 1);
  sprintf(buffer, "%s%s", your_name, str);
  insert_wise_message(buffer, "m", db, err);
  str = ;
  buffer = realloc(buffer, namelen + sizeof(str) + 1);
  sprintf(buffer, "%s%s", your_name, str);
  insert_wise_message(buffer, "a", db, err);
  str = ;
  buffer = realloc(buffer, namelen + sizeof(str) + 1);
  sprintf(buffer, "%s%s", your_name, str);
  insert_wise_message(buffer, "e", db, err);
  free(buffer);
}
