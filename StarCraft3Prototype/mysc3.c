//--------------------------------------------
// NAME: Valentin Stoyanov
// CLASS: Xib
// NUMBER: 7
// PROBLEM: #3
// FILE NAME: mysc3.c (unix file name)
// FILE PURPOSE:
// Starcraft 3 Prototype Implementation
//---------------------------------------------

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#define MAP_MINERALS 5000
#define NEW_WORKER_PRICE 50
#define NEW_SOLDIER_PRICE 50
#define NEW_COMMAND_CENTER_PRICE 400
#define MINNING_MINERALS 8
#define INITIAL_WORKERS 5
#define DESIRED_NUM_OF_SOLDIERS 20

int workers_counter = INITIAL_WORKERS;
int map_minerals = MAP_MINERALS;
int left_minerals = MAP_MINERALS;
int minned_minerals = 0;
int soldiers = 0;
int cmd_centers = 1;
int mutex_counter = 3;

pthread_t* workers;
pthread_mutex_t* mutexes;

void* worker(void* worker);
void create_and_train_new_soldier();
void create_and_train_new_worker();
void create_new_command_center();

//--------------------------------------------
// FUNCTION: free_resourses
// Its purpose is to free the used memory
// PARAMETERS:
// NO
//----------------------------------------------
void free_resourses() {
	int i = 0;
	for(i; i < mutex_counter; i++) {
		if(pthread_mutex_destroy(&mutexes[i])) {
			free_resourses();
			perror("Can not destroy mutex");
			exit(EXIT_FAILURE);
		}
	}

	free(mutexes);
	free(workers);
}

//--------------------------------------------
// FUNCTION: input_manager
// Its purpose is to check what is the option
// and to call the relevant function
// PARAMETERS:
// char option - the option that will be checked
//----------------------------------------------
void input_manager(char option) {
	switch(option) {
		case 'm' :
			create_and_train_new_soldier();
			break;
		case 's' :
			create_and_train_new_worker();
			break;
		case 'c' :
			create_new_command_center();
			break;
	}
}

//--------------------------------------------
// FUNCTION: input_getter
// This function gets arguement from stdin
// and pases it to input_manager
// PARAMETERS:
// NO
//----------------------------------------------
void* input_getter() {
	char c;
	while((c = getchar()) != EOF) {
		input_manager(c);
	}
	return NULL;
}

//--------------------------------------------
// FUNCTION: main
// Initiallize variables, create and joins threads
// PARAMETERS:
// NO
//----------------------------------------------
int main() {

	workers = malloc(workers_counter * sizeof(pthread_t));
	mutexes = malloc(mutex_counter * sizeof(pthread_mutex_t));

	int i = 0;

	for(i; i < mutex_counter; i++) {
		if (pthread_mutex_init(&mutexes[i], NULL)) {
			free_resourses();
			char output_msg[29];
			sprintf(output_msg, "Can not initiallize mutex[%d]", i);
			perror(output_msg);
			exit(EXIT_FAILURE);
		}
	}

	pthread_t input_thread;
	if(pthread_create(&input_thread, NULL, input_getter, NULL)) {
		free_resourses();
		perror("Can not create a new thread(input_thread)");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < workers_counter; i++) {
		if(pthread_create(&workers[i], NULL, worker, (void*)((intptr_t)i))) {
			free_resourses();
			char output_msg[46];
			sprintf(output_msg, "Can not create a new thread(worker: %d thread)", i);
			perror(output_msg);
			exit(EXIT_FAILURE);
		}
	}

	if(pthread_join(input_thread, NULL)) {
		free_resourses();
		perror("Can not wait for input thread termination");
		exit(EXIT_FAILURE);
	}

	for(i = 0; i < workers_counter; i++) {
		if(pthread_join(workers[i], NULL)) {
			free_resourses();
			char output_msg[38];
			sprintf(output_msg, "Can not wait for %d thread termination", i);
			perror(output_msg);
			exit(EXIT_FAILURE);
		}
	}

	free_resourses();
	return 0;
}

//--------------------------------------------
// FUNCTION: worker
// Function that every worker executes
// PARAMETERS:
// void* worker - the worker id
//----------------------------------------------
void* worker(void* worker) {
	int id = (int)(worker);

	while(left_minerals != 0) {
		printf("SCV %d is mining\n", id + 1);

		pthread_mutex_lock(&mutexes[1]);
			left_minerals -= MINNING_MINERALS;
		pthread_mutex_unlock(&mutexes[1]);

		printf("SCV %d is transporting minerals\n", id + 1);
		sleep(2);

		int i = 2;
		bool is_delivered = false;
		do{
			for(i ; i < mutex_counter; i++) {
				if(!pthread_mutex_trylock(&mutexes[i])) {
					is_delivered = true;

					printf("SCV %d delivered minerals to Command center %d\n", id + 1, i - 2 + 1);

					pthread_mutex_lock(&mutexes[0]);
						minned_minerals += MINNING_MINERALS;
					pthread_mutex_unlock(&mutexes[0]);

					pthread_mutex_unlock(&mutexes[i]);
					break;
				}
			}
			if(!is_delivered) {
				sleep(1);
			}
		}while (!is_delivered);
	}

	return NULL;
}

//--------------------------------------------
// FUNCTION: create_and_train_new_soldier
// Creates new soldiers
// PARAMETERS:
// NO
//----------------------------------------------
void create_and_train_new_soldier() {
	if(minned_minerals < NEW_SOLDIER_PRICE) {
		printf("Not enough minerals.\n");
	}else{
		pthread_mutex_lock(&mutexes[0]);
			minned_minerals -= NEW_SOLDIER_PRICE;
		pthread_mutex_unlock(&mutexes[0]);

		sleep(1);
		soldiers++;
		printf("You wanna piece of me, boy?\n");
	}

	if(soldiers == DESIRED_NUM_OF_SOLDIERS) {
		printf("MAP MINERALS: %d\nLEFT MINERALS: %d\nMINNED MINERALS: %d\n", MAP_MINERALS, left_minerals, MAP_MINERALS - left_minerals);
		free_resourses();
		exit(EXIT_SUCCESS);
	}
}

//--------------------------------------------
// FUNCTION: create_and_train_new_worker
// It creates new workers
// PARAMETERS:
// NO
//----------------------------------------------
void create_and_train_new_worker() {
	if(minned_minerals < NEW_WORKER_PRICE) {
		printf("Not enough minerals.\n");
	}else{
		pthread_mutex_lock(&mutexes[0]);
			minned_minerals -= NEW_WORKER_PRICE;
		pthread_mutex_unlock(&mutexes[0]);

		sleep(1);
		workers_counter++;
		workers = realloc(workers, workers_counter * sizeof(pthread_t));
		if(workers == NULL) {
			free_resourses();
			perror("Can not reallocate new memory for new worker");
			exit(EXIT_FAILURE);
		}
		if(pthread_create(&workers[workers_counter - 1], NULL, worker, (void*)((intptr_t)(workers_counter - 1)))) {
			free_resourses();
			char output_msg[46];
			sprintf(output_msg, "Can not create a new thread(worker: %d thread)", workers_counter);
			perror(output_msg);
			exit(EXIT_FAILURE);
		}

		printf("SCV good to go, sir.\n");
	}
}

//--------------------------------------------
// FUNCTION: create_new_command_center
// Creates new command centers
// PARAMETERS:
// NO
//----------------------------------------------
void create_new_command_center() {
	if(minned_minerals < NEW_COMMAND_CENTER_PRICE) {
		printf("Not enough minerals.\n");
	}else{
		pthread_mutex_lock(&mutexes[0]);
			minned_minerals -= NEW_COMMAND_CENTER_PRICE;
		pthread_mutex_unlock(&mutexes[0]);

		sleep(2);
		mutex_counter++;
		mutexes = realloc(mutexes, mutex_counter * sizeof(pthread_mutex_t));
		if(mutexes == NULL) {
			free_resourses();
			perror("Can not reallocate new memory for new command center");
			exit(EXIT_FAILURE);
		}
		printf("Command center %d created.\n", mutex_counter - 3 + 1);
	}
}
