#include <stdio.h>
#include <string.h>

struct restruant{
    int num;
    char name[64];
    int open;
    int close;
    double rate;

};

int main() {

  struct restruant restruant0, restruant1, restruant2;
  restruant0.num = 0;
  strcpy(restruant0.name, "Sushi Atsumi");
  restruant0.open = 11;
  restruant0.close = 23;
  restruant0.rate = 3.5;
  restruant1.num = 1;
  strcpy(restruant1.name, "The Thirsty Horse");
  restruant1.open = 17;
  restruant1.close = 2;
  restruant1.rate = 4.5;
  restruant2.num = 2;
  strcpy(restruant2.name, "Magic Bean Coffee");
  restruant2.open = 6;
  restruant2.close = 15;
  restruant2.rate = 4.1;

  int time, choice, dif;
  printf("What time is it?");
  scanf(" %d", &time);
  printf(" %d) %s        open: %d:00  close: %d:00  stars: %.1f \n", restruant0.num, restruant0.name, restruant0.open, restruant0.close, restruant0.rate);
  printf(" %d) %s   open: %d:00  close: 0%d:00  stars: %.1f \n", restruant1.num, restruant1.name, restruant1.open, restruant1.close, restruant1.rate);
  printf(" %d) %s   open: 0%d:00  close: %d:00  stars: %.1f \n", restruant2.num, restruant2.name, restruant2.open, restruant2.close, restruant2.rate);

  printf("What restaurant do you want to visit? [0,1,2]");
  scanf(" %d", &choice);

  if(choice == 0){
    if(time >= restruant0.open && time <= restruant0.close){
      dif = restruant0.close - time;
      printf("Excellent choice.  %s will be open for  %d more hours", restruant0.name, dif);
    }
    else if(time > restruant0.close){
      printf(" %s closed at %d o'clock", restruant0.name, restruant0.close);
    }
    else{
      printf(" %s isn't open until  %d o'clock!!", restruant0.name, restruant0.open);
    }
  }
  else if(choice == 1){
    if(time >= restruant1.open && time <= restruant1.close){
      dif = restruant1.close - time;
      printf("Excellent choice.  %s will be open for  %d more hours", restruant1.name, dif);
    }
    else if(time > restruant1.close){
      printf(" %s closed at %d o'clock", restruant1.name, restruant1.close);
    }
    else{
      printf(" %s isn't open until  %d o'clock!!", restruant1.name, restruant1.open);
    }
  }
  else if(choice == 2){
    if(time >= restruant2.open && time <= restruant2.close){
      dif = restruant2.close - time;
      printf("Excellent choice.  %s will be open for  %d more hours", restruant2.name, dif);
    }
    else if(time > restruant2.close){
      printf(" %s closed at %d o'clock", restruant2.name, restruant2.close);
    }
    else{
      printf(" %s isn't open until  %d o'clock", restruant2.name, restruant2.open);
    }
  }
  else{
    printf("Not a resturant option");
  }

  return 0;
}
