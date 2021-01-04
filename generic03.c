#include <stdio.h>
#include <stdio.h>

#include <pthread.h>

typedef void *func_ptr_t (void *);

void *myfunc(void *);
void *myfunc1(void *);

long counter;

pthread_mutex_t lock;

void main()
{
  printf("-- Multithreading Example -- \n");
  func_ptr_t *func_ptr[] = {myfunc,myfunc1};
  
  if(pthread_mutex_init(&lock,NULL) != 0)
  {
    printf("Mutex init failed \n");
    goto done;
  }

  pthread_t tid[2];

  pthread_create(&tid[0], NULL, func_ptr[0],NULL);
  pthread_create(&tid[1], NULL, func_ptr[1],NULL);

  pthread_join(tid[0],NULL);
  pthread_join(tid[1],NULL);

//  func_ptr[0](NULL);
done:
  printf("Finished \n");
}

void *myfunc(void *arg)
{
  printf("%s \n",__FUNCTION__);
  pthread_mutex_lock(&lock);  
  printf("Counter = %ld \n", counter);

  long i;
  counter ++;
  for(i=0;i<0xFFFFFFF;i++)
  counter ++ ;

  printf("Counter After Loop = %ld \n", counter);
  pthread_mutex_unlock(&lock);  
  
  return NULL;
}

void *myfunc1(void *arg)
{
  printf("%s \n",__FUNCTION__);
  pthread_mutex_lock(&lock);  
  printf("Counter = %ld \n", counter);
  
  long i;
  counter ++;
  for(i=0;i<0xFFFFFFF;i++)
  counter -- ;

  printf("Counter After Loop = %ld \n", counter);
  pthread_mutex_unlock(&lock);  
  return NULL;
}
