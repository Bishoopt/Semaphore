#include "producerCustomer.h"
#include "Message.h"
#include <unistd.h>

int memoryKey;
int semaphoreKey;
int main(int argc, char* argv[])
{
    if(argc!=6)
    {
      std::cout<<"Customer: MEMKEY SEMKEY QUENUMBER SLEEPTIME RAND\n";
      return -1;
    }
    int queueNumber=atoi(argv[3]);
    int sleepTime=atoi(argv[4]);
    memoryKey=atoi(argv[1]);
    semaphoreKey=atoi(argv[2]);
    srand(atoi(argv[5]));
    Message mess;
    int numberOfSkipped=0;
    int firstCharacter,randomChar;
    while(1)
    {
      semDown(FULL(queueNumber));
      semDown(MUTEX(queueNumber));
      mess=getMessage(queueNumber);
      
      semDown(CONSOLERW);
      std::cout<<"Customer "<<(char)(queueNumber+'A')<<": "<<mess.toString()<<std::endl;
      semUp(CONSOLERW);
      
      semUp(MUTEX(queueNumber));
      semUp(EMPTY(queueNumber));
      if(mess.isEmpty()==false)
      {
         if(mess.getPriority()==0)
         {
          firstCharacter=mess.popFirstCharacter();
          if(numberOfSkipped==0)
          {
            randomChar=rand()%4;
            mess.setLastCharacter(randomChar<3?randomChar:'X'-'A');
          }else --numberOfSkipped;
          if(firstCharacter!='X'-'A')
          {
            
            semDown(EMPTY(firstCharacter));
            semDown(MUTEX(firstCharacter));
            
            semDown(CONSOLERW);
            std::cout<<(char)(queueNumber+'A')<<" -> "<<(char)(firstCharacter+'A')<<" :"<<mess.toString()<<std::endl;
            semUp(CONSOLERW);
            
            writeMessage(firstCharacter,mess);
            semUp(MUTEX(firstCharacter));
            semUp(FULL(firstCharacter));
          }
        }else
         {
          numberOfSkipped+=10;
          firstCharacter=mess.popFirstCharacter();
          if(firstCharacter!='X'-'A')
          {
            
            semDown(EMPTY(firstCharacter));
            semDown(MUTEX(firstCharacter));
            
            semDown(CONSOLERW);
            std::cout<<(char)(queueNumber+'A')<<" -> "<<(char)(firstCharacter+'A')<<" :"<<mess.toString()<<std::endl;
            semUp(CONSOLERW);
            
            writeMessage(firstCharacter,mess);
            semUp(MUTEX(firstCharacter));
            semUp(FULL(firstCharacter));
         }
        }
       }
      
      usleep(sleepTime);
    }
    return 0;
}

