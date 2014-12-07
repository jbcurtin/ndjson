#include <stdio.h>
#include <stdlib.h>
#include "jki.h"

int main(void)
//()//int argc, char* argv[])
{
  char key_chain[] = "data,0,bean\0";
  char key_chain_with_index_as_root[] = "3,data,0,bean\0";
  printf("%s", key_chain);
  return 0;
}

