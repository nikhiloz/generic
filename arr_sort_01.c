#include <stdio.h>

void main()
{
  int a[5] = {3,7,2,10,1};
  int len = 5;
  int l_len;
  for(;len >0; len--)
  {
    l_len = len - 1 ;
    for(;l_len > 0; l_len--)
    {
      printf("\n len = %d l_len = %d a[l_len - 1] = %d a[l_len - 2] = %d", len,l_len,a[l_len],a[l_len - 1]);
      if(a[l_len] > a[l_len -1] )
      {
        /* Swap Them */
        a[l_len ] = a[l_len ] ^ a[l_len -1];
        a[l_len - 1] = a[l_len ] ^ a[l_len -1];
        a[l_len ] = a[l_len ] ^ a[l_len -1];
      }
    }
  }

  for(len =5;len > 0; len --)
    printf("%d,",a[len -1]);
}