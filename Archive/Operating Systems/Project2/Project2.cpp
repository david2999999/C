// David Jiang
// Project 2

#include "pch.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include "pthread.h"
#include "semaphore.h"
#include "sched.h"
#include "time_functions.h"
#include "setpath_defs.h"

using namespace std;

void *producer(void *param); // producer function to run when thread starts
void *consumer(void *param); // consumer function to run when thread starts

sem_t sem_critical, sem_fill, sem_empty;
pthread_t read, write;

#define BUFFER_SIZE 10
string buffer[BUFFER_SIZE];
int read_index = 0, write_index = 0;

int main()
{
	ifstream readFile;
	ofstream writeFile;

	readFile.open(in_path);
	writeFile.open(out_path);

	// if the read/write file can not be opened, exit the program
	if (!readFile) {
		cerr << "Unable to open file read.txt";
		exit(1);
	}

	sem_init(&sem_fill, 0, 0);
	sem_init(&sem_empty, 0, BUFFER_SIZE);
	sem_init(&sem_critical, 0, 1);

	start_timing();

	// start both read and write thread here
	if (pthread_create(&read, NULL, producer, &readFile)) {
		printf("Error creating producer thread");
		return -1;
	}
	if (pthread_create(&write, NULL, consumer, &writeFile)) {
		printf("Error creating consumer thread");
		return -1;
	}

	pthread_join(read, NULL);
	pthread_join(write, NULL);

	stop_timing();

	cout << "CPU elapsed time: " << (get_nanodiff() / 1000000.0) << " ms" << endl;
	cout << "Wall Clock Time: " << (get_wall_clock_diff() * 1000) << " ms" << endl;

	sem_destroy(&sem_critical);
	sem_destroy(&sem_fill);
	sem_destroy(&sem_empty);
	
	return 0;
}

// function to read lines from the files and insert into the buffer
void *producer(void *param) {
	ifstream *readFile = (ifstream*)param;

	if (readFile) {
		string line;
		boolean peak = true;

		while (1) {
			sem_wait(&sem_empty);	 // decrease the number of empty slots inside the buffer 
			getline(*readFile, line);
			sem_wait(&sem_critical); // creates a lock for the critical section

			buffer[write_index] = line;	// add a line into the buffer
			write_index = (write_index + 1) % BUFFER_SIZE;	// circular array

			sem_post(&sem_critical);// unlock the critical section

			if (peak) peak = false;
			else sem_post(&sem_fill);	// increase the number of slots filled in the buffer
		
			if (readFile->eof()) {
				// finished the file
				sem_wait(&sem_empty); // adding a special character into the buffer, decrease the number of empty slots
				sem_wait(&sem_critical); // need a critical section to add the special character

				buffer[write_index] = ")(*&^%$#@!";	// add the special character

				sem_post(&sem_critical); // close the critical section of adding the special character
				sem_post(&sem_fill);	// increase the amount of filled slot by 1
				break;
			}
		}
	}
	else {
		cerr << "Unable to open execute the producer thread due to error of read file";
		exit(1);
	}

	pthread_exit(NULL);
	return NULL;
}

void *consumer(void *param) {
	ofstream *writeFile = (ofstream*)param;

	if (writeFile)
	{
		while (1) {
			sem_wait(&sem_fill);	// decrease one of the filled buffer
			sem_wait(&sem_critical);	// start the lock for the critical section

			if (buffer[(read_index + 1) % BUFFER_SIZE]  == ")(*&^%$#@!") { // found the special character
				(*writeFile) << buffer[read_index] << endl;
				break;
			} else 
				(*writeFile) << buffer[read_index] << endl;	// write a line into the write file from the buffer
			
			read_index = (read_index + 1) % BUFFER_SIZE; // increase the read index

			sem_post(&sem_critical); // unlock the critical section
			sem_post(&sem_empty);	// increase the number of empty spaces
		}
	}
	else {
		cerr << "Unable to open execute the consumer thread due to error of write file";
		exit(1);
	}

	pthread_exit(NULL);
	return NULL;
}

#include "setpath_fn.h"