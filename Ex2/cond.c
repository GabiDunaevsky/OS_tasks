#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

volatile int value = 0;
pthread_mutex_t mymutex;
pthread_t thread_one;
pthread_t thread_two;
pthread_cond_t cond;

void* main_one(void* ignored)
{
    while (value < 10)
    {
        pthread_mutex_lock(&mymutex);
        pthread_cond_wait(&cond, &mymutex);
        // fprintf(stderr, "T1: value=%d\n", value);
        pthread_mutex_unlock(&mymutex);
    }
    return (void*)0;
}

void* main_two(void* ignored)
{
    int i;

    for (i = 0; i < 10; i++)
    {
        pthread_mutex_lock(&mymutex);
        value++;
        // fprintf(stderr, "T2: value=%d\n", value);
        pthread_cond_broadcast(&cond);
        // fprintf(stderr, "Broadcasted but T1 cannot continue for 1 second\n");
        sleep(1);
        pthread_mutex_unlock(&mymutex);
        pthread_self();
    }

    return (void*)0;
}

void start_thread(void* (*a_entry_point)(void*),
                  pthread_t* a_handle)
{
    pthread_attr_t thread_attributes;

    pthread_attr_init(&thread_attributes);
    pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_JOINABLE);
    pthread_create(a_handle, &thread_attributes, a_entry_point, 0);
}

int main()
{
    pthread_mutexattr_t attr;
    pthread_t thread_one_handle;
    pthread_t thread_two_handle;

    /* Init mutex. */
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&mymutex, &attr);

    /* Init condition. */
    pthread_cond_init(&cond, 0);
    struct timespec start, end;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock_gettime");
        return -1;
    }
    /* Start threads. */
    start_thread(main_one, &thread_one_handle);
    start_thread(main_two, &thread_two_handle);

    /* Wait for threads. */
    pthread_join(thread_one_handle, 0);
    pthread_join(thread_two_handle, 0);
    long eccum = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
    double norm = (double) eccum/1000000;
    printf("Wake a task using signal (cond) average time: %f ns\n", norm);

    /* Clean up. */
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mymutex);

    return 0;
}