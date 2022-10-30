#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char** argv) {

  char* filename = argv[1];
  char phrase [100];
  int size, w, h;
  int i = 0;
  int j = 0;
  int count = 7;

  if(filename == NULL){
    printf("Error no file \n");
  }

  if (argc != 2) {
    printf("usage: encode <file.ppm>\n");
    return 0;
  }

  unsigned char* pixels = (unsigned char*)read_ppm(filename, &w, &h);
  if(pixels == NULL){
    printf("Error, not a valid file\n");
    exit(0);
  }
  printf("Reading file %s with width %d and height %d\n", filename, w, h);

  printf("Enter a phrase: \n");
  scanf("%[^\n]%*c", phrase);

  size = strlen(phrase);
  printf("Max number of characters in the image: %d\n", size);

  while(i <= size){
    unsigned char letter = phrase[i];
    unsigned char mask = 0x01;
    unsigned char a = 0xFE;
    while(j < 8){
      unsigned char lm = letter & (mask << count);
      unsigned char opposite =  lm >> count;
      count--;

      if(opposite){
        pixels[i*8 +j] = pixels[i*8 +j] | opposite;
      }
      else{
        pixels[i*8 + j] = pixels[i*8 + j] & a;
      }
      if(count < 0){
        count = 7;
      }
      j++;
    }
    j = 0;
    i++;
  }

  char* new_fp = malloc(strlen(filename)+8);
  strcpy(new_fp, filename);
  new_fp[strlen(new_fp)-4] = '\0';
  strcat(new_fp,"-encode.ppm");
  printf("Writting file %s\n", new_fp);
  write_ppm(new_fp, (struct ppm_pixel*)pixels, w, h);
  free(pixels);
  free(new_fp);
  
  return 0;
}

