#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "buf.h"
#include "log.h"

char URL[] = "https://api.github.com/users/jbcurtin";
char *KEYS[] = {"name", "location", "public_repos", "hireable"};

void print_token(char* js, jsmntok_t* tokens, unsigned int tidx)
{
  unsigned int diff = tokens[tidx].end - tokens[tidx].start;
  char string[diff+1];
  memcpy(string, &js[tokens[tidx].start], diff + 1);
  string[diff] = '\0';
  printf("%s\n", string);
}

void extract_keys(char* js)
{

  jsmntok_t *tokens = json_tokenise(js);

  typedef enum { START, KEY, PRINT, SKIP, STOP} parse_state;
  parse_state state = START;

  // TODO: Now that the parser is correctly implemented.
  // It's time to look into how to properly build the datastructure to
  // break down the data into an indexable content-type.
  //
  // Dynamic Array - DArray
  // http://c.learncodethehardway.org/book/ex34.html
  // HashMap
  // http://c.learncodethehardway.org/book/ex37.html
  //
  // Academic
  // http://www.cs.utexas.edu/users/fussell/cs310h/lectures/Lecture_18-310h.pdf
  // http://c.learncodethehardway.org/book/ex15.html
  // http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

  size_t object_tokens = 0;

  for(size_t i = 0, j = 1; j>0; i++, j--)
  {
    jsmntok_t *t = &tokens[i];
    log_assert(t->start != -1 && t->end !=-1);

    if (t->type == JSMN_ARRAY || t->type == JSMN_OBJECT)
    {
      j += t->size;
    }

    switch (state)
    {
      case START:
        if(t->type != JSMN_OBJECT && t->type != JSMN_ARRAY)
        {
          log_die("Invalid response: root element must be an object or arry.\n");
        }

        if (t->type == JSMN_ARRAY)
        {
          printf("JSMN_ARRAY not supported");
          abort();
        }

        state = KEY;
        object_tokens = t->size;

        if (object_tokens == 0)
        {
          state = STOP;
        }

        if (object_tokens % 2 != 0)
        {
          log_die("Invalid respones:  object must have even number of children.\n");
        }

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
