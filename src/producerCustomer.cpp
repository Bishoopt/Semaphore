#include "producerCustomer.h"
extern int semaphoreKey;
extern int memoryKey;
int CreateSemaphores()
{
    int semgetRet;
    semgetRet = semget(IPC_PRIVATE, 3*numberOfQueues+1, 0600 |  SHM_W | SHM_R);
    if(semgetRet <= 0)
	{
		printf("Error semget\n");
		abort();
	}else semaphoreKey=semgetRet;
	for(unsigned int i=0;i<numberOfQueues;++i)
    {
        semctl(semgetRet, MUTEX(i), SETVAL, 1);
        semctl(semgetRet, FULL(i), SETVAL, 0);
        semctl(semgetRet, EMPTY(i), SETVAL, maxQueueLength);
    }
    semctl(semgetRet, CONSOLERW, SETVAL, 1);
    return semgetRet;
};
int CreateMemory()
{
    int shmgetRet;
    shmgetRet = shmget(IPC_PRIVATE,numberOfQueues*sizeof(PriorityQueue)+numberOfQueues*maxQueueLength*sizeof(Message), SHM_W | SHM_R);
	if(shmgetRet <= 0)
	{
		printf("Error shmget\n");
		abort();
	}else memoryKey=shmgetRet;
	void *mem=shmat(shmgetRet, NULL, 0);
	memset(mem,0,numberOfQueues*sizeof(PriorityQueue)+numberOfQueues*maxQueueLength*sizeof(Message));
	DetachMemory(mem);
	return shmgetRet;
};
PriorityQueue* getMemory()
{
    return (PriorityQueue *)shmat(memoryKey, NULL, 0);
}
void DetachMemory(void* p)
{
  shmdt(p);
}
void writeMessage(int queNumber,Message m)
{
    PriorityQueue* queues=nullptr;
    queues=getMemory();
    queues[queNumber].setMessage((Message *)(((void*)queues)+numberOfQueues*sizeof(PriorityQueue)+maxQueueLength*sizeof(Message)*queNumber));
    queues[queNumber].insertElement(m);
    DetachMemory((void*)queues);
}
Message getMessage(int queNumber)
{
    PriorityQueue* queues=nullptr;
    queues=getMemory();
    queues[queNumber].setMessage((Message *)(((void*)queues)+numberOfQueues*sizeof(PriorityQueue)+maxQueueLength*sizeof(Message)*queNumber));
    Message ret=queues[queNumber].getElement();
    DetachMemory((void*)queues);
    return ret;
}
void printQueue(int queNumber)
{
    PriorityQueue* queues=nullptr;
    queues=getMemory();
    queues[queNumber].setMessage((Message *)(((void*)queues)+numberOfQueues*sizeof(PriorityQueue)+maxQueueLength*sizeof(Message)*queNumber));
	int i=queues[queNumber].getStart();
  do
  {
	std::cout<<queues[queNumber].getMessage()[i].toString()<<" ";
	++i;
	i%=maxQueueLength;
  }while(i!=queues[queNumber].getEnd());
std::cout<<std::endl;
    DetachMemory((void*)queues);
}
void DeleteSemaphores(int semKey)
{
    semctl(semKey, 0, IPC_RMID);
}
void DeleteMemory(int memKey)
{
    shmctl(memKey, 0, IPC_RMID);
}
void semDown(int num)
{
    struct sembuf sem = {0,0,0};
		sem.sem_num = num;
		sem.sem_op = -1;
		semop(semaphoreKey, &sem, 1);
}
void semUp(int num)
{
    struct sembuf sem = {0,0,0};
		sem.sem_num = num;
		sem.sem_op = 1;
		semop(semaphoreKey, &sem, 1);
}
