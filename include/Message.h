#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>

#define EMPTYVALUE (127)

class Message
{
    public:
        Message(char v1=0,char v2=0,char v3=0,int8_t prio=0);
        virtual ~Message();
        char popFirstCharacter();
        bool isEmpty();
        void setPriority(int8_t);
        int8_t getPriority();
        void setLastCharacter(char);

        std::string toString();
    protected:

    private:
    char value[3];
    int8_t priority;

};

#endif // MESSAGE_H
