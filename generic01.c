#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int sum(int, int);
int diff(int, int);

int func_custom1(int, int(*)(int, int));

#define DEBUG 0x00 + 0x10

void main()
{

#if DEBUG & 0x1
/* Check for endianness */
  int i = 1;
  char c= *(char *)&i;
  char *Endian = c ? "Little Endian " : " Big Endian " ;
  printf("Machine is %s \n",Endian);
#endif

#if DEBUG & 0x2
/* Function Pointer */
  typedef int (func_ptr)(int , int);
  func_ptr *func[4] = {&sum, &diff};

  int result = func[0](2,3);
  printf("result of sum is %d \n", result);
  printf("result of diff is %d \n", func[1](5,2));

/* Pass Function pointer as Argument */
  result = func_custom1(5,sum);
  printf("Result of Operation is %d \n", result);
#endif

#if DEBUG & 0x4
/*Constant Pointer and Pointer to a Constant */
  int val1 = 10 , val2 = 20;

  int * const ptr1 = &val1 ; /* Constant Pointer */
  const int *ptr2 = &val2 ;  /* Pointer to a constant */

  printf("De-referenced value of ptr1 is %d \n", *ptr1);
  *ptr1 = 40;    /* ALLOWED */ 
//  ptr1 = &val2  /* error: assignment of read-only location ‘*p’ */
  printf("again De-referenced value of ptr1 is %d \n", *ptr1);

  printf("De-referenced value of ptr2 is %d \n", *ptr2);
//  *ptr2 = 40; /* error: assignment of read-only location ‘*p’ */
  ptr2 = &val1;  /* ALLOWED */ 
  printf("again De-referenced value of ptr2 is %d \n", *ptr2);

  /* Exercise */
  const int val3 = 30, val4 = 40;
  const int *ptr3;
  ptr3 = &val3;
  printf("De-referenced value of ptr3 is %d \n", *ptr3);
//  *ptr3 = 90;
  ptr3 = &val4;
  printf("Again De-referenced value of ptr3 is %d \n", *ptr3);
#endif

#if DEBUG & 0x8
/* Bit Operations */
  char a = 15;
  char b = 255 - 15;
  char result ;
  a = a ^ b; 
  b = a ^ b; 
  a = a ^ b; 
  printf("Ok it a = %d & b = %d \n",(uint8_t)a,b);

/* Absolute Value */
  a = -20;
  b = 20;
  printf("Intermediate value of b is %d \n",b >> 31);
  a= (a ^ (a >> 31)) - (a >> 31);
  printf("Absolute value is %d \n",a);

/* Factorial checking */
  int n = 16;
  result = n > 0 ? (n & (n - 1)) == 0 : 0;
  printf("Factorial is Yes/ No = %d \n", result);
#endif

#if DEBUG & 0x10
/* Absolute Value */
  int a = -20;
  int b = 20;

  printf("Intermediate value of a is %d \n",a >> 31);
  printf("%d \n", a ^ (a >> 31) );

  if (!(b & (1 << 31)))
    b = -1 ^ (b -1);
  printf("Negetive of b : %d \n",b);

  int16_t u1 = 1 << 15 ;
  printf(" 1 << 31 is = %d \n", u1 );

  printf("Intermediate value of b is %d \n",b >> 31);

  a= (a ^ (a >> 31)) - (a >> 31);
  printf("Absolute value is %d \n",a);
#endif

#if DEBUG & 0x20
/* Array of Char Pointers */
  char *ptr[] = {"Nikhilesh" , "Rajiv", "Manoj"};
  printf("%s \n",ptr[0]);
#endif

#if DEBUG & 0x40
/* Pointer to a char Array */
  char name[] = {"Hello This is me \n"};
  char *c1 = name ;
  printf("%s \n",c1);
  printf("%s",name);
#endif

#if DEBUG & 0x80
  uint8_t a = 254 ;
  uint8_t b = 251 ;
  uint8_t c ;

#if 0
  if((a+b) > sizeof(uint8_t))
  {
    // a = ~a;
    c = a^b;
    printf("%d %d %d\n",a,b,c);

    b = c^b;
    printf("%d %d %d\n",a,b,c);

    a = c^a;
    printf("%d %d %d\n",a,b,c);
  }
#endif

  if(a > b)
  {
    a = a - b ;
    b = a + b ;
    a = b - a ;
  }
  else 
  {
    a = b - a ;
    b = b - a ;
    a = a + b ;
  }

  printf ("%d %d ",a,b);

  printf("Here \n");
#endif
}

int sum (int a , int b) {return a+b ;}
int diff (int a , int b) {return a-b ;}
int func_custom1(int a, int(*func)(int, int)){ return func(a,a); }

