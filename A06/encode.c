#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
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

  

  return 0;
}

