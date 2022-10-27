#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel* read_ppm(const char* filename, int* w, int* h) {
  char str[1068];
  char check[2];
  FILE* fp = fopen(filename, "rb");
  if(fp == NULL){
    //printf("Not a valid file");
    return NULL;
  }
  fgets(str,1068,fp);
  sscanf(str, " %s", check);
  if(check[0] != 'P' || check[1] != '6'){
    //printf("Not a valid file");
    return NULL;
  }
  fgets(str,1068,fp);
  fgets(str,1068,fp);
  sscanf(str, " %d %d", w,h);
  struct ppm_pixel* arr;
  arr = malloc(sizeof(struct ppm_pixel) * (*w)*(*h));

  fgets(str,1068,fp);
  fread(arr,sizeof(struct ppm_pixel),(*w)*(*h),fp);
  
  fclose(fp); 
  return(arr);
}

struct ppm_pixel** read_ppm_2d(const char* filename, int* w, int* h) {

  return NULL;
}
