#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

char convert(int intensity){
  if(0 <= intensity && intensity <= 25){
    return '@';
  }
  else if(26 <= intensity && intensity <= 50){
    return '#';
  }
  else if(51 <= intensity && intensity <= 75){
    return '%';
  }
  else if(76 <= intensity && intensity <= 100){
    return '*';
  }
  else if(101 <= intensity && intensity <= 125){
    return 'o';
  }
  else if(126 <= intensity && intensity <= 150){
    return ';';
  }
  else if(151 <= intensity && intensity <= 175){
    return ':';    
  }
  else if(176 <= intensity && intensity <= 200){
    return ',';
  }
  else if(201 <= intensity && intensity <= 225){
    return '.';
  }
  else if(226 <= intensity && intensity <= 255){
    return ' ';
  }
  else{
    return 'e';
  }
}

int main(int argc, char** argv) {
  int w;
  int h;
  int intensity;
  int r;
  int g;
  int b;
  if (argc != 2) {
    printf("usage: ascii_image <file.ppm>\n");
    return 0;
  }
  
  char *file = argv[1];
  struct ppm_pixel* ppm_array;
  ppm_array = read_ppm(file,&w,&h);
  if(ppm_array == NULL){
    printf("Not a valid file \n");
    return 0;
  }
  printf("Reading %s: with width %d and height %d \n", file,w,h);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      struct ppm_pixel a = ppm_array[i*h + j];
      r = (int)a.red;
      g = (int)a.green;
      b = (int)a.blue;
      intensity = (int)(r + g + b)/3;
      char symbol = convert(intensity);
      printf(" %c", symbol);
      //printf(" %d %d %d %d\n", r,g,b,intensity);
    }
    printf("\n");
  }

  free(ppm_array);
  return 0;
}

