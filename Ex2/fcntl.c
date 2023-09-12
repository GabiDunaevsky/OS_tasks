#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
 char* file = "test.txt";
 int fd;
 struct flock lock;

//  printf ("opening %s\n", file);
 /* Open a file descriptor to the file. */
 fd = open (file, O_WRONLY);
 /* Initialize the flock structure. */
 memset (&lock, 0, sizeof(lock));
struct timespec start, end;
    if (clock_gettime(CLOCK_REALTIME, &start) == -1) {
        perror("clock_gettime");
        return -1;
    }
for (size_t i = 0; i < 1000000; i++)
{
    lock.l_type = F_WRLCK;
    /* Place a write lock on the file. */
    fcntl (fd, F_SETLKW, &lock);

    /* Release the lock. */
    lock.l_type = F_UNLCK;
    fcntl (fd, F_SETLKW, &lock);
}
if (clock_gettime(CLOCK_REALTIME, &end) == -1) {
        perror("clock_gettime");
        return -1;
    }
long eccum = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
double norm = (double) eccum/1000000;
    printf("Wake a task using lock (fcntl) average time: %f ns\n", norm);

 close (fd);
 return 0;
}