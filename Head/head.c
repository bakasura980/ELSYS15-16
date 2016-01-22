//Valentin Stoyanov, XIb, #7.
//head implementation

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define SIZE 10

void file_printer(int *fd) {
	int lc = 0;
	int rrv = 0;
	int i = 0;
	int srv = 0;
	char buff[1];
	int file_size = lseek(*fd, 0, SEEK_END);
	lseek(*fd, 0, SEEK_SET);
	while(lc != SIZE) {
		srv = lseek(*fd, i, SEEK_SET);
		if(srv < 0) {
			perror("seek");
			break;
		}
		rrv = read(*fd, buff , 1);
		if(rrv < 0) {
			perror("read");
			break;
		}
		if(srv != file_size) {
			if(buff[0] == '\n') lc++;
			if(write(1, buff, 1) < 0) {
				perror("write");
			}
		}else break;
		i++;
	}
}

void file_manager(int fname_length, char fname[fname_length]) {
	int fd = open(fname, O_RDONLY);
	if(fd < 0) {
		perror(fname);
	}else {
		file_printer(&fd);	
	}
	if(close(fd) < 0) {
		perror(fname);
	}
}

int main(int argc, char* argv[]) {
	int i = 1;
	if(argc <= 1) {
		write(1, "No Arguments\n", 13); 
	}else{
		for(i; i < argc; ++i) {
			file_manager(strlen(argv[i]), argv[i]);
		}
	}
	return 0;
}
