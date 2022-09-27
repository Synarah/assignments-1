#include <stdio.h>

int main() {
  int matrix[4][4];
  int val;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j <4; j++){
      scanf(" %d", &val);
      matrix[i][j] = val;
    }
  }

  int max = 0;
  int cur = 0;
  int extra = 0;
  for(int k = 0; k < 4; k++){
    for(int l = 0; l < 4; l++){
      if(matrix[l][k] == 0){
        max = max + extra;
      }
      else if(l <= 2 && matrix[l+1][k] == 0){
        if(l <= 1 && matrix[l+2][k] == 0){
          if(l == 0 && matrix[l+3][k] == 0){
            max = max + extra;
          }
          else{
            if(l == 0 && matrix[l+3][k] == matrix[l][k]){
              cur = matrix[l+3][k] + matrix[l][k];
              if(cur > max){
                max = cur;
              }
            }
          }
        }
          else{
            if(l <= 1 && matrix[l+2][k] == matrix[l][k]){
              cur = matrix[l+2][k] + matrix[l][k];
              if(cur > max){
                max = cur;
              }
            }
          }
        }
        else{
          if(l <= 2 && matrix[l+1][k] == matrix[l][k]){
              cur = matrix[l+1][k] + matrix[l][k];
              if(cur > max){
                max = cur;
              }
            }
        }
      }
    } 

    for(int y = 0; y < 4; y++){
    for(int x = 0; x < 4; x++){
      if(matrix[y][x] == 0){
        max = max + extra;
      }
      else if(x <= 2 && matrix[y][x+1] == 0){
        if(x <= 1 && matrix[y][x+2] == 0){
          if(x == 0 && matrix[y][x+3] == 0){
            max = max + extra;
          }
          else{
            if(x == 0 && matrix[y][x+3] == matrix[y][x]){
              cur = matrix[y][x+3] + matrix[y][x];
              if(cur > max){
                max = cur;
              }
            }
          }
        }
          else{
            if(x <= 1 && matrix[y][x+2] == matrix[y][x]){
              cur = matrix[y][x+2] + matrix[y][x];
              if(cur > max){
                max = cur;
              }
            }
          }
        }
        else{
          if(x <= 2 && matrix[y][x+1] == matrix[y][x]){
              cur = matrix[y][x+1] + matrix[y][x];
              if(cur > max){
                max = cur;
              }
            }
        }
      }
    }
    if(max == 0){
      for(int a = 0; a < 4; a++){
        for(int b = 0; b <4; b++){
          cur = matrix[a][b];
          if(cur > max){
            max = cur;
          }
    }
  }
    }
    printf("The largest value is %d", max); 
  return 0;
}
