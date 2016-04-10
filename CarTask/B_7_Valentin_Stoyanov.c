#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define DRIVERS 5
#define CARS 3

pthread_mutex_t mutex;
int cars[CARS] = {1, 2, 3};

void* rent(void* driver) {
  int i = 0;
  for(i; i < CARS; ++i){
    if(pthread_mutex_trylock(&mutex) == 0){
      sleep(1);
      printf("%d\n", (int)driver);
      pthread_mutex_unlock(&mutex);
    }
  }
  sleep(1);
  return NULL;
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t threads[DRIVERS];
  int i = 0;

  for(i; i < DRIVERS; ++i){
    pthread_create(&threads[i], NULL, rent, (void*)&i);
  }

  for(i = 0; i < DRIVERS; ++i){
    pthread_join(threads[i], NULL);
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}
