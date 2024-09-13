/***************************************************
 * exclaim.c
 * Author: Isbah Ameer
 * Date: September 12th, 2024
 * Turning words into exclaimations
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  char userInput[32];
  char symbol[4] = {'@', '#', '!', '*'};
  int n;

  printf("Enter a word: ");
  scanf("%s", userInput);

  printf("OMG! "); //print statement starts

  for (int i = 0; i < strlen(userInput); i++){
    if (userInput[i] >= 'a' && userInput[i] <= 'z'){
      n = rand() % 4;
      // replacing lowercase letter with symbol
      userInput[i] = symbol[n];
    }
    printf("%c", userInput[i]);

  }
  printf("\n");

  return 0;
}
