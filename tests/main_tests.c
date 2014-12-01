#include <stdio.h>
#include <stdlib.h>
#include "tokenise.h"
#include "log.h"

int main(void)//int argc, char* argv[])
{
  printf("Test Checer Success");
  printf("\n");

  FILE *_f = fopen("sample", "r");
  fseek(_f, 0, SEEK_END);
  size_t _fsize = ftell(_f);
  fseek(_f, 0, SEEK_SET);

  char *string = malloc(_fsize +1);
  size_t r = fread(string, _fsize, 1, _f);
  if (r < 1)
    log_die("File is Empty");
  fclose(_f);
  string[_fsize] = '\0';

  printf("Loaded Scritp\n");
  extract_keys(string);
  return 0;
}

