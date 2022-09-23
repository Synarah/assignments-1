#include <stdio.h>
#include <stdlib.h>

struct restruant{
    int num;
    char name[64];
    int open;
    int close;
    double rate;

};

int main() {

  struct restruant *restaurants;
  restaurants = malloc(sizeof(restaurants)*20);
  printf("Enter a number of returants: ");
  int n;
  scanf(" %d", &n);
  for(int i = 0; i < n; i++){
    restaurants[i].num = i;
    printf("Enter a name: ");
    scanf(" %[^\n]%*c", restaurants[i].name);
    printf("Open time: ");
    scanf(" %d%*c", &restaurants[i].open);
    printf("Close time: ");
    scanf(" %d%*c", &restaurants[i].close);
    printf("Stars: ");
    scanf(" %lf%*c", &restaurants[i].rate);
  }
  for(int j = 0; j < n; j++){
    if(restaurants[j].open < 10 && restaurants[j].close < 10){
      printf(" %d) %s        open: 0%d:00  close: 0%d:00  stars: %.1f \n", restaurants[j].num, restaurants[j].name, restaurants[j].open, restaurants[j].close, restaurants[j].rate);
    }
    else if(restaurants[j].open < 10){
    printf(" %d) %s        open: 0%d:00  close: %d:00  stars: %.1f \n", restaurants[j].num, restaurants[j].name, restaurants[j].open, restaurants[j].close, restaurants[j].rate);
    }
    else if(restaurants[j].close < 10){
    printf(" %d) %s        open: %d:00  close: 0%d:00  stars: %.1f \n", restaurants[j].num, restaurants[j].name, restaurants[j].open, restaurants[j].close, restaurants[j].rate);
    }
    else{
      printf(" %d) %s        open: %d:00  close: %d:00  stars: %.1f \n", restaurants[j].num, restaurants[j].name, restaurants[j].open, restaurants[j].close, restaurants[j].rate);
    }  
  }
  free(restaurants);
  return 0;
}