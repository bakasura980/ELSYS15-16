#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define NUM_OF_THREADS 4

void* check(void* num) {
	int x = *(int*)num;
	int i = 0;
	float result;
	for(i; i < x; ++i) {
		result = (sin(i)*sin(i)) + (cos(i)*cos(i));
		if(result != 1) {
			return (void*)0;
		}
	}
	return (void*)1;
}

int main() {
	int x = 25000000;
	pthread_t threads[NUM_OF_THREADS];
	int i = 0;
	
	for (i; i < NUM_OF_THREADS; ++i){
    if (pthread_create(&threads[i], NULL, check, &x)){
      perror("Error while creating");
    }
    x += 25000000;
  }
	
  for (i = 0; i < NUM_OF_THREADS; i++){
    void *result;
    pthread_join(threads[i], (void**)&result);
    //printf("Thread %d returned %d\n", i, result);
    if(!result){
    	printf("Result : False\n");
    	exit(0);
    }
  }
	printf("Result : True\n");
	return 0;
}





