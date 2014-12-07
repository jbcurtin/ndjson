#include <stdio.h>
#include <stdlib.h>
#include "jki.h"

int main(void)
{
  char key_chain[] = "data,0,bean\0";
  char key_chain_with_index_as_root[] = "3,data,0,bean\0";
  jki_parser *parser;
  jki_init(parser);
  printf("%s\n", key_chain);
  return 0;
}

