#include <stdio.h>
#include <stdlib.h>

#include "libNDJson"

int main(int argc, char* argv[])
{
  FILE *_f = fopen("sample", "r");
  fseek(_f, 0, SEEK_END);
  long _fsize = ftell(_F);
  fseek(_f, 0, SEEK_SET);

  char *string = malloc(_fsize +1);
  fread(string, _fsize, 1, _f);
  fclose(_f);
  string[_fsize]=0;

  extract_keys(string);
}
