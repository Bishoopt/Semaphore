#ifndef PRODUCERCUSTOMER_H
#define PRODUCERCUSTOMER_H
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include "PriorityQueue.h"

const unsigned int numberOfQueues = 3;

#define MUTEX(X) (3*X)
#define EMPTY(X) (3*X+1)
#define FULL(X) (3*X+2)
#define CONSOLERW (numberOfQueues*3+1)


int CreateSemaphores();
int CreateMemory();

void writeMessage(int queNumber,Message m);
Message getMessage(int queNumber);
PriorityQueue* getMemory();
void printQueue(int queNumber);
void DetachMemory(void* p);
void DeleteSemaphores(int);
void DeleteMemory(int);

void semDown(int num);
void semUp(int num);

#endif // PRODUCERCUSTOMER_H
