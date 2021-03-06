#include <stdio.h>
#include <stdlib.h>
#include "tokenise.h"
#include "log.h"

int main(void)//int argc, char* argv[])
{
  FILE *_f = fopen("data/sample.json", "r");
  fseek(_f, 0, SEEK_END);
  size_t _fsize = ftell(_f);
  fseek(_f, 0, SEEK_SET);

  char *string = malloc(_fsize +1);
  size_t r = fread(string, _fsize, 1, _f);
  if (r < 1)
    log_die("File is Empty");
  fclose(_f);
  string[_fsize+1] = '\0';

  printf("Loaded Script\n");
  extract_keys(string);
  return 0;
}

