#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

double bank_balance = 0.0;
double ivan_account = 0.0;
double petar_account = 0.0;
pthread_mutex_t mutex;

void deposit(double amount, double *to) {
	// Adds amount to account *to
	// Adds amount to total bank balance
	*to += amount;
	bank_balance += amount;
}

void withdraw(double amount, double *from) {
	// Removes amount from account *from
	// Removes amount from total bank balance
	*from -= amount;
	bank_balance -= amount;
}

void *ivan(void *arg) {
	int i;
	for(i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		if(rand() % 2 <= 1) {
			deposit(rand() % 10000, &ivan_account);
		}
		else {
			withdraw(rand() % 10000, &ivan_account);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void *petar(void *arg) {
	int i;
	for(i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		if(rand() % 1000 <= 500) {
			deposit(rand() % 10000, &petar_account);
		}
		else {
			withdraw(rand() % 10000, &petar_account);
		}
		pthread_mutex_unlock(&mutex);
	}
}


int main() {
	srand(time(NULL));
	// Something very clever
	pthread_mutex_init(&mutex, NULL);
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, ivan, NULL);
	pthread_create(&thread2, NULL, petar, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	pthread_mutex_destroy(&mutex);
	printf("%f %f\n", ivan_account + petar_account, bank_balance);

	return 0;
}
