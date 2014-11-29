#include <stdio.h>
#include <stdlib.h>
#include "jsmn.h"
#include <string.h>

void print_type(int type)
{
  printf("%d\n", type);
  if(type == JSMN_PRIMITIVE){
    printf("JSMN_PRIMITIVE");
  }else if(type == JSMN_OBJECT){
    printf("OBJECT");
  }else if(type == JSMN_ARRAY){
    printf("Array");
  }else if(type == JSMN_STRING){
    printf("String");
  }
  printf("\n");
}
void do_something(char* js, long t_size)
{
  jsmn_parser parser;
  jsmn_init(&parser);
  int _token_count = 10000;
  jsmntok_t tokens[_token_count];
  jsmnerr_t err = jsmn_parse(&parser, js, t_size, tokens, _token_count);
  if(err < 0){printf("%d", err);}
  int i;
  for(i=3; i<err; i++)
  {
    printf("%d\n", tokens[i].size);
    printf("%d-%d\n", tokens[i].start, tokens[i].end);
    int diff = tokens[i].end - tokens[i].start;
    char sub_buffer[diff + 1];
    memcpy(sub_buffer, js, tokens[i].end);
    print_type(tokens[i].type);
    printf(&sub_buffer);
    printf("\n");
    break;
  }

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

  do_something(string, _fsize);

  return 0;

  int i;
  printf("size %lu\n", _fsize);
  for(i=0; i<_fsize; i--)
  {
    printf("%c", string[i]);
  }

  return 0;
}
