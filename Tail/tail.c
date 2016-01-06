//--------------------------------------------
// NAME: Valentin Stoyanov
// CLASS: XIb
// NUMBER: 7
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE: реализация на tail
//---------------------------------------------

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 10
#define BS "==>"
#define ES "<=="

//--------------------------------------------
// STRUCTURE: Array
// PARAMETERS:
// *arr - масив от char-ове
// capacity - капацитетът на масива
// size - размерът на масива
//----------------------------------------------
typedef struct {
	char *arr;
	size_t capacity;
	size_t size;
} Array;

//--------------------------------------------
// FUNCTION: arr_init 
// Инициализиране на диманичния масив
// PARAMETERS:
// a - pointer към структурата, която трябва да се инициализира
//----------------------------------------------
void arr_init(Array *a) {
	a->arr = (char *)malloc(SIZE * sizeof(char));
	a->capacity = SIZE;
	a->size = 0;
}

//--------------------------------------------
// FUNCTION: arr_free
// Освобождава паметта, след като динамично създаденият масив вече не е нужен
// PARAMETERS:
// a - pointer към структурата, която трябва да се инициализира
//----------------------------------------------
void arr_free(Array *a) {
	free(a->arr);
	a->arr = NULL;
	a->size = 0;	
}

//--------------------------------------------
// FUNCTION: arr_size
// Връща големината на масива
// PARAMETERS:
// a - pointer към структурата, която трябва да се инициализира
//----------------------------------------------
int arr_size(Array *a) {
	return a->size;
}

//--------------------------------------------
// FUNCTION: arr_resize
// Удвоява размера на масива
// PARAMETERS:
// a - pointer към структурата, която трябва да се инициализира
//----------------------------------------------
void arr_resize(Array *a) {
	a->capacity *= 2;
  a->arr = realloc(a->arr, sizeof(char) * a->capacity);
}

//--------------------------------------------
// FUNCTION: arr_push
// Добавя променлива в края на масива
// PARAMETERS:
// a - pointer към структурата, която трябва да се инициализира
// с - променливата, която трябва да се добави
//----------------------------------------------
void arr_push(Array *a, char c) {
	if(a->size == a->capacity) {
		arr_resize(a);
	}
	a->arr[a->size++] = c;
}

//--------------------------------------------
// FUNCTION: row_counter
// Брой от колко реда има във файла.
// PARAMETERS:
// *dsc - pointer към файловия дескриптор
// сounter - броячът на редовете
//----------------------------------------------
int row_counter(int* dsc) {
	int counter = 0;
	char buff[1];
	while(read(*dsc, buff, 1) > 0) {
		if(buff[0] == '\n') counter++;
	}
	return counter;
}

//--------------------------------------------
// FUNCTION: get_pos
// Взима позицията, от която трябва да започне извеждането
// PARAMETERS:
// *dsc - pointer към файловия дескриптор
// r - броят редове, които има файла
// i - брояч, чрез който се обхожда файла
// fpos - позицията, на която се намираме във файла
// lc - брояч, който следи на кой ред сме
// fs - големината на файла
//----------------------------------------------
int get_pos(int* dsc, int r) {
	int i, fpos = 0, lc = 0;
	int fs = lseek(*dsc, 0, SEEK_END);
	i = fs;
	fpos = fs;
	char buff[1];
	for(i; i >= 0; i--) {
		read(*dsc, buff, 1);
		if(buff[0] == '\n' && (fs - i) > 1) {
			lc++;
			if(lc == SIZE) break;
		}
		fpos--;
		lseek(*dsc, fpos, SEEK_SET);
	}
	fpos++;
	return fpos;
}

//--------------------------------------------
// FUNCTION: print
// Извежда от файла на стандартния изход
// PARAMETERS:
// *dsc - pointer към файловия дескриптор
// p - позията, от която да започне извеждането
//----------------------------------------------
void print(int* dsc, int p) {
	lseek(*dsc, p, SEEK_SET);
	char buff[1];
	while(read(*dsc, buff, 1) > 0) {
		write(1, buff, 1);
	}
}

//--------------------------------------------
// FUNCTION: file_manager
// Извиква горните функции и предава техните стойности на други.
// PARAMETERS:
// file - името на файла, който да бъде отворен
// size - дължината на името на файла
// argnum - броя на аргументите подадени на командния ред
// fd - файлов дескриптор на файла
// rows - колко реда има дадения файл
// pos - позицията, от която да започне извеждането
//----------------------------------------------
void file_manager(int size, char file[size], int argnum) {
	int fd = open(file, O_RDONLY);
	if (fd < 0) {
		perror(file);
		exit(EXIT_FAILURE);
	}
	int rows = row_counter(&fd);
	int pos = 0;
	if(rows > SIZE) pos = get_pos(&fd, rows);
	if(argnum > 2) {
		write(1, BS, 3);
		write(1, file, size);
		write(1, ES, 3);
		write(1, "\n", 1);
		print(&fd, pos);
		write(1, "\n", 1);
	}else print(&fd, pos);
	close(fd);
}

//--------------------------------------------
// FUNCTION: get_pos_stdin
// Взима индекса на масива, от който да започне извеждането
// PARAMETERS:
// a - pointer към структурата
// i - брояч, който обхожда масива
// apos - позицията, на която се намираме
// lc - броя нови редове
// as - размер на масива
// buff - променлива, която приема стойности от масива
//----------------------------------------------
int get_pos_stdin(Array *a) {
	int i, apos = 0, lc = 0;
	int as = arr_size(a);
	i = as;
	apos = as;
	char buff;
	for(i; i >= 0; i--) {
		buff = a->arr[apos];
		if(buff == '\n' && (as - i) > 1) {
			lc++;
			if(lc == SIZE) break;
		}
		apos--;
	}
	apos++;
	return apos;
}

//--------------------------------------------
// FUNCTION: stdin_manager
// Извиква горните функции и извежда на стандартния изход
// PARAMETERS:
// j - брояч, от който започва извеждането
// lc - броя нови редове
// ch - масив, в който четем от стандартния вход
// array - структурата
//----------------------------------------------
void stdin_manager() {
	int j = 0, lc = 0;
	char ch[1];
	Array array;
	arr_init(&array);
	while(read(0, ch, sizeof(ch)) > 0) {
		arr_push(&array, ch[0]);
		if(ch[0] == '\n') lc++;
	}
	if(ch[0] != '\n') {
		lc++;
		arr_push(&array, '\n');
	}
	if(lc > SIZE) j = get_pos_stdin(&array);
	write(1, "\n", 1);
	write(1, "\n", 1);
	for(j; j < arr_size(&array); ++j) {
		ch[0] = array.arr[j];
		write(1, ch, 1);
	}
	write(1, "\n", 1);
	arr_free(&array);
}

//--------------------------------------------
// FUNCTION: main
// За всеки аргумент извиква съответната функция
// PARAMETERS:
// argc - броя на аргументите от командния ред
// argv - самите аргументи
// i - брояч, който да обхожда argv
//----------------------------------------------                                  
int main(int argc, char* argv[]) {
	int i;
	for(i = 1; i < argc; i++) {
		if(*argv[i] == '-') {
			stdin_manager();
		}else {
			file_manager(strlen(argv[i]), argv[i], argc);
		}
	}
	return 0;
}
