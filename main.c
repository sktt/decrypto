#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

void char_occurs(char* string, int result[]) {
  int c = -1;
  do {
    c = *string > 'Z' ? *string-'a' : *string-'A';
    result[c]++; 
  } while(*(++string) != '\0');
}

void seq_rep(char* string, char* result[], int* positions){ 
  int strlen = strnlen(string, INT_MAX), 
      winsize = 4, winpos, startpos = 0, i;
  while(winsize++ < strlen/2) {
    startpos = 0;
    for(startpos = 0; startpos < strlen-winsize; startpos++) {
      winpos = startpos+winsize;
      for(winpos = startpos+winsize; winpos <= strlen-winsize; winpos++) {
        if (!memcmp(string+startpos, string+winpos, winsize)) {
          char* strmatch = (char*)malloc(strlen/2);
          memcpy(strmatch, string+winpos, winsize);
          for(i=0; result[i] != 0 && strstr(strmatch,result[i]) == NULL; i++)
            ;
          result[i] = strmatch;
          positions[i] = winpos;
        }
      }
    }
  }
}

int main(int argc, char** args){
  if (argc <= 1) {
    return 1;
  }
  int occurs[26] = { 0 };
  char_occurs(args[1], occurs);
  int i = 0;
  int j = 0;
  for( ; i <= 'z'-'a'; i++){
    printf("%c:%d :\t", 'a'+i,occurs[i]);
    for(j = occurs[i]; j; j--){
      printf("|");
    }
    printf("\n");
  }
  char* matches[100] = { 0 };
  int positions[100];
  seq_rep(args[1], matches, positions);
  printf("patterns: ");
  for (i=0; matches[i]; i++)
    printf("%s@%d, ", matches[i],positions[i]);
  printf("\n");
  return 0;
}
