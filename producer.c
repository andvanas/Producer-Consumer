#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
	// Initialization of semaphores
	int tbl = shm_open("table", O_CREAT | O_RDWR, 0666);
	ftruncate(tbl, sizeof(int));
	int* table = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, tbl, 0);
	sem_t* fill = sem_open("fill", O_CREAT, 0666, 0);
	sem_t* avail = sem_open("available", O_CREAT, 0666, 2);
	sem_t* mutex = sem_open("mutex", O_CREAT, 0666, 1);
	// Initialization of loop amount and prompts the user with amount of items to produce
	int loop = 20;
	int i = 0;
	printf("\nProducer ready to create %d items.\n", loop);

	for(i=0; i < loop; ++i) {
		printf("hi");
		// Semaphore waits for an available spot in the table
		sem_wait(avail);
		// Creates a random number
		int randNum = rand() % 2 + 1;
		sleep(randNum);
		*table=randNum;
		// Semaphore waits for mutex, adds to the table, and posts to the table
		sem_wait(mutex);
		++(*table);
		sem_post(mutex);
		// Prompts user after item is produced and shows the amount of items in table
		printf("Item produced, there are now %d item(s) in the table.\n", *table);
		sem_post(fill);
	}
	// Closes semaphores
	sem_close(fill);
	sem_close(avail);
	sem_close(mutex);
	// Unlinks semaphores
	sem_unlink("fill");
	sem_unlink("available");
	sem_unlink("mutex");
	// Closes table
	munmap(table, sizeof(int));
	close(tbl);
	shm_unlink("table");
	// Prompts user that the producer is cleaned up
	printf("Producer cleaned up!\n");
	return 0;
}
