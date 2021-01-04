#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0x04

#define FALSE 0
#define TRUE 1

#if DEBUG & 0x04

int my_strlen(char *s)
{
  int result = 0;
  
  if(s == NULL)
   return 0;

  while(*s)
  {
   result++ ;
   s++ ;
  }

  return result;
}


int check_subset(char *str1, char *str2, int length)
{
  char *temp_str2 = str2 ;
  char *temp_str1 = str1 ;
  int temp_length ;

  while(length <= my_strlen(temp_str1))
  {
    temp_length = length;

    if(*(char *)temp_str2 == *(char *)temp_str1)
    { 
      while(*(char *)temp_str2 == *(char *)temp_str1)
      {
        temp_str2++ ;
        temp_str1++ ;
        temp_length-- ;
   
        if(temp_length == 0)
          return TRUE ;
      }
    }
    else
      temp_str1++;
  }
  return FALSE;
}
#endif

void main()
{
  char *s = "my name is Nikhilesh" ;
  char *s1;
  char b[] = {'1','2','3'};

#if DEBUG1 
  s = s1;
  b = s;
#endif
  
#if DEBUG & 0x01
  /* Next Operation */
  printf("S string is : %s & size of S is %d \n",s,strlen(s));
  printf("B array is : %s and size of b array is : %d \n",b, strlen(b));
#endif

#if DEBUG & 0x02
 /* Next Operation */
  s++;
  printf("%s \n",s);
#endif

#if DEBUG & 0x04
  char *str1 = "This is meNikhil" ;
  char *str2 = "Nikhil" ;
  int length = strlen(str2);

  int result = check_subset(str1,str2,length);
  printf(" It is %d",result);
#endif

#if DEBUG & 0x08
  /* Next Operation */
  /* Printing in Reverse order */

  s = "My+name++is+++super++++chutiya  .";
  char *s2 =s ;

  int counter = 0;
  int len_count = strlen(s);

  char *temp_s;
 
  s2 = s + len_count;  

  while(len_count >= 0 )
  {
    if((*(char *)s2) == '+' || len_count == 0)
    {

      if(len_count != 0)
      {
        temp_s = s2+1;
        counter-- ;
      }
      else 
        temp_s =s2;

      while (counter > 0)
      {
        printf("%c",*temp_s);
        temp_s++;
        counter --;
      }

      /* Print the Delimeter as it has entered the condition */
      if(len_count != 0)
        printf("%c",*s2);

      counter = 0;
    }

    counter ++;
    len_count --;
    s2--;
  }

//  printf("\n Total number of delimeter is %d \n", counter);
  
#endif

}
