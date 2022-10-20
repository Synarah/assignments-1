#include <stdio.h>

int main() {
  unsigned long img;
  scanf(" %lx", &img);
  printf("Image (unsigned long): %lx\n", img);
  unsigned long mask = 0x1ul << 63;
  unsigned long a;
  int b = 63;
  for(int i = 0; i < 64; i++){
    a = mask & img;
    a = a >> b;
    if(a == 1){
      printf("@");
    }
    else{
      printf(" ");
    }
    b--;
    mask = mask >> 1;
    if(i != 0 && (i + 1) % 8 == 0){
      printf("\n");
    }
  }
  return 0;
}
