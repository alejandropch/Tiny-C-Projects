
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>
#include "service.h"

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
    {", my boy... why are you still awake? Hard programming night I see... I sense it..\n", "em"},
    {"!, Use your time wisely, you will. Trust in your judgement, I do\n", "m"},
    {", the chosen one you are\n", "a"},
    {", remember this you will. The dark side of the force, only the weak embrace it\n", "e"}
  };
  buffer = (char *) malloc(namelen + sizeof(messages[0]) * 2 + 1);
  if(buffer == NULL){
    fprintf(stderr, "Unable to allocate memory to buffer");
    return;
  }
  for (int i = 0; i < sizeof(messages) / sizeof(messages[0]); i++){
    if(sizeof(messages[i]) + namelen + 1 > sizeof(buffer))
    {
      fprintf(stdout, "Reallocating memory to buffer");
      buffer = realloc(buffer, (sizeof(messages[i]) + namelen + 1) * 2);
      if(buffer == NULL){
        fprintf(stderr, "Unable to allocate memory to buffer");
        return;
      }
    }
    sprintf(buffer, "%s%s", your_name, str);
    insert_wise_message(buffer, "em", db, err);
  }
  free(buffer);
}
