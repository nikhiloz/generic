
#include <stdio.h>

void main()
{
  int a = 0x23 ;
  int b = 0x33 ;

  int c = a - b;

  printf("%i \n" , c);

  printf("Enter value of a: ");
  scanf("%d",&a);

  printf("Enter value of b: ");
  scanf("%i",&b);	

  printf("a=%d, b=%d\n",a,b);

}
