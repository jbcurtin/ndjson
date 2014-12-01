#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "buf.h"
#include "log.h"

char URL[] = "https://api.github.com/users/jbcurtin";
char *KEYS[] = {"name", "location", "public_repos", "hireable"};

void print_token(jsmntok_t *t, char* js)
{
  int diff = t->end - t->start;
  char *string;
  memcpy(&string, &t[t->start], diff+1);
  printf("%s", &string);
}
void extract_keys(char* js)
{

  jsmntok_t *tokens = json_tokenise(js);
  //print_token(&tokens[0], &js);
  exit(0);
  //abort();

  typedef enum { START, KEY, PRINT, SKIP, STOP} parse_state;
  parse_state state = START;

  size_t object_tokens = 0;

  for(size_t i = 0, j = 1; j>0; i++, j--)
  {
    jsmntok_t *t = &tokens[i];
    log_assert(t->start != -1 && t->end !=-1);

    if (t->type == JSMN_ARRAY || t->type == JSMN_OBJECT)
      j += t->size;

    switch (state)
    {
      case START:
        if(t->type != JSMN_OBJECT)
          log_die("Invalid response: root element must be an object.");

        state = KEY;
        object_tokens = t->size;

        if (object_tokens == 0)
          state = STOP;

        if (object_tokens % 2 != 0)
          log_die("Invalid respones:  object must have even number of children.");

        break;

      case KEY:
        object_tokens--;

        if (t->type != JSMN_STRING)
          log_die("Invalid response: object keys must be strings");

        state = SKIP;

        for(size_t i = 0; i< sizeof(KEYS)/sizeof(char *); i++)
        {
          if (json_token_streq(js, t, KEYS[i]))
          {
            printf("%s: ", KEYS[i]);
            state = PRINT;
            break;
          }
        }
          break;
      case SKIP:
          if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
            log_die("Invalid Response: object values must be strings or primitives.");

          object_tokens--;
          state = KEY;

          if (object_tokens == 0)
            state = STOP;

          break;
      case PRINT:
          if (t->type != JSMN_STRING && t->type != JSMN_PRIMITIVE)
            log_die("Invalid response: object values must be strings or primitives.");

          char *str = json_token_tostr(js, t);
          puts(str);

          object_tokens--;
          state = KEY;

          if (object_tokens == 0)
            state = STOP;

          break;
      case STOP:
          break;
      default:
          log_die("Invalid state %u", state);
    }
  }
}
