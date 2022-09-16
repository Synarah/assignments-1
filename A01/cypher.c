#include <stdio.h>
#include <string.h>
int main() {
  char buff[128];
  printf("Enter a word: ");
  scanf(" %s", buff);
  
  printf("Enter a shift: ");
  int shift;
  scanf(" %d", &shift);

  int n = strlen(buff);
  for (int i = 0; i < n; i++) {
    char c = buff[i];
    if(shift < 0){
      if(c >= 'a' && c <= 'z'){
        c = c + shift;
      }  
      if(c < 'a'){
        c = c + 'z' - 'a' + 1;
      }
      buff[i] = c;
    }
    else{
      if(c >= 'a' && c <= 'z'){
        c = c + shift;
      if(c > 'z'){
        c = c - 'z' + 'a' - 1;
      }
      buff[i] = c;
      }
    }  
  }
  printf(" %s", buff);
  return 0;
}
