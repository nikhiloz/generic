#include <stdio.h>
#include <stdint.h>

void main()
{
  uint8_t i =1,j;
  i = i<< 8;
  printf("%d",(uint8_t)i);

  int8_t i1 = 0x23;
  int8_t i2 = 0x33;
  int8_t i3 = i1-i2;

  printf("\n %d %x",(int8_t)i3,*(int8_t *)&i3);

}
