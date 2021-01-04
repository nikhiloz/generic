#include <stdio.h>

void main()
{
  int a[5] = {3,7,2,10,1};
  int len = 5;
  int Length;
  for(;len >0; len--)
  {
    Length = len - 1 ;
    for(;Length > 0; Length--)
    {
      printf("\n len = %d Length = %d a[Length - 1] = %d a[Length - 2] = %d", len,Length,a[Length],a[Length - 1]);
      
      if(a[Length] > a[Length -1] )
      {
        /* Swap Them */
        a[Length ] = a[Length ] ^ a[Length -1];
        a[Length - 1] = a[Length ] ^ a[Length -1];
        a[Length ] = a[Length ] ^ a[Length -1];
      }
    }
  }

  printf("\nCompleted Sorting \n");
  for(len =5;len > 0; len --)
    printf("%d,",a[len -1]);
    
  printf("\nEnd of Program \n");
}
