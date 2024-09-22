/*----------------------------------------------
 * Author: Isbah Ameer
 * Date: 09/20/2024
 * Description: This program reads in song data from 
 songlist.csv, and uses dynamic memory allocation to store 
 the song list.
 * References: the code segment reading in a 
 file is inspired fromDive into Systems — Section 2.8:
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[128];
    char artist[128];
    int duration;  
    float danceability;
    float energy;
    float tempo;
    float valence;
} Song;

void format_duration(int duration, int *minutes, int *seconds) {
    *minutes = duration / 60;
    *seconds = duration % 60;
}
void printSongList(Song *songs, int num_songs) {
    printf("\n=======================\n");
    for (int i = 0; i < num_songs; i++) {
        int minutes, seconds;
        format_duration(songs[i].duration, &minutes, &seconds);
        printf("%d) %-28s artist: %-20s duration %d:%02d D: %.3f E: %.3f T: %.3f V: %.3f\n", 
            i, songs[i].title, songs[i].artist, minutes, seconds, 
            songs[i].danceability, songs[i].energy, songs[i].tempo, songs[i].valence);
    }
    printf("=======================\n\n");
}

int main() {
    FILE *infile = fopen("songlist.csv", "r");
    if (infile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    char buffer[256];
    fgets(buffer, sizeof(buffer), infile);
    int num_songs = atoi(strtok(buffer, ","));
    
    Song *songs = (Song *)malloc(num_songs * sizeof(Song));
    if (songs == NULL) {
        printf("Memory allocation failed.\n");
        fclose(infile);
        return 1;
    }

    for (int i = 0; i < num_songs; i++) {
        if (fgets(buffer, sizeof(buffer), infile) == NULL) {
            printf("Error reading file.\n");
            free(songs);
            fclose(infile);
            return 1;
        }

        char *token = strtok(buffer, ",");
        strncpy(songs[i].title, token, 127);
        songs[i].title[127] = '\0';

        token = strtok(NULL, ",");
        strncpy(songs[i].artist, token, 127);
        songs[i].artist[127] = '\0';
        
        token = strtok(NULL, ",");
        songs[i].duration = atoi(token);
        
        token = strtok(NULL, ",");
        songs[i].danceability = atof(token);

        token = strtok(NULL, ",");
        songs[i].energy = atof(token);

        token = strtok(NULL, ",");
        songs[i].tempo = atof(token);

        token = strtok(NULL, ",");
        songs[i].valence = atof(token);
    }

    printSongList(songs, num_songs);
    free(songs);
    fclose(infile);
    return 0;
}
