#include "producerCustomer.h"
#include "Message.h"
#include <unistd.h>

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    if(argc!=5)
    {
      std::cout<<"IntelligentPriorityProducer: MEMKEY SEMKEY QUENUMBER(1,2,..) SLEEPTIME(us)\n";
      return -1;
    }
    int queueNumber=atoi(argv[3]);
    int sleepTime=atoi(argv[4]);
    memoryKey=atoi(argv[1]);
    semaphoreKey=atoi(argv[2]);
    while(1)
    {
      if(semctl(semaphoreKey,EMPTY(queueNumber),GETVAL)<=5)
      {
        Message m('X'-'A','X'-'A','X'-'A',1);
        semDown(EMPTY(queueNumber));
        semDown(MUTEX(queueNumber));
        semDown(CONSOLERW);
	        std::cout<<"IntelligentPriorityProducer "<<(char)('A'+queueNumber)<<": "<<m.toString()<<std::endl;
          writeMessage(queueNumber,m);
        semUp(CONSOLERW);
        semUp(MUTEX(queueNumber));
        semUp(FULL(queueNumber));
      }
      usleep(sleepTime);
    }
    return 0;
}

