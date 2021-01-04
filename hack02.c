#include <stdio.h>

static void series(int n, int start)
{
  int i =1;
  
  /* Print first term */
  printf("%d, ",start);

  for(;n>1; n--,i++)
  {
  
    if(i&1)
    {
      start = start - 8;
      printf("%d, ",start);
    }
    else{
      start = start*2;
      printf("%d, ",start);
    }

  }
  
}

void main()
{
  series(7,55);
}


