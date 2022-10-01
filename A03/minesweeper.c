#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv) {

  int m = atoi(argv[1]);
  int n = atoi(argv[2]);
  double p = atof(argv[3]);

  char* mine = malloc(sizeof(char) * m * n);

  srand(time(0));
  int prob;
  char val;
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      prob = rand() % 100;
      if(prob < (p * 100)){
        val = 'X';
        mine[i*n + j] = val;
      }
      else{
        val = '.';
        mine[i*n + j] = val;
      }
      printf(" %c", val);
    }
    printf("\n");
  }
  printf("\n\n");
  
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      int bombs = 0;
      val = '.';
      if(mine[i*n + j] == 'X'){
        val = 'X';
      }
      else if(i == 0 && j == 0){
        if(mine[i*n +j+1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j+1] == 'X'){
          bombs++;
        }
      }
      else if(i == 0 && j < n-1){
        if(mine[(i)*n + j-1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j+1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j-1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j+1] == 'X'){
          bombs++;
        }
      }
      else if(i == 0 && j == n-1){
        if(mine[(i)*n + j-1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j-1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
      }
      else if(j == 0 && i != 0){
        if(mine[(i-1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i-1)*n + j+1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j+1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j+1] == 'X'){
          bombs++;
        }
      }
      else if(j == 0 && i == m-1){
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j + 1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j + 1] == 'X'){
          bombs++;
        }
      }
      else if(i == m-1 && j < n-1){
        if(mine[(i-1)*n + j -1] == 'X'){
          bombs++;
        }
        if(mine[(i-1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i-1)*n + j + 1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j - 1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j + 1] == 'X'){
          bombs++;
        }
      }
      else if(i == m-1 && j == n){
        if(mine[(i+1)*n + j - 1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j - 1] == 'X'){
          bombs++;
        }
      }
      else{
        if(mine[(i-1)*n + j - 1] == 'X'){
          bombs++;
        }
        if(mine[(i-1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i-1)*n + j + 1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j - 1] == 'X'){
          bombs++;
        }
        if(mine[(i)*n + j + 1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j - 1] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j] == 'X'){
          bombs++;
        }
        if(mine[(i+1)*n + j + 1] == 'X'){
          bombs++;
        }
      }
      if(val == 'X'){
        val = 'X';
        mine[i*n + j] = val;
      }
      else if(bombs == 0){
        val = '0';
        mine[i*n + j] = val;
      }
      else if(bombs > 0){
        val = bombs + '0';
        mine[i*n + j] = val;
      }
      
      printf(" %c", val);
    }
    printf("\n");
  }
  

  free(mine);
  return 0;
}
