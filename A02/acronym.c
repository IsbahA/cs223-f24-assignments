/***************************************************
 * acronym.c
 * Author: Isbah Ameer
 * Date: September 13th, 2024
 * Creating acronyms from a sentence
 */
#include <stdio.h>
#include <string.h>

int main()
{
  char userInput[1024];
  char acronym[1024];
  int index = 0;

  printf("Enter a phrase: ");
  scanf("%[^\n]%*c", userInput);

  // if the first letter of the input is capital, it is added to the acronym
  if (userInput[0] >= 'A' && userInput[0] <= 'Z')
  {
    acronym[index++] = userInput[0];
  }

  for (int i = 1; i < strlen(userInput); i++)
  {
    if (userInput[i] >= 'A' && userInput[i] <= 'Z' && userInput[i - 1] == ' ')
    {
      acronym[index++] = userInput[i];
    }
  }
  acronym[index] = '\0';

  printf("Your acronym is %s\n", acronym);
  return 0;
}