#include <stdio.h>
#include <stdlib.h>
#include "jki.h"

void jki_print_token(jki_token *token, const char *js)
{
  int start = token->start;
  int end = token->end;
  int diff = end - start;
  char string[diff+2];
  memcpy(string, &js[start], (size_t) diff+1);
  string[diff+1] = '\0';
  if(token->type == JKI_ARRAY_KEY)
    printf("Array Type");
  if(token->type == JKI_OBJECT_KEY)
    printf("Object Type");
  printf("-Key:%s\n", string);
}
int main(void)
{
  char key_chain[] = "data4,0234213512623,bean,aoeu\0";
  char key_chain_with_index_as_root[] = "3,data,0,bean\0";
  unsigned int token_len = 10;
  int r;
  jki_token *tokens = malloc(sizeof(jki_token) * token_len + 1);
  jki_parser parser;
  jki_init(&parser);
  r = jki_parse(&parser, key_chain, sizeof(key_chain), tokens, token_len + 1);
  int i;
  for(i=0; i<r;i++)
    jki_print_token(&tokens[i], key_chain);
  printf("Time to support multi-byte code!\n");
  printf("Maybe write some unit tests around this first...\n");
  abort();
  return 0;
}

