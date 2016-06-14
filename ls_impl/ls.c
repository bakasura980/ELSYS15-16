#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdbool.h>
#include<time.h>
#include<unistd.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>

#define COLOR_RESET   "\x1b[0m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDBLUE    "\033[1m\033[34m"

bool recursively = false;
bool more_info = false;
bool hidden_files = false;

struct stat file_stat;
int blocks = 0;

bool isDir(char *filename) {
  struct stat file_stat;
  if(stat(filename, &file_stat) == -1) {
    perror(filename);
    exit(EXIT_FAILURE);
  }
  if(S_ISDIR(file_stat.st_mode)) {
    return true;
  }else{
    return false;
  }
}

bool existance(char* filename) {
  if(access( filename, F_OK ) != -1) {
      return true;
  } else {
      return false;
  }
}

char * path_creator(char *dirname, char *filename) {
  if(dirname[strlen(dirname) - 1] != '/') {
    strcat(dirname, "/");
  }
  char *path = strdup(dirname);
  strcat(path, filename);
  return path;
}

void count_blocks() {
  blocks += file_stat.st_blocks;
}

void print_permissions() {
  printf( (S_ISDIR(file_stat.st_mode)) ? "d" : "-");
  printf( (file_stat.st_mode & S_IRUSR) ? "r" : "-");
  printf( (file_stat.st_mode & S_IWUSR) ? "w" : "-");
  printf( (file_stat.st_mode & S_IXUSR) ? "x" : "-");
  printf( (file_stat.st_mode & S_IRGRP) ? "r" : "-");
  printf( (file_stat.st_mode & S_IWGRP) ? "w" : "-");
  printf( (file_stat.st_mode & S_IXGRP) ? "x" : "-");
  printf( (file_stat.st_mode & S_IROTH) ? "r" : "-");
  printf( (file_stat.st_mode & S_IWOTH) ? "w" : "-");
  printf( (file_stat.st_mode & S_IXOTH) ? "x" : "-");
}

void print_link() {
  printf(" %d", file_stat.st_nlink);
}

void print_owner() {
  struct passwd *pw = getpwuid(file_stat.st_uid);
  printf(" %s", (pw == 0) ? "-" : pw->pw_name);
}

void print_group() {
  struct group  *gr = getgrgid(file_stat.st_gid);
  printf(" %s", (gr == 0) ? "-" : gr->gr_name);
}

void print_size() {
  printf(" %d",file_stat.st_size);
}

void print_date() {
  char date[20];
  strftime(date, 20, "%b %d %H:%M", localtime(&(file_stat.st_ctime)));
  printf(" %s", date);
}

void print_file_name(char *filename) {
  printf(" %s%s%s\n", (S_ISDIR(file_stat.st_mode)) ?  BOLDBLUE
  : (file_stat.st_mode & S_IXUSR ? BOLDGREEN : COLOR_RESET), filename, COLOR_RESET);
}

void print_file_info(char *dirname, char *filename) {
  print_permissions();
  print_link();
  print_owner();
  print_group();
  print_size();
  print_date();
  print_file_name(filename);
  count_blocks();
}

void parse(char *dirname, char *filename) {
  if(stat(path_creator(dirname, filename), &file_stat) == -1) {
    perror(path_creator(dirname, filename));
    exit(EXIT_FAILURE);
  }
  if(hidden_files && filename[0] == '.') {
    if(more_info) {
      print_file_info(dirname, filename);
    }else{
      print_file_name(filename);
    }
  }else{
    if(filename[0] != '.') {
      if(more_info) {
        print_file_info(dirname, filename);
      }else{
        print_file_name(filename);
      }
    }
  }
}

void traverse(char *dirname) {
  DIR *dir = opendir(dirname);
  if(dir == NULL) {
    perror(dirname);
    exit(EXIT_FAILURE);
  }
  struct dirent *entry;

  while ((entry = readdir(dir)) != NULL) {
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      parse(dirname, entry->d_name);
      continue;
    }
    if(recursively) {
      if(isDir(path_creator(dirname, entry->d_name))) {
        if(hidden_files) {
          printf("%s:\n", path_creator(dirname, entry->d_name));
          traverse(path_creator(dirname, entry->d_name));
        }else{
          if(entry->d_name[0] != '.') {
            printf("%s:\n\n", path_creator(dirname, entry->d_name));
            traverse(path_creator(dirname, entry->d_name));
          }
        }
      }else{
        parse(dirname, entry->d_name);
      }
    }else{
      parse(dirname, entry->d_name);
    }
  }
  if(closedir(dir) == -1) {
    perror(dirname);
  }
  if (more_info) {
    printf("total %d\n", blocks);
  }
  blocks = 0;
}

int main(int argc, char **argv) {
  int opt;

  while ((opt = getopt(argc, argv, "laR")) != -1) {
    switch (opt) {
      case 'l':
        more_info = true;
        break;
      case 'a':
        hidden_files = true;
        break;
      case 'R':
        recursively = true;
        break;
      default:
        printf("Unknown option - %c\n", opt);
        break;
    }
  }

  int i = 1;
  char *path = "./";
  int options_counter = 0;
  if(argc == 1) {
    traverse(path);
  }else{
    for(i; i < argc; i++) {
      if(argv[i][0] == '-') {
        options_counter++;
      }
    }
    if(argc - options_counter == 1) {
      traverse(path);
    }else{
      i = 1;
      for(i; i < argc; i++) {
        if(argv[i][0] != '-') {
          if(isDir(argv[i])) {
            if(argc - options_counter > 2) {
              printf("%s:\n\n", argv[i]);
            }
            traverse(argv[i]);
          }else{
            if(existance(argv[i])) {
              if(more_info) {
                print_file_info(path, argv[i]);
              }else{
                print_file_name(argv[i]);
              }
            }else{
              printf("%s can not be accessed\n", argv[i]);
            }
          }
        }
      }
    }
  }
  return 0;
}
