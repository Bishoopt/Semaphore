#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include "Message.h"

const unsigned int maxQueueLength = 20;

class PriorityQueue
{
    public:
        PriorityQueue();
        virtual ~PriorityQueue();
        Message getElement();
        void insertElement(Message);
        std::string toString();
	Message* getMessage();
	void setMessage(Message*);
	unsigned int getStart();
	unsigned int getEnd();
    protected:
    ;
    private:
	unsigned int Start, End;
    	Message* message;
};

#endif // PRIORITYQUEUE_H
