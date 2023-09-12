#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>


int main (int argc, char** argv)
{
    pthread_mutex_t mutex;

    // Create a mutex with the default parameters
    if (0 != (errno = pthread_mutex_init(&mutex, NULL)))
    {
        perror("pthread_mutex_init() failed");
        return EXIT_FAILURE;
    }
    struct timespec start, end;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock_gettime");
        return -1;
    }

    for ( int i = 0; i < 1000000; i++)
    {
        
        if (0 != (errno = pthread_mutex_lock(&mutex)))
        {
            perror("pthread_mutex_lock failed");
            exit(EXIT_FAILURE);
        }
        if (0 != (errno = pthread_mutex_unlock(&mutex)))
        {
            perror("pthread_mutex_unlock failed");
            exit(EXIT_FAILURE);
        }
    }
    if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        perror("clock_gettime");
        return -1;
    }
    long eccum = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    double norm = (double) eccum/1000000;
    printf("Wake a task using lock (mutex) average time: %f ns\n", norm);
       return EXIT_SUCCESS;
}