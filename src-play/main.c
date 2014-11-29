#include <stdio.h>

int main(int argc, char* argv[])
{
  int ages[] = {23,34,53};
  int i;
  for(i=sizeof(ages)-1; i>0; i--)
  {
    printf("%d", ages[i]);
  }
  return 0;
}
