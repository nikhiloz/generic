#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

typedef void *my_func_t (void *);
void *thread_func(void *);

pthread_mutex_t lock;


int counter;

void main()
{
  printf(" Multithreading Example \n");
  my_func_t *func1[] = {thread_func,thread_func};

  pthread_t tid[2] ;

  int i = 0;

  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    printf("\n mutex init failed\n");
    goto done;
  }

  pthread_create(&tid[0],NULL,func1[0],(void *)&i);
  pthread_create(&tid[1],NULL,func1[1],(void *)&i);

  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);

done:
  printf("Finish \n");

}

void *thread_func(void *a)
{
    pthread_mutex_lock(&lock);
 // printf("I am Thread Func nik %d \n", *(int *)a);
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d started\n", counter);

    for(i=0; i<(0xFFFFFFFF);i++)
    {
     /* Do nothing just keep incrementing i */
    };

    printf("\n Job %d finished\n", counter);

    pthread_mutex_unlock(&lock);
    return NULL;

}
