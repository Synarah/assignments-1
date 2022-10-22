#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: glitch <file.ppm>\n");
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

  for(int i = 0; i < h; i++){
    for(int j = 0; j < w; j++){
      struct ppm_pixel p = pixels[i*w + j];
      p.red = p.red << (rand() % 2);
      p.blue = p.blue << (rand() % 2);
      p.green = p.green << (rand() % 2);
      pixels[i*w + j] = p;
    }
  }

  char* new_fp = malloc(strlen(filename)+8);
  strcpy(new_fp, filename);
  new_fp[strlen(new_fp)-4] = '\0';
  strcat(new_fp,"-glitch.ppm");
  printf("Writting file %s\n", new_fp);
  write_ppm(new_fp, pixels, w, h);

  free(pixels);
  free(new_fp);
  return 0;
}

