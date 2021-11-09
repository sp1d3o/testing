#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_W 1000
#define MAX_F 500

void clear(void);

int main(int argc, char *argv[])
{
  FILE* rep = fopen("code_to_change.c", "r");
  FILE* tmp = fopen("Temp.c", "w");

  int ch;
  int chk;

  if(rep == NULL || tmp == NULL) {
    perror("\nError");
  }
  
  else {
    char target[MAX_W] = "func";
    clear;
    char replace[MAX_F] = "printf";
    clear;

    while(1) {
      ch = fgetc(rep);
      if(ch == EOF) {
        break;
      }
      else if(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        fputc(ch, tmp);
      }
      else {
        char buffer[MAX_W];
        fseek(rep, -1, SEEK_CUR);
        fscanf(rep, "%500s", buffer);
        if(strcmp(buffer, target) == 0) {
          strcpy(buffer, replace);
        }
        fprintf(tmp," %s", buffer);
      }
    }
    fclose(rep);
    chk = fclose(tmp);
    if(chk == EOF) {
      remove("Temp.c");
      perror("\nFailed");
    }
    else {
      if(rename("Temp.c", "code_to_change.c") == 0) {
        printf("Good\n");
      }
      else {
        remove("code_to_change.c");
        if(rename("Temp.c", "code_to_change.c") == 0) {
          printf("Good\n");
        }
        else {
          remove("Temp.c");
          perror("\nFail");
        }
      }
    } 
  }

  //int ch = system(gcc...);
  return 0;
}

void clear() 
{
  int clear;
  
  while((clear = getchar()) != '\n' && clear != EOF);
}
