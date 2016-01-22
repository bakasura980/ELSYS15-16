#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


#define STINSYM '-'
#define SIZE 10
#define HSB "==>"
#define HSE "<==\n"

typedef struct {
	char *arr;
	size_t capacity;
	size_t size;
} Array;

void arr_init(Array *a) {
	a->arr = (char *)malloc(SIZE * sizeof(char));
	a->capacity = SIZE;
	a->size = 0;
}

void arr_free(Array *a) {
	free(a->arr);
	a->arr = NULL;
	a->size = 0;	
}

int arr_get_size(Array *a) {
	return a->size;
}

void arr_resize(Array *a) {
	a->capacity *= 2;
  a->arr = realloc(a->arr, sizeof(char) * a->capacity);
}

void arr_push(Array *a, char c) {
	if(a->size == a->capacity) {
		arr_resize(a);
	}
	a->arr[a->size++] = c;
}

int stdin_get_pos(Array *a) {
	int pos = 0;
	int rc = 0;
	char buff[1];
	int asize = arr_get_size(a);
	int i = asize;
	pos = asize;
	for(i; i >= 0; --i) {
		buff[0] = a->arr[pos];
		if(buff[0] == '\n' && (asize - i) > 1) {
			rc++;
			if(rc == SIZE) return pos++;
		}
		pos--;
	}
}

void stdin_manager() {
	int i = 0;
	int rc = 0;
	char buff[1];
	Array content;
	arr_init(&content);
	while(read(0, buff, 1) > 0) {
		arr_push(&content, buff[0]);
		if(buff[0] == '\n') rc++;
	}
	if(buff[0] != '\n') {
		arr_push(&content, '\n');
		rc++;
	}
	int asize = arr_get_size(&content);
	if(rc > SIZE) i = stdin_get_pos(&content);
	write(1, "\n", 1);
	write(1, "\n", 1);
	for(i ; i < asize; ++i) {
		write(1, &content.arr[i], 1);
	}
	write(1, "\n", 1);
	arr_free(&content);
}

int rows_counter(int *fd) {
	int counter = 0;
	char buff[1];
	while(read(*fd, buff, 1) > 0) {
		if(buff[0] == '\n') counter++;
	}
	return counter;
}

int file_get_pos(int *fd) {
	int pos = 0;
	int rc = 0;
	char buff[1];
	int fsize = lseek(*fd, 0, SEEK_END);
	int i = fsize;
	pos = fsize;
	for(i; i >= 0; --i) {
		read(*fd, buff, 1);
		if(buff[0] == '\n' && (fsize - i > 1)) {
			rc++;
			if(rc == SIZE) return pos++;
		}
		pos--;
		lseek(*fd, i, SEEK_SET);
	}
}

void file_printer(int *fd, int pos) {
	char buff[1];
	lseek(*fd, pos, SEEK_SET);
	while(read(*fd, buff, 1) > 0) {
		write(1, buff, 1);
	}
}

void file_manager(int fname_length, char fname[fname_length], int argsnum) {
	int fd = open(fname, O_RDONLY);
	if(fd < 0) {
		perror(fname);
	}else{
		int rows = rows_counter(&fd);
		int pos = 0;
		if(rows > SIZE) pos = file_get_pos(&fd);
		if(argsnum > 1) {
			write(1, HSB, 3);
			write(1, fname, fname_length);
			write(1, HSE, 4);
		}
		file_printer(&fd, pos);
		write(1, "\n", 1);
	}
	close(fd);
}

int main(int argc, char* argv[]) {
	int i;
	for(i = 1; i < argc; ++i) {
		if(*argv[i] == STINSYM) {
			stdin_manager();
		}else{
			file_manager(strlen(argv[i]), argv[i], argc - 1);
		}
	}
	return 0;
}
