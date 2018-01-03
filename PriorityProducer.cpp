#include "producerCustomer.h"
#include <unistd.h>

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    if(argc!=6)
    {
      std::cout<<"PriorityProducer: MEMKEY SEMKEY QUENUMBER(1,2,..) SLEEPTIME(us) RAND\n";
      return -1;
    }
    int queueNumber=atoi(argv[3]);
    int sleepTime=atoi(argv[4]);
    memoryKey=atoi(argv[1]);
    semaphoreKey=atoi(argv[2]);
    srand(atoi(argv[5]));
    while(1)
    {
      Message m(rand()%3,rand()%3,rand()%3,1);
      semDown(EMPTY(queueNumber));
      semDown(MUTEX(queueNumber));
      semDown(CONSOLERW);
	      std::cout<<"PriorityProducer "<<(char)('A'+queueNumber)<<": "<<m.toString()<<std::endl;
        writeMessage(queueNumber,m);
      semUp(CONSOLERW);
      semUp(MUTEX(queueNumber));
      semUp(FULL(queueNumber));
      usleep(sleepTime);
    }
    return 0;
}

