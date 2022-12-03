#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"
#include "write_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);


  srand(time(0));

  struct ppm_pixel *pal = malloc(sizeof(struct ppm_pixel) * maxIterations);
  for(int i = 0; i < maxIterations; i++){
    pal[i].red = rand() % 255;
    pal[i].green = rand() % 255;
    pal[i].blue = rand() % 255;
  }

  struct ppm_pixel *pix = malloc(sizeof(struct ppm_pixel) * size * size);

  double t; 
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);

  for(int i= 0; i<size; i++){
    for(int j=0; j<size; j++){
      float xfrac = ((float) j)/size;
      float yfrac = ((float) i)/size;
      float x0 = xmin + xfrac * (xmax - xmin);
      float y0 = ymin + yfrac * (ymax - ymin);
    
      float x = 0.0;
      float y = 0.0;
      int iter = 0;
      while (iter < maxIterations && x*x + y*y < 2*2){
        float xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
        iter++;
      }
      if(iter < maxIterations){
        pix[i * size + j] = pal[iter];
      }
      else{
        pix[i * size + j].red = 0;
        pix[i * size + j].green = 0;
        pix[i * size + j].blue = 0;
      }
    }
  }

  gettimeofday(&tend, NULL);

  t = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
  int timestamp = time(0);

  printf("Computed mandelbrot set (%dx%d) in %f seconds\n", size, size,t);

  char fp[100];
  sprintf(fp, "mandelbrot-%d-%d.ppm", size, timestamp);
  printf("Writing file: %s\n", fp);
  write_ppm(fp, pix, size, size);

  free(pix);
  free(pal);
  

}
