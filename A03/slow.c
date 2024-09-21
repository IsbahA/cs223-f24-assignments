/*----------------------------------------------
 * Author: Isbah Ameer
 * Date: 09/20/2024
 * Description: Turns phrase into ent-speech.
 ---------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
  char buff[32];
  int pause;
  int i, j, k = 0;

  printf("Pause length: ");
  scanf("%d", &pause);
  printf("Text: ");
  scanf("%s", buff);

  int inputLength = strlen(buff);
  // calculate size required to store output
  int outputLength = inputLength + (pause * inputLength) + 1; //+1 for terminating char
  char *outputStore = malloc(outputLength);

  for (i = 0; i < inputLength; i++)
  {
    outputStore[k++] = buff[i];
    for (j = 0; j < pause; j++)
    {
      outputStore[k++] = '.';
    }
  }
  outputStore[k] = '\0';
  printf("%s\n", outputStore);
  free(outputStore);

  return 0;
}
