/***************************************************
 * songs.c
 * Author: Isbah Ameer
 * Date: September 13th, 2024
 * Users can view a list of songs and edit the attributes of the list
 */
#include <stdio.h>
#include <string.h>

struct songList
{
  char title[32];
  char artist[32];
  int durationMin;
  int durationSec;
  float danceability;
};

void printSongList(struct songList s[])
{
  printf("\n=======================\n");
  for (int i = 0; i < 3; i++)
  {
    // structure of song list
    printf("%d) %-20s artist: %-20s duration %d:%02d danceability: %.2f\n", i, s[i].title, s[i].artist, s[i].durationMin, s[i].durationSec, s[i].danceability);
  }
  printf("=======================\n\n");
}

int main()
{
  int songID;
  char attribute[32];

  struct songList s[3];
  strcpy(s[0].title, "Shout");
  strcpy(s[0].artist, "Tears for Fears");
  s[0].durationMin = 4;
  s[0].durationSec = 11;
  s[0].danceability = 0.5;

  strcpy(s[1].title, "As It Was");
  strcpy(s[1].artist, "Harry Styles");
  s[1].durationMin = 2;
  s[1].durationSec = 47;
  s[1].danceability = 0.7;

  strcpy(s[2].title, "Wish you were here");
  strcpy(s[2].artist, "Pink Floyd");
  s[2].durationMin = 5;
  s[2].durationSec = 34;
  s[2].danceability = 0.3;

  printSongList(s);

  printf("Enter a song ID to edit [0,1,2]: ");
  scanf("%d%*c", &songID);

  if (songID < 0 || songID > 2)
  {
    printf("Song ID is invalid!\n");
    return 1;
  }

  printf("Which attribute do you wish to edit? [artist, title, duration, danceability]: ");
  scanf(" %[^\n]%*c", attribute);

  if (strcmp(attribute, "artist") == 0)
  {
    printf("Enter a new artist: ");
    scanf(" %[^\n]%*c", s[songID].artist);
  }
  else if (strcmp(attribute, "title") == 0)
  {
    printf("Enter a new title: ");
    scanf(" %[^\n]%*c", s[songID].title);
  }
  else if (strcmp(attribute, "duration") == 0)
  {
    printf("Enter a new duration(minutes): ");
    scanf("%d%*c", &s[songID].durationMin);
    printf("Enter  a new duration (seconds): ");
    scanf("%d%*c", &s[songID].durationSec);
  }
  else if (strcmp(attribute, "danceability") == 0)
  {
    printf("Enter new danceability: ");
    scanf("%f%*c", &s[songID].danceability);
  }
  else
  {
    printf("Invalid Attribution!\n");
    return 1;
  }
  printSongList(s);
  return 0;
}
