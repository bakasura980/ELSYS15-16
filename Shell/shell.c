//--------------------------------------------
// NAME: Valentin Stoyanov
// CLASS: XIb
// NUMBER: 7
// PROBLEM: #2
// FILE NAME: shell.c
// FILE PURPOSE:
// реализация на shell
//---------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#define SIZE 32
#define DELIM " \n"
#define EX "exit\n"
#define ENTER "\n"
#define CL "clear\n"
#define CLEAR printf("\033[H\033[J")

//--------------------------------------------
// FUNCTION: get_cmdline
// Чете и връща ред от стандартния вход
// PARAMETERS:
// line - string, в който да се прочете реда
// bsize - размер на буфер 
//----------------------------------------------
char* get_cmdline() {
	char *line = NULL;
	ssize_t bsize = 0;
	getline(&line, &bsize, stdin);
	return line;
}

//--------------------------------------------
// FUNCTION: parse_cmdline
// Разделя прочетения ред и връща масив от string-ове
// PARAMETERS:
// cmdline - редът, който трябва да се parse-не
// alloc_size - размерът, с който да се инициализира масива от string-ове
// parsed_line - масивът от string-ове, който държи parse-натия ред
// token - запазва част от реда
// copy - копие на cmdline
// i - брояч
// ws - булева променлива, която да е true, ако има space в реда
//----------------------------------------------
char** parse_cmdline(const char* cmdline) {
	int alloc_size = SIZE;
	char** parsed_line = malloc(alloc_size * sizeof(char*));
	char* token;
	char* copy = strdup(cmdline);
	int i = 0;
	bool ws = true;
	for(i = 0; i < strlen(cmdline); ++i) {
		if(&cmdline[i] == " ") {
			ws = false;
		}
	}
	i = 0;
	if(ws) {
		token = strtok(copy, DELIM);
		while(token != NULL) {
			parsed_line[i] = token;
			i++;
			if(i >= alloc_size) {
				alloc_size += SIZE;
				parsed_line = realloc(parsed_line, alloc_size * sizeof(char*));
			}
			token = strtok(NULL, DELIM);
		}
		parsed_line[i] = NULL;
	}else parsed_line[0] = copy;
	return parsed_line;
}

//--------------------------------------------
// FUNCTION: shell_execute
// Създава процеса и подава на execv аргументите
// PARAMETERS:
// args - parse-натия string
// fpid - съхранява върнатата стойност на fork()
// wpid - съхранява върнатата стойност на waitpid()
//----------------------------------------------
void shell_execute(char** args) {
	pid_t fpid, wpid;
	int status;
	fpid = fork();
	if(fpid == 0) {
		if(execv(args[0], args) < 0) {
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}else if(fpid < 0) {
			perror(args[0]);
			exit(EXIT_FAILURE);
		}else {
			do{
				wpid = waitpid(fpid, &status, 0);
			}while(wpid != fpid);
		}
}

//--------------------------------------------
// FUNCTION: shell_manager
// Извиква горните функции и им предава върнатите стойности 
// PARAMETERS:
// l - прочетения ред от стандартния вход
// pl - parse-натия ред
//----------------------------------------------
void shell_manager() {
	char* l;
	char** pl;
	while(1) {
		printf("> ");
		l = get_cmdline();
		if(strcmp(l, ENTER) != 0) {
			if(strcmp(l, EX) == 0) {
				CLEAR;
				exit(EXIT_SUCCESS);
			}
			if(strcmp(l, CL) == 0) CLEAR;
			else {
				pl = parse_cmdline(l);
				shell_execute(pl);
				free(l);
				free(pl);
			}
		}
	}
}

//--------------------------------------------
// FUNCTION: main
// Извиква функцията, която управлява shell-а
// PARAMETERS:
// няма
//----------------------------------------------
int main() {
    	shell_manager();
	return 0;
}







