#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>

int main(){
	// Initialization of semaphores and shared table
        int shm_fd = shm_open("table", O_RDWR, 0666);
        int* table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
        sem_t* fill = sem_open("fill", O_CREAT, 0666, 0);
        sem_t* avail = sem_open("available", O_CREAT, 0666, 2);
        sem_t* mutex = sem_open("mutex", O_CREAT, 0666, 1);
	// Initialization of loop counter
        int loop = 20;
	// Prints to user how many items the consumer is ready to recieve
        printf("\nConsumer ready to receive %d items.\n", loop);

        for(int i = 1; i < loop; ++i) {
		sem_wait(fill);
		// Calculates random number
                int randNum = rand() % 2 + 1;
                sleep(randNum);
		// Semaphore wait for producer, subtracts from table, and posts
		sem_wait(mutex);
		--(*table);
		sem_post(mutex);
		// Prompts user about item being consumed and how much remains
		printf("Item consumed, %d remaining.\n", *table);
		sem_post(avail);
        }
	// Closes semaphores
	sem_close(fill);
        sem_close(avail);
        sem_close(mutex);
	// Unlinks semaphores
        sem_unlink("fill");
        sem_unlink("available");
        sem_unlink("mutex");
	// Closes and unlinks table
        munmap(table, sizeof(int));
        close(*table);
        shm_unlink("table");
	// Prints to console that the consumer is cleaned
        printf("Consumer cleaned up!\n");
        return 0;
}


