#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <pthread.h>
#include "read_ppm.h"
#include "write_ppm.h"

pthread_mutex_t mutex;
pthread_barrier_t barrier;

struct thread_data{
  int id;
  struct ppm_pixel *pix;
  int start_col;
  int end_col;
  int start_row;
  int end_row;
  struct ppm_pixel *pal;
  int size;
  int maxIterations;
  float xmin;
  float ymin;
  float xmax;
  float ymax;
  int *mem;
  int *count;
  int *con;
};

void formula1(int id, struct ppm_pixel *pix, int start_col , int end_col, int start_row, int end_row, struct ppm_pixel *pal, int size, int maxIterations, float xmin, float ymin, float xmax, float ymax, int *mem, int *count, int *con){
  for(int i = start_row; i < end_row; i++){
    for(int j = start_col; j < end_col; j++){
      float xfrac = ((float) i)/size;
      float yfrac = ((float) j)/size;
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
        //pix[i * size + j].red = 1;
        //pix[i * size + j].green = 1;
        //pix[i * size + j].blue = 1;
        mem[i * size + j] = 1;
      }
      else{
        //pix[i * size + j].red = 0;
        //pix[i * size + j].green = 0;
        //pix[i * size + j].blue = 0;
        mem[i * size + j] = 0;
      }
    }
  }
}

void formula2(int id, struct ppm_pixel *pix, int start_col , int end_col, int start_row, int end_row, struct ppm_pixel *pal, int size, int maxIterations, float xmin, float ymin, float xmax, float ymax, int *mem, int *count, int *con){
  for(int i = start_row; i < end_row; i++){
    for(int j = start_col; j < end_col; j++){
      if(mem[i * size + j] == 1){
        float xfrac = ((float) i)/size;
        float yfrac = ((float) j)/size;
        float x0 = xmin + xfrac * (xmax - xmin);
        float y0 = ymin + yfrac * (ymax - ymin);
      
        float x = 0.0;
        float y = 0.0;
        while (x*x + y*y < 2*2){
          float xtmp = x*x - y*y + x0;
          y = 2*x*y + y0;
          x = xtmp;

          int yrow = round(size * (y - ymin)/(ymax - ymin));
          int xcol = round(size * (x - xmin)/(xmax - xmin));
          if(yrow < 0 || yrow >= size){
            continue;
          }
          if(xcol < 0 || xcol >= size){
            continue;
          }

          pthread_mutex_lock(&mutex);
          count[yrow * size + xcol] += 1;
          if(count[yrow * size + xcol] > *con){
            *con = count[yrow * size + xcol];
          }
          pthread_mutex_unlock(&mutex);
        }
      }
    }
  }
}

void formula3(int id, struct ppm_pixel *pix, int start_col , int end_col, int start_row, int end_row, struct ppm_pixel *pal, int size, int maxIterations, float xmin, float ymin, float xmax, float ymax, int *mem, int *count, int *con){
  float gamma = 0.681;
  float factor = 1.0/gamma; 
  for(int i = start_row; i < end_row; i++){
    for(int j = start_col; j < end_col; j++){
      float val = 0; 

      if(count[i * size + j] > 0){
        val = log(count[i * size + j])/log(*con);
        val = pow(val, factor);
      }
      pix[i * size + j].red = val * 255;
      pix[i * size + j].green = val * 255;
      pix[i * size + j].blue = val * 255;
    }
  }
  printf("Thread %d finished\n", id);
}

void *do_formula(void *userdata){
  struct thread_data *data = (struct thread_data *) userdata;
  formula1(data->id, data->pix, data->start_col, data->end_col, data->start_row, data->end_row, data->pal, data->size, data->maxIterations, data->xmin, data->ymin, data->xmax, data->ymax, data->mem, data->count, data->con);
  formula2(data->id, data->pix, data->start_col, data->end_col, data->start_row, data->end_row, data->pal, data->size, data->maxIterations, data->xmin, data->ymin, data->xmax, data->ymax, data->mem, data->count, data->con);
  pthread_barrier_wait(&barrier);
  formula3(data->id, data->pix, data->start_col, data->end_col, data->start_row, data->end_row, data->pal, data->size, data->maxIterations, data->xmin, data->ymin, data->xmax, data->ymax, data->mem, data->count, data->con);
  return (void*) NULL; 
}

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  int numProcesses = 4;

  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:p:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> "
        "-b <ymin> -t <ymax> -p <numProcesses>\n", argv[0]); break;
    }
  }
  printf("Generating buddhabrot with size %dx%d\n", size, size);
  printf("  Num processes = %d\n", numProcesses);
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
  int *mem = malloc(sizeof(int)* size * size);
  int *count = malloc(sizeof(int)* size * size);
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      count[i * size + j] = 0;
    }
  }
  int con = 0;

  double t; 
  struct timeval tstart, tend;
  gettimeofday(&tstart, NULL);

  pthread_t threads[4];
  pthread_mutex_init(&mutex, NULL);
  pthread_barrier_init(&barrier, NULL, 4);
  struct thread_data data[4];

  for(int i = 0; i < 4; i++){
    if(i == 0){
      printf("%d) Sub-image block: cols (0, 240) to rows (0,240)\n", i);
      data[i].id = i;
      data[i].pix = pix;
      data[i].start_col = 0;
      data[i].end_col = 240;
      data[i].start_row = 0;
      data[i].end_row = 240;
      data[i].pal = pal;
      data[i].size = size;
      data[i].maxIterations = maxIterations;
      data[i].xmin = xmin;
      data[i].ymin = ymin;
      data[i].xmax = xmax;
      data[i].ymax = ymax;
      data[i].mem = mem;
      data[i].count = count;
      data[i].con = &con;
      pthread_create(&threads[i], NULL, do_formula, (void*) &data[i]);
    }
    else if(i == 1){
        printf("%d) Sub-image block: cols (240, 480) to rows (0,240)\n", i); 
        data[i].id = i;
        data[i].pix = pix;
        data[i].start_col = 240;
        data[i].end_col = 480;
        data[i].start_row = 0;
        data[i].end_row = 240;
        data[i].pal = pal;
        data[i].size = size;
        data[i].maxIterations = maxIterations;
        data[i].xmin = xmin;
        data[i].ymin = ymin;
        data[i].xmax = xmax;
        data[i].ymax = ymax;
        data[i].mem = mem;
        data[i].count = count;
        data[i].con = &con;
        pthread_create(&threads[i], NULL, do_formula, (void*) &data[i]);
      }
      else if(i == 2){
        printf("%d) Sub-image block: cols (0, 240) to rows (240,480)\n", i); 
        data[i].id = i;
        data[i].pix = pix;
        data[i].start_col = 0;
        data[i].end_col = 240;
        data[i].start_row = 240;
        data[i].end_row = 480;
        data[i].pal = pal;
        data[i].size = size;
        data[i].maxIterations = maxIterations;
        data[i].xmin = xmin;
        data[i].ymin = ymin;
        data[i].xmax = xmax;
        data[i].ymax = ymax;
        data[i].mem = mem;
        data[i].count = count;
        data[i].con = &con;
        pthread_create(&threads[i], NULL, do_formula, (void*) &data[i]);
      }
      else if(i == 3){
        printf("%d) Sub-image block: cols (240, 480) to rows (240,480)\n", i); 
        data[i].id = i;
        data[i].pix = pix;
        data[i].start_col = 240;
        data[i].end_col = 480;
        data[i].start_row = 240;
        data[i].end_row = 480;
        data[i].pal = pal;
        data[i].size = size;
        data[i].maxIterations = maxIterations;
        data[i].xmin = xmin;
        data[i].ymin = ymin;
        data[i].xmax = xmax;
        data[i].ymax = ymax;
        data[i].mem = mem;
        data[i].count = count;
        data[i].con = &con;
        pthread_create(&threads[i], NULL, do_formula, (void*) &data[i]);
      }
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  gettimeofday(&tend, NULL);

  t = tend.tv_sec - tstart.tv_sec + (tend.tv_usec-tstart.tv_usec)/1.e6;
  int timestamp = time(0);

  printf("Computed buddhabrot set (%dx%d) in %f seconds\n", size, size,t);

  char fp[100];
  sprintf(fp, "buddhabrot-%d-%d.ppm", size, timestamp);
  printf("Writing file: %s\n", fp);
  write_ppm(fp, pix, size, size);

  pthread_mutex_destroy(&mutex);
  pthread_barrier_destroy(&barrier);
  free(pix);
  free(pal);
  free(mem);
  free(count);
}
