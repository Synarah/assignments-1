#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  // load feep-raw and print out the grid of pixels
  int w;
  int h;

  struct ppm_pixel* ppm_array = read_ppm("feep-raw.ppm",&w,&h);
  if(ppm_array == NULL){
    printf("Not a valid file");
  }
  else{
    printf("Testing file feep-raw.ppm: %d %d", w,h);
  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      printf("(%hhu,%hhu,%hhu) ", ppm_array[i*h + j].red, ppm_array[i*h + j].green,ppm_array[i*h + j].blue);
    }
    printf("\n");
  }
  free(ppm_array);
  }
  
  return 0;
}

