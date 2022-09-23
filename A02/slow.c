#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  char buff[32];
  printf("Pause Length: ");
  int pause;
  scanf(" %d", &pause);
  
  printf("Text: ");
  scanf(" %s", buff);

  int k = 0;
  char* slow = malloc(sizeof(char) * 40);
  for(int i = 0; i < sizeof(buff); i++){
    slow[k] = buff[i];
    k++;
    for(int j = 0; j < pause; j++){
      slow[k] = '.';
      k++;
    }
  }
  printf(" %s", slow);

  free(slow);
  return 0;
}

