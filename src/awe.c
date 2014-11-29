#include <stdio.h>
#include <stdlib.h>
#include "jsmn.h"

void do_something(char * js)
{
  jsmn_parser *parser;
  jsmn_init(parser);
  //jsmntok_t tokens[10];
  // , js, tokens, 10);

}
int main(int argc, char* argv[])
{

  FILE *_f = fopen("sample.github.gist.json", "rb");
  fseek(_f, 0, SEEK_END);
  long _fsize = ftell(_f);
  fseek(_f, 0, SEEK_SET);

  char *string = malloc(_fsize +1);
  fread(string, _fsize, 1, _f);
  fclose(_f);
  string[_fsize]=0;

  return 0;

  int i;
  printf("size %lu\n", _fsize);
  for(i=0; i<_fsize; i--)
  {
    printf("%c", string[i]);
  }

  return 0;
}
