#include <stdio.h>
#include <stdlib.h>

#define CLR_BIT(x,n) do{                   \
                       x &= (~(1 << n));   \
                     } while(0)
        
#define SET_BIT(x,n) x |= (1 << n)

static void *malloc_t (size_t size)
{
  return malloc(size);
}

static int sum(int x , int y)
{
  return x+y;
}

static int diff(int x , int y)
{
  return x-y;
}

static int *pass_func(int val)
{

  int *k = (int *)malloc_t(1);
  *k = val;
  return k;
}

/* Main Function to Test*/
void main(int argc, char **argv)
{
  printf("Hello \n");

  /*Argument counts handling*/
  printf("Argument count = %d \n", argc);
  printf("Arguments are = %s \n", *argv);
  if(argc > 1)
  printf("Arguments are = %s \n", *(++argv));
  else if(argc > 2)
  printf("Arguments are = %s \n", *(++argv));
  else if(argc > 3)
  printf("Arguments are = %s \n", *(++argv));

  /* Array of Function Pointer */
  typedef int (func_arr_t)(int, int);
  func_arr_t *func_arr[] = {sum, diff};
  printf("%d \n",func_arr[0](1,4));
  printf("%d \n",func_arr[1](8,4));

  /* Bit Operation */
  int i = 224;
  printf("%d \n", i);
  CLR_BIT(i,5);
  printf("%d \n", i);
  SET_BIT(i,5);
  printf("%d \n", i);

  /* Malloc and its Wrapper*/
  //  pass_func(10);  
  printf("%d \n",++(*(pass_func(150))));

  /* Check for endian ness */
  int n = 1;
  // little endian if true
  if(*(char *)&n == 1) 
    printf("Machine is Little Endian \n");
  else 
    printf("Machine is Big Endian \n");

  /* Individual Bits in structure */

  struct str_t {
  int a1:1;
  int a2:2;
  int a3:5;
  };

  struct str_t st;
  st.a1 =0;
  st.a2= 1;
  st.a3=15;

  printf("st.a1 = %d \n",st.a1);
  printf("st.a2 = %d \n",st.a2);
  printf("st.a3 = %d \n",st.a3);

  /* Array of Char Pointers */
  char *ptr[] = {"Nikhilesh" , "Rajiv", "Manoj"};
  printf("%s \n",ptr[0]);

  /* Pointer to a char Array */
  char name[] = {"Hello This is me \n"};
  char *c = name ;
  printf("%s \n",c);
  printf("%s",name);

  int n1 = 10;
  n1 < 10?printf("YES \n"):printf("NO \n");

}
