#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

char *base_cmd = "ls -l '%s'";

int main(int argc, char **argv) {
  char stat[20] = {0};
  int a = 0;
  char stat_file[1024] = {0};
  char file[10] = {0};
  memcpy(stat, base_cmd, 20);
  
  printf("Files:\n");
  system("ls");
  printf("\n");

  char *rl = readline("Select file to see details: ");
  memcpy(file, rl, strlen(rl));
  sprintf(stat_file, stat, file);
  system(stat_file);
}

