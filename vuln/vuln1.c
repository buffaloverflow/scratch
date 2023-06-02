#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *base_cmd = "ls -l %s";

int main(int argc, char **argv) {
  char file[10] = {0};
  char stat[20] = {0};
  char stat_file[1024] = {0};
  memcpy(stat, base_cmd, 20);
  
  printf("Files:\n");
  system("ls");
  printf("\n");

  strcat(file, readline("Select file to see details: "));
  sprintf(stat_file, stat, file);
  system(stat_file);
}

