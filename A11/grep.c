/*-------------------------------------------------
 * Author: Isbah Ameer
 * Date: 12/01/2024
 * Description: This program implements grep, 
 * searching for keywords in a given set of files.
 -------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

//struct holding thread data
typedef struct
{
  int id;
  int starting_file; //file indices
  int ending_file;
  char *keyword;
  char **files; //pointer to list of file names
  int matches;
} ThreadData;

pthread_mutex_t mutex;

//function that each thread executes
void *grep(void *arg)
{
  ThreadData *data = (ThreadData *)arg;
  char line[1000]; //buffer holding max 1000 line reads
  data->matches = 0; //match counter initialization

  for (int i = data->starting_file; i <= data->ending_file; ++i)
  {
    FILE *file = fopen(data->files[i], "r");
    if (!file)
    {
      perror("Error opening file");
      continue;
    }

    while (fgets(line, sizeof(line), file))
    {
      if (strstr(line, data->keyword))
      {
        pthread_mutex_lock(&mutex);
        printf("Thread %d) %s:%s", data->id, data->files[i], line);
        pthread_mutex_unlock(&mutex);
        data->matches++;
      }
    }
    fclose(file);
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  struct timeval start, end;
  gettimeofday(&start, NULL);

  if (argc < 4)
  {
    fprintf(stderr, "usage: ./grep <NumThreads> <Keyword> <Files>\n");
    return 1;
  }

  int num_threads = atoi(argv[1]);
  char *keyword = argv[2];
  int num_files = argc - 3;

  if (num_threads < 1 || num_threads > 10)
  {
    fprintf(stderr, "Number of threads must be between 1 and 10\n");
    return 1;
  }

  pthread_t threads[10];
  ThreadData thread_data[10];
  pthread_mutex_init(&mutex, NULL);

  int files_per_thread = num_files / num_threads;
  int extra_files = num_files % num_threads;

  int current_file = 0;

  for (int i = 0; i < num_threads; ++i)
  {
    thread_data[i].id = i;
    thread_data[i].keyword = keyword;
    thread_data[i].files = &argv[3];
    thread_data[i].starting_file = current_file;
    thread_data[i].ending_file = current_file + files_per_thread - 1;

    if (extra_files > 0)
    {
      thread_data[i].ending_file++;
      extra_files--;
    }

    current_file = thread_data[i].ending_file + 1;

    pthread_create(&threads[i], NULL, grep, &thread_data[i]);
  }

  for (int i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }

  gettimeofday(&end, NULL);

  double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
  printf("\nElapsed time: %.6f seconds\n", elapsed_time);

  for (int i = 0; i < num_threads; ++i)
  {
    printf("Thread %d found %d lines containing keyword: %s\n", thread_data[i].id, thread_data[i].matches, keyword);
  }

  pthread_mutex_destroy(&mutex);
  return 0;
}
