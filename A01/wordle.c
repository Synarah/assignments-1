#include <stdio.h>
#include <string.h>
#include <time.h>
#include "words.h" // header that defined chooseWord()

int main() {
  srand(time(0));
  const char* word = chooseWord();
  printf("cheat: %s\n", word);

  char user[6];
  printf("Welcome to Wordle");
  for(int i =0; i <= 6; i++){
    printf("Please enter a 5-letter word: ");
    scanf(" %s", user);
    if(word[0] == user[0] && word[1] == user[1] && word[2] == user[2] && word[3] == user[3] && word[4] == user[4]){
      for(int j = 0; j <= 4; j++){
        printf(" %c is in the word and in the correct spot \n", word[j]);
      }
      printf("You guessed it. The word is %s", word);
      i = 7;
    }
    else{
      for(int k = 0; k <= 4; k++){
        if(user[k] != word[0] && user[k] != word[1] && user[k] != word[2] && user[k] != word[3] && user[k] != word[4]){
          printf(" %c is not in the word \n", user[k]);
        }
        else if(user[k] == word[k]){
          printf(" %c is in the word and in the correct spot \n", user[k]);
        }
        else if(user[k] == word[0] || user[k] == word[1] || user[k] == word[2] || user[k] == word[3] || user[k] == word[4]){
          printf(" %c is in the word but not in the correct spot \n", user[k]);
        }
      }
    }

    }

  return 0;
}
