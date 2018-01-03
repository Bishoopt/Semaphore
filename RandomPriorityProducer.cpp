#include "producerCustomer.h"
#include <unistd.h>

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    if(argc!=5)
    {
      std::cout<<"RandomPriorityProducer: MEMKEY SEMKEY SLEEPTIME(us) RAND\n";
      return -1;
    }
    int sizeOfQueueA,sizeOfQueueB,sizeOfQueueC,min;
    int queueNumber;
    int sleepTime=atoi(argv[3]);
    memoryKey=atoi(argv[1]);
    semaphoreKey=atoi(argv[2]);
    srand(atoi(argv[4]));
    while(1)
    {
      Message m(rand()%3,rand()%3,rand()%3,1);
      queueNumber=rand()%3;
      while(semctl(semaphoreKey,EMPTY(queueNumber),GETVAL)==0)
      {
        ++queueNumber;
        queueNumber%=numberOfQueues;
      }
      semDown(EMPTY(queueNumber));
      semDown(MUTEX(queueNumber));
      semDown(CONSOLERW);
      	std::cout<<"RandomPriorityProducer "<<(char)('A'+queueNumber)<<": "<<m.toString()<<std::endl;
        writeMessage(queueNumber,m);
      semUp(CONSOLERW);
      semUp(MUTEX(queueNumber));
      semUp(FULL(queueNumber));
      usleep(sleepTime);
    }
    return 0;
}

