#include "producerCustomer.h"
#include <unistd.h>

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    if(argc!=5)
    {
      std::cout<<"Print Queue: MEMKEY SEMKEY QUENUMBER(1,2,..) SLEEPTIME(us)\n";
      return -1;
    }
    int queueNumber=atoi(argv[3]);
    int sleepTime=atoi(argv[4]);
    memoryKey=atoi(argv[1]);
    semaphoreKey=atoi(argv[2]);
    while(1)
    {
      semDown(FULL(queueNumber));
      semDown(MUTEX(queueNumber));
        std::cout<<(char)(queueNumber+'A')<<": ";
        printQueue(queueNumber);
      semUp(MUTEX(queueNumber));
      semUp(FULL(queueNumber));
      if(semctl(semaphoreKey,EMPTY(queueNumber),GETVAL)==0)
      {
        std::cout<<"!!!QUEUE "<<(char)('A'+queueNumber)<<" IS FULL!!!"<<std::endl;
	std::cout<<"DELETE MEMORY AND SEMPAHORES"<<std::endl;
        DeleteSemaphores(semaphoreKey);
        DeleteMemory(memoryKey);
      }
      usleep(sleepTime);
    }
    return 0;
}

