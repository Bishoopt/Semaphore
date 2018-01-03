#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
    //ctor
}

PriorityQueue::~PriorityQueue()
{
    //dtor
}
Message PriorityQueue::getElement()
{
    Message m = message[Start];
    Start++;
    Start %= maxQueueLength;
    return m;
}

void PriorityQueue::insertElement(Message element)
{

        int endCopy=Start;
        while(element.getPriority()<message[endCopy].getPriority())
            endCopy=(endCopy+1)%maxQueueLength;
        //i to index pierwszej normalnej wiadomosci
        ///teraz przesun wiadomosci o 1
        for(int i=End;i!=endCopy;)
        {
            if((int)(i-1)<0)
            {
                message[i]=message[maxQueueLength-1];
                i=maxQueueLength-1;
            }
            else
                message[i]=message[--i];
        }
        message[endCopy]=element;
        ++End;
        End %= maxQueueLength;
    
}
std::string PriorityQueue::toString()
{
  std::string s="";
  int i=Start;
  while(i!=End);
  {
    s+=message[i].toString()+" ";
    ++i;
    i%=maxQueueLength;
  }
  return s;
}
void PriorityQueue::setMessage(Message* m)
{
	message=m;
}
Message* PriorityQueue::getMessage()
{
	return message;
}
unsigned int PriorityQueue::getStart()
{
	return Start;
}
unsigned int PriorityQueue::getEnd()
{
	return End;
}
