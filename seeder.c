
#include "seeder.h"
#include "service.h"

typedef struct {
  char *text;
  char daytime[2];
} Messages;

void seeder(sqlite3 *db, char * your_name, char *err){
  time_t now;
  struct tm *clock;
  time(&now);
  char *buffer;
  int namelen = strlen(your_name);
  clock = localtime(&now);
  Messages messages[] = {
    {", my boy... why are you still awake? Hard programming night I see... I sense it..\n", "em"},
    {"! Use your time wisely, you will. Trust in your judgement, I do\n", "m"},
    {", the chosen one you are\n", "a"},
    {", remember this you will. The dark side of the force, only the weak embrace it\n", "e"}
  };
  buffer = (char *) malloc((namelen + strlen(messages[0].text) + 1) * 2);
  if(buffer == NULL){
    fprintf(stderr, "Unable to allocate memory to buffer");
    return;
  }
  sprintf(buffer, "%s%s", your_name, messages[0].text);
  insert_wise_message(buffer, messages[0].daytime, db, err);
  for (int i = 1; i < sizeof(messages) / sizeof(messages[1]); i++){
    if(strlen(messages[i].text) + namelen + 1 > strlen(buffer))
    {
      fprintf(stdout, "Reallocating memory to buffer\n");
      buffer = realloc(buffer, (strlen(messages[i].text) + namelen + 1) * 2);
      if(buffer == NULL){
        fprintf(stderr, "Unable to allocate memory to buffer");
        return;
      }
    }
    sprintf(buffer, "%s%s", your_name, messages[i].text);
    insert_wise_message(buffer, messages[i].daytime, db, err);
  }
  free(buffer);
}
