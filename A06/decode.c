#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: decode <file.ppm>\n");
    return 0;
  }
  int w, h;
  char* filename = argv[1];
  struct ppm_pixel* pixels = read_ppm(filename, &w, &h);
  if(pixels == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  printf("Reading file %s with width %d and height %d\n", filename, w, h);

  int size = w*h*3;
  int* lsb = malloc(sizeof(int) *size);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      struct ppm_pixel p = pixels[i*w + j];
      lsb[i*w + j] = (int)p.red%2;
      lsb[i*w + j + 1] = (int)p.green%2;
      lsb[i*w + j + 2] = (int)p.blue%2;
    }
  }

  size = (w*h*3)/8;
  printf("Max number of characters in the image: %d", size);
  int* c = malloc(sizeof(int) *size);
  size = 0;
  for(int i = 0; i < h*w*3; i = i+8){
    c[size] = ((2*2*2*2*2*2*2)*(lsb[i])) + ((2*2*2*2*2*2)*(lsb[i+1])) + ((2*2*2*2*2)*(lsb[i+2])) + ((2*2*2*2)*(lsb[i+3])) + ((2*2*2)*(lsb[i+4])) + ((2*2)*(lsb[i+5])) + ((2)*(lsb[i+6])) + ((1)*(lsb[i+7]));
    printf("%c", (char) c[size]);
    size++;
  }

  

  return 0;
}

