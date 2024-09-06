/***************************************************
 * mathgame.c
 * Author: Isbah Ameer
 * Implements a math game
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int numRounds, correctAns = 0;
  int num1;
  int num2;
  int ans;

  printf("Welcome to Math Game!\n");
  printf("How many rounds do you want to play? ");
  scanf("%d", &numRounds);
  for (int i = 0; i < numRounds; i++)
  {
    num1 = rand() % 9 + 1;
    num2 = rand() % 9 + 1;

    printf("%d + %d = ? ", num1, num2);
    scanf("%d", &ans);

    if (ans == num1 + num2)
    {
      printf("Correct! :) \n");
      correctAns++;
    }
    else
    {
      printf("Incorrect :( \n");
    }
  }

  printf("You answered %d/%d correctly. \n", correctAns, numRounds);
  return 0;
}
